# -*- coding: cp936 -*-
"""���������΢���Ӧ�ʵ����������ʵ�����У�����Ҳ�����ܿ���һЩ���޹�����ַ�����
 ���´ʵ��޷�������¼�������������Ƿ���Դ��޹�����ַ�������ȡ������ĵ����أ�
 ������һ���ַ���"iinbinbing"����ȡ��ͬλ�õ��ַ���b������i������n������g����ϳɵ���"bing"��
 ����1��ʼ�����Ļ�����b�� ��i�� ��n�� ��g����4����ĸ���ֵ�λ�÷ֱ�Ϊ
 (4,5,6,10) (4,5,9,10),(4,8,9,10)��(7,8,9,10)��
 ���ܹ�������ϳ�4�����ʡ�bing����
 ���ǵ������ǣ��ָ��������ַ�����ֻ����Сд��b�� ��i�� ��n�� ��g����4����ĸ��
 ����һ������ϳɶ��ٸ�����bing?
 (�ַ������Ȳ�����10000�����ڽ�����ܱȽϴ��������10^9 + 7ȡ����֮��Ľ����) """

def count(word):   #��������
    b,i,n,g = 0,0,0,0
    for k in range(len(word)):
        if word[k] == "b":
            b += 1
        elif word[k] == "i":
            i += 1
        elif word[k] == "n":
            n += 1
        elif word[k] == "g":
            g +=1
        else:
            return False
    return b*i*n*g

def main():
    while True:
        word = raw_input("Please enter a word (Only has 'b',��i��,��n��,��g�� ) >> ")
        num =False
        if len(word) <= 10000:
            num =  count(word)      
        if num != False:
            break
    print "This word has",num,"'bing's"
    print (10^9+7) % num

main()
             
