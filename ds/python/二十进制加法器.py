# -*- coding: cp936 -*-
"""在二十进制中，我们除了使用数字0-9以外，还使用字母a-j(表示10-19)，
给定两个二十进制整数，求它们的和。
输入是两个二十进制整数，且都大于0，不超过100位；
输出是它们的和（二十进制），且不包含首0。"""

data1,data2 = [],[]
for i in range(0,10):
    data1.append(str(i))
for i in range(ord("A"),ord("A")+10):
    data2.append(chr(i))
    
def getNum():#获得数字
    while True:
        count = 0
        tnum = 0
        num = raw_input("Please input a binary-coded decimal word >> " )
        if len(num)>1000:
            continue
        for i in range(len(num)):
            if num[i] in data1:
                tnum+=int(num[i])*20**(len(num)-i-1)
            elif num[i] in data2:
                tnum+=(ord(num[i])-55)*20**(len(num)-i-1)
            else:
                count =1
                continue
        if count == 0:
            break
    return num,tnum

def modify(s):#建立对应关系
    for i in range(10,20):
        if s == i:
            s = chr(ord("A")+i-10)
            return s
    return s
                    
def trans(num):#将10进制数转换为20进制
    trannum=""
    while num!=0:
        s=modify(num%20)
        trannum=str(s)+trannum
        num=num/20
    return trannum

def main():
    num1,tnum1=getNum()
    num2,tnum2=getNum()
    num=tnum1+tnum2
    trannum=trans(num)
    print num1,"+",num2,"=",trannum

main()
    


    
