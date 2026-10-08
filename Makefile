CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = mini-redis
SRCS = src/main.cpp src/client/client.cpp src/protocol/parser.cpp src/server/server.cpp src/store/store.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
