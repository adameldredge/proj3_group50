#pragma once
#include <string>
#include <vector>
#include <map>
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
    Person* newPerson(string name, bool namePresent)
    {
        Person* p = new Person(name);
        p->setID(size+1);
        size++;
        if (root == nullptr)
            root = p;
        nodes.emplace(name,p);
        size++;

        return p;
    }
    void addEdge(string srcName, string destName)
    {
        Person* tempsrc;
        Person* tempdest;
        if (nodes.find(srcName) == nodes.end())
            tempsrc = newPerson(srcName,false);
        else
            tempsrc = nodes[srcName];
        if (nodes.find(destName) == nodes.end())
            tempdest = newPerson(destName, false);
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
};
