export CXX	:= g++

CXXFLAGS 	:= -O3 -mavx -mavx2 -g --static-pie -std=c++14 -fmax-errors=100 -fno-omit-frame-pointer -fPIE -lm -no-pie -fPIC

export DESTDIR	:= $(CURDIR)/bin
export OBJDIR	:= $(CURDIR)/obj
TABLES		:= $(CURDIR)/tables

OUT	  	:= $(DESTDIR)/main

.PHONY: all hash list text main
all: hash list text main

hash: | $(DESTDIR) $(OBJDIR) $(TABLES)
	@ echo ------ COMPILE hash ------
	@ cd $(CURDIR)/src/hash && $(MAKE)

list: | $(DESTDIR) $(OBJDIR) $(TABLES)
	@ echo ------ COMPILE list ------
	@ cd $(CURDIR)/src/list && $(MAKE)

text: | $(DESTDIR) $(OBJDIR) $(TABLES)
	@ echo ------ COMPILE text ------
	@ cd $(CURDIR)/src/text && $(MAKE)

main: | $(DESTDIR) $(OBJDIR) $(TABLES)
	@ echo ------ COMPILE main ------
	@ $(CXX) -c $(CURDIR)/src/main.cpp -o $(OBJDIR)/main.o $(CXXFLAGS)
	@ $(CXX) $(OBJDIR)/main.o $(OBJDIR)/hashtable.o $(OBJDIR)/hashfuncs.o $(OBJDIR)/listPtr.o $(OBJDIR)/textProcessing.o $(OBJDIR)/bkdr.o -o $(OUT) $(CXXFLAGS)

.PHONY: clean
clean:
	rm -rf $(DESTDIR) $(OBJDIR) $(TABLES)

$(DESTDIR):
	@ mkdir $(DESTDIR)
$(OBJDIR):
	@ mkdir $(OBJDIR)
$(TABLES):
	@ mkdir $(TABLES)
