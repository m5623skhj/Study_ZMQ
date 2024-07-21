#include <zmq.hpp>
#include <string>
#include <iostream>
#include <Windows.h>

int main()
{
	zmq::context_t context(1);
	zmq::socket_t socket(context, ZMQ_REP);
	socket.bind("tcp://*:5555");

	while (true)
	{
		zmq::message_t req(0);
		socket.recv(req);
		std::cout << "Recived Hello" << std::endl;

		Sleep(1);

		zmq::message_t reply(5);
		memcpy((void*)reply.data(), "World", 5);
		socket.send(reply, zmq::send_flags::none);
	}

	socket.close();

	return 0;
}