#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;
int ope[7][7];
int yt;
int sum;
void op(int d);
void add(int d);
int judge(int d);
int leng(int k){
 if(k == 0){
  return 1;
 }
 else{
  int l = 0;
  for(int i = 0; i < 10; i++){
   int s = 1;
   for(int j = 0; j < i; j++){
    s = s * 10;
   }
   if(k < s){
    l = i;
    break;
   }
  }
  return l;
 }
}
void cd(int d){
 int t = 0;
 for(int i = 0; i < d; i++){
  for(int j = 0; j < d; j++){
   if(ope[i][j] > t){
    t = ope[i][j];
   }
  }
 }
 int l = leng(t);
 for(int i = 0; i < d; i++){
  for(int j = 0; j < d; j++){
   int u = leng(ope[i][j]);
   cout << ope[i][j] << " ";
   for(int s = 0; s < l - u; s++){
    cout << " ";
   }
  }
  cout << endl;
 }
 if(t == sum){
  cout << "你赢了！"<< endl;
 }
 if(judge(d) == 0){
  cout << "你输了！"<< endl;
 }
}
void rtol(int d){
 int tem[7][7];
 for(int i = 0; i < d; i++){
  for(int j = 0; j < d; j++){
   tem[i][j] = ope[i][j];
  }
 }
 for(int i = 0; i < d; i++){
  for(int j = 0; j < d; j++){
   ope[i][j] = tem[i][d - 1 - j];
  }
 }
}
void utol(int d){
 int tem[7][7];
 for(int i = 0; i < d; i++){
  for(int j = 0; j < d; j++){
   tem[i][j] = ope[i][j];
  }
 }
 for(int i = 0; i < d; i++){
  for(int j = 0; j < d; j++){
   ope[i][j] = tem[j][i];
  }
 }
}
void utod(int d){
 int tem[7][7];
 for(int i = 0; i < d; i++){
  for(int j = 0; j < d; j++){
   tem[i][j] = ope[i][j];
  }
 }
 for(int i = 0; i < d; i++){
  for(int j = 0; j < d; j++){
   ope[i][j] = tem[d - 1 - i][j];
  }
 }
}
void run(int d){//a:left d:right s:down w:up
    if(yt != 3){
     yt = 3;
     add(d);
    }
 cd(d);
    char a;
    cin >> a;
    if(a == 'a'){
     op(d);
    }
    else if(a == 'd'){
     rtol(d);
     op(d);
     rtol(d);
    }
    else if(a == 's'){
     utod(d);
     utol(d);
     op(d);
     utol(d);
     utod(d);
    }
    else if(a == 'w'){
     utol(d);
     op(d);
     utol(d);
    }
    run(d);
}
int judge(int d){
 int u = 0;
 int te[7][7];
 for(int i = 0; i < d; i++){
  for(int j = 0; j < d; j++){
   te[i][j] = ope[i][j];
  }
 }
 op(d);
    for(int i = 0; i < d; i++){
     for(int j = 0; j < d; j++){
      if(te[i][j] != ope[i][j]){
       u = 1;
          break;
      }
     }
     if(u == 1){
      break;
     }
    }
    for(int i = 0; i < d; i++){
  for(int j = 0; j < d; j++){
   ope[i][j] = te[i][j];
  }
 }
 if(u != 0){
  return u;
 }
 else{
  for(int i = 0; i < d; i++){
   for(int j = 0; j < d; j++){
    te[i][j] = ope[i][j];
   }
  }
  rtol(d);
     op(d);
     rtol(d);
     for(int i = 0; i < d; i++){
      for(int j = 0; j < d; j++){
       if(te[i][j] != ope[i][j]){
        u = 1;
           break;
       }
      }
      if(u == 1){
       break;
      }
     }
     for(int i = 0; i < d; i++){
   for(int j = 0; j < d; j++){
    ope[i][j] = te[i][j];
   }
  }
  if(u != 0){
   return u;
  }
  else{
   for(int i = 0; i < d; i++){
    for(int j = 0; j < d; j++){
     te[i][j] = ope[i][j];
    }
   }
   utod(d);
      utol(d);
      op(d);
      utol(d);
      utod(d);
      for(int i = 0; i < d; i++){
       for(int j = 0; j < d; j++){
        if(te[i][j] != ope[i][j]){
         u = 1;
            break;
        }
       }
       if(u == 1){
        break;
       }
      }
      for(int i = 0; i < d; i++){
    for(int j = 0; j < d; j++){
     ope[i][j] = te[i][j];
    }
   }
   if(u != 0){
    return u;
   }
   else{
    for(int i = 0; i < d; i++){
     for(int j = 0; j < d; j++){
      te[i][j] = ope[i][j];
     }
    }
    utol(d);
       op(d);
       utol(d);
       for(int i = 0; i < d; i++){
        for(int j = 0; j < d; j++){
         if(te[i][j] != ope[i][j]){
          u = 1;
             break;
         }
        }
        if(u == 1){
         break;
        }
       }
       for(int i = 0; i < d; i++){
     for(int j = 0; j < d; j++){
      ope[i][j] = te[i][j];
     }
    }
    return u;
   }
  }
 }
}
void add(int d){
 int s = 0;
    for(int i = 0; i < d; i++){
     for(int j = 0; j < d; j++){
      if(ope[i][j] == 0){
       s++;
      }
     }
    }
    double random(double,double);
 srand(unsigned(time(0)));
 int r = int(random(0,s));
 s = 0;
 int u = 0;
 for(int i = 0; i < d; i++){
  for(int j = 0; j < d; j++){
   if(ope[i][j] == 0){
    if(s == r){
     ope[i][j] = 2;
     u = 1;
     break;
    }
    s++;
   }
  }
  if(u == 1){
   break;
  }
 }
}
void op(int d){
 int temp[7][7];
    int tem[7][7];
 for(int i = 0; i < d; i++){
  for(int j = 0; j < d; j++){
   tem[i][j] = ope[i][j];
   temp[i][j] = ope[i][j];
  }
 }
 for(int i = 0; i < d; i++){
     for(int j = 0; j < d; j++){
      int r = 0;
      int u = 0;
      for(int k = 0; k < d; k++){
       if(tem[i][k] != 0){
        int s = 0;
        int y = 0;
        for(int e = k + 1; e < d; e++){
         if(tem[i][e] != 0){
          s = tem[i][e];
          y = e;
          break;
         }
        }
        if(tem[i][k] == s){
         r = 2 * s;
         tem[i][k] = 0;
         tem[i][y] = 0;
         break;
        }
        else{
         r = tem[i][k];
         tem[i][k] = 0;
         break;
        }
       }
      }
      ope[i][j] = r;
     }
    }
    int r = 0;
    for(int i = 0; i < d; i++){
     for(int j = 0; j < d; j++){
      if(ope[i][j] != temp[i][j]){
       r = 1;
       break;
      }
     }
     if(r == 1){
      break;
     }
    }
    if(r != 0){
     add(d);
    }
}
int main(){
 int d = 0;
 cout << "欢迎来到拼数字游戏！" << endl;
 cout << "游戏说明：a：左，d：右，w：上，s：下。"<< endl;
 cout << "请选择方格边长"<< endl;
 cin >> d;
 cout << "请输入您希望达到的数"<< endl;
 cin >> sum;
 run(d);
 return 0;
}
double random(double start, double end){
 return start+(end-start)*rand()/(RAND_MAX + 1.0);
}
