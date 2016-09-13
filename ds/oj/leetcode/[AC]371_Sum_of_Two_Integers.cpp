#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class Solution {
public:
    string toReverseBinary(int n){
        string r;
        while(n!=0) {r= r+ (n%2==0 ?"0":"1"); n/=2;}
        return r;
    }

    int toInt(string reverseStr){
        int num = 0;
        for (int i = 0; i<reverseStr.size(); ++i){
            num += (reverseStr[i]-'0')*pow(2,i);
        }
        return num;
    }

    bool needCarry(int a, int b, int c){
        int oneNum =0;
        oneNum = (a==1 ? oneNum+1:oneNum);
        oneNum = (b==1 ? oneNum+1:oneNum);
        oneNum = (c==1 ? oneNum+1:oneNum);
        return (oneNum>=2 ? true:false);
    }

    int getSumOld(int a, int b) {
        string aStr = toReverseBinary(a);
        string bStr = toReverseBinary(b);
        string str = "";
        int strSize = min(aStr.size(),bStr.size());
        int carry = 0;
        for (int i = 0; i<strSize; ++i){
            int num = (((aStr[i])-'0')^((bStr[i])-'0')^carry) ;
            str.append(1,char(num + '0'));
            carry = (needCarry(((aStr[i])-'0'), ((bStr[i])-'0'), carry))?1:0;
        }
        if (aStr.size() > strSize){
            for (int i = strSize; i<aStr.size(); ++i){
                int num = (((aStr[i])-'0')^carry) ;
                str.append(1,char(num + '0'));
                (needCarry(((aStr[i])-'0'),carry, 0));
            }

        }

        else if (bStr.size() > strSize){
            for (int i = strSize; i<bStr.size(); ++i){
                int num = (((bStr[i])-'0')^carry) ;
                str.append(1,char(num + '0'));
                (needCarry(((bStr[i])-'0'),carry, 0));
            }

        }

        if (carry == 1) str.append("1");

        return toInt(str);
    }

    int getSum(int a, int b){
        int carry = b;
        int sum = a;
        while (carry!=0){
            int tmp = sum;
            sum = tmp ^ carry;
            carry = (tmp & carry) << 1;
        }
        return sum;
    }
};

int main()
{
    Solution s;
    cout<<s.getSum(-4,7);
    return 0;
}
