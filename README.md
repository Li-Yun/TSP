# TSP

The program is to solve Travel Sellman Problem (TSP) using a genetic algorithm. This program is implemented by C++, and users must compile the program and prepare an input file before they execute it. Please follow the following instructions for compiling this program and preparing an input file. <br />

Step 1: Text file preparation:
Before running genetic algorithm program, users have to parepare a text file of
recoding some information: the number of cities, locations of each city, and a 
started city. In particular, please use the following format to record all of 
the messages. <br />

Format: <br />
[ number of cities ] <br />
[ city number ] [ x-coordinate ] [ y-coordinate ] <br />
[ start city number ] <br />

For example: <br />
5 <br />
1 20 100 <br />
2 40 20 <br />
3 60 80 <br />
4 120 80 <br />
5 160 200 <br />
1 <br />

Step 2: Compiling genetic algorithm program: <br />
After preparing a text file of recoding city's information, the next step is 
compiling whole program. Please use the following command to compile and run 
this program. <br />

1. compile the program: <br />
g++ -std=c++11 main.cpp -o file_name <br />
For example: <br />
g++ -std=c++11 main.cpp -o output <br />

2. run the program: <br />
./file_name text_file_name [optional arguments] <br />

The order of optional arguments is: <br />
visualization_flag population_flag geneartion_number population_size selection_size mutation_rate <br />

For example: <br />
./output city.txt <br />

Note: Users can try different parameter values by typing values optional <br />
arguments. Optional arguments include: <br />
1. visualization flag (default: 0) <br />
2. population flag (default: 0) <br />
3. geneartion number (default: 100) <br />
4. population size (default: 20) <br />
5. the size of selection pool in selection operation (default: 10) <br />
6. mutation rate (default: 0.015) <br />

Have fun. <br />

