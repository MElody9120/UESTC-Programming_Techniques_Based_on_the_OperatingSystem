cc 	    = g++
cflags  = -ldl -o
soflags = -fpic -shared -o

2_1 : 2_1.cpp
	$(cc) 2_1.cpp $(cflags) 2_1

HC : Hello_China.cpp
	$(cc) Hello_China.cpp $(soflags) libHC.so
	mv libHC.so libTest.so

HW : Hello_World.cpp
	$(cc) Hello_World.cpp $(soflags) libHW.so
	mv libHW.so libTest.so

clean:
	rm libH*.so