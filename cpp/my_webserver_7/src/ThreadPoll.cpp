#include "ThreadPoll.h"
#include <iostream>

ThreadPoll::ThreadPoll(int size) : stop(false) {
    for (int i=0; i<size; ++i) {
        // create size number of threads
        // use emplace_back instead of push_back, to avoid copy constructor to waste resource
        threads.emplace_back(std::thread([this](){
            while(true) {
                std::function<void()> task;
                {   
                    // get the mutex locker and lock it 
                    std::unique_lock<std::mutex> lock(tasks_mtx);
                    // wait for unlock
                    cv.wait(lock, [this]() {
                        return stop || !tasks.empty();
                    });
                    if (stop && tasks.empty()) {
                        return;
                    }
                    // get the task from task queue
                    task = tasks.front();
                    tasks.pop();
                }
                // run task
                task();
            }   
        }));
    }
}

ThreadPoll::~ThreadPoll() {
    std::cout<<"in threadPoll distructor"<<std::endl;
    {
        // lock
        std::unique_lock<std::mutex> lock(tasks_mtx);
        stop = true;
    }
    cv.notify_all();
    for(std::thread &th : threads) {
        if (th.joinable()) {
            // std::cout<< "wait for join: " << &th << std::endl;
            th.join();
        }
    }
}

void ThreadPoll::add(std::function<void()> func) {
    {
        // lock
        std::unique_lock<std::mutex> lock(tasks_mtx);
        if (stop) {
            throw std::runtime_error("ThreadPoll already stop, cannot add task any more");
        }
        tasks.emplace(func);
    }
    // release locker
    cv.notify_one();
}