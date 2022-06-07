#include "src/EventLoop.h"
#include "src/Server.h"

int main() {
    EventLoop* eventloop = new EventLoop();
    Server* server = new Server(eventloop);
    eventloop->loop();
    delete eventloop;
    delete server;
    return 0;
}

