hcc: hcc.c

test: hcc
	./hcc -test
	./test.sh

clean:
	rm -f hcc *.o *~ tmp*
