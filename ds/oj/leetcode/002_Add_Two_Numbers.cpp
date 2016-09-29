#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        int carry = 0;
        ListNode *prev;
        ListNode *head;
        head = prev = new ListNode(0);
        while (l1 && l2) {
            int sum = l1->val + l2->val + carry;
            if (sum >= 10) {
                sum -= 10;
                carry = 1;
            } else {
                carry = 0;
            }
            ListNode* newNode = new ListNode(sum);
            prev->next = newNode;
            prev = prev->next;
            l1 = l1->next;
            l2 = l2->next;
        }

        while (l1){
            int sum = l1->val + carry;
            if (sum >= 10) {
                sum -= 10;
                carry = 1;
            } else {
                carry = 0;
            }
            ListNode* newNode = new ListNode(sum);
            prev->next = newNode;
            prev = prev->next;
            l1= l1->next;
        }

        while (l2){
            int sum = l2->val + carry;
            if (sum >= 10) {
                sum -= 10;
                carry = 1;
            } else {
                carry = 0;
            }
            ListNode* newNode = new ListNode(sum);
            prev->next = newNode;
            prev = prev->next;
            l2 = l2->next;
        }

        if (carry) {
            ListNode* newNode = new ListNode(1);
            prev->next = newNode;
            prev = prev->next;
        }

        return head->next;
    }
};

int main()
{
    Solution s;
    s.addTwoNumbers()
    return 0;
}
