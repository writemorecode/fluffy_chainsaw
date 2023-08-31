CC = gcc
CFLAGS = -Wall 
LDFLAGS = -fPIC -shared

setup:
	bison -y -d lexyacc-code/calc3.y
	@mv y.tab.c y.tab.h lexyacc-code/
	flex -o lexyacc-code/lex.yy.c lexyacc-code/calc3.l 
	gcc -c lexyacc-code/y.tab.c lexyacc-code/lex.yy.c
	@mv lex.yy.o y.tab.o lexyacc-code/

clean:
	rm -f bin/* lib/* obj/*

SRCDIR = lexyacc-code
OBJDIR = obj
LIBDIR = lib
SOURCES = $(shell find $(SRCDIR) -type f -name "*.s")

$(OBJDIR)/stack.o: $(SRCDIR)/stack.c
	gcc -Wall -Werror -Wpedantic -std=c99 -O2 -c -o $@ $^

$(OBJDIR)/functions.o: $(SOURCES)
	as -o $@ $^

$(LIBDIR)/libfunctions.so: $(OBJDIR)/functions.o
	gcc -o $@ -shared -fPIC $<

calc3c: setup $(LIBDIR)/libfunctions.so $(OBJDIR)/stack.o
	$(CC) $(CFLAGS) lexyacc-code/y.tab.o lexyacc-code/lex.yy.o lexyacc-code/calc3c.c -o bin/calc3c.exe

calc3g: setup $(LIBDIR)/libfunctions.so
	$(CC) $(CFLAGS) lexyacc-code/y.tab.o lexyacc-code/lex.yy.o lexyacc-code/calc3g.c -o bin/calc3g.exe

calc3i: setup $(LIBDIR)/libfunctions.so
	$(CC) $(CFLAGS) lexyacc-code/y.tab.o lexyacc-code/lex.yy.o lexyacc-code/calc3i.c -o bin/calc3i.exe

