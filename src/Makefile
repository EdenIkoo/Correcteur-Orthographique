CC = gcc
CFLAGS = -ansi -pedantic -Wall

correcteur_2: Listes.o ArbreBK.o Levenshtein.o correcteur_2.o
	$(CC) -o correcteur_2 $(CFLAGS) Listes.o ArbreBK.o Levenshtein.o correcteur_2.o

correcteur_1: Listes.o ATR.o Levenshtein.o correcteur_1.o
	$(CC) -o correcteur_1 $(CFLAGS) Listes.o ATR.o Levenshtein.o correcteur_1.o

correcteur_0: Listes.o ATR.o correcteur_0.o
	$(CC) -o correcteur_0 $(CFLAGS) Listes.o ATR.o correcteur_0.o

correcteur_2.o: correcteur_2.c Listes.h ArbreBK.h Levenshtein.h
	$(CC) -c $(CFLAGS) correcteur_2.c

correcteur_1.o: correcteur_1.c Listes.h ATR.h Levenshtein.h
	$(CC) -c $(CFLAGS) correcteur_1.c

correcteur_0.o: correcteur_0.c Listes.h ATR.h
	$(CC) -c $(CFLAGS) correcteur_0.c

Listes.o: Listes.c Listes.h
	$(CC) -c $(CFLAGS) Listes.c

Levenshtein.o: Levenshtein.c Levenshtein.h ATR.h Listes.h
	$(CC) -c $(CFLAGS) Levenshtein.c

ATR.o: ATR.c ATR.h
	$(CC) -c $(CFLAGS) ATR.c

ArbreBK.o: ArbreBK.c ArbreBK.h Levenshtein.h Listes.h
	$(CC) -c $(CFLAGS) ArbreBK.c

clean:
	rm -f *.o
	rm correcteur_2
	rm correcteur_1
	rm correcteur_0