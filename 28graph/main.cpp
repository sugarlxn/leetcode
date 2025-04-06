#include<iostream>
#include<vector>
#include<cstdio>
#include<filesystem>
#include<queue>
#include<utility>

using namespace std;

#define LOCAL 

int dir[4][2]={0,1,1,0,-1,0,0,-1};
void dfs(const vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y){
    for(int i=0; i<4; i++){
        int nextx = x + dir[i][0];
        int nexty = y + dir[i][1];
        //越界直接跳过
        if(nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()){
            continue;
        }
        if(!visited[nextx][nexty] && grid[nextx][nexty] == 1){
            //标记为访问
            visited[nextx][nexty] = true;
            dfs(grid, visited, nextx, nexty);
        }
    }
}
void bfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y){
    queue<pair<int,int>> que;
    que.push({x,y});
    //入队列标记当前节点
    visited[x][y] = true;
    while (!que.empty())
    {
        //出队列
        pair<int,int> item = que.front(); que.pop();
        int item_x = item.first;
        int item_y = item.second;
        for(int i=0; i<4; i++){
            int next_x = item_x + dir[i][0];
            int next_y = item_y + dir[i][1];
            //防止越界
            if(next_x < 0 || next_x >= grid.size() || next_y < 0 || next_y >= grid[0].size()){
                continue;
            }
            //当下一个节点没有被访问过 且为陆地时
            if(visited[next_x][next_y] == false && grid[next_x][next_y] == 1){
                //入队列
                que.push({next_x, next_y});
                visited[next_x][next_y] = true;
            }
        }
    }
    
}


int main(int argc, char * argv[]){

    //C++风格的等效代码
    // #include <fstream>
    // std::ifstream inFile("in.txt");
    // std::ofstream outFile("out.txt");
    // // 然后使用 inFile 替代 cin，outFile 替代 cout

#ifdef LOCAL
    //获取当前工作目录
    std::filesystem::path current_path = std::filesystem::current_path();
    current_path += "/../";
    std::filesystem::path in_path = current_path / "in.txt";
    std::filesystem::path out_path = current_path / "out.txt";
    FILE* inFile = freopen(in_path.c_str(), "r", stdin);
    FILE* outFile = freopen(out_path.c_str(), "w", stdout);
    if (!inFile) {
        cerr << "Could not open in.txt for reading" << endl;
        return 1;
    }
    if (!outFile) {
        cerr << "Could not open out.txt for writing" << endl;
        return 1;
    }
#endif

    cout << "good day today!" << endl;

    int n,m;
    cin >> n >> m;
    //初始化vector grid
    vector<vector<int>> grid(n, vector<int>(m, 0));
    for(int i = 0; i < n; i++){
        for(int j=0; j < m; j++){
            cin >> grid[i][j];
        }
    }

    //visited 数组
    vector<vector<bool>> visited(n, vector<bool>(m, false));

    int result = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            //当前节点没有被访问过 且 grid 为陆地时 result ++
            if(!visited[i][j] && grid[i][j] == 1){
                visited[i][j] = true; //标记当前节点为访问
                result +=1;  //岛屿加一
                // dfs(grid, visited, i, j); //标记这个岛屿其他相连的陆地
                bfs(grid, visited, i, j);
            }
        }
    }
    cout << result << endl;

#ifdef LOCAL
    if(inFile){
        fclose(inFile);
    }
    if(outFile){
        fclose(outFile);
    }
#endif

    return 0;
}