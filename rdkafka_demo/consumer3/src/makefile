OBJDIR=../obj
BIN=../bin

TARGET = $(BIN)/consumer2

CC = g++

INCLUDEPATH += -I/usr/local/include/librdkafka
LIBS += -L/usr/local/lib/ -lrdkafka
CFLAGS= -g -std=c++11 -Wall -O2

SRCS := $(wildcard *.cpp)  
OBJS := $(patsubst %cpp, $(OBJDIR)/%o, $(SRCS))  

all: $(TARGET)  

$(TARGET): $(OBJS)  
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(OBJDIR)/%.o:%.cpp
	$(CC) $(CFLAGS) $(INCLUDEPATH) -c -o $@ $<

clean:  
	rm -f $(OBJDIR)/*.o $(TARGET) 
