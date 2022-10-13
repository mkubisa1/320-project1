all: predictors

predictors: main.o getBinary.o bimodalOneBit.o
	g++ main.o getBinary.o bimodalOneBit.o -o predictors

main.o: main.cpp getBinary.h bimodalOneBit.h
	g++ -c main.cpp getBinary.h bimodalOneBit.h
# .h files would go here as well

getBinary.o: getBinary.h getBinary.cpp bimodalOneBit.h
	g++ -c getBinary.h getBinary.cpp bimodalOneBit.h bimodalOneBit.cpp

clean:
	rm -f *.o predictors a.out *.gch