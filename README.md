# DPLL
A very simple DPLL Sat Solver that easy to understand.


## 1. How to Build
**Step 1:** Download the source code. For example,
~~~
$ git clone https://github.com/jacky860226/DPLL.git
~~~

**Step 2:** Go to the project root and build by
~~~
$ cd DPLL
$ make
~~~

### 1.1. Dependencies

* [GCC](https://gcc.gnu.org/) (version >= 7.5.0) or other working c++ compliers

## 2. How to run

~~~
$ ./DPLL [<input file>]
~~~

If there is no `<input file>`, it will use standard input.

### 2.1 Input format
The input is a SAT formula is DIMACS format. A detailed description can be found [here](http://www.satcompetition.org/2009/format-benchmarks2009.html).

### 2.2 Input example

Input:
```
p cnf 4 5
1 -2 0
2 -3 0
3 -4 0
1 4 0
-1 0
```

Output:
```
SAT
-1 -2 3 4 5 0
```