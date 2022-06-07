server:
	g++ -g src/util.cpp \
		client.cpp \
		src/InetAddress.cpp \
		src/Buffer.cpp	\
		src/Socket.cpp  -o client && \
	g++ -g src/util.cpp \
		src/ThreadPoll.cpp	\
		server.cpp \
		src/Epoll.cpp \
		src/InetAddress.cpp \
		src/Socket.cpp \
		src/Channel.cpp \
		src/EventLoop.cpp \
		src/Acceptor.cpp \
		src/Connection.cpp \
		src/Buffer.cpp \
		src/Server.cpp -lpthread -o server
clean:
	rm server && rm client