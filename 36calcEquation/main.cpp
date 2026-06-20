#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;


class Solution {

public:

    vector<double> calcEuation(vector<pair<string, string>>& equations, vector<double>& values, vector<pair<string, string>>& queries) {
        //邻接表
        unordered_map<string, vector<pair<string, double>>> graph;
        
        //建图， a/b = k -> a->b = k, b->a = 1/k
        for(int i=0; i<equations.size(); i++){
            string a = equations[i].first;
            string b = equations[i].second;
            double k = values[i];
            graph[a].push_back({b, k});
            graph[b].push_back({a, 1.0/k});
        }

        //BFS 求src 到 dst 的路径乘积
        auto bfs = [&](const string& src, const string& dst) -> double {
            //节点不存在
            if (!graph.count(src) || !graph.count(dst)) return -1.0;
            //起点=终点
            if(src == dst) return 1.0;

            //visited 记录访问过的节点
            unordered_set<string,bool> visited;
            queue<pair<string,double>> q; //节点和当前乘积
            q.push({src, 1.0});
            visited.insert(src);

            while(!q.empty()){
                auto [node, product] = q.front();
                q.pop();

                for(auto& [neighbor, value] : graph[node]){
                    if(visited.count(neighbor)) continue;
                    double new_product = product * value;
                    if(neighbor == dst) return new_product; //找到目标节点
                    if(!visited.count(neighbor)){
                        visited.insert(neighbor);
                        q.push({neighbor, new_product});
                    }
                }
            }

            return -1.0;    
         
        };


        //处理查询
        vector<double> results;
        for(auto& [src, dst] : queries){
            results.push_back(bfs(src, dst));
        }
        return results;

    }


};


int main(int argc, char * argv[]){



    return 0;
}