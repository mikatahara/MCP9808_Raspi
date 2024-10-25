mcp9808 : Wiringpi_MCP9808.o main.o
	gcc -o mcp9808 main.o Wiringpi_MCP9808.o -lwiringPi

Wiringpi_MCP9808.o : Wiringpi_MCP9808.cpp Wiringpi_MCP9808.h
	gcc -o Wiringpi_MCP9808.o -c Wiringpi_MCP9808.cpp

main.o : main.cpp Wiringpi_MCP9808.h
	gcc -o main.o -c main.cpp
