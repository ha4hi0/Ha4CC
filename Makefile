COMPILER=gcc
CFLAGS=-std=c11 -Wall -g -static
SRCS=codegen.c  container.c  main.c  parse.c analyze.c utility.c tokenize.c node.c scope.c

Ha4CC: $(SRCS)
	$(COMPILER) -o Ha4CC $(SRCS) $(LDFLAGS)

test: Ha4CC
	./Ha4CC -test
	./test.sh

clean:
	rm -f Ha4CC *.o *~ tmp*
