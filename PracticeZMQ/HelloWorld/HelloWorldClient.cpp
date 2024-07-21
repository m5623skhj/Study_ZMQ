#include <zmq.hpp>
#include <string>
#include <iostream>

int main()
{
	zmq::context_t context(1);
	std::cout << "Connection to server" << std::endl;
	zmq::socket_t requester(context, ZMQ_REQ);
	requester.connect("tcp://localhost:5555");

	const std::string hello = "Hello";
	for(int reqNum = 0; reqNum < 10; ++reqNum)
	{
		zmq::message_t req(hello.begin(), hello.end());
		std::cout << "Sending Hello " << reqNum << std::endl;
		requester.send(req, zmq::send_flags::none);

		zmq::message_t reply(0);
		requester.recv(reply);
		std::cout << "Received World " << reqNum << std::endl;
	}

	requester.close();

	return 0;
}