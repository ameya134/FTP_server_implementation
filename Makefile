
SOURCES= main.c \
	 server.c

TARGET=fptserver


CC=g++
CCFLAGS= -std=c++14 -Og -Wall -Werror


OBJS=$(SOURCES:.c=.o)

%.o : %.c
	$(CC) $(CCFLAGS) -c $< -o $@

.PHONY: all
all:	$(TARGET).out

$(TARGET).out : $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@


.PHONY: clean
clean:
	rm -rf $(TARGET).out $(OBJS)
