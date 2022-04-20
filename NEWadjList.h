#pragma once
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include "WebScraper.h"

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
        void setProfileLink(string l) {
            int index = l.find("nm") + 2;
            try {
                this->id = stoi(l.substr(index, 7));
                this->profileLink = l;
            }
            catch (std::invalid_argument) {}
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
        string profileLink;
        unsigned int id;
        bool visited;
        bool identified;
        vector<Person*> adjNodes;
    };

    // Member Variables
    Person* root;
    int size;
    map<string, Person*> nodes;
    WebScraper w;

    // Functions
    AdjacencyList()
    {
        root = nullptr;
        size = 0;
        loopAddData();
    }
    Person* newPerson(string name)
    {
        Person* p = new Person(name);
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
    void recursiveAddEdges(unsigned int count, string name, bool& endRecursion) {
        if (count >= 3) {
            return;
        }
        if (size > 110000) {
            //cout << "110,000 nodes!" << endl;
            endRecursion = true;
            return;
        }
        vector<string> moviesFromProfile;
        bool killSwitch = false;
        w.getProfileMovieLinks(nodes[name]->profileLink, moviesFromProfile);
        vector<string> castAtIndex;
        vector<string> profilesFromMovie;
        for (unsigned int i = 0; i < moviesFromProfile.size(); i++) {
            castAtIndex = w.getMovieRoster(moviesFromProfile.at(i), profilesFromMovie);
            for (unsigned int j = 0; j < castAtIndex.size(); j++) {
                if (killSwitch) {
                    break;
                }
                addEdge(name, castAtIndex.at(j));
                if (nodes[castAtIndex.at(j)]->profileLink == "") {
                    nodes[castAtIndex.at(j)]->setProfileLink(profilesFromMovie.at(j));
                }
                recursiveAddEdges(count + 1, castAtIndex.at(j), killSwitch);
            }
            castAtIndex.clear();
            if (killSwitch) {
                break;
            }
        }
        profilesFromMovie.clear();
        moviesFromProfile.clear();

    }
    void loopAddData() {
        vector<string> movieLinks; //links to all movies from topThousand at page i
        vector<string> names; //list of names from the movie at j
        vector<string> linksToProfiles; //links to actor's profile
        bool killSwitch = false;
        for (unsigned int i = 0; i < 11; i++) {
            movieLinks = w.getLinksFromSearch(w.extractTopThousand(to_string(i + 1)));
            if (killSwitch) { break; }
            for (unsigned int j = 0; j < movieLinks.size(); j++) {
                if (killSwitch) { break; }
                names = w.getMovieRoster(movieLinks.at(j), linksToProfiles); //now have linkstoprofiles set
                //we have all our names here, so go through names and add everyone in this movie as well as
                //everyone in their other movies
                for (unsigned int k = j + 1; k < names.size(); k++) {
                    addEdge(names.at(j), names.at(k));
                }
                for (unsigned int p = 0; p < names.size(); p++) {
                    if (nodes[names.at(p)]->profileLink == "") {
                        nodes[names.at(p)]->profileLink = linksToProfiles.at(p);
                    }
                    recursiveAddEdges(0, names.at(p), killSwitch);
                    if (killSwitch) { break; }
                }
                names.clear();
            }
            linksToProfiles.clear();
            movieLinks.clear();
        }
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