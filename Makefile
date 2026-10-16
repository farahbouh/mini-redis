CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Isrc -MMD -MP

TARGET = mini-redis
SRCS = src/main.cpp \
       src/client/client.cpp \
       src/protocole/analyseur.cpp \
       src/serveur/serveur.cpp \
       src/stockage/stockage.cpp
OBJS = $(SRCS:.cpp=.o)

TEST_TARGET = test_stockage
TEST_SRCS = tests/store_test.cpp \
            src/stockage/stockage.cpp
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

TEST_ANA_TARGET = test_analyseur
TEST_ANA_SRCS = tests/analyseur_test.cpp \
                src/protocole/analyseur.cpp
TEST_ANA_OBJS = $(TEST_ANA_SRCS:.cpp=.o)

DEPS = $(OBJS:.o=.d) $(TEST_OBJS:.o=.d) $(TEST_ANA_OBJS:.o=.d)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_ANA_TARGET): $(TEST_ANA_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

test: $(TEST_TARGET) $(TEST_ANA_TARGET)
	./$(TEST_TARGET)
	./$(TEST_ANA_TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TEST_OBJS) $(TEST_ANA_OBJS) $(DEPS) $(TARGET) $(TEST_TARGET) $(TEST_ANA_TARGET)

-include $(DEPS)

.PHONY: all test clean