CC=gcc
TEST_RUNNER=run_test
UNAME_S := $(shell uname -s)

FLAGS= -std=c11 -I./ -Wall -Werror -Wextra
TEST_FLAGS=-lcheck -lm -pthread 

ifeq ($(UNAME_S),Linux)
    TEST_FLAGS=-lcheck -lsubunit -lm -pthread -lrt
endif

ifeq ($(UNAME_S),Darwin)
    TEST_FLAGS=-lcheck -lm -pthread 
endif

ifeq ($(UNAME_S),Windows_NT)
    TEST_FLAGS=-lcheck -lsubunit -lm -pthread -lrt
endif

SRC_DIR=./
TEST_DIR=./test

SRC_C_FILES := $(shell find $(SRC_DIR) -name "s21_*.c")
TEST_C_FILES := $(shell find $(TEST_DIR) -name "test_*.c")

TEST_OBJECTS_DIR=./test/obj 
SRC_OBJECTS_DIR=./obj

all: s21_string.a test

rebuild: clean all 

s21_string.a: $(SRC_C_FILES)
	$(CC) $(FLAGS) -c $(SRC_C_FILES)
	ar -rcs s21_string.a s21_*.o
	ranlib s21_string.a

test: s21_string.a $(TEST_C_FILES)
	$(CC) --coverage s21_string.a -o $(TEST_RUNNER) $(TEST_C_FILES) $(SRC_C_FILES) $(TEST_FLAGS) $(FLAGS)

gcov_report:
	mkdir -p report 
	./$(TEST_RUNNER) 
	lcov -t "Report" -c -d ./ --output-file ./coverage.info
	genhtml ./coverage.info --output-directory ./report/

clean: 
	rm -rf *.a $(TEST_RUNNER) 
	rm -rf *.o
	rm -rf *.gcda 
	rm -rf *.gcno 
	rm -rf coverage.info 
	rm -rf report/ 