# Learning Makefiles from Stian

# Label
all: Compiler # dependency* technically what we're going to compile

# Specify what happens with the dependency
Compiler:
	g++ -o output infix-postfix.cpp
	make run

run:
	./output