# -*- coding: cp936 -*-
"""�ڶ�ʮ�����У����ǳ���ʹ������0-9���⣬��ʹ����ĸa-j(��ʾ10-19)��
����������ʮ���������������ǵĺ͡�
������������ʮ�����������Ҷ�����0��������100λ��
��������ǵĺͣ���ʮ���ƣ����Ҳ�������0��"""

data1,data2 = [],[]
for i in range(0,10):
    data1.append(str(i))
for i in range(ord("A"),ord("A")+10):
    data2.append(chr(i))
    
def getNum():#�������
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

def modify(s):#������Ӧ��ϵ
    for i in range(10,20):
        if s == i:
            s = chr(ord("A")+i-10)
            return s
    return s
                    
def trans(num):#��10������ת��Ϊ20����
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
    


    
