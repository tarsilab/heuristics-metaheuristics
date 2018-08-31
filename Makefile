all: tp1

tp1: main.cpp graph.cpp heuristics.cpp
	g++ -std=c++11 -c -g graph.cpp
	g++ -std=c++11 -c -g heuristics.cpp
	g++ -std=c++11 -c -g main.cpp
	g++ -std=c++11 -o tp1 graph.o heuristics.o main.o