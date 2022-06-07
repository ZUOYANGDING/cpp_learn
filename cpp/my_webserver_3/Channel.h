#pragma once
#include <sys/epoll.h>

class Epoll;

/**
 * @brief class wrap a fd, make diff type of connections have diff operation logic  
 * 
 */
class Channel {
    private:
        Epoll *ep;
        int fd;
        // events that need to be monitor
        uint32_t events;
        // events on fd when epoll return 
        uint32_t revents;
        // if fd in(use EPOLL_CTL_ADD to add) Epoll or not(use EPOLL_CLT_MOD to update)
        bool inEpoll;
    public:
        Channel(Epoll* _ep, int _fd);
        ~Channel();

        int getFd() const;
        uint32_t getEvents() const;
        uint32_t getRevents() const;
        bool getInEpoll() const;
        void setInEpoll();
        void setRevents(uint32_t);
        void enableReading();
};