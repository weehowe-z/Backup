#########################################################################
# File Name: easytest.sh
# Created Time: Mon 02 Nov 2015 06:46:41 PM CST
#########################################################################
#!/bin/bash
# nvcc a+b.cu
 nvcc A+B.cu
#     scale   threads per block
# ./a.out 100000 1
# ./a.out 100000 4
# ./a.out 100000 20
# ./a.out 200 30
./a.out 200000000  10000
./a.out 200000000  100000
./a.out 200000000  900000
./a.out 200000000  1
# gcc bruteforce.cpp -lstdc++


rm a.out
