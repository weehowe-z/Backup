#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    void mergeKLists(ListNode* list1, ListNode* list2) {
        ListNode* head = new ListNode(-1);
        ListNode* current = head;
        ListNode* p = list1;
        ListNode* q = list2;
        while (p&&q) {
          if (p->val<=q->val){
            current->next = p;
            p = p -> next;
            current = current->next;
          }else{
            current->next = q;
            q = q -> next;
            current = current->next;
          }
        }
        while (p){
          current -> next = p;
          p = p -> next;
          current = current -> next;
        }

        while (q){
          current -> next = q;
          q= q->next;
          current = current -> next;
        }

        list2 = head->next;
    }

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.size()==0) return nullptr;
        while(lists.size()>1){
          std::vector<ListNode*>::iterator current = lists.begin();
          std::vector<ListNode*>::iterator next = lists.begin();
          while(true){
            next = current+1;
            if (next == lists.end()) break;
            else{
              mergeKLists(*current,*next);
              current = lists.erase(current);
              ++current;
              if (current == lists.end()) break;
            }
          }
        }
        return lists[0];
    }
};

int main(int argc, char const *argv[]) {
  /* code */
  return 0;
}
