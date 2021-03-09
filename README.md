--Files---
Main.cpp: this is the main program which contains both the memory and processor
Sample5.txt : contains the instructions file I made
Sample1.txt - Sample4.txt : These are the files that are provided by the project to run
ReadMe.txt: this file provides information about the file structure of the program and how to compile the program

TO COMPILE AND RUN
1. Open the terminal and change to the directory where main.cpp and the sample files are.

2. Type the following to compile:

g++ main.cpp -std=c++0x -o main

	or
g++ main.cpp -std=c++0x 


3. To run program do the following:
./main "filename" "timerINT"
	or
./a.out "filename" "timerINT"

Note the timer is has to be an integer. The timer represents the amount of instructions executed to trigger an interupt.  
