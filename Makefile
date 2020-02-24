CFLAGS=-std=c11 -Wall -g -static
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

Ha4CC: $(OBJS)
	$(CC) -o Ha4CC $(OBJS) $(LDFLAGS)

$(OBJS): Ha4CC.h

test: Ha4CC
	./Ha4CC -test
	./test.sh

clean:
	rm -f Ha4CC *.o *~ tmp*
