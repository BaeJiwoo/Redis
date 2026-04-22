#include "RedisConn.h"
#include <chrono>
#include <thread>
#include <iostream>


int main() {
	RedisCpp::CRedisConn con;
	
	std::string value;

	const char* host = "172.18.175.153";
	uint16_t port = 6379;

	if (!con.connect(host, port)) {
		printf("Connect Error %s\n", con.getErrorStr().c_str());
		std::this_thread::sleep_for(std::chrono::seconds(2));
		return -1;
	}
	else {
		std::cout << "connect success\n";
	}

	std::string id, pw;
	std::cout << "ID를 입력하세요\n>>";
	std::cin >> id;
	std::cout << "패스워드를 입력하세요\n>>";
	std::cin >> pw;
	con.checkuser(id, pw);

	return 0;


}