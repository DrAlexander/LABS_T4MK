all: 
	swig -c++ -python BigNumb.i
	g++ -fPIC -c BigNumb.cpp
	g++ -fPIC -c BigNumb_wrap.cxx -I/usr/include/python2.7
	g++ -shared BigNumb.o BigNumb_wrap.o -o _BigNumb.so
	rm BigNumb.o BigNumb_wrap.cxx BigNumb_wrap.o
	
windows32:
	swig -c++ -python BigNumb.i
	g++ -c BigNumb.cpp
	g++ -c BigNumb_wrap.cxx -IC:\Python27\include
	g++ BigNumb.o BigNumb_wrap.o -Ic:\python27\include -Lc:\python27\libs -lpython27 -shared -o _BigNumb.pyd
	del BigNumb.o BigNumb_wrap.cxx BigNumb_wrap.o
	
windows64:
	swig -c++ -python BigNumb.i
	C:\TDM-GCC-64\bin\g++ -c BigNumb.cpp
	C:\TDM-GCC-64\bin\g++ -c BigNumb_wrap.cxx -IC:\Python27\include
	C:\TDM-GCC-64\bin\g++ BigNumb.o BigNumb_wrap.o -Ic:\python27\include -Lc:\python27\libs -lpython27 -shared -o _BigNumb.pyd
	del BigNumb.o BigNumb_wrap.cxx BigNumb_wrap.o