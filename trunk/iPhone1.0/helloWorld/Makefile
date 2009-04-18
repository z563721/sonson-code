.SUFFIXES:.m.h

CC		= /usr/local/arm-apple-darwin/bin/gcc
CXX		= /usr/local/arm-apple-darwin/bin/g++
CFLAG	= 
LDFLAGS=-Wl,-syslibroot,/usr/local/arm-apple-darwin/heavenly -lobjc -framework CoreFoundation -framework Foundation -framework UIKit -framework LayerKit -framework CoreGraphics
LD		= $(CC)
TARGET	= HelloWorld
OBJS	= main.o MyApp.o

all:$(TARGET)

$(TARGET):$(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^
	cp -r ./resource $(TARGET).app
	mv $(TARGET) ./$(TARGET).app/

clean:
	rm -rf $(OBJS) $(TARGET) $(TARGET).app
	
.m.o:
	$(CC) -c $(C_FLAG) $<
