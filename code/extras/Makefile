CC = gcc
CFLAGS = -fPIC 
LDFLAGS = -shared

all: libfactorial.so libgcd.so liblntwo.so libprint.so

%.o: %.s
	as -o $@ $^ 

lib%.so: %.o
	$(CC) -ggdb3 $(CFLAGS) $(LDFLAGS) -o $@ $^

clean:
	rm -f *.o *.so

