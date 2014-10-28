CC=gcc
CFLAGS=
#-O0 pour pas d'optimisation (valgrind)
LDFLAGS=
EXEC=bibligraphe

all: $(EXEC)

bibligraphe: graphe.o liste.o main.o
	$(CC) -o $@ $^ $(LDFLAGS)

graphe.o: liste.h

main.o: graphe.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
			
