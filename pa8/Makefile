#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 8
#
# make                         makes WordFrequency
# make Words                   makes Words
# make DictionaryTest          makes DictionaryTest
# make clean                   removes all binaries
# make checkWordFrequency      runs WordFrequency Gutenberg myout under valgrind
# make checkWords              runs Words in3 myout3 under valgrind
# make checkDictionaryTest     runs DictionaryTest under valgrind
#
#------------------------------------------------------------------------------

MAIN           = WordFrequency
MAINOBJ        = $(MAIN).o
MAINSRC        = $(MAIN).cpp
TEST1          = Words
TEST1OBJ       = $(TEST1).o
TEST1SRC       = $(TEST1).cpp
TEST2          = DictionaryTest
TEST2OBJ        = $(TEST2).o
TEST2SRC        = $(TEST2).cpp
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

$(TEST1) : $(TEST1OBJ) $(ADTOBJ)
	$(LINK) $(TEST1) $(TEST1OBJ) $(ADTOBJ)

$(TEST1OBJ) : $(ADT_H) $(TEST1SRC)
	$(COMPILE) $(TEST1SRC)

$(TEST2) : $(TEST2OBJ) $(ADTOBJ)
	$(LINK) $(TEST2) $(TEST2OBJ) $(ADTOBJ)

$(TEST2OBJ) : $(ADT_H) $(TEST2SRC)
	$(COMPILE) $(TEST2SRC)

$(ADTOBJ) : $(ADT_H) $(ADTSRC)
	$(COMPILE) $(ADTSRC)

clean :
	$(REMOVE) $(MAIN) $(MAINOBJ) $(TEST1) $(TEST1OBJ) $(TEST2) $(TEST2OBJ) $(ADTOBJ)

check$(MAIN) : $(MAIN)
	$(MEMCHECK) ./$(MAIN) Gutenberg.txt myout

check$(TEST1) : $(TEST1)
	$(MEMCHECK) ./$(TEST1) $(INFILE) $(OUTFILE)

check$(TEST2) : $(TEST2)
	$(MEMCHECK) ./$(TEST2)
