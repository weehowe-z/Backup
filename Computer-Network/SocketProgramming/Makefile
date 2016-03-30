#General Java Makefile

JAVAC=javac
sources = $(wildcard src/*.java)
classes = $(sources:.java=.class)

all: $(classes)

clean :
	rm -f bin/*.class

DateSocket :
		$(JAVAC) src/DateSocket/*.java -d bin/

%.class : %.java
	$(JAVAC) $< -d bin/
