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

int main(int argc, char *argv[]) {

    string s;
    cin >> s;
    cout << "Input: " << s << endl;

    unordered_set<char> charSet;
    unordered_map<char, int> charIndexMap;
    charSet.insert(s[0]);
    charSet.insert(s[1]);
    charSet.insert(s[2]);
    charIndexMap[s[0]] = 0;
    charIndexMap[s[1]] = 1;
    charIndexMap[s[2]] = 2;

    for(auto c : charSet) {
        cout << c << " ";
    }
    cout << endl;

    for(auto p : charIndexMap) {
        cout << p.first << " " << p.second << endl;
    }
    cout << endl;
    //or using iterator
    for(unordered_set<char>::iterator it = charSet.begin(); it != charSet.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    for(unordered_map<char, int>::iterator it = charIndexMap.begin(); it != charIndexMap.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    cout << endl;
    cout << "ACM template " << endl;
    return 0;
}