#TEMPLATE MAKEFILE PROGRAMMI C CL-SR

CC=javac #Compilatore

SOURCE_FILE_1= Client.java #Programma Client
SOURCE_FILE_2=Server.java #Programma Server

SOURCE_FILES=Client.java Server.java #Lista di tutti i Sorgenti

EXEC_FILES=Client.class Server.class #Nomi di tutti i Programmi

$(EXEC_FILES): $(SOURCE_FILES)
	$(CC) $(SOURCE_FILE_1)
	$(CC) $(SOURCE_FILE_2)

.PHONY: clean
clean:
	rm -f $(EXEC_FILES)
