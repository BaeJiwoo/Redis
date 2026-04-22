#pragma once
#include "hiredis.h"
#include <string>

#pragma comment(lib, "ws2_32.lib")

namespace RedisCpp {
	class CRedisConn {
	public:
		CRedisConn() = default;
		~CRedisConn() {
			closeredis();
		}

		bool connect(const char* hostname_, uint16_t port_) {
			mRedisContext = redisConnect(hostname_, port_);
			if (mRedisContext != NULL && mRedisContext->err) {
				printf("Error: %s\n", mRedisContext->errstr);
				// handle error
				printf("마에러고치라\n");

				return false;
			}
			else {
				printf("Connected to Redis\n");
			}

			return true;
		}

		void checkuser(std::string id_, std::string pw_) {
			/*id_.erase(id_.find_last_not_of(" \n\r\t") + 1);
			pw_.erase(pw_.find_last_not_of(" \n\r\t") + 1);*/

			printf("ID 길이: %zu, PW 길이: %zu\n", id_.length(), pw_.length());
			const char* script = "if redis.call('HGET', KEYS[1], 'pw') == ARGV[1] then return 1 else return 0 end";

			redisReply* reply = (redisReply*)redisCommand(mRedisContext, "EVAL %s 1 user:%s %s", script, id_.c_str(), pw_.c_str());
			//redisReply* reply = (redisReply*)redisCommand(mRedisContext, "HGET user:jiwoo pw");

			if (reply == NULL) {
				printf("서버 통신 실패\n");
				return;
			}


			if (reply->type == REDIS_REPLY_INTEGER) {
				if (reply->integer == 1) {
					printf("인증 성공: 서버에서 검증 완료\n");
				}
				else {
					printf("인증 실패: 비밀번호가 틀림 (DB:%s vs 입력:%s)\n", reply->str, pw_.c_str());
				}
			}
			else if (reply->type == REDIS_REPLY_NIL) {
				printf("인증 실패: 사용자가 존재하지 않음\n");
			}
			else {
				printf("기타 에러: Reply Type = %d\n", reply->type);
			}

			freeReplyObject(reply);
		}

		std::string getErrorStr() {
			return mRedisContext->errstr;
		}


		void closeredis() {
			redisFree(mRedisContext); 
			mRedisContext = NULL;
		}
	private:
		redisContext* mRedisContext = NULL;
	};


}
