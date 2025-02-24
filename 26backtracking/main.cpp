#include<iostream>
#include<vector>

using namespace std;

class BackTracking{
private:
    vector<vector<int>> result; //存放符合结果的集合
    vector<int> path; //用来存放符合条件的结果

    void backtracking(int n, int k, int startIndex){
        if(path.size() == k){ // path.size 是递归深度
            result.push_back(path);
            return;
        }
        for(int i = startIndex; i <= n - (k - path.size()) +1; i++){ //减枝优化 i <= n - (k - path.size()) +1  原来 i <= n
            path.push_back(i);// 处理节点
            backtracking(n, k, i+1); //递归
            path.pop_back(); //回溯,撤销处理的节点
        }

    }
public:
    vector<vector<int>> combine(int n, int k){
        result.clear();
        path.clear();
        backtracking(n, k, 1); //为什么这里从 1 开始?
        return result;
    }
};

int main(int argc, char* argv[]){
    
    cout << "backtracking" << endl;
    vector<vector<int>> resutl = BackTracking().combine(4,2); //从[1,2,3,4] 中取 2 个数 所有的不重复集合
    for(auto path : resutl){
        cout << "[";
        for(auto item : path){
            cout << item; 
            cout << (item == path.back() ? "]" : ",");
        }
    }
    cout << endl;
    return 0;
}