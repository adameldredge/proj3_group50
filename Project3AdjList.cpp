// Project3AdjList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include "WebScraper.h"
#include "AdjacencyList.h"
using namespace std;

int main() {
	//add userInterface here, mainly smfl stuff and variables to use on graph
	//once Courtney's stuff runs, we have four strings
	//use if and cout debugging to test getting info... use known profile and connection link
	string source, dest, srcComp, destComp;
	getline(cin, source);
	getline(cin, srcComp);
	getline(cin, dest);
	getline(cin, destComp);
	AdjacencyList graph;
	WebScraper w;
	//string srcInfo = w.extractSearchInfo(source);
	//string destInfo = w.extractSearchInfo(goal);
	//string linkToProfile = w.search_for_name(w.extractSearchInfo(source), source, srcComp);
	//string linkToConnections = w.getLinkToConnections(w.search_for_name(w.extractSearchInfo(source), source, srcComp));
	//string linkToGoal = w.search_for_name(w.extractSearchInfo(dest), dest, destComp);
	pair<pair<vector<string>, vector<string>>, vector<string>> connections;
	string profileLink = w.search_for_name(w.extractSearchInfo(source), source, srcComp);
	connections = w.getConnectionsAndLinks(w.getLinkToConnections(profileLink));
	graph.recursiveAddData(0, profileLink, source, srcComp);
	

	//go through source's connections and add them to graph with addEdge
	//we need to access those profiles, then look at their "following" tab or their connections area


	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
