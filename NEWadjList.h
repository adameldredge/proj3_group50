#pragma once
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <queue>

using namespace std;

struct AdjacencyList
{
    struct Person
    {
        Person()
        {
            name = "";
            id = 0;
            visited = false;
            identified = false;
        }
        Person(string n)
        {
            name = n;
            id = 0;
            visited = false;
            identified = false;
        }
        Person operator=(const Person& d)
        {
            name = d.name;
            id = d.id;
            visited = d.visited;
            identified = d.identified;
            return* this;
        }
        bool operator==(const Person& d)
        {
            return ((d.name == name) && (d.adjNodes == adjNodes) && (d.id == id));
        }
        void setID(unsigned int i)
        {
            id = i;
        }
        unsigned int getID()
        {
            return id;
        }
        void addAdj(Person* n)
        {
            adjNodes.push_back(n);
        }
        vector<Person*> getAdj()
        {
            return adjNodes;
        }
        string name;
        unsigned int id;
        bool visited;
        bool identified;
        vector<Person*> adjNodes;
    };

    // Member Variables
    Person* root;
    int size;
    map<string, Person*> nodes;

    // Functions
    AdjacencyList()
    {
        root = nullptr;
        size = 0;
    }
    Person* newPerson(string name)
    {
        Person* p = new Person(name);
        p->setID(size+1);
        size++;
        if (root == nullptr)
            root = p;
        nodes.emplace(name,p);

        return p;
    }
    void addEdge(string srcName, string destName)
    {
        Person* tempsrc;
        Person* tempdest;
        if (nodes.find(srcName) == nodes.end())
            tempsrc = newPerson(srcName);
        else
            tempsrc = nodes[srcName];
        if (nodes.find(destName) == nodes.end())
            tempdest = newPerson(destName);
        else
            tempdest = nodes[destName];
        tempsrc->addAdj(tempdest);
    }
    Person* getPerson(string name, unsigned int id)
    {
        Person* temp = nodes[name];
        if (!temp)
            return nullptr;
        if (temp->id == id)
            return temp;
    }




    // Once Graph is fully made
    // Dijkstra's
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
        for (int i = path.size()-1; i >= 0; i--)
        {
            updatedPath.push_back(path.at(i));
        }
        return updatedPath;
    }

    // BFS
    vector<AdjacencyList::Person*> DFSvsBFS(map<string,AdjacencyList::Person*> graph)
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
        return pathDFS;
    }
};