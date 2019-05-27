hcc: hcc.c

test: hcc
	./test.sh

clean:
	rm -f hcc *.o *~ tmp*
