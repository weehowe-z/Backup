# -*- coding: cp936 -*-
"""һ�ֱ�����Ϸ�Ǵ�1��ʼ�����������������7�ı�����7��14��21��28������
���߰�������7������7��17��27��37�������������ִ�������������ܱ�����
��������������m�����֣������������m�����ֵĵ�һ����������������Ǽ���
���磬���������������������֣���С�Ŀ���������������27��28��������27��
����m, �����m�����������ֵ�һ�����������С���ܵ�����"""

def mod7(num):#�ж�����
    if num % 7 == 0:
        return True
    return False

def has7(num):#�жϺ���
    num=str(num)
    for i in range(len(num)):
        if num[i] == "7":
            return True
    return False

def output(num,time):#�������
    print "These numbers are:", 
    for i in range(time):
        print num - time + i + 1,

def clap(time):#���ּ��ж�
    num = 1
    clap = 0
    while True:
        if mod7(num) or has7(num):
            clap += 1
        else:
            clap = 0
        if clap == time:
           output(num,time)
           break
        num += 1

def main():
    time = 0
    while True:
        try:
            time = input("Please enter clap times (positive integer) >> ")
        except NameError:
            print "Enter positive integer Please! "
        if time > 0 and type(time) == int:
            break
    clap(time)

main()
    

        
