from Tkinter import *
from math import sin,cos,pi
from time import sleep

def main():
    root = Tk()
    c = Canvas(root,width=300,height=200,bg='white')
    c.pack()

    orbit = c.create_oval(50,50,250,150)
    sun = c.create_oval(110,85,140,115,fill='red')
    earth = c.create_oval(245,95,255,105,fill='blue')
    moon = c.create_oval(265,98,270,103)
    eX = 250      # earth's X
    eY = 100      # earth's Y
    m2eX = 20     # moon's X relative to earth
    m2eY = 0      # moon's Y relative to earth
    t = 0

    global speed
    speed=0.01
    
    def slow():
        global speed
        if speed>=0.001:  
            speed-=0.001
    def fast():
        global speed
        speed+=0.001
    def stop():
        global speed
        speed=0

    Button1=Button(root,text="faster",command=fast)
    Button1.pack()
    Button2=Button(root,text="slower",command=slow)
    Button2.pack()
    Button3=Button(root,text=" stop ",command=stop)
    Button3.pack()
    
    Label(root,text="Animation by Zwh,Thank you!",fg="red",width=40).pack()
    
    while True:
        t = t + speed*pi
        new_eX = 150 + 100 * cos(t)
        new_eY = 100 - 50 * sin(t)   
        new_m2eX = 20 * cos(12*t)
        new_m2eY = -15 * sin(12*t)
        
        edx = new_eX - eX
        edy = new_eY - eY
        mdx = new_m2eX - m2eX
        mdy = new_m2eY - m2eY
  
        c.move(earth,edx,edy)
        c.move(moon,mdx+edx,mdy+edy)
        c.update()

        eX = new_eX
        eY = new_eY
        m2eX = new_m2eX
        m2eY = new_m2eY

        sleep(0.04)
main()
