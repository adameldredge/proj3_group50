#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <stack>
#include <queue>
using namespace std;
#include "AdjacencyList.h"

pair<string,vector<AdjacencyList::Person*>> DFSvsBFS(map<string,AdjacencyList::Person*> graph)
{
    // DFS
    stack<AdjacencyList::Person*> s;
    vector<AdjacencyList::Person*> pathDFS;
    AdjacencyList::Person* start = graph.begin()->second;
    start->identified = true;
    s.push(start);
    while (!s.empty())
    {
        AdjacencyList::Person* current = s.top();
        pathDFS.push_back(current);
        s.pop();
        for (auto it : current->adjNodes)
        {
            if (!it->identified && !it->visited)
            {
                it->identified = true;
                s.push(it);
            }
        }
        current->visited = true;
    }
    // Go back through and mark all as non-visited or identified.
    for (auto it : graph)
    {
        it.second->visited = false;
        it.second->identified = false;
    }
    // BFS
    queue<AdjacencyList::Person*> q;
    vector<AdjacencyList::Person*> pathBFS;
    start = graph.begin()->second;
    start->identified = true;
    q.emplace(start);
    while (!q.empty())
    {
        AdjacencyList::Person* current = q.front();
        pathBFS.push_back(current);
        q.pop();
        for (auto it : current->adjNodes)
        {
            if (!it->identified && !it->visited)
            {
                it->identified = true;
                q.emplace(it);
            }
        }
        current->visited = true;
    }
    // Find smaller vector and return
    if (pathDFS.size() < pathBFS.size())
        return make_pair("DFS",pathDFS);
    else
        return make_pair("BFS",pathBFS);
}

