#include <zmq.hpp>
#include <string>
#include <iostream>

/*
2. 하나의 클라이언트가 recv 2회 이상 불가능 : 크래시 발생
*/
void TestCase2(zmq::socket_t& requester)
{
	std::string first = "fir";
	std::string second = "sec";

	{
		zmq::message_t req(first.begin(), first.end());
		std::cout << "Send first " << std::endl;
		auto result = requester.send(req, zmq::send_flags::none);
		if (result.has_value() == false)
		{
			std::cout << "result not has value with first" << std::endl;
			return;
		}
	}

	{
		zmq::message_t req(second.begin(), second.end());
		std::cout << "Send second " << std::endl;
		auto result = requester.send(req, zmq::send_flags::none);
		if (result.has_value() == false)
		{
			std::cout << "result not has value with second" << std::endl;
			return;
		}
	}
}

bool DefaultCase(zmq::socket_t& requester, std::string hello, int reqNum)
{
	zmq::message_t req(hello.begin(), hello.end());
	std::cout << "Sending Hello " << reqNum << std::endl;
	requester.send(req, zmq::send_flags::none);

	zmq::message_t reply(0);
	requester.recv(reply);
	std::cout << "Received World " << reqNum << std::endl;

	return true;
}

int main()
{
	zmq::context_t context(1);
	std::cout << "Connection to server" << std::endl;
	zmq::socket_t requester(context, ZMQ_REQ);
	requester.connect("tcp://localhost:5555");
	// TestCase 3 : 라운드로빈 테스트
	// 5555 -> 5556 -> 5555 -> 5556 -> ... 이런 식으로 정상 동작함
	requester.connect("tcp://localhost:5556");

	const std::string hello = "Hello";
	for(int reqNum = 0; reqNum < 10; ++reqNum)
	{
		DefaultCase(requester, hello, reqNum);
		//TestCase2(requester);
	}

	requester.close();

	return 0;
}