

CXXFLAGS += \
	-std=c++14 \
	-Wconversion \
	-Wall -Wextra \
	-pedantic-errors \
	-Wstrict-aliasing \
	-Wno-unused-parameter

PROGRAMS := \
	extract-sections

all: $(PROGRAMS) run

run:
	./extract-sections ../CppCoreGuidelines.md

clean:
	$(RM) $(PROGRAMS) *.md