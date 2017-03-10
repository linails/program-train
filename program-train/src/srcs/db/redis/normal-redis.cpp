/*
 * Progarm Name: normal-redis.cpp
 * Created Time: 2017-03-10 17:01:48
 * Last modified: 2017-03-10 17:19:25
 * @author: minphone.linails linails@foxmail.com 
 */

#include "normal-redis.hpp"
#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include "hiredis/hiredis.h"
#include <cstdio>

using std::cout;
using std::endl;
using std::string;
using std::vector;

NormalRedis::NormalRedis()
{
}

NormalRedis::~NormalRedis()
{
}

int  NormalRedis::main(int argc, char **argv)
{
    int ret = 0;

    ret = this->basic(); assert(-1 != ret);

    return ret;
}

int  NormalRedis::basic(void)
{
    redisContext *conn = redisConnect("127.0.0.1", 6379);
    if(NULL != conn && conn->err){
        printf("connection error : %s\n", conn->errstr);
        return -1;
    }

    redisReply *reply = (redisReply*)redisCommand(conn, "set foo 1234");
    freeReplyObject(reply);

    reply = (redisReply*)redisCommand(conn, "get foo");
    printf("redis read : %s \n", reply->str);

    freeReplyObject(reply);

    return 0;
}


