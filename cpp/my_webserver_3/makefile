server:
	g++ help.cpp client.cpp InetAddress.cpp Socket.cpp -o client && \
	g++ help.cpp server.cpp Epoll.cpp InetAddress.cpp Socket.cpp Channel.cpp -o server
clean:
	rm server && rm client