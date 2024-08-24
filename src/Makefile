CC=gcc
# CFLAGS=-Wall -Werror -Wextra -std=c11 -lm# -fsanitize=address -g
CFLAGS= -lm -Wall -Werror -Wextra -std=c11 -O2 -funroll-loops -mavx -g
VALGRIND=valgrind --leak-check=full --leak-resolution=med -s
OS:= $(shell uname -s)
LINFLAGS=-lcheck -pthread -lrt -lm -lsubunit
SRCFILE =  calc.c
OBJECTS =  calc.o


all: clean test 

calc.a:
	$(CC) -c $(CFLAGS) $(SRCFILE)
	@ar rcs calc.a $(OBJECTS)
	ranlib calc.a

test: clean calc.a
ifeq ($(OS), Darwin)
	gcc $(OBJECTS) tests_smartcalc.c -o test -lm $(shell pkg-config --cflags --libs check) -fsanitize=address # -lcheck -lpthread #-fsanitize=address
	./test
	rm -rf *.o *.a 
else
	gcc tests_smartcalc.c calc.a -o test $(LINFLAGS)
	./test
	rm -rf *.o *.a 
endif
cppcheck: test
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

gcov_report: clean
ifeq ($(OS), Darwin)
	gcc --coverage tests_smartcalc.c -o test $(SRCFILE) -lcheck
	./test
	gcov -f calc.gcda
	lcov -t "test" -o test.info -c -d .   
	genhtml -o report test.info
	open ./report/index.html
else
	gcc --coverage tests_smartcalc.c -o test $(SRCFILE) $(LINFLAGS)
	./test
	gcov -f calc.gcda
	lcov -t "test" -o test.info -c -d .  
	genhtml -o report test.info
	xdg-open ./report/index.html
endif

check: clean style leaks

style: test
	cp ../materials/linters/.clang-format .clang-format 
	# clang-format -style=google -i *.c *.h
	clang-format -style=google -n *.c *.h
	rm .clang-format 

leaks: test
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./test
	rm -rf calc.o
else
	#sudo dnf install valgrind
	$(VALGRIND) --leak-check=full --show-leak-kinds=all --track-origins=yes ./test 
	rm -rf calc.o
endif
install: uninstall
	mkdir -p ../build
	qmake6 smart_calc/smart_calc.pro -o ../build/Makefile
	cd ../build; make > /dev/zero 2> /dev/zero
	mkdir -p ~/Applications ; cp -r ../build/smart_calc.app ~/Applications/smart_calc.app

uninstall: clean
	rm -rf ../build
	rm -rf ~/Applications/smart_calc.app
dist:
	cd .. && tar -czvf smart_calc.tar src

dvi:
	open smart_calc/dvi.html
clean:
	-rm -rf *.o && rm -rf *.gcno && rm -rf *.exec
	-rm -rf *.a && rm -rf *.gcda
	-rm -rf *.info && rm -rf *.gcov
	-rm -rf ./gcov_report
	-rm -rf ./run_tests ./test 
	-rm -rf ./report/
	-rm -rf *.log
