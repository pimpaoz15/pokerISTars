CC = gcc

TARGET = pokeristars

all:
	$(CC) -Wall -o $(TARGET) Analyze_Input.c Pokeristars.c Analyze_Hand_5.c Analyze_Hand_7.c Analyze_Hand_9.c Analyze_Hand_10.c Untie.c di_Mode.c Print_Results.c c_Mode.c s1_Mode.c dx_Mode.c

clean:
	rm $(TARGET)
