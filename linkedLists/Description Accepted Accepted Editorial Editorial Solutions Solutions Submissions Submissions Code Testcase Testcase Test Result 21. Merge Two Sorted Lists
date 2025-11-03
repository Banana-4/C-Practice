/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
    if (!list1 && !list2) {
        return 0;
    } 
    if (!list1) {
        return list2;
    }
    if(!list2) {
        return list1;
    }
    struct ListNode* current;
    if (list1->val <= list2->val) {
        current = list1;
        current->next = mergeTwoLists(list1->next, list2);
    } else {
        current = list2;
        current->next = mergeTwoLists(list1, list2->next);
        }
    return current;
}
