CC=ghc

DRIVER				= main.hs
TESTER				= tester.hs

LIBRARY_FILES		= Tree.hs

DRIVER_EXEC			= driver
TESTER_EXEC			= tester


driver:$(DRIVER) $(LIBRARY_FILES)	
	$(CC) -o  $(DRIVER_EXEC) $(DRIVER) $(LIBRARIES_FILES)	

run_driver:$(DRIVER_EXEC)
	./$(DRIVER_EXEC)


test:$(TESTER) $(LIBRARY_FILES) 
	$(CC) -o  $(TESTER_EXEC) $(TESTER) $(LIBRARY_FILES)

run_test:$(TESTER_EXEC)
	./$(TESTER_EXEC)


.PHONY: clean
clean:
	rm -f *.o
	rm -f *.hi
	rm -f $(DRIVER_EXEC)
	rm -f $(TESTER_EXEC)