CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Isrc
TARGET = mini-redis
SRCS = src/main.cpp src/client/client.cpp src/protocole/analyseur.cpp src/serveur/serveur.cpp src/magasin/magasin.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean