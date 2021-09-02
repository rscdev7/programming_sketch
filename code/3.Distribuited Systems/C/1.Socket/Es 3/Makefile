#TEMPLATE MAKEFILE PROGRAMMI C CL-SR

CC=gcc #Compilatore
CFLAGS=-g -Wall #Flags

SOURCE_FILE_1= Client.c #Programma Client
SOURCE_FILE_2=Server.c #Programma Server

SOURCE_FILES=Client.c Server.c #Lista di tutti i Sorgenti

EXEC_FILE_1= Client #Nome del Programma Client
EXEC_FILE_2= Server #Nome del Programma Server

EXEC_FILES=Client Server #Nomi di tutti i Programmi

$(EXEC_FILES): $(SOURCE_FILES)
	$(CC) $(CFLAGS) $(SOURCE_FILE_1) -o $(EXEC_FILE_1)  
	$(CC) $(CFLAGS) $(SOURCE_FILE_2) -o $(EXEC_FILE_2)

.PHONY: clean
clean:
	rm -f $(EXEC_FILES)
