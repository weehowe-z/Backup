# -*- coding: cp936 -*-
"""本届大赛由微软必应词典冠名，但现实生活中，我们也经常能看到一些毫无规则的字符串，
 导致词典无法正常收录，不过，我们是否可以从无规则的字符串中提取出正规的单词呢？
 例如有一个字符串"iinbinbing"，截取不同位置的字符‘b’、‘i’、‘n’、‘g’组合成单词"bing"。
 若从1开始计数的话，则‘b’ ‘i’ ‘n’ ‘g’这4个字母出现的位置分别为
 (4,5,6,10) (4,5,9,10),(4,8,9,10)和(7,8,9,10)，
 故总共可以组合成4个单词”bing“。
 咱们的问题是：现给定任意字符串，只包含小写‘b’ ‘i’ ‘n’ ‘g’这4种字母，
 请问一共能组合成多少个单词bing?
 (字符串长度不超过10000，由于结果可能比较大，请输出对10^9 + 7取余数之后的结果。) """

def count(word):   #计算数量
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
        word = raw_input("Please enter a word (Only has 'b',‘i’,‘n’,‘g’ ) >> ")
        num =False
        if len(word) <= 10000:
            num =  count(word)      
        if num != False:
            break
    print "This word has",num,"'bing's"
    print (10^9+7) % num

main()
             
