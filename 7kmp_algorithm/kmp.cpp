#include <iostream>
#include <vector>
#include <string>
using namespace std;
class KMP{
public:
    /// @brief 计算next数组
    /// @param next 
    /// @param s 
    void mygetNext(vector<int>& next, const string& s){
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

    /// @brief KMP算法字符串匹配
    /// @param haystack 文本字符串
    /// @param needle 模板字符串
    /// @return 首次匹配字符串的索引，未匹配返回-1，匹配字符串为空则返回0
    int strStr(const string& haystack,const string& needle){
        if(needle.size() == 0){
            return 0;
        }
        vector<int> next(needle.size(), 0);
        mygetNext(next, needle);
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

};

int main(int argc, char * argv[]){
    
    string s1 = "aabaabaaf";
    string s2 = "aabaaf";
    KMP kmp;
    int index = kmp.strStr(const_cast<const string&>(s1), const_cast<const string&>(s2));
    cout << index << endl;

    return 0;
}