//假如一个数组中存储了一个股票，在一天交易窗口内各时间点的股票价格（正整数）。只允许一次买入和一次卖出，请提供一个算法，计算出通过卖出和买入可以得到的最大利润

#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

std::vector<std::string> split(std::string str,std::string pattern)
{
  std::string::size_type pos;
  std::vector<std::string> result;
  str+=pattern;//扩展字符串以方便操作
  int size=str.size();

  for(int i=0; i<size; i++)
  {
    pos=str.find(pattern,i);
    if(pos<size)
    {
      std::string s=str.substr(i,pos-i);
      result.push_back(s);
      i=pos+pattern.size()-1;
    }
  }
  return result;
}

long strToInt(string num)
{
    stringstream ss;
    ss<<num;

    long i;
    ss>>i;
    return i;
}

int main()
{
    char c;
    string str;
    vector<int> vec;
    vector<int> orgvec;
    getline(cin,str);
    vector<string> strvec;

    strvec = split(str,",");

    for (int i = 0 ; i< strvec.size();++i){
        vec.push_back(strToInt(strvec[i]));
        orgvec.push_back(strToInt(strvec[i]));
    }

    /*
    while(cin>>c){
        if (c!=','){
            vec.push_back(c-'0');
        }
    }
    */


    sort(vec.begin(),vec.end());

    for (int i = 0 ; i < vec.size();++i){
        for (int j= vec.size()-1; j>i ; --j){
            if (find(orgvec.begin(),orgvec.end(),vec[i])< find(orgvec.begin(),orgvec.end(),vec[j])) {cout<<vec[j]-vec[i];return 0;}
            //<<((find(org_vec.begin().org_vec.end(),vec[i])- org_vec.begin())<(find(org_vec.begin().org_vec.end(),vec[j]))- org_vec.begin())<<endl;
        }
    }
    int low = vec[0];
    int high = vec.back();
    //cout<<high-low<<endl;

    return 0;
}
