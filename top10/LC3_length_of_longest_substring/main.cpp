// #include <iostream>
// #include <fstream>
// #include <string>

#include <bits/stdc++.h>

using namespace std;

#define LOCAL
#ifdef LOCAL
    ifstream in("../input.txt");
    ofstream out("../output.txt");
#define cin in
#define cout out
#endif

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* curr = head;
    while (curr != nullptr) {
        ListNode* nextTemp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextTemp;
    }
    return prev;
}


int hIndex(vector<int>& citations) {
    sort(citations.begin(), citations.end(), greater<int>());
    int h = 0;
    for (int i = 0; i < citations.size(); i++) {
        if (citations[i] >= i + 1) {
            h++;
        } else {
            break;
        }
    }
    return h;
}

int main(int argc, char *argv[]) {

    int n = 0;
    cin >> n;
    vector<int> arr(n);
    for(int i=0; i<n; i++){
        cin >> arr[i];
    }

    int h = hIndex(arr);
    cout << "H-Index: " << h << endl;

    return 0;
}