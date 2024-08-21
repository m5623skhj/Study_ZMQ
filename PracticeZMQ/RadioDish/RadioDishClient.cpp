#include <zmq.h>
#include <iostream>
#include <Windows.h>

int main()
{
	void* context = zmq_ctx_new();
	void* dishSocket = zmq_socket(context, 15); // ZMQ_DISH = 15

	if (zmq_bind(dishSocket, "udp://*:9999") != 0)
	{
		std::cout << "zmq_bind() failed " << zmq_strerror(errno) << std::endl;
		return 0;
	}

	zmq_join(dishSocket, "GroupName");

	while (1)
	{
		char buffer[255];

		int received = zmq_recv(dishSocket, buffer, sizeof(buffer) - 1, 0);
		if (received > 0)
		{
			buffer[received] = '\0';
			std::cout << buffer << std::endl;
		}
	}

	zmq_close(dishSocket);
	zmq_ctx_term(context);

	return 0;
}