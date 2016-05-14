def iterative_combination(n,k):
    if n<k:             #if n<k 
        return 0
    o,p,q=1,1,1
    for i in range(1,n+1):  #calculate fenzi
        o*=i
    for i in range(1,k+1):  #calculate fenmu
        p*=i
    for i in range(1,n-k+1):#calculate fenmu
        q*=i
    return o/(p*q)          

def recursion_combionation(n,k):
    if n<k:     #if n<k Cnk
        return 0
    if k==1:        #if k==1 Cnk
        return n
    return (recursion_combionation(n-1,k-1)+recursion_combionation(n-1,k))#recursion

n=input("input n:")
k=input("input k:")
print recursion_combionation(n,k)
print iterative_combination(n,k)
