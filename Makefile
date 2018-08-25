all: tp1

tp1: main.cpp graph.cpp
	g++ -std=c++11 -c -g graph.cpp
	g++ -std=c++11 -c -g main.cpp
	g++ -std=c++11 -o tp1 graph.o main.o