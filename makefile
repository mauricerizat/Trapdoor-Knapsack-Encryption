#TRAPDOOR KNAPSACK ENCRYPTION PROGRAM

trapKnap.out: main.o header.h operations.o 
	g++ -o trapKnap.out main.o header.h operations.o 

main.o: main.o header.h operations.o 
	g++ -c main.cpp

operations.o: operations.cpp header.h 
	g++ -c operations.cpp

clean:
	rm *.o trapKnap.out
