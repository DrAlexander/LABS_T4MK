all: BI.cpp BigNumb.cpp
	g++ -c -fPIC BigNumb.cpp
	g++ -shared -o libBigNumb.so BigNumb.o
	LD_LIBRARY_PATH=./ g++ BI.cpp -lBigNumb -I. -Wl,-rpath,. -L. -o BI_2
	
windows: BI.cpp BigNumb.cpp
	g++ -c BigNumb.cpp
	g++ -shared -o BigNumb.dll BigNumb.o
	g++ BI.cpp BigNumb.dll -I. -Wl,-rpath,. -L. -o BI_2.exe