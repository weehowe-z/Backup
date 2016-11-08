#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Interval {
  int start;
  int end;
  Interval(): start(0),end(0){}
  Interval(int s, int e): start(s),end(e){}
};


class Solution {
public:
    static bool mysort(Interval &a, Interval &b){
      if (a.start < b.start) return true;
      else if (a.start == b.start) return (a.end<b.end);
      return false;
    }

    vector<Interval> merge(vector<Interval>& intervals) {
      if (intervals.size()<=1) return intervals;
      sort(intervals.begin(), intervals.end(), mysort);
      std::vector<Interval>::iterator it = intervals.begin();
      std::vector<Interval>::iterator next = it;
      while (it != intervals.end()) {
        next = it+1;
        if (next!=intervals.end()){
            if ((next->start <= it->end)){
              next -> start = min(it->start, next->start);
              next -> end = max(it -> end, next->end);
              it = intervals.erase(it);
              continue;
            }
        }else{
          return intervals;
        }
        ++it;
      }
      return intervals;
    }
};

int main(int argc, char const *argv[]) {
  /* code */


  return 0;
}
