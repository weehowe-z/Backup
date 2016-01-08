#########################################################################
# File Name: easytest.sh
# Created Time: Mon 02 Nov 2015 06:46:41 PM CST
#########################################################################
#!/bin/bash
# nvcc a+b.cu
 nvcc A+B.cu
#     scale   threads per block
./a.out 100000 1
./a.out 100000 4
./a.out 100000 20
./a.out 200 30
./a.out 20  9


rm a.out
