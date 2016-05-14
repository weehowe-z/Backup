//1243. 我有特别的微调技巧
//Description
//又到了期末评分的时候了。X老师总是为打分这件事感到发愁，这是因为如果同学们分数都偏高或者偏低，领导就会请自己喝茶。
//
//因此为了确保分数呈现正态分布，X老师决定对分数进行微调。假设班上的分数按照学号排成一个数列，X老师拥有特别的微调技巧。作为他忠实助教的你，需要编写一个微调系统。 需要实现的操作如下：

//0 l r -- 将学号l到r之间（包含两端，下同）所有同学的成绩的算术平均输出；

//1 l r -- 将l到r之间所有同学的最高分输出；

//2 l r -- 将l到r之间所有同学的成绩翻转，即l同学成绩变为r同学成绩，l+1同学的变为r-1的，以此类推；

//3 l r -- 依次输出l到r之间所有同学的成绩，用空格分开；

//4 l r -- 将l到r之间所有同学的成绩下调1，若已经是0分则不变。


#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
    int n,m,l,r,opt,high;
    double total;
    int *grade;
    cin>>n>>m;
    grade=new int[n];
    for (int i=0;i<n;++i) cin>>grade[i];
    for (int i=0;i<m;++i){
        cin>>opt>>l>>r;
        switch(opt)
        {
            case 0:
                {
                    total=0;
                    for (int j=l;j<=r;++j) total+=grade[j];
                    cout<<fixed<<setprecision(2)<<total/n<<endl;
                    break;
                }
            case 1:
                {
                    high=grade[0];
                    for (int j=l;j<=r;++j){
                        if (high<grade[j]) high=grade[j];
                    }
                    cout<<high<<endl;
                    break;
                }
            case 2:
                {
                    for (int j=l;j<=(r+l)/2;++j){
                        high=grade[j];
                        grade[j]=grade[l+r-j];
                        grade[l+r-j]=high;
                    }
                    break;
                }
            case 3:
                {
                    for (int j=l;j<=r;++j) cout<<grade[j]<<" ";
                    cout<<endl;
                    break;
                }
            case 4:
                {
                    for (int j=l;j<=r;++j){
                        if (grade[j]>0) --grade[j];
                    }
                }
        }
    }
    delete []grade;
    return 0;
}
