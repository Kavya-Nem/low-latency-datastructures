#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 7
#
# make                         makes Words
# make DictionaryClient        makes DictionaryClient
# make clean                   removes all binaries
# make checkWords              runs Words in3 myout3 under valgrind
# make checkDictionaryClient   runs DictionaryClient under valgrind
#
#------------------------------------------------------------------------------

MAIN           = Words
MAINOBJ        = $(MAIN).o
MAINSRC        = $(MAIN).cpp
TEST           = DictionaryClient
TESTOBJ        = $(TEST).o
TESTSRC        = $(TEST).cpp
ADT            = Dictionary
ADTOBJ         = $(ADT).o
ADTSRC         = $(ADT).cpp
ADT_H          = $(ADT).h
COMPILE        = g++ -std=c++17 -Wall -c
LINK           = g++ -std=c++17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full
INFILE         = in3
OUTFILE        = myout3

$(MAIN) : $(MAINOBJ) $(ADTOBJ)
	$(LINK) $(MAIN) $(MAINOBJ) $(ADTOBJ)

$(MAINOBJ) : $(ADT_H) $(MAINSRC)
	$(COMPILE) $(MAINSRC)

$(TEST) : $(TESTOBJ) $(ADTOBJ)
	$(LINK) $(TEST) $(TESTOBJ) $(ADTOBJ)

$(TESTOBJ) : $(ADT_H) $(TESTSRC)
	$(COMPILE) $(TESTSRC)

$(ADTOBJ) : $(ADT_H) $(ADTSRC)
	$(COMPILE) $(ADTSRC)

clean :
	$(REMOVE) $(MAIN) $(MAINOBJ) $(TEST) $(TESTOBJ) $(ADTOBJ)

check$(MAIN) : $(MAIN)
	$(MEMCHECK) ./$(MAIN) $(INFILE) $(OUTFILE)

check$(TEST) : $(TEST)
	$(MEMCHECK) ./$(TEST)
