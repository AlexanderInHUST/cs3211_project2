# cs3211_project2

A CS3211 project.

## Build

```
make seq // for sequential version
```
or 
```
make par // for parallel version
```

## Run

```
./simulation.seq [input_file_name] [prefix_of_output_files] [size_n]
```

or

```
mpirun -np [size_n * size_n] ./simulation.par [input_file_name] [prefix_of_output_files]
```

## Example

```
./simulation.seq input.in ./test 2
```

or 

```
mpirun -np 9 ./simulation.par input.in ./test
```

Then the program gets input data from input.in and generates output files at current folder named test1.ppm, test2.ppm, test3.ppm......... until end.
