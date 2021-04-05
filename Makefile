
LIBS= -lsfml-graphics -lsfml-window -lsfml-system
EXE= main


all:
	g++ main.cpp -o $(EXE) $(LIBS)

.PHONY:
	clear

clear:
	rm $(EXE)
