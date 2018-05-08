CC            = g++
CFLAGS        = -I/usr/local/include/opencv2 -I/usr/local/include/opencv
LDFLAGS       = -L/usr/local/lib
LIBS          = -lopencv_core -lopencv_imgcodecs -lopencv_highgui
OBJS          = main.cpp
PROGRAM       = main

all:            $(PROGRAM)

$(PROGRAM):     $(OBJS)
	        $(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) $(LIBS)



