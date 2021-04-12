CXX := g++
TARGET := DPLL
CXXFLAGS := -std=c++14 -O3 -Wall -Wextra
INCLUDE := src/include
SRC_DIRS := src\
			src/lib\
			src/lib/DPLL
SRCS := $(wildcard $(SRC_DIRS:=/*.cpp))
OBJS := $(SRCS:.cpp=.o)
DEPS = $(OBJS:.o=.d)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I $(INCLUDE) -MMD -c $< -o $@

clean:
	rm -rf $(TARGET) $(OBJS) $(DEPS)

ifeq (test,$(firstword $(MAKECMDGOALS)))
  TEST_CASE_ID := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  $(eval $(TEST_CASE_ID):;@:)
endif

test: $(TARGET)
	@echo test on case$(TEST_CASE_ID)

.PHONY: all clean test
-include $(DEPS)