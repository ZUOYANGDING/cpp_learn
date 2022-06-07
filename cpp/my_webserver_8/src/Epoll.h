#include <sys/epoll.h>
class Channel;

class Epoll {
    private:
        int fd;
        struct epoll_event* events;
    public:
        Epoll();
        ~Epoll();

        void updateChannel(Channel*);
        std::vector<Channel*> poll(int timeout=-1);
};