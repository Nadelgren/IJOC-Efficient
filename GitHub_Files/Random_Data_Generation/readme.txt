This folder contains C code to generate random data that is intended to simulate solutions to a Biobjective 
Mixed Integer Linear Program as they are discovered by a Branch-and-Bound solver. 

The C code can be compiled with gcc using the command "gcc generate_data_from_seed.c -o generate_data -lm"

The resulting executable takes four arguments:
  (1) A filename containing seeds for a random number generator
  (2) The number of seeds to be read from the file
  (3) A value for the parameter "mu" -- Larger "mu" values result in greater separation between solutions 
      generated early and late in the data generation (see the IJOC paper for further explanation)
  (4) A value for the parameter "N" -- A maximum number of solutions to be generated
  
Running the executable generates a new file (in the current directory) entitled "input_data.txt"
Each line of the file represents either a singleton or a line segment in R^2, specified by six data values,
space delimited:
  (1) binary indicator of singleton vs. segment -- 1 = singleton, 2 = segment
  (2) x-value of first point
  (3) y-value of first point
  (4) x-value of second point (0 if a singleton)
  (5) y-value of second point (0 if a singleton)
  (6) slope of segment (0 is a singleton) -- Note: No segments with actual 0 slope are generated 
