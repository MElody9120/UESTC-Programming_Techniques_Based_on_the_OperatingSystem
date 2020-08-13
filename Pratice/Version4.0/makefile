cc      = g++
cflags  = -ldl -g -o
soflags = -fpic -shared -o
sodeps  = IPrintPlugin.cpp
dep     = pluginCounter.cpp pluginController.cpp

2_4 : 2_4.cpp $(depcpp) libHC.so libHW.so
	$(cc) 2_4.cpp $(dep) $(cflags) 2_4

libHC.so : Hello_China.cpp
	$(cc) Hello_China.cpp $(sodeps) $(soflags) libHC.so
	cp libHC.so plugin/

libHW.so : Hello_World.cpp
	$(cc) Hello_World.cpp $(sodeps) $(soflags) libHW.so
	cp libHW.so plugin/

clean:
	rm *.so