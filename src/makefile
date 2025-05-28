CC = g++
CFLAGS= -Wall -Werror -Wextra -std=c++17
OS = $(shell uname)

TARGET := Viewer

ifeq ($(OS),Linux)
    det_OS = -lgtest
else
    det_OS = -lgtest
endif

all: clean install


install: uninstall
	mkdir -p ../build
	qmake -o qmakefile -spec linux-g++ CONFIG+=debug CONFIG+=qml_debug && make -f qmakefile && make -f qmakefile clean && rm -rf qmakefile && mv $(TARGET) ../build

uninstall:
	rm -rf ../build/$(TARGET)

dvi:
	open ../Manual.md

dist:
	mkdir -p ../dist
	cp -R ../build/$(TARGET) ../dist
	cp ../Manual.md ../dist
	cd ../dist && tar cvzf $(TARGET).tgz *
	cd ../dist && rm -rf $(TARGET) Manual.md

test: clean
	$(CC) --coverage Logic/*.cpp Test/*.cpp -o testresult $(det_OS)
	./testresult

clean:
	rm -rf testresult *.gcda *.gcno *.o *.info *.a test/*.gcno
