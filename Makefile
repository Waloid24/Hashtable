export CXX	:= g++

CXXFLAGS 	:= -g --static-pie -std=c++14 -fmax-errors=100 -fno-omit-frame-pointer -fPIE -lm -no-pie -fPIC

export CUSTOM_FLAGS := -O2

# 				-mavx -mavx2 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++0x-compat \
# 				-Wc++11-compat -Wc++14-compat -Wcast-align -Wcast-qual -Wchar-subscripts \
# 				-Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body \
# 				-Wfloat-equal 	-Wformat-nonliteral -Wformat-security -Wformat-signedness \
# 				-Wformat=2 -Winline -Wlarger-than=8192 -Wlogical-op -Wmissing-declarations \
# 				-Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith \
# 				-Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo \
# 				-Wstack-usage=8192 -Wstrict-null-sentinel -Wstrict-overflow=2 \
# 				-Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types \
# 				-Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef \
# 				-Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros \
# 				-Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing \
# 				-Wno-old-style-cast -Wno-varargs -fcheck-new -fsized-deallocation \
# 				-fstack-protector -fstrict-overflow -flto-odr-type-merging \
# 				-fsanitize=address -fsanitize=alignment \
# 				-fsanitize=bool -fsanitize=bounds -fsanitize=enum \
# 				-fsanitize=float-cast-overflow -fsanitize=float-divide-by-zero \
# 				-fsanitize=integer-divide-by-zero -fsanitize=leak \
# 				-fsanitize=nonnull-attribute -fsanitize=null -fsanitize=object-size \
# 				-fsanitize=return -fsanitize=returns-nonnull-attribute -fsanitize=shift \
# 				-fsanitize=signed-integer-overflow -fsanitize=undefined \
# 				-fsanitize=unreachable -fsanitize=vla-bound -fsanitize=vptr

export DESTDIR	:= $(CURDIR)/bin
export OBJDIR	:= $(CURDIR)/obj
TABLES		:= $(CURDIR)/tables
OUT	  	:= $(DESTDIR)/main

isLog 		 = yesLogs

.PHONY: all hash list text logs main

# ifeq ($(isLog), yesLogs)

all: hash list text logs main

# else
#
# all: hash list text main
#
# endif

hash: | $(DESTDIR) $(OBJDIR) $(TABLES)
	@ echo ------ COMPILE hash ------
	@ cd $(CURDIR)/src/hash && $(MAKE)

list: | $(DESTDIR) $(OBJDIR) $(TABLES)
	@ echo ------ COMPILE list ------
	@ cd $(CURDIR)/src/list && $(MAKE)

text: | $(DESTDIR) $(OBJDIR) $(TABLES)
	@ echo ------ COMPILE text ------
	@ cd $(CURDIR)/src/text && $(MAKE)

logs: | $(DESTDIR) $(OBJDIR) $(TABLES)
	@ echo ------ COMPILE logs ------
	@ cd $(CURDIR)/logs && $(MAKE)

# ifeq ($(isLog), yesLog)

main: | $(DESTDIR) $(OBJDIR) $(TABLES)
	@ echo ------ COMPILE main ------
	@ $(CXX) -c $(CURDIR)/src/main.cpp -o $(OBJDIR)/main.o $(CXXFLAGS) $(CUSTOM_FLAGS)
	@ $(CXX) $(OBJDIR)/main.o $(OBJDIR)/hashtable.o $(OBJDIR)/hashfuncs.o $(OBJDIR)/listPtr.o $(OBJDIR)/textProcessing.o $(OBJDIR)/bkdr.o $(OBJDIR)/logs.o -o $(OUT) $(CXXFLAGS) $(CUSTOM_FLAGS)

# else
#
# main: | $(DESTDIR) $(OBJDIR) $(TABLES)
# 	@ echo ------ COMPILE main ------
# 	@ $(CXX) -c $(CURDIR)/src/main.cpp -o $(OBJDIR)/main.o $(CXXFLAGS)
# 	@ $(CXX) $(OBJDIR)/main.o $(OBJDIR)/hashtable.o $(OBJDIR)/hashfuncs.o $(OBJDIR)/listPtr.o $(OBJDIR)/textProcessing.o $(OBJDIR)/bkdr.o -o $(OUT) $(CXXFLAGS)
#
# endif

.PHONY: clean
clean:
	rm -rf $(DESTDIR) $(OBJDIR) $(TABLES)

$(DESTDIR):
	@ mkdir $(DESTDIR)
$(OBJDIR):
	@ mkdir $(OBJDIR)
$(TABLES):
	@ mkdir $(TABLES)
