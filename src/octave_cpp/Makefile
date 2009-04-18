
PACKAGE	= sample02
SRCS	= $(PACKAGE).cpp
HEADS	= 
OBJS	= $(SRCS:.cpp=.o)

FILES	= README Makefile $(HEADS) $(SRCS)
VER	= `date +%Y%m%d`

MACPORTS_INC = /opt/local/include/
MACPORTS_LIB = /opt/local/lib/

OCTAVE_INC = /opt/local/include/octave-2.9.9/
OCTAVE_LIB = /opt/local/lib/octave-2.9.9/

#DEBUG	= -ggdb -pg # -lefence

# common (*.o)
LD	= g++
LDFLAGS	= -g $(DEBUG)
LDLIBS	= -L$(OCTAVE_LIB) -loctave

# C (*.c)
CC	= g++
CFLAGS	= -g -O2 -Wall $(DEBUG)
CPPFLAGS= -I.

# C++ (*.cpp)
CXX	= g++
CXXFLAGS= -g -O2 -Wall $(DEBUG) -fno-exceptions -I$(OCTAVE_INC)

# etc
SHELL	= /bin/sh
RM	= rm -f
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
	./$(PACKAGE)
	
test: all
	./$(PACKAGE)
