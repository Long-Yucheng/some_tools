DIR_SRC = ./source
DIR_OBJ = ./obj
DIR_BIN = ./bin

# 注意其他模块的路径，也在SRC里面
SRC = $(shell find $(DIR_SRC) -name *.cpp)
OBJ = $(patsubst %.cpp, ${DIR_OBJ}/%.o, $(notdir ${SRC}))

# Target Name
TARGET   = spfsforecast

BIN_TARGET = ${DIR_BIN}/${TARGET}

# Declaration of variables
CC       = gcc
CXX      = g++
CXXFLAGS = -g -Wall -O2 -DDEBUG
LDFLAGS  =

# Libs
LIBS    = -lmysqlclient -lpthread -L/usr/lib/mysql -lstdc++ -ldl
INCPATH = -I/usr/include/mysql

# Main target 由 .o文件 链接而成
$(BIN_TARGET):$(OBJ)
	$(CXX) -o $@ $(OBJ) $(LIBS)


# .o文件 由 .cpp 编译而成
$(DIR_OBJ)/%.o:${DIR_SRC}/%.cpp
	$(CXX) $(CXXFLAGS) -c $(INCPATH) $< -o $@


# 删除生成的 .o文件 以及 可执行程序
.PHONY:clean
clean:
	rm -f ${DIR_OBJ}/*.o $(BIN_TARGET)

