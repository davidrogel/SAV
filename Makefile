
LIBS= -lsfml-graphics -lsfml-window -lsfml-system
EXE= main


$(EXE): main.cpp
	$(CXX) main.cpp -o $(EXE) $(LIBS)

.PHONY:
	clear

clear:
	rm $(EXE)
