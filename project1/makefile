CXX = g++
CXXFLAGS = -Wall

driver: fuel.o driver.cpp
	$(CXX) $(CXXFLAGS) fuel.o driver.cpp -o driver

fuel.o: fuel.h fuel.cpp
	$(CXX) $(CXXFLAGS) -c fuel.cpp

clean:
	rm *.o*
	rm *~ 

run:
	./driver

val:
	valgrind ./driver