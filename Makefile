pwgen:		main.c pwgen.o get_rand.o
	cc -Wall -o pwgen main.c pwgen.o get_rand.o

pwgen.o:	pwgen.h pwgen.c
	cc -Wall -c pwgen.c

get_rand.o:	pwgen.h get_rand.c
	cc -Wall -c get_rand.c

clean:
	rm -f *.o pwgen
