CC = g++

CFLAGS= -g -std=c++11  -pthread -Wall -O2 

LIB= -lssl -lcrypto

TARGET = main

SRCS := $(wildcard *.cpp)  

OBJS := $(patsubst %cpp, %o, $(SRCS))  

all: $(TARGET)  

$(TARGET): $(OBJS)  
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)
	rm *.o

%.o:%.cpp
	$(CC) $(CFLAGS) -c $<

clean:  
	rm -f *.o $(TARGET) 
