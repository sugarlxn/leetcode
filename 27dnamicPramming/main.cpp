#include<iostream>
// #include<bits/stdc++.h>
#include<vector>

using namespace std;

//二维dp数组动态规划 - 01 背包问题
// weight 存储每件物品所占空间, value 存储每件物品的价值
vector<vector<int>> dp_2d(vector<int> weight, vector<int> value, int bagweight){
    //dp数组, dp[i][j]， 背包空间为j的条件下，[0-i]物品中任取，所获得的最大价值dp[i][j]
    vector<vector<int>> dp(weight.size(), vector<int>(bagweight + 1, 0));

    //初始化dp数组
    // 初始化, 因为需要用到dp[i - 1]的值
    // j < weight[0]已在上方被初始化为0
    // j >= weight[0]的值就初始化为value[0]
    for(int j = weight[0]; j <= bagweight; j++){
        dp[0][j] = value[0];
    }

    for(int i = 1; i < weight.size();  i++){ //遍历物品
        for(int j = 0; j <= bagweight; j++){ //遍历容量
            if(j < weight[i]){
                dp[i][j] = dp[i-1][j];
            }else{
                dp[i][j] = max(dp[i-1][j], dp[i-1][j - weight[i]] + value[i]);
            }
        }
    }

    return dp;
}

//滚动数组 动态规划 - 01 背包问题
vector<int> dp_1d(vector<int> weight, vector<int> value, int bagweight){
    //一维dp数组
    vector<int> dp(bagweight+1, 0);

    //顺序遍历
    for(int i = 0; i < weight.size(); i++){
        //倒叙遍历
        for(int j = bagweight; j >= weight[i]; j--){
            //dp 递推
            dp[j] = max(dp[j], dp[j-weight[i]] + value[i]);
        }
    }
    return dp;
}


int main(int argc, char * argv[]){

    cout << "good day today!" << endl;
    vector<int> weight = {1,3,4};
    vector<int> value = {15, 20, 30};
    int bagweight = 4;
    vector<vector<int>> dp = dp_2d(weight, value, bagweight);

    for(auto items : dp){
        for(auto item : items){
            cout << item << " ";
        }
        cout << endl;
    }

    cout << "============" << endl;
    vector<int> dp1 = dp_1d(weight, value, bagweight);
    for(auto item : dp1){
        cout << item << " ";
    }    
    cout << endl;

    return 0;
}