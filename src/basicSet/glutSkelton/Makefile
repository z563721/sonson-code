
PACKAGE	= glutSkelton
SRCS	= $(PACKAGE).cpp 
HEADS	= 
OBJS	= $(SRCS:.cpp=.o)

FILES	= README Makefile $(HEADS) $(SRCS)
VER	= `date +%Y%m%d`

#DEBUG	= -ggdb -pg # -lefence

# common (*.o)
LD	= /usr/bin/g++-4.0
LDFLAGS	= -g $(DEBUG) -L/System/Library/Frameworks/OpenGL.framework/Libraries -L/System/Library/Frameworks/GLUT.framework
LDLIBS	= -lm -framework OpenGL -framework GLUT

# C (*.c)
CC	= gcc
CFLAGS	= -g -O2 -Wall $(DEBUG)
CPPFLAGS= -I.

# C++ (*.cpp)
CXX	= /usr/bin/gcc-4.0 -x c++
CXXFLAGS= -g -O2 -Wall $(DEBUG) -fno-exceptions $(CFLAGS_OPENGL) $(CFLAGS_GLUT)
CFLAGS_OPENGL = -I/System/Library/Frameworks/OpenGL.framework/Headers
CFLAGS_GLUT = -I/System/Library/Frameworks/GLUT.framework/Headers

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
	./$(PACKAGE) < sample-data | less
	
test: all
	./$(PACKAGE) GLUT
