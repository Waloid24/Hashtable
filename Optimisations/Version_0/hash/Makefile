CXX             ?= g++
CXXASM		?= nasm
CXXFLAGS        ?= -mavx -mavx2 -g --static-pie -std=c++14 -fmax-errors=100 -fno-omit-frame-pointer -fPIE -lm -pie

SRC	:= hashtable.cpp hashfuncs.cpp
SRC_ASM := bkdr.asm
OBJ	:= $(addprefix $(OBJDIR)/, $(SRC:.cpp=.o))
hashBkdr:= $(addprefix $(OBJDIR)/, $(SRC_ASM:.asm=.o))

all: $(OBJ) $(hashBkdr)

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	 $(CXX) -c $^ -o $@ $(CXXFLAGS)

$(OBJDIR)/%.o: %.asm | $(OBJDIR)
	$(CXXASM) -f elf64 $^ -o $@
