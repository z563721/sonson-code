
PACKAGE	= opencvSkelton
SRCS	= $(PACKAGE).cpp imgtool.cpp
HEADS	= imgtool.h
OBJS	= $(SRCS:.cpp=.o)

FILES	= README Makefile $(HEADS) $(SRCS)
VER	= `date +%Y%m%d`

#DEBUG	= -ggdb -pg # -lefence

# common (*.o)
LD	= gcc
LDFLAGS	= -g $(DEBUG)
LDLIBS	= -lm $(LIBS_MAGICK) $(LIBS_OPENCV)
LIBS_MAGICK	= -lMagick -ltiff -lpng -lz -lpthread -lm -lpthread
LIBS_OPENCV	= -lcxcore -lcv -lhighgui -lcvaux -lml

# C (*.c)
CC	= gcc
CFLAGS	= -g -O2 -Wall $(DEBUG)
CPPFLAGS= -I.

# C++ (*.cpp)
CXX	= g++
CXXFLAGS= -g -O2 -Wall $(DEBUG) -fno-exceptions $(CFLAGS_MAGICK) $(CFLAGS_OPENCV)
CFLAGS_MAGICK = `Magick-config --cppflags` 
CFLAGS_OPENCV = `pkg-config opencv --cflags`

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
	./$(PACKAGE) test.bmp
