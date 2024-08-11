#include <zmq.hpp>
#include <string>
#include <iostream>
#include <Windows.h>

/*
1. server 가 먼저 SEND 불가능 : 크래시 발생
*/
bool TestCase1(zmq::socket_t& socket, int loopSize)
{
	std::cout << "Take " << loopSize << std::endl;
	zmq::message_t reply(5);
	memcpy((void*)reply.data(), "World", 5);
	auto result = socket.send(reply, zmq::send_flags::none);
	if (result.has_value())
	{
		std::cout << "Send failed " << loopSize << std::endl;
		return false;
	}

	return true;
}

bool TestCase2(zmq::socket_t& socket)
{
	zmq::message_t req(0);
	socket.recv(req);
	std::cout << "Recived" << std::endl;

	return true;
}

bool DefaultCase(zmq::socket_t& socket)
{
	zmq::message_t req(0);
	socket.recv(req);
	std::cout << "Recived Hello" << std::endl;


	zmq::message_t reply(5);
	memcpy((void*)reply.data(), "World", 5);
	socket.send(reply, zmq::send_flags::none);

	return true;
}

int main()
{
	zmq::context_t context(1);
	zmq::socket_t socket(context, ZMQ_REP);
	socket.bind("tcp://*:5555");

	int i = 0;
	while (true)
	{
		++i;

		DefaultCase(socket);
		//TestCase1(socket, i);
		//TestCase2(socket);

		Sleep(1);
	}

	socket.close();

	return 0;
}