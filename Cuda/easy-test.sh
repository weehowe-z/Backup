#########################################################################
# File Name: easytest.sh
# Created Time: Mon 02 Nov 2015 06:46:41 PM CST
#########################################################################
#!/bin/bash
# nvcc a+b.cu
 nvcc A+B.cu
./a.out 1 1
./a.out 2 1
./a.out 3 1
./a.out 4 1
./a.out 5 1
./a.out 6 1
./a.out 7 1
./a.out 8 1
./a.out 9 3



rm a.out
