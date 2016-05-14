def recursion_Fibonacci(x):
    while x<=2:
        return 1
    return (recursion_Fibonacci(x-1)+recursion_Fibonacci(x-2))

def circulate_Fibonacci(x):
    if x<=2:
        return 1
    Fib=[0]*x
    Fib[0]=1          #deifne 
    Fib[1]=1
    for i in range(2,x):
        Fib[i]=Fib[i-1]+Fib[i-2]
    return Fib[x-1]

def loop_Fibonacci(x):
    previous=1
    current=1
    for i in range(x-2):
        previous,current=current,previous+cuurent
    return previous
