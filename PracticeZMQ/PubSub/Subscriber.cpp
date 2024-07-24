#include <zmq.hpp>
#include <string>
#include <iostream>

int main()
{
	zmq::context_t context(1);
	zmq::socket_t subscriber(context, ZMQ_SUB);
	subscriber.connect("tcp://*:5556");

	for(int updatedNum = 0; updatedNum < 100; ++updatedNum)
	{
		zmq::message_t msg(0);
		subscriber.recv(msg);
		std::cout << msg << std::endl;
	}

	subscriber.close();
	context.close();

	return 0;
}