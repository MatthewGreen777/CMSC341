CXX = g++
CXXFLAGS = -Wall

mytest: vdetect.o mytest.cpp
	$(CXX) $(CXXFLAGS) vdetect.o mytest.cpp -o mytest

vdetect.o: vdetect.h vdetect.cpp
	$(CXX) $(CXXFLAGS) -c vdetect.cpp

clean:
	rm *.o*
	rm *~ 

run:
	./mytest

val:
	valgrind ./mytest