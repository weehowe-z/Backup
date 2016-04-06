#General Java Makefile
JAVAC=javac
sources = $(wildcard src/*.java)
classes = $(sources:.java=.class)

# all: $(classes)
all: GUI

clean :
	rm -f Downloads/*
	rm -rf FileShare/

# %.class : %.java
# $(JAVAC) $< -d .

Server :
	$(JAVAC) src/Server.java -d .

Client :
	$(JAVAC) src/Client.java -d .

GUI : Server Client
	$(JAVAC) src/GUI.java -d .
