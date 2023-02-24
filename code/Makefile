setup:
	bison -y -d calc3.y
	flex calc3.l
	gcc -c y.tab.c lex.yy.c

clean:
	rm -f *.exe

calc3g: setup
	gcc y.tab.o lex.yy.o calc3g.c -o calc3g.exe

calc3b: setup
	gcc y.tab.o lex.yy.o calc3i.c -o calc3i.exe

