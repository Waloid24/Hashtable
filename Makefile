export CXX	:= g++

CXXFLAGS 	:= -mavx -mavx2 -g --static-pie -std=c++14 -fmax-errors=100 \
-Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++0x-compat \
-Wc++11-compat -Wc++14-compat -Wcast-align -Wcast-qual -Wchar-subscripts \
-Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body \
-Wfloat-equal 	-Wformat-nonliteral -Wformat-security -Wformat-signedness \
-Wformat=2 -Winline -Wlarger-than=8192 -Wlogical-op -Wmissing-declarations \
-Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith \
-Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo \
-Wstack-usage=8192 -Wstrict-null-sentinel -Wstrict-overflow=2 \
-Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types \
-Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef \
-Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros \
-Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing \
-Wno-old-style-cast -Wno-varargs -fcheck-new -fsized-deallocation \
-fstack-protector -fstrict-overflow -flto-odr-type-merging \
-fno-omit-frame-pointer -fPIE -fsanitize=address -fsanitize=alignment \
-fsanitize=bool -fsanitize=bounds -fsanitize=enum \
-fsanitize=float-cast-overflow -fsanitize=float-divide-by-zero \
-fsanitize=integer-divide-by-zero -fsanitize=leak \
-fsanitize=nonnull-attribute -fsanitize=null -fsanitize=object-size \
-fsanitize=return -fsanitize=returns-nonnull-attribute -fsanitize=shift \
-fsanitize=signed-integer-overflow -fsanitize=undefined \
-fsanitize=unreachable -fsanitize=vla-bound -fsanitize=vptr -lm -no-pie -fPIC

export DESTDIR	:= $(CURDIR)/bin
export OBJDIR	:= $(CURDIR)/obj
TABLES		:= $(CURDIR)/tables

OUT	  := $(DESTDIR)/main

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
	@ $(CXX) $(OBJDIR)/main.o $(OBJDIR)/hashtable.o $(OBJDIR)/listPtr.o $(OBJDIR)/textProcessing.o -o $(OUT) $(CXXFLAGS)

.PHONY: clean
clean:
	rm -r $(DESTDIR) $(OBJDIR)

$(DESTDIR):
	@ mkdir $(DESTDIR)
$(OBJDIR):
	@ mkdir $(OBJDIR)
$(TABLES):
	@ mkdir $(TABLES)
