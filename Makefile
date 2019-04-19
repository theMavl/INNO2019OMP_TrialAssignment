all:
	cd gui && /usr/bin/qmake -o Makefile cont.pro -spec linux-g++ CONFIG+=qtquickcompiler && make
	cd cli && make

run:
	cd gui && ./cont