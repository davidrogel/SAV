
LIBS= -lsfml-graphics -lsfml-window -lsfml-system
EXE= main


$(EXE): main.cpp
	g++ main.cpp -o $(EXE) $(LIBS)

.PHONY:
	clear

clear:
	rm $(EXE)
