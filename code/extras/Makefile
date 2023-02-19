CC = gcc
CFLAGS = -fPIC 
LDFLAGS = -shared

all: libfactorial.so libgcd.so liblntwo.so

%.o: %.s
	as -o $@ $^ 

lib%.so: %.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

clean:
	rm -f *.o *.so

