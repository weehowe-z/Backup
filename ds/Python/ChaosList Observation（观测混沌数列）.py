"""
Created on 2014 JAN 15
author: Weehowe.Z
"""
def printword(word):
    print word.center(27)
def printtitle(num):
    print 
    printword("Chaos List ver1.0")
    print
    print "%.2f%10.2f%10.2f" %(num-0.01,num,num+0.01)
    print "-"*27
def printlist(base,num,times):
    num1,num2,num3=num-0.01,num,num+0.01
    for i in range(times):
        num1 = chaosformula(base,num1)
        num2 = chaosformula(base,num2)
        num3 = chaosformula(base,num3) 
        print "%.5f%10.5f%10.5f" %(num1,num2,num3)
def chaosformula(base,num):
    num = base*num*(1-num)
    return num
def chaos():
    base=input("Please enter a base:")
    num=round(input("Please enter your number in (0,1):"),2)
    times=input("How many times would you have?:")
    printtitle(num)
    printlist(base,num,times)
    print
    printword("Created on 2014 JAN 15")
    printword("author: Weehowe.Z")
chaos()
