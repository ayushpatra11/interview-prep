// two sum, merge sorted array, merge two sorted lists

#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

// two sum - hashmap O(n)
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int,int> seen;
    for (int i = 0; i < (int)nums.size(); i++) {
        int c = target - nums[i];
        if (seen.count(c)) return {seen[c], i};
        seen[nums[i]] = i;
    }
    return {};
}

// merge sorted array in-place from back O(m+n)
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int i = m-1, j = n-1, k = m+n-1;
    while (j >= 0) {
        if (i >= 0 && nums1[i] > nums2[j]) nums1[k--] = nums1[i--];
        else nums1[k--] = nums2[j--];
    }
}

struct ListNode {
    int val; ListNode* next;
    ListNode(int v, ListNode* n = nullptr) : val(v), next(n) {}
};

// merge two sorted linked lists
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode dummy(0); ListNode* cur = &dummy;
    while (l1 && l2) {
        if (l1->val <= l2->val) { cur->next = l1; l1 = l1->next; }
        else { cur->next = l2; l2 = l2->next; }
        cur = cur->next;
    }
    cur->next = l1 ? l1 : l2;
    return dummy.next;
}

int main() {
    vector<int> a = {2,7,11,15};
    auto r = twoSum(a, 9);
    cout << r[0] << " " << r[1] << "\n";  // 0 1

    vector<int> n1 = {1,2,3,0,0,0}, n2 = {2,5,6};
    merge(n1, 3, n2, 3);
    for (int x : n1) cout << x << " "; cout << "\n";  // 1 2 2 3 5 6
    return 0;
}
