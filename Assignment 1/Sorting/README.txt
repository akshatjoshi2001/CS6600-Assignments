Compile the code using the following
command:
gcc main.c -lm -o main.o
• The syntax for running the sorting program is as follows:
./main.o <sorting algorithm> <size of array>
• You can choose one of quick,radix,merge,bubble,selection for the sorting algorithm parameter.
• Example: To sort a random array of size 100 using quick sort run:
./main.o quick 100
• The python files analyze.py and plots.py have been provided for running cachegrind for the sorting algorithms
and generating the plots using the cachegrind output.
• All Cachegrind output is stored in the dump folder and plots are stored in the plots folder.