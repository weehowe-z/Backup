import winsound
from Tkinter import*
root=Tk()
c=Canvas(root,width=100,height=100,bg='white')
c.pack()
c.focus_set()
def so1(event):
    winsound.Beep(392, 200)
def la1(event):
    winsound.Beep(440, 200)
def si1(event):
    winsound.Beep(494, 200)
def do(event):
    winsound.Beep(523, 200)
def re(event):
    winsound.Beep(578, 200)
def mi(event):
    winsound.Beep(659, 200)
def fa(event):
    winsound.Beep(698, 200)
def so(event):
    winsound.Beep(784, 200)
def la(event):
    winsound.Beep(880, 200)
def si(event):
    winsound.Beep(988, 200)
def do2(event):
    winsound.Beep(1046, 200)
def re2(event):
    winsound.Beep(1175, 200)
def mi2(event):
    winsound.Beep(1318, 200)
def fa2(event):
    winsound.Beep(1397, 200)
def so2(event):
    winsound.Beep(1568, 200)



    
    

c.bind('q',so1)
c.bind('w',la1)
c.bind('e',si1)
c.bind('1',do)
c.bind('2',re)
c.bind('3',mi)
c.bind('4',fa)
c.bind('5',so)
c.bind('6',la)
c.bind('7',si)
c.bind('8',do2)
c.bind('9',re2)
c.bind('0',mi2)
c.bind('-',fa2)
c.bind('=',so2)
root.mainloop()
