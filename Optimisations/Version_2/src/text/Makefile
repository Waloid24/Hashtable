CXX             ?= g++
CXXFLAGS        ?= -O3 -mavx -mavx2 -g --static-pie -std=c++14 -fmax-errors=100 -fno-omit-frame-pointer -fPIE -lm -pie

SRC	:= textProcessing.cpp
OBJ	:= $(addprefix $(OBJDIR)/, $(SRC:.cpp=.o))

all: $(OBJ)

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	@ $(CXX) -c $^ -o $@ $(CXXFLAGS)
