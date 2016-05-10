#########################################################################
# File Name: easytest.sh
# Created Time: Mon 02 Nov 2015 06:46:41 PM CST
#########################################################################
#!/bin/bash
nvcc string_matching.cu

rm output/*.txt
./a.out testCase/1/input.txt output/output1.txt
./a.out testCase/2/input.txt output/output2.txt
./a.out testCase/3/input.txt output/output3.txt
./a.out testCase/4/input.txt output/output4.txt
./a.out testCase/5/input.txt output/output5.txt
./a.out testCase/6/input.txt output/output6.txt
./a.out testCase/7\ large\ pattern/input.txt output/output7.txt



# gcc bruteforce.cpp -lstdc++


rm a.out
