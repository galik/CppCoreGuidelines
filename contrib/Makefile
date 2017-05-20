

CXXFLAGS += \
	-std=c++14 \
	-g3 -O0 \
	-Wconversion \
	-Wall -Wextra \
	-pedantic-errors \
	-Wstrict-aliasing \
	-Wno-unused-parameter

PROGRAMS := \
	extract-sections

all: $(PROGRAMS)

run: all
	./extract-sections ../CppCoreGuidelines.md

clean:
	$(RM) $(PROGRAMS) *.md