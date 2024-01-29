CC=gcc
STDFLAGS=-Wall -Werror -Wextra -std=c11
GCOV_FLAGS=-fprofile-arcs -ftest-coverage
TEST_SRC=$(wildcard tests/*.c)
SRC=$(wildcard *.c)
OBJ=$(patsubst %.c,%.o, ${SRC})
TARGET=s21_viewer.a


OS := $(shell uname -s)
ifeq ($(OS),Linux)
	OPEN_CMD=xdg-open
	CHECK_FLAGS=-lcheck -lsubunit -lrt -lpthread -lm
endif
ifeq ($(OS),Darwin)
	OPEN_CMD=open
	CHECK_FLAGS=-lcheck -lpthread -lm
endif

$(TARGET): ${SRC}
	$(CC) -c $(STDFLAGS) $(SRC)
	ar rc $@ $(OBJ)
	ranlib $@
	cp $@ lib$@
	rm -rf *.o

all: install gcov_report

install:
	cd ../ && cmake -B build "src/" && make -C build && mv build/ VIEWER && rm -rf VIEWER/build/
	
uninstall:
	 rm -rf ../VIEWER

dist:
	mkdir ../s21_VIEWER
	cp -r ../src/* ../s21_VIEWER
	tar cvzf ../s21_viewer-1.0.tar.gz ../s21_VIEWER
	rm -rf ../s21_VIEWER

dvi:
	latex documentation.tex
	dvipdfm documentation.dvi
	$(OPEN_CMD) documentation.pdf 2> /dev/null
	rm documentation.dvi documentation.log documentation.aux

test: $(TARGET)
	${CC} $(STDFLAGS) ${TEST_SRC} $< -o test_exe $(CHECK_FLAGS)
	./test_exe
	rm -f test_exe

gcov_report:
	$(CC) $(GCOV_FLAGS) $(STDFLAGS) ${TEST_SRC} $(SRC) -o test_exe  $(CHECK_FLAGS)
	./test_exe
	lcov -capture --directory . --output-file main_coverage.info
	genhtml *.info -o ./gcov_report
	rm -rf *.gcda *.gcno *.info test_exe
	${OPEN_CMD} gcov_report/index.html 2> /dev/null
	rm -f test_exe

clang:
	cp ../materials/linters/.clang-format .clang-format
	@echo "TO BE FORMATTED:"
	@clang-format -n *.c *.h *.cpp 2> res2.txt
	@clang-format -n tests/*.c tests/*.h 2> res1.txt
	@cat res2.txt res1.txt > res.txt
	@cat res.txt
	@rm res2.txt res1.txt
	@if [ -s res.txt ]; then\
		echo "PERFORMING FORMATTING...";\
		clang-format -i *.c *.h *.cpp;\
		clang-format -i tests/*.c tests/*.h;\
		echo "RESULTS:";\
		clang-format -n *.c *.h *.cpp;\
		clang-format -n tests/*.c tests/*.h;\
	else\
		echo "YOUR FILE IS ALREADY FORMATTED";\
	fi
	@echo "MOVING CLANG BACK"
	@rm  .clang-format res.txt

clean:
	rm -rf libs21_viewer.a s21_viewer.a a.out test_exe gcov_report documentation.pdf ../s21_viewer-1.0.tar.gz
