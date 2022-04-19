#include <iostream>
#include <istream>
#include <vector>
#include <map>
#include <string>
using namespace std;
#include "AdjacencyList.h"

bool isAdjacent (AdjacencyList::Person* first , AdjacencyList::Person* second)
{
    for (int i = 0; i < first->adjNodes.size(); i++)
    {
        if (first->adjNodes.at(i) == second)
            return true;
    }
    return false;
}

vector<AdjacencyList::Person*> dijkstra (map<string, AdjacencyList::Person*> graph, AdjacencyList::Person* source, AdjacencyList::Person* Destination)
{
    map<int, AdjacencyList::Person*> S;
    map<int, AdjacencyList::Person*> VS;
    map<AdjacencyList::Person*, int> d;
    map<AdjacencyList::Person*, AdjacencyList::Person*> p;

    // Add all People to VS
    for (auto it : graph)
    {
        VS[it.second->id] = it.second;
    }

    // Move source person to S
    S[source->id] = VS[source->id];
    VS.erase(source->id);

    // Set source as predecessor and max as distance (or 1 if connected to source)
    for (auto it : VS)
    {
        if (isAdjacent(S[source->id], it.second))
            d[it.second] = 1;
        else
            d[it.second] = numeric_limits<int>::max();

        p[it.second] = S[source->id];
    }

    // Iterate through VS and update distances and predecessors
    while (!VS.empty())
    {
        AdjacencyList::Person* smallestDistance = VS.begin()->second;
        for (auto it : VS)
        {
            if (d[it.second] < d[smallestDistance])
            {
                smallestDistance = it.second;
            }
        }
        S[smallestDistance->id] = VS[smallestDistance->id];
        VS.erase(smallestDistance->id);
        for (auto it : S[smallestDistance->id]->adjNodes)
        {
            if (d[smallestDistance] + 1 < d[it])
            {
                d[it] = d[smallestDistance] + 1;
                p[it] = S[smallestDistance->id];
            }
        }
    }

    // Iterate through predecessors of destination until find source and output all through a vector
    AdjacencyList::Person* currentPredecessor = p[Destination];
    vector<AdjacencyList::Person*> path;
    path.push_back(Destination);
    while (currentPredecessor != source)
    {
        path.push_back(currentPredecessor);
        currentPredecessor = p[currentPredecessor];
    }
    path.push_back(source);
    // Flip vector
    vector<AdjacencyList::Person*> updatedPath;
    for (int i = path.size()-1; i >= 0; i++)
    {
        updatedPath.push_back(path.at(i));
    }
    return updatedPath;
}

