#
# 'make depend' uses makedepend to automatically generate dependencies 
#	       (dependencies are added to end of Makefile)
# 'make'	build executable file 
# 'make clean'  removes all .o and executable files
#

CC= clang
CFLAGS= -Wall -g
INCLUDES= 
LFLAGS= -lpthread
LIBS= 
SRCS= charlie.c oompa-loompas.c children.c
OBJS= $(SRCS:.c=.o)
EXEC= ChocolateFactory

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean

all:    clean $(EXEC)

$(EXEC): $(OBJS) 
	$(CC) $(CFLAGS) $(INCLUDES) -o $(EXEC) $(OBJS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) *.o *~ $(EXEC)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
