CXX         ?= g++
CXXASM		?= nasm
CXXFLAGS    ?= -g --static-pie -std=c++14 -fmax-errors=100 -fno-omit-frame-pointer -fPIE -lm -pie

CUSTOM_FLAGS    ?= 	-Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++0x-compat \
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
			-fsanitize=address -fsanitize=alignment \
			-fsanitize=bool -fsanitize=bounds -fsanitize=enum \
			-fsanitize=float-cast-overflow -fsanitize=float-divide-by-zero \
			-fsanitize=integer-divide-by-zero -fsanitize=leak \
			-fsanitize=nonnull-attribute -fsanitize=null -fsanitize=object-size \
			-fsanitize=return -fsanitize=returns-nonnull-attribute -fsanitize=shift \
			-fsanitize=signed-integer-overflow -fsanitize=undefined \
			-fsanitize=unreachable -fsanitize=vla-bound -fsanitize=vptr

SRC	:= hashtable.cpp hashfuncs.cpp
OBJ	:= $(addprefix $(OBJDIR)/, $(SRC:.cpp=.o))

all: $(OBJ)

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	@ $(CXX) -c $^ -o $@ $(CXXFLAGS) $(CUSTOM_FLAGS)
