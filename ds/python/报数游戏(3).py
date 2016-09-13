# -*- coding: cp936 -*-
"""一种报数游戏是从1开始连续报数，如果报到7的倍数（7，14，21，28……）
或者包含数字7的数（7，17，27，37……）就用拍手代替这个数而不能报出。
假设你连续听到m声拍手，问造成你听到m声拍手的第一下拍手所代表的数是几？
例如，你听到了两次连续的拍手，最小的可能这两次拍手是27和28，因此输出27。
输入m, 输出这m次连续的拍手第一下所代表的最小可能的数。"""

def mod7(num):#判断整除
    if num % 7 == 0:
        return True
    return False

def has7(num):#判断含有
    num=str(num)
    for i in range(len(num)):
        if num[i] == "7":
            return True
    return False

def output(num,time):#输出数字
    print "These numbers are:", 
    for i in range(time):
        print num - time + i + 1,

def clap(time):#拍手及判断
    num = 1
    clap = 0
    while True:
        if mod7(num) or has7(num):
            clap += 1
        else:
            clap = 0
        if clap == time:
           output(num,time)
           break
        num += 1

def main():
    time = 0
    while True:
        try:
            time = input("Please enter clap times (positive integer) >> ")
        except NameError:
            print "Enter positive integer Please! "
        if time > 0 and type(time) == int:
            break
    clap(time)

main()
    

        
