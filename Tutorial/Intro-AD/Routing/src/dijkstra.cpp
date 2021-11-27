/*
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 1.0.0
 * @Date: 2021-08-30 23:35:57
 * @LastEditTime: 2021-09-01 21:23:26
 * @Description:  
 */

#include<iostream>
#include<vector>
#include<queue>
using namespace std;

#define INF 65535
typedef pair<int, int> ipair;
typedef vector<pair<int, int>> vpair;

void addEdge(vector<vpair> &adj, int i, int j, int w)
{
    // 使用邻接表定义图: 
    // 索引为起始节点序号，值为所有与该节点相连的边，用终止节点及权重表示
    adj[i].push_back(make_pair(j, w));
    adj[j].push_back(make_pair(i, w));
}

vector<int> dijkstra(vector<vpair> &adj, int n, int start)
{
    vector<int> dist(n, INF); // 距离数组:存储每个节点到起始节点的最短距离
    vector<bool> visited(n, false); // 标记数组:划分集合
    priority_queue<ipair, vector<ipair>, greater<ipair>> pq; //小顶堆：有序存储距离和对应节点
    
    pq.push(make_pair(0, start)); // 将起始距离和起始节点加入队列 (顺序颠倒是为了排序)
    dist[start] = 0;
    
    while(!pq.empty())
    {   
        // 取出未访问节点中距离最小的节点
        int u = pq.top().second;
        pq.pop();
        if (visited[u]) continue;
        // 标记为已访问
        visited[u] = true;
        // 对所有相关节点进行松弛操作
        for (ipair edge: adj[u])
        {
            // (没有对邻居进行判断，因此有可能会再次将已访问过的加入)
            int v = edge.first, w = edge.second;
            if (dist[v]>dist[u]+ w)
            {
                dist[v] = dist[u] + w;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    return dist;
}

int main() 
{ 
    int n = 9; 
    vector<vpair> adj(n); 
    addEdge(adj, 0, 1, 4); addEdge(adj, 0, 7, 8); 
    addEdge(adj, 1, 2, 8); addEdge(adj, 1, 7, 11); 
    addEdge(adj, 2, 3, 7); addEdge(adj, 2, 8, 2); 
    addEdge(adj, 2, 5, 4); addEdge(adj, 3, 4, 9); 
    addEdge(adj, 3, 5, 14);addEdge(adj, 4, 5, 10); 
    addEdge(adj, 5, 6, 2); addEdge(adj, 6, 7, 1); 
    addEdge(adj, 6, 8, 6); addEdge(adj, 7, 8, 7); 
  
    vector<int> dist = dijkstra(adj, n, 0);
    for (int i=0; i<n; i++)
    {
        cout << i << ' ' << dist[i] << endl;
    }
  
    return 0; 
}