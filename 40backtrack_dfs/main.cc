#include <iostream>
#include <vector>

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
    return 0;
}   