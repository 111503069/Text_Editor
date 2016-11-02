project : editormain.o datastructure.o filefunctions.o
	cc editormain.o datastructure.o filefunctions.o -o project -lncurses
editormain.o: editormain.c datastructure.h filefunctions.h
	cc -Wall -c editormain.c
datstructure.o:  datastructure.c datastructure.h
	cc -Wall -c datastructure.c
filefunctions.o :  filefunctions.c datastructure.h filefunctions.h
	cc  -Wall -c filefunctions.c
