# C++ implementation of Paging

A C++ program that simulates a paging system using the aging algorithm.

#### A page table entry consists of 32 bits
```
R M P <---- Page frame number ---->
x x x xxxxxxxxxxxxxxxxxxxxxxxxxxxxx
where,
R = Referenced bit
M = Modified bit
P = Present/absent bit
Rest all bits are for the page frame number
```

### The aging algorithm

The NFU (Not Frequently Used) algorithm requires a software counter associated with each page,
initially zero. At each clock interrupt, the Operating System scans all pages in memory. For
each page, the R bit, which is 0 or 1, is added to the counter.

A simple modification to NFU can be made which is known as the aging algorithm. The modification
has two parts. First, the counters are each shifted right 1 bit before the R bit is added in.
Second, the R bit is added to the leftmost rather than the rightmost bit.


### Sample input file
```
16 4 32
2
0 w 40
1 w 40
1 r 5
0 r 50
1 w 200
0 r 170
```

All fields on a line are separated by whitespace.
The first line of the input file contains three integers: the number of virtual pages, the number of
physical page frames, and the size of a page. In the example file, there are 16 virtual
pages, 4 physical page frames, and the size of the page is 32 bytes.
The second line is the number of processes that will be running for the simulation. In the sample
input file, two processes will be running.
The remaining lines contain a virtual memory reference to be simulated. The first number is
the number of the process requesting the reference. The second field, either "r" or "w", indicates
if the reference is a read or a write. The last number is the virtual memory location being
requested.

### Compile
```
$ g++ -Wall -std=c++11 -o main.o *.cpp
```
### Execute
```
Usage: ./main.o <input_file>
```

**Requirements**
- gcc


[![Contact me on Codementor](https://www.codementor.io/m-badges/sandesh87/im-a-cm-b.svg)](https://www.codementor.io/@sandesh87?refer=badge)

