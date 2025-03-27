#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_set>
#include<map>

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

class Solution {
    private:
        vector<vector<int>> result;
        vector<int> path;
        void backtracking(vector<int>& nums, int startIndex, vector<bool>& used){
            //收集子集
            result.push_back(path);
            //返回条件
            if(startIndex >= nums.size()){
                return;
            } 
            for(int i = startIndex; i < nums.size(); i++){
                //去重
                if(i > 0 && nums[i] == nums[i-1] && used[i-1] == false){
                    continue;
                }
                //处理当前节点
                used[i] = true;
                path.push_back(nums[i]);
                //递归
                backtracking(nums, i+1, used);
                //回溯
                used[i] = false;
                path.pop_back();
            }
        }
    
    public:
        vector<vector<int>> subsetsWithDup(vector<int>& nums) {
            vector<bool> used(nums.size(), false);
            result.clear();
            path.clear();
            sort(nums.begin(), nums.end());
            backtracking(nums, 0, used);
            return result;
        }
    };

class Solution2 {
    private:
        vector<vector<int>> result;
        vector<int> path;
        void backtracking(vector<int>& nums, int startIndex, vector<bool>& used){
            //收集集合
            if(path.size() > 1){
                result.push_back(path);
            }
            //返回条件
            if(startIndex >= nums.size()){
                return;
            }
            //同层元素去重
            unordered_set<int> uset;
            for(int i = startIndex; i < nums.size(); i++){
                //去重
                if(i > 0 && nums[i] == nums[i-1] && used[i-1] == false){
                    continue;
                }
                //减枝判断当前序列是否为升序
                if((path.empty() == false && nums[i] < path.back()) || uset.find(nums[i]) != uset.end()){
                    continue;
                }
                //处理当前节点
                uset.insert(nums[i]); // 记录当前元素在本层已经使用过
                path.push_back(nums[i]);
                used[i] = true;
                backtracking(nums, i+1, used);
                used[i] = false;
                path.pop_back();
            }
        }
    
    public:
        vector<vector<int>> findSubsequences(vector<int>& nums) {
            vector<bool> used(nums.size(), false);
            result.clear();
            path.clear();
            backtracking(nums, 0, used);
            return result;
        }
    };

class Solution3{


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

    vector<int> nums{1,2,2};
    for(auto item : nums){
        cout << item << " ";
    }
    cout << endl;
    Solution().subsetsWithDup(nums);

    vector<int> nums2{1,2,3,1,1,1};
    vector<vector<int>> result =  Solution2().findSubsequences(nums2);
    for(auto path : result){
        for(auto item : path){
            cout << item; 
            cout << ",";
        }
        cout << " ";
    }
    cout << endl;

    cout << "====" << endl;
    unordered_map<string, map<string, int>> targets;
    vector<vector<string>> tickets = {{"JFK", "KUL"}, {"JFK", "NRT"}, {"NRT", "JFK"}};
    for(vector<string>& vec : tickets){
        cout << vec[1] << " "; //终点
        targets[vec[0]][vec[1]]++;
    }
    cout << endl;
    for(pair<const string, int>& target : targets["JFK"]){
        cout << target.first << " " << target.second << endl;
    }


    return 0;
}