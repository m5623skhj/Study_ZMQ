#include <zmq.h>
#include <iostream>
#include <Windows.h>

int main()
{
	void* context = zmq_ctx_new();
	void* radioSocket = zmq_socket(context, 14); // ZMQ_RADIO = 14

	if (zmq_bind(radioSocket, "udp://*:9999") != 0)
	{
		std::cout << "zmq_bind() failed " << zmq_strerror(errno) << std::endl;
		return 0;
	}

	while (1)
	{
		std::string message = "Hello";
		zmq_send(radioSocket, message.c_str(), message.size(), 0);
		Sleep(1);
	}

	zmq_close(radioSocket);
	zmq_ctx_term(context);

	return 0;
}