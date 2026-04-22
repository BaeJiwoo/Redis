#define _CRT_SECURE_NO_WARNINGS
#include "RedisConn.h"
#include "EnvReader.h"
#include <chrono>
#include <thread>
#include <iostream>


int main() {
	EnvReader env(".env");
	RedisCpp::CRedisConn con;
	
	std::string value;

	std::string host = env.get("REDIS_HOST", "127.0.0.1");
	uint16_t port = static_cast<uint16_t>(env.getInt("REDIS_PORT", 6379));

	if (!con.connect(host.c_str(), port)) {
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