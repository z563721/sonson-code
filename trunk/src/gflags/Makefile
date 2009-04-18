PACKAGE	= gflags_test
SRCS	= $(PACKAGE).cpp hoge.cpp
HEADS	= hoge.h
OBJS	= $(SRCS:.cpp=.o)
FILES	= README Makefile $(HEADS) $(SRCS)
VER		= `date +%Y%m%d`
#DEBUG	= -ggdb -pg # -lefence

# common (*.o)
LD	= gcc
LDFLAGS	= -g $(DEBUG)
LDLIBS	= -lgflags -lstdc++

# C (*.c)
CC	= gcc
CFLAGS	= -g -O2 -Wall $(DEBUG)
CPPFLAGS= -I.

# C++ (*.cpp)
CXX		= g++
CXXFLAGS= -g -O2 -Wall $(DEBUG) -fno-exceptions

# etc
SHELL	= /bin/sh
RM		= rm -f
PROF	= gprof

### rules ###

.SUFFIXES:
.SUFFIXES: .o .c .cpp

all: $(PACKAGE)

$(PACKAGE): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $@ $(LDLIBS)

$(OBJS): $(HEADS) Makefile

.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
.cpp.o:
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

### useful commands ###

clean:
	$(RM) $(PACKAGE) $(OBJS)
	$(RM) core gmon.out *~ #*#
	$(RM) .DS_Store

run: all
	./$(PACKAGE) < sample-data | less
	
test: all
	./$(PACKAGE) --flagBool --flagInt32 100 --flagInt64 128 --flagUint64 128 --flagDouble 0.001 --flagString ABC
