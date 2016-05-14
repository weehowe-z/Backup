import string
def standard(x):
    x=x.upper()         #Capitalize
    delset = string.punctuation     
    x =x.translate(None,delset)    #del set
    x=x.replace(" ","")           #del " "
    return x                      
def recursion_palindrome(x):
    if x=="":           
        return 1                    #1 for it is 
    if x[0]==x[-1]:          # compare first and last letter
        return recursion_palindrome(x[1:-1])   #same and recursion
    else:          
        return 0        #0 for it isn't
def main():
    x=raw_input("Please input a sentence:")
    x=standard(x)
    jud=recursion_palindrome(x)
    if jud==1:             #judge whether it is
        print "It's palindrome."
    else:
        print "It's not palindrome."
main()
