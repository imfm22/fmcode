// 25. Reverse Nodes in k-Group
// https://leetcode-cn.com/problems/reverse-nodes-in-k-group/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

// Solution

struct ListNode* reverseKGroup(struct ListNode* head, int k){
    if (k <= 1) return head;
    
    int len = 1;
    struct ListNode *ptr = head;
    while ((ptr = ptr->next)) ++len;

    if (len < k) return head;

    struct ListNode prehead = {0, head};

    ptr = &prehead;
    for (int round = len / k; round > 0; --round) {
        struct ListNode *cur = ptr->next;
        for (int i = 0; i < k - 1; ++i) {
            struct ListNode *tmp = cur->next;
            cur->next = tmp->next;
            tmp->next = ptr->next;
            ptr->next = tmp;
        }
        ptr = cur;
    }

    return prehead.next;
}

/***************************************************/
/********************* test ************************/
/***************************************************/

struct ListNode * createNode(int val, struct ListNode *next);
void freeNodeList(struct ListNode *node);
struct ListNode * nodeListFromStr(char *str);
void printNodeList(const struct ListNode *node);
int isNodeListEqual(struct ListNode *n1, struct ListNode *n2);

int main() {
    struct ListNode *head = nodeListFromStr("[1,2,3,4,5,6,7,8]");
    printNodeList(head);
    struct ListNode *reversed = reverseKGroup(head, 3);
    printNodeList(reversed);

    struct ListNode *ans = nodeListFromStr("[3,2,1,6,5,4,7,8]");
    assert(isNodeListEqual(reversed, ans));

    freeNodeList(reversed);
    freeNodeList(ans);
    return 0;
}

struct ListNode * createNode(int val, struct ListNode *next) {
    struct ListNode *ret = (struct ListNode*)malloc(sizeof(struct ListNode));
    ret->val = val;
    ret->next = next;
    return ret;
}

void freeNodeList(struct ListNode *node) {
    struct ListNode *tmp;
    while (node) {
        tmp = node->next;
        free(node);
        node = tmp;
    }
}

struct ListNode * nodeListFromStr(char *str) {
    int ch;
    int val;
    struct ListNode ret = {0, NULL};
    struct ListNode *ptr = &ret;
    int preIsDigit = 0;
    while ((ch = *str++)) {
        if (isdigit(ch)) {
            if (preIsDigit) {
                val = val * 10 + (ch - '0');
            } else {
                val = ch - '0';
                preIsDigit = 1;
            }
        } else {
            if (preIsDigit) {
                ptr->next = createNode(val, NULL);
                ptr = ptr->next;
            }
            preIsDigit = 0;
        }
    }

    return ret.next;
}

void printNodeList(const struct ListNode *node) {
    const struct ListNode *tmp = node;
    printf("{");
    while (tmp) {
        printf("%d, ", tmp->val);
        tmp = tmp->next;
    }
    printf("\b\b}\n");
}

int isNodeListEqual(struct ListNode *n1, struct ListNode *n2) {
    struct ListNode *ptr1 = n1, *ptr2 = n2;
    while (ptr1) {
        if (ptr2 == NULL || ptr1->val != ptr2->val)
            return 0;
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }
    return 1;
}
