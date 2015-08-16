main.fcgi : main.o json.o GlobalFunc.h lightjson.h Log.o reader.o redis.o request.o response.o router.o SimpleRedisClient.o UrlParser.o writer.o
	g++ -o main.fcgi main.o json.o GlobalFunc.o lightjson.h Log.o reader.o redis.o request.o response.o router.o SimpleRedisClient.o UrlParser.o writer.o -g -lfcgi -std=c++11

main.o : main.cpp
	g++ -c -g main.cpp -std=c++11

json.o : json.cpp json.h
	g++ -c -g json.cpp -std=c++11

Log.o : Log.cpp Log.h
	g++ -c -g Log.cpp -std=c++11

reader.o : reader.cpp reader.h
	g++ -c -g reader.cpp -std=c++11

redis.o : redis.cpp redis.h
	g++ -c -g redis.cpp -std=c++11

request.o : request.cpp request.h
	g++ -c -g request.cpp -std=c++11

response.o : response.cpp response.h GlobalFunc.o lightjson.h Log.o
	g++ -c -g response.cpp lightjson.h -std=c++11

router.o : router.cpp router.h
	g++ -c -g router.cpp -std=c++11

SimpleRedisClient.o : SimpleRedisClient.cpp SimpleRedisClient.h
	g++ -c -g SimpleRedisClient.cpp -std=c++11

UrlParser.o : UrlParser.cpp UrlParser.h GlobalFunc.o
	g++ -c -g UrlParser.cpp -std=c++11

writer.o : writer.cpp writer.h
	g++ -c -g writer.cpp -std=c++11

GlobalFunc.o : GlobalFunc.cpp GlobalFunc.h
	g++ -c -g GlobalFunc.cpp -std=c++11
