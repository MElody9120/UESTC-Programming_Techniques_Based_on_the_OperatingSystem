cc      = g++
cflags  = -ldl
soflags = -fpic -shared
defh    = pluginCounter.h

2_3 : 2_3.cpp pluginCounter.cpp libHC.so libHW.so
	$(cc) -o 2_3 2_3.cpp pluginCounter.cpp $(defh) $(cflags)

libHC.so : Hello_China.cpp
	$(cc) -o libHC.so Hello_China.cpp $(soflags)
	cp libHC.so plugin/

libHW.so : Hello_World.cpp
	$(cc) -o libHW.so Hello_World.cpp $(soflags)
	cp libHW.so plugin/

clean:
	rm *.so