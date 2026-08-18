#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class sulotion{
public:

    vector<string> ans;

    void backtrack(string path, int left, int right, int n){
        if(path.size() == 2*n){
            ans.push_back(path);
            return;
        }

        if(left < n){
            backtrack(path + "(", left + 1, right, n);
        }

        if(right < left){
            backtrack(path + ")", left, right + 1, n);
        }
    }

    vector<string> generateParenthesis(int n) {
        backtrack("", 0, 0, n);
        return ans;
    }

};

int main(int argc, char* argv[]) {
    int n = 3;
    sulotion s;
    vector<string> ans = s.generateParenthesis(n);
    for(auto& str : ans){
        cout << str << endl;
    }

    string c = "ate";
    sort(c.begin(), c.end());
    cout << c << endl;  

    unordered_map<string, int> m;
    m[c] = 1;
    cout << m[c] << endl;
    string d = "eat";
    m[d] = 2;
    cout << m[d] << endl;
    string e = "tea";
    m[e] = 3;

    //遍历unordered_map
    for(auto& p : m){
        cout << p.first << " : " << p.second << endl;
    }

    //or the second method to traverse unordered_map
    for(auto& [key, value] : m){
        cout << key << " : " << value << endl;
    }

    return 0;
}