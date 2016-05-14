#进制转换(10进制以下)
def trans(num,dex):
    trannum=""
    while num!=0:
        s=num%dex
        trannum=str(s)+trannum
        num=num/dex
    return trannum
#判断回文
def pal(num):
    if num =="":
        return True
    if num[0]== num[-1]:
        return pal(num[1:-1])
    else:
        return False
#多重回文
def multipal(num):
    key=0
    for dex in range(2,11):
        k=trans(num,dex)
        if pal(k)==True:
            key=key+1
        if key==2:
            return True
    return False

def main(n,s):
    while n>0:
        s+=1
        if multipal(s):
            print s
            n=n-1
        
