def circulate_factorial(x):
    fact=1
    while x>0:
        fact*=x
        x=x-1
    return fact

def recursion_factorial(x):
    while x==0:
        return 1
    else:
        return x*recursion_factorial(x-1)
