all: predictors

predictors: main.o getBinary.o 
	g++ main.o getBinary.o -o predictors

main.o: main.cpp getBinary.h
	g++ -c main.cpp getBinary.h
# .h files would go here as well

getBinary.o: getBinary.h getBinary.cpp
	g++ -c getBinary.h getBinary.cpp

clean:
	rm -f *.o predictors a.out *.gch