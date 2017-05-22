#======================================================
# /contrib/Makefile
#-------------------------------------------------------
# Assums every source file is a whole program and
# compiles each one to an executable of the same name.
#

# Chance to add your personal flags
-include Makefile.local

CXXFLAGS += \
	-std=c++14 \
	-Wconversion \
	-Wall -Wextra \
	-pedantic-errors \
	-Wstrict-aliasing \
	-Wno-unused-parameter

PROGRAMS := $(patsubst %.cpp,%,$(wildcard *.cpp))

all: $(PROGRAMS)

clean:
	$(RM) $(PROGRAMS)
	