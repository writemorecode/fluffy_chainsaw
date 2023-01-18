lntwo: lntwo_test.c liblntwo.so
	gcc -g -L . lntwo_test.c -o lntwo -llntwo 

factorial: libfactorial.so factorial_test.c
	gcc -L. factorial_test.c -o factorial -lfactorial 

gcd: libgcd.so gcd_test.c
	gcc -ggdb3 -L. gcd_test.c -o gcd -lgcd 

liblntwo.so: lntwo.o
	gcc -g -shared -fPIC lntwo.o -o liblntwo.so

libfactorial.so: factorial.o
	gcc -shared -fPIC factorial.o -o libfactorial.so

libgcd.so: gcd.o
	gcc -g -shared -fPIC gcd.o -o libgcd.so

lntwo.o: lntwo.s
	as lntwo.s -o lntwo.o

factorial.o: factorial.s
	as factorial.s -o factorial.o

gcd.o: gcd.s
	as gcd.s -o gcd.o

clean:
	rm -f *.o *.so lntwo factorial gcd
