CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Isrc -MMD -MP

# Programme principal
TARGET = mini-redis
SRCS = src/main.cpp \
       src/client/client.cpp \
       src/protocole/analyseur.cpp \
       src/serveur/serveur.cpp \
       src/stockage/stockage.cpp
OBJS = $(SRCS:.cpp=.o)

# Test de Stockage
TEST_STO_TARGET = test_stockage
TEST_STO_SRCS = tests/store_test.cpp \
                src/stockage/stockage.cpp
TEST_STO_OBJS = $(TEST_STO_SRCS:.cpp=.o)

# Test de l'Analyseur
TEST_ANA_TARGET = test_analyseur
TEST_ANA_SRCS = tests/analyseur_test.cpp \
                src/protocole/analyseur.cpp
TEST_ANA_OBJS = $(TEST_ANA_SRCS:.cpp=.o)

# Test du Serveur (a besoin de Client, Analyseur et Stockage)
TEST_SRV_TARGET = test_serveur
TEST_SRV_SRCS = tests/serveur_test.cpp \
                src/serveur/serveur.cpp \
                src/client/client.cpp \
                src/protocole/analyseur.cpp \
                src/stockage/stockage.cpp
TEST_SRV_OBJS = $(TEST_SRV_SRCS:.cpp=.o)

ALL_OBJS = $(OBJS) $(TEST_STO_OBJS) $(TEST_ANA_OBJS) $(TEST_SRV_OBJS)
DEPS = $(ALL_OBJS:.o=.d)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_STO_TARGET): $(TEST_STO_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_ANA_TARGET): $(TEST_ANA_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_SRV_TARGET): $(TEST_SRV_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# make test : lance les trois tests
test: $(TEST_STO_TARGET) $(TEST_ANA_TARGET) $(TEST_SRV_TARGET)
	./$(TEST_STO_TARGET)
	./$(TEST_ANA_TARGET)
	./$(TEST_SRV_TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(ALL_OBJS) $(DEPS) $(TARGET) $(TEST_STO_TARGET) $(TEST_ANA_TARGET) $(TEST_SRV_TARGET)

-include $(DEPS)

.PHONY: all test clean