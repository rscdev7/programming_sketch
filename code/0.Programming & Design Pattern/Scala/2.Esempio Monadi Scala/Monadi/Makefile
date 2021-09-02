CC				= scalac

SOURCE_LIBS  	= ./Monad/LazyMonad.scala ./Monad/Trasformations/package.scala
SOURCE_MAIN     = tester.scala
EXEC			= Main

CLEAN_1  		= *.class
CLEAN_2			= ./Monad/*.class
CLEAN_3			= ./Monad/Trasformations/Trasform/


compile:
	$(CC) $(SOURCE_LIBS) 
	$(CC) $(SOURCE_MAIN) 

exec:
	scala $(EXEC)


.PHONY: clean
clean:
	rm $(CLEAN_1)
	rm $(CLEAN_2)
	rm -r $(CLEAN_3)
