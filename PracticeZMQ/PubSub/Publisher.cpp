#include <zmq.hpp>
#include <string>
#include <iostream>

int main()
{
	zmq::context_t context(1);
	zmq::socket_t publisher(context, ZMQ_PUB);
	publisher.bind("tcp://*:5556");
	publisher.bind("ipc://whather.ipc");

	srand(static_cast<unsigned int>(time(NULL)));
	while (true)
	{
		int code = std::rand() % 100000;
		int temperature = std::rand() % 215 - 80;
		int relhumidity = std::rand() % 50 + 10;

		std::string updateString = 
			std::to_string(code) + " " + std::to_string(temperature) + " " + std::to_string(relhumidity);
		zmq::message_t updateMessage(updateString.begin(), updateString.end());
		publisher.send(updateMessage, zmq::send_flags::none);
	}

	publisher.close();
	context.close();

	return 0;
}