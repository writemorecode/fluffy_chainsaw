lntwo: lntwo_test.c liblntwo.so
	gcc -g -L . lntwo_test.c -o lntwo -llntwo 

factorial: libfactorial.so factorial_test.c
	gcc -O2 -L. factorial_test.c -o factorial -lfactorial 

libfactorial.so: factorial.o
	gcc -O2 -shared -fPIC factorial.o -o libfactorial.so

factorial.o: factorial.s
	as factorial.s -o factorial.o

liblntwo.so: lntwo.o
	gcc -g -shared -fPIC lntwo.o -o liblntwo.so

lntwo.o: lntwo.s
	as lntwo.s -o lntwo.o

clean:
	rm -f *.o *.so lntwo factorial
