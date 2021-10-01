/*
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 1.0.0
 * @Date: 2021-08-31 20:34:19
 * @LastEditTime: 2021-09-01 17:57:51
 * @Description:  
 */

#include<iostream>
#include<vector>
using namespace std;
#define INF INT16_MAX

void floyd(vector<vector<int>> &adj, vector<vector<int>> &dist, vector<vector<int>> &next)
{
    int n = adj.size();
    // 初始化距离数组k=0时:
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            dist[i][j] = adj[i][j];
            if (adj[i][j]!=INF) next[i][j] = j; // 有边才有中继节点
        }
    }

    for (int k=0; k<n; k++)
    {
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<n; j++)
            {
                if (dist[i][k]+dist[k][j]<dist[i][j])
                {
                    dist[i][j] = dist[i][k]+dist[k][j]; // 松弛
                    next[i][j] = next[i][k]; // 保存最近的中继节点
                }
            }
        }
    }
}

void printPath(int i, int j, vector<vector<int>> &next)
{
    if (next[i][j]==-1) return;
    vector<int> path = {i};
    
    while(i!=j)
    {
        i = next[i][j];
        path.push_back(i);
    }

    for (int a : path) cout << a << ' ';
}


int main()
{
    int n = 4; 
    vector<vector<int>> adj(n, vector<int>(n, INF));
    adj[0][0] = 0; adj[0][2] = -2;
    adj[1][1] = 0; adj[1][0] = 4; adj[1][2] = 3;
    adj[2][2] = 0; adj[2][3] = 2;
    adj[3][3] = 0; adj[3][1] = -1;

    vector<vector<int>> dist(n, vector<int>(n, INF)), next(n, vector<int>(n, -1));
    floyd(adj, dist, next);
    printPath(0,1, next);

}