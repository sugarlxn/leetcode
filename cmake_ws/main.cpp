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


/// @brief 代码随想录的KMP写法
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

/// @brief 计算next数组
/// @param next 
/// @param s 
void mygetNext(vector<int>& next, string& s){
    int j = 0;
    next[0] = 0;
    for(int i = 1; i < s.size(); i++){
        while(j > 0 && s[i] != s[j])
        {
            //回退
            j = next[j-1];
        }
        if(s[i] == s[j]){
            j++;
        }
        next[i] = j;
    }
}

int strStr(const string& haystack,const string& needle){
    if(needle.size() == 0){
        return 0;
    }
    vector<int> next(needle.size(), 0);
    mygetNext(next, const_cast<string&>(needle));
    cout << "next[]: ";
    for(int i=0; i<needle.size(); i++){
        cout << next[i] << " ";
    }
    cout << endl;
    int j = 0;
    for(int i = 0; i < haystack.size(); i++){
        while (j>0 && haystack[i] != needle[j])
        {   
            //回退
            j = next[j-1];
        }
        if(haystack[i] == needle[j]){
            j++;
        }
        if(j == needle.size()){
            return (i - needle.size() + 1);
        }
        
    }
    return -1;
}



int main(int argc, char *argv[])
{

    string s1 = "aabaabaaf";
    string s2 = "aabaaf";
    Solution solution;
    cout << solution.strStr(s1, s2) << endl;

    string s = "aabaaf";
    vector<int> next(s.size(), 0);
    mygetNext(next, s);
    cout << "next[]: ";
    for(int i=0; i<s.size(); i++){
        cout << next[i] << " ";
    }
    cout << endl;

    cout << strStr(s1, s2) << endl;


    return 0;
}
