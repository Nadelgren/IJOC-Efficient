This folder contains C code to generate random instances of the Biobjective Mixed Integer Linear Program (BOMILP)
that are intended to be solvable very quickly, but have a extreme number of line segments in the Pareto frontier. 
See the IJOC paper for the problem formulation, if desired.

The C code can be compiled with gcc using the command "gcc write_ran_high_Pareto.c -o make_instance -lm"

The resulting executable takes two arguments:
  (1) A value for the parameter "N" -- The linear relaxation of the feasible set is 2 dimensional and designed 
  so that each 1-d face is a chord of a circle. N indicates the radius of the circle.
  (2) A value for the parameter "k" -- The number of chords to generate.
  
Running the executable generates an instance of BOMILP stored in two *.lp files, testp1.lp and testp2.lp. The two 
files have identical feasible sets, but different objectives.
