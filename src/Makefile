CC = g++
CFLAGS = -std=c++17 -Wall -Werror -Wextra
GCOV_FLAG = -fprofile-arcs -ftest-coverage -fPIC -O0
GCOV_FLAG_TEST = --coverage
TEST_FLAG = -lgtest_main -lgtest
OPEN = open

ifeq ($(shell uname), Linux)
	OPEN = xdg-open
endif

SOURCE = test/test_tree.cpp

.PHONY: all
all: gcov_report

.PHONY: test
test: clean
	$(CC) $(CFLAGS) $(SOURCE) $(TEST_FLAG) -o tests
	./tests

.PHONY: gcov_report
gcov_report: clean
	$(CC) $(CFLAGS) $(SOURCE) $(GCOV_FLAG_TEST) -o tests $(TEST_FLAG)
	./tests
	gcovr -r . --html --html-details -o report.html
	rm -f *.gcda *.gcno
	$(OPEN) report.html
	
.PHONY: clean
clean:
	-rm -rf *.o *.a *.out *.gcda *.gcno *.css *.html
	-rm -rf tests
	
.PHONY: style
style:
	clang-format -n -style=Google red_black_tree/*.h red_black_tree/*.tpp

.PHONY: valgrind
valgrind:
	valgrind --leak-check=full -q  -s --track-origins=yes ./tests
