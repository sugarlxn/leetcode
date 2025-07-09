#include <iostream>
#include <fstream>
#include <utility>
#include <list>
#include <climits>
#include <queue>
using namespace std;

#define LOCAL
#ifdef LOCAL
    ifstream infile("../in.txt");
    ofstream outfile("../out.txt");
#define cin infile
#define cout outfile
#endif

//edge
struct Edge{
    int to;
    int val;
    Edge(int to, int val): to(to), val(val){};
};

struct edge_greater{
    bool operator()(const pair<int,int>& lhs, const pair<int,int>& rhs){
        return lhs.second > rhs.second;
    }
};

int main(int argc, char * argv[]){

    int N,M;
    cin >> N >> M;
    vector<list<Edge>> grid(N+1);//节点编号 1 ~ N
    //初始化grid 图
    for(int i=1; i<M; i++){
        int from, to, val;
        cin >> from >> to >> val;
        grid[from].push_back(Edge(to,val));
    }

    vector<bool> visited(N+1, false);
    vector<int> minidst(N+1, INT_MAX);
    //pair<int,int> pair<to, val> 存储源节点到边to的最小代价val(minidst[to])
    priority_queue<pair<int,int>, vector<pair<int,int>>, edge_greater> pq;

    int start = 1;
    int end = N;

    //初始化
    minidst[start] = 0;
    pq.push(pair(start,minidst[start])); //节点1 to = 1 val = 0

    while(!pq.empty()){

        //1 选取pq中最小的边
        pair<int,int> cur = pq.top(); pq.pop();
        if(visited[cur.first]) continue;

        //2 标记为访问
        visited[cur.first] = true;

        //3 更新minidst
        for(Edge item : grid[cur.first]){
            if(!visited[item.to] && minidst[item.to] > minidst[cur.first] + item.val){
                minidst[item.to] = minidst[cur.first] + item.val;
                pq.push(pair(item.to, minidst[item.to]));
            }
        }

        //调试日志
        cerr << cur.first << " " << minidst[cur.first] << endl;
        for(int i=1; i<=N; i++){
            cerr << i << ":" << minidst[i] << " ";
        }
        cerr << endl;
        
    }

    if(minidst[end] == INT_MAX) cout << -1;
    else cout << minidst[end];   

    return 0;
}