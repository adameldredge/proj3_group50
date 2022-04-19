#pragma once

#include <iostream>
#include <fstream>
#include "../vcpkg/installed/x86-windows/include/cpr/cpr.h"
#include "../vcpkg/installed/x86-windows/include/gumbo.h"
#include <istream>
#include <vector>
#include <map>
#include <string>
#include "AdjacencyList.h"
#include "WebScraper.h"
using namespace std;

struct AdjacencyList {
	struct Person {
		Person() {
			name = "";
			company = "";
			sameName = nullptr;
			id = 0;
			visited = false;
			identified = false;
		}
		Person(string n, string c) {
			name = n;
			company = c;
			sameName = nullptr;
			id = 0;
			visited = false;
			identified = false;
		}
		Person operator=(const Person& d) {
			name = d.name;
			company = d.company;
			sameName = d.sameName;
			id = d.id;
			visited = d.visited;
			identified = d.identified;
			return *this;
		}
		bool operator==(const Person& d) {
			return ((d.name == name) && (d.company == company) && (d.adjNodes == adjNodes) && (d.id == id));
		}
		void setID(unsigned int i) {
			id = i;
		}
		unsigned int getID() {
			return id;
		}
		Person* getSameName() {
			return sameName;
		}
		void chainNames(Person* p) {
			if (sameName == nullptr) {
				sameName = p;
			}
			else {
				chainNames(sameName);
			}
		}
		void addAdj(Person* n) {
			adjNodes.push_back(n);
		}
		vector<Person*> getAdj() {
			return adjNodes;
		}
		string name;
		string company;
		unsigned int id;
		bool visited;
		bool identified;
		vector<Person*> adjNodes;
		Person* sameName;
	};
	/*struct Person {
		Person() {
			name = "";
			company = "";
			sameName = nullptr;
			id = 0;
		}
		Person(string n, string c) {
			name = n;
			company = c;
			sameName = nullptr;
			id = 0;
		}
		Person operator=(const Person& d) {
			name = d.name;
			company = d.company;
			sameName = d.sameName;
			id = d.id;
			return *this;
		}
		bool operator==(const Person& d) {
			return ((d.name == name) && (d.company == company) && (d.adjNodes == adjNodes) && (d.id == id));
		}
		void setID(unsigned int i) {
			id = i;
		}
		unsigned int getID() {
			return id;
		}
		Person* getSameName() {
			return sameName;
		}
		void chainNames(Person* p) {
			if (sameName == nullptr) {
				sameName = p;
			}
			else {
				chainNames(sameName);
			}
		}
		void addAdj(Person* n) {
			adjNodes.push_back(n);
		}
		vector<Person*> getAdj() {
			return adjNodes;
		}
		string name;
		string company;
		unsigned int id;
		vector<Person*> adjNodes;
		Person* sameName;
		bool identified;
		bool visited;
	};*/
	AdjacencyList() {
		root = nullptr;
		size = 0;
	}
	Person* newPerson(string name, string company, bool namePresent) {
		Person* p = new Person(name, company);
		p->setID(size + 1);
//		bool namePresent = false;
		if (namePresent) {
			nodes[name]->chainNames(p);
			size++;
		}
		else {
			if (root == nullptr) {
				root = p;
			}
			nodes.emplace(name, p);
			size++;
		}
		return p;
	}
	void addEdge(string srcName, string srcComp, string destName, string destComp) {
		Person* tempSrc;
		Person* tempDest;
		if (nodes.find(srcName) == nodes.end()) {
			tempSrc = newPerson(srcName, srcComp, false);
		}
		else {
			if (nodes[srcName]->company != srcComp) {
				tempSrc = newPerson(srcName, srcComp, true);
			}
			else {
				tempSrc = nodes[srcName];
				while (tempSrc->company != srcComp) {
					tempSrc = tempSrc->sameName;
				}
			}
		}
		if (nodes.find(destName) == nodes.end()) {
			tempDest = newPerson(destName, destComp, false);
		}
		else {
			if (nodes[destName]->company != destComp) {
				tempDest = newPerson(destName, destComp, true);
			}
			else {
				tempDest = nodes[destName];
				while (tempDest->company != destComp) {
					tempDest = tempDest->sameName;
				}
			}
		}
		tempSrc->addAdj(tempDest);
	}
	Person* getPerson(string name, unsigned int id_) {
		Person* temp = nodes[name];
		if (!temp) {
			return nullptr;
		}
		if (temp->id == id_) {
			return temp;
		}
		else {
			while (temp->id != id_ && temp != nullptr) {
				temp = temp->sameName;
			}
			return temp;
		}
	}
	void recursiveAddData(unsigned int count, string profileLink, string source, string sourceCompany) {
		if (count >= 6) {
			return;
		}
		pair<pair<vector<string>, vector<string>>, vector<string>> connections = w.getConnectionsAndLinks(w.getLinkToConnections(profileLink));
		for (unsigned int i = 0; i < connections.first.first.size(); i++) {
			addNamesFromScrape(connections.first, source, sourceCompany);
			recursiveAddData(count + 1, connections.second.at(i), connections.first.first.at(i), connections.first.second.at(i));
		}
	}

	void addNamesFromScrape(pair<vector<string>, vector<string>> names, string source, string sourceComp) {
		for (unsigned int i = 0; i < names.first.size(); i++) {
			addEdge(source, sourceComp, names.first.at(i), names.second.at(i));
		}
	}
	bool hasDestination(string dest, string destComp) {
		if (nodes.find(dest) == nodes.end()) {
			return false;
		}
		return (nodes[dest]->company == destComp);
	}
	
	//add algorithms here for dijk and bfs

private:
	Person* root;
	//size represents total number of PEOPLE stored, not necessarily unique names
	//can find the number of unique names by size - nodes.size
	int size;
	map<string, Person*> nodes;
	WebScraper w;
};

