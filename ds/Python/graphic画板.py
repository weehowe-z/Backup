# -*- coding: cp936 -*-
import Tkinter            # ����Tkinterģ��
class MyButton:            # ���尴ť��
    def __init__(self,root,canvas,label,type):       # ���ʼ��
       self.root = root         # ��������ֵ
       self.canvas = canvas
       self.label = label
       if type == 0:          # �������ʹ�����ť
        button = Tkinter.Button(root,text = 'DrawLine',command = self.DrawLine)
       elif type == 1:
        button = Tkinter.Button(root,text = 'DrawArc',command = self.DrawArc)
       elif type == 2:
        button = Tkinter.Button(root,text = 'DrawRec',command = self.DrawRec)
       else :
        button = Tkinter.Button(root,text = 'DrawOval',command = self.DrawOval)
       button.pack(side = 'left')
    def DrawLine(self):          # DrawLine��ť�¼�������
       self.label.text.set('Draw Line')
       self.canvas.SetStatus(0)
    def DrawArc(self):          # DrawArc��ť�¼�������
       self.label.text.set('Draw Arc')
       self.canvas.SetStatus(1)
    def DrawRec(self):          # DrawRec��ť�¼�������
       self.label.text.set('Draw Rectangle')
       self.canvas.SetStatus(2)
    def DrawOval(self):          # DrawOval��ť�¼�������
       self.label.text.set('Draw Oval')
       self.canvas.SetStatus(3)
class MyCanvas:            # ����Canvas��
    def __init__(self,root):
       self.status = 0          # ��������ֵ
       self.draw = 0
       self.root = root
       self.canvas = Tkinter.Canvas(root,bg = 'white',      # ����Canvas���
         width = 600,
         height = 480)
       self.canvas.pack()
       self.canvas.bind('<ButtonRelease-1>',self.Draw)      # ���¼������
       self.canvas.bind('<Button-2>',self.Exit)      # ���¼����м�
       self.canvas.bind('<Button-3>',self.Del)       # ���¼����Ҽ�
       self.canvas.bind_all('<Delete>',self.Del)      # ���¼���Delete��
       self.canvas.bind_all('<KeyPress-d>',self.Del)      # ���¼���d��
       self.canvas.bind_all('<KeyPress-e>',self.Exit)      # ���¼���e��
    def Draw(self,event):          # ��ͼ�¼�������
       if self.draw == 0:          # �ж��Ƿ��ͼ
        self.x = event.x
        self.y = event.y
        self.draw = 1
       else:           # ����self.status���Ʋ�ͬͼ��
        if self.status == 0:
         self.canvas.create_line(self.x,self.y,event.x,event.y)
         self.draw = 0
        elif self.status == 1:
         self.canvas.create_arc(self.x,self.y,event.x,event.y)
         self.draw = 0
        elif self.status == 2:
         self.canvas.create_rectangle(self.x,self.y,event.x,event.y)
         self.draw = 0
        else:
         self.canvas.create_oval(self.x,self.y,event.x,event.y)
         self.draw = 0
    def Del(self,event):          # �������Ҽ���d����ɾ��ͼ��
       items = self.canvas.find_all()
       for item in items:
        self.canvas.delete(item)
    def Exit(self,event):          # �������м���e�����˳�
       self.root.quit()
    def SetStatus(self,status):         # ���û��Ƶ�ͼ��
       self.status = status
class MyLabel:            # �����ǩ��
    def __init__(self,root):         # ���ʼ��
       self.root = root         # ��������
       self.canvas = canvas
       self.text = Tkinter.StringVar()        # ���ɱ�ǩ���ñ���
       self.text.set('Draw Line')
       self.label = Tkinter.Label(root,textvariable = self.text,fg = 'red',width = 50)
       self.label.pack(side = 'left')
root = Tkinter.Tk()           # ����������
canvas = MyCanvas(root)           # ���ɻ�ͼ���
label = MyLabel(root)           # ���ɱ�ǩ
MyButton(root,canvas,label,0)          # ���ɰ�ť
MyButton(root,canvas,label,1)
MyButton(root,canvas,label,2)
MyButton(root,canvas,label,3)
root.mainloop()            # ������Ϣѭ��
