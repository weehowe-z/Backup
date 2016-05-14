from Tkinter import *
from math import *

def Koch_curves(n):  #main moudle
    global x,y,degree,length,num
    if n==0:  #n=0 draw for length steps 
        c.create_line(x,y,x+length*cos(degree),y-length*sin(degree))
        x+=length*cos(degree)
        y-=length*sin(degree)
    else:
        length/=3        #use recursion to draw curves
        Koch_curves(n-1)
        degree+=pi/3
        Koch_curves(n-1)
        degree-=pi*2/3
        Koch_curves(n-1)
        degree+=pi/3
        Koch_curves(n-1)
        length*=3
def Curves():                #to get the number
    Koch_curves(num.get())

root =Tk() 
c=Canvas(root,width=800,height=600,bg='white') #pack canvas
c.pack()
num=IntVar()   #int num to 0
num.set(0)
a=Label(root,text="enter the num below and press the bottom to draw",fg="red")
a.pack()
b=Button(root,width=20,text="press me!",command=Curves)  #pack event buttom
b.pack()
e=Entry(root,textvariable=num)   #pack enter
e.pack() 
x,y,degree,length=40.0,400.0,0,800    #int

root.mainloop() 
