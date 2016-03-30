#General Java Makefile

JAVAC=javac
# sources = $(wildcard src/*.java)
# classes = $(sources:.java=.class)

all: FileSocket

clean :
	rm -f bin/*/*.class

DateSocket :
		$(JAVAC) src/DateSocket/*.java -d bin/

FileSocket:
		$(JAVAC) src/FileSocket/*.java -d bin/



# %.class : %.java
#   $(JAVAC) $< -d bin/
