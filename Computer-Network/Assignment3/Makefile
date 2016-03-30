#General Java Makefile
JAVAC=javac
sources = $(wildcard src/*.java)
classes = $(sources:.java=.class)

all: $(classes)

clean :
	rm -f FileSocket/*.class

%.class : %.java
	$(JAVAC) $< -d .
