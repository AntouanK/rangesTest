rangesTest
==========

simple C++ test

The program reads a list of number pairs representing closed ranges from a file called "extents.txt". 
It also reads a list of points from "numbers.txt".  

The results are the hits each number has in all the ranges.

We can have the results, in any file we want, simply by giving the -o flag with our filename


simple brute force version in demo.cpp
---------------------------------------
usage

```g++ demo.cpp -o demo && ./demo -o res.txt```
