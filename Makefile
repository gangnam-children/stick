CXX = g++ -std=c++11

SRCS = lib/json/json.cpp lib/json/reader.cpp lib/json/writer.cpp lib/string/split.cpp \
lib/log/Log.cpp lib/redis/SimpleRedisClient.cpp lib/redis/redis.cpp \
src/request.cpp src/response.cpp src/router.cpp src/url_dispatcher.cpp src/main.cpp \
src/user.cpp src/ranking.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = bin/server.fcgi
LIBS = -lfcgi -lredis3m

.SUFFIXES: .cpp .o

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LIBS)

clean :
	rm $(OBJS)

