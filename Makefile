include = ./headers
cc = g++


hashmap: src/main.cpp
	$(cc) -o main -g -I $(include) $^ -pthread