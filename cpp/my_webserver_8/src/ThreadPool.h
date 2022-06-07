#pragma once
#include <functional>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>

class ThreadPoll{
    private:
        std::vector<std::thread> threads;
        std::queue<std::function<void()>> tasks;
        std::mutex tasks_mtx;
        std::condition_variable cv;
        bool stop;
    public:
        ThreadPoll(int size=std::thread::hardware_concurrency());
        ~ThreadPoll();
        // void add(std::function<void()>);
        template <class F, class... Args> auto add(F&& f, Args&&... args) -> std::future<typename std::result_of<F(args...)>::type>;
};

template<class F, class... Args>
auto ThreadPoll::add(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type> {
    using return_type = typename std::result_of<F(Args...)>::type;

    auto task = std::make_shared<std::packaged_task<return_type()>>(
        
    );
}