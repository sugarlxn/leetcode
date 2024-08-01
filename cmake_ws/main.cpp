#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "linklist.hpp"
using namespace std;

//单链表
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {} //节点构造函数，此时不再有默认构造函数
    ListNode(): val(0), next(NULL) {} //默认构造函数, 在为struct添加构造函数时，需要添加默认构造函数
};

vector<int> test1(vector<int>& nums){
    vector<int> res = nums;
    res[res.size()-1] = 8;
    return res;
}

/// @brief  打印vector
/// @tparam T 
/// @param nums 
/// @param flag 
template <typename T>
void my_printf_vector(const vector<T>& nums, bool flag = 0){
    //横向打印
    if(flag == 0){
        for(T i : nums){
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
    //纵向打印
    else{
        for(T i : nums){
            std::cout << i << std::endl;
        }
    }
}

/// @brief 打印matrix
/// @tparam T 
/// @param matrix 
template <typename T>
void my_printf_matrix(const vector<vector<T>>& matrix){
    for(vector<T> v : matrix){
        for(T i : v){
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
}

void my_printf_args(int argc, char *argv[]){
    for(int i = 0; i < argc; i++){
        cout << argv[i] << " ";
    }
    cout << endl;
}

void getNext(int* next, const string& s){
    int j = -1;
    next[0] = j;
    for(int i = 1; i < s.size(); i++) { // 注意i从1开始
        while (j >= 0 && s[i] != s[j + 1]) { // 前后缀不相同了
            j = next[j]; // 向前回退
        }
        if (s[i] == s[j + 1]) { // 找到相同的前后缀
            j++;
        }
        next[i] = j; // 将j（前缀的长度）赋给next[i]
    }
}


vector<int> computeNext(const string& pattern) {  
    int m = pattern.length();  
    vector<int> next(m, 0); // 初始化next数组，长度为模式串的长度  
  
    // 计算next数组  
    int j = 0; // j代表当前正在处理的next[j]  
    int t = next[0] = -1; // next[0]通常设为-1，表示没有前缀与后缀匹配  
    while (j < m - 1) {  
        if (t == -1 || pattern[j] == pattern[t]) {  
            ++j;  
            ++t;  
            if (pattern[j] != pattern[t])  
                next[j] = t;  
            else  
                next[j] = next[t];  
        } else {  
            t = next[t];  
        }  
    }  
    return next;  
}  

class Solution {
public:
    void getNext(int* next, const string& s) {
        int j = -1;
        next[0] = j;
        for(int i = 1; i < s.size(); i++) { // 注意i从1开始
            while (j >= 0 && s[i] != s[j + 1]) { // 前后缀不相同了
                j = next[j]; // 向前回退
            }
            if (s[i] == s[j + 1]) { // 找到相同的前后缀
                j++;
            }
            next[i] = j; // 将j（前缀的长度）赋给next[i]
        }
    }
    int strStr(string haystack, string needle) {
        if (needle.size() == 0) {
            return 0;
        }
		vector<int> next(needle.size());
		getNext(&next[0], needle);
        cout << "next[]:" << endl;
        for(int i=0; i<needle.size(); i++){
            cout << next[i] << " ";
        }
        cout << endl;
        int j = -1; // // 因为next数组里记录的起始位置为-1
        for (int i = 0; i < haystack.size(); i++) { // 注意i就从0开始
            while(j >= 0 && haystack[i] != needle[j + 1]) { // 不匹配
                j = next[j]; // j 寻找之前匹配的位置
            }
            if (haystack[i] == needle[j + 1]) { // 匹配，j和i同时向后移动
                j++; // i的增加在for循环里
            }
            if (j == (needle.size() - 1) ) { // 文本串s里出现了模式串t
                return (i - needle.size() + 1);
            }
        }
        return -1;
    }
};

void my_getnext(string& s){
    int next[s.size()+1]={0};
    int i=0,j=-1;
    next[0]=-1;
    
    for(i=1;i<s.size();i++){
        while(j>=0 && s[i]!=s[j]){
            j=next[j];
        }
        next[i]=j;
        j++;
    }

}

int Index_KMP(string& S, string& T, int * next){
    if(T.size()==0){
        return 0;
    }
    int i=1,j=1;
    while(i<=S.size() && j<=T.size()){
        if(j==0 || S[i]==T[j]){
            i++;
            j++;
        }
        else{
            j=next[j];
        }
    }
    if(j>T.size()){
        return i-T.size();
    }
    else{
        return -1;
    }
}

int main(int argc, char *argv[])
{

    string s1 = "hellohellohello";
    string s2 = "abaabc";
    Solution solution;
    cout << solution.strStr(s1, s2) << endl;

    return 0;
}
