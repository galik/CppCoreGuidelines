

CXXFLAGS += \
	-std=c++14 \
	-g0 -O3 \
	-Wconversion \
	-Wall -Wextra \
	-pedantic-errors \
	-Wstrict-aliasing \
	-Wno-unused-parameter

PROGRAMS := \
	extract-sections \
	add-github-syntax-highlights

all: $(PROGRAMS)

run: all
	./add-github-syntax-highlights < ../CppCoreGuidelines.md > ../CppCoreGuidelinesSH.md 
	./extract-sections ../CppCoreGuidelinesSH.md ../sections

clean:
	$(RM) $(PROGRAMS)