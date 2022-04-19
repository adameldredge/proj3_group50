#ifndef Webscraper
#define Webscraper
#endif

#pragma once
#include <iostream>
#include <fstream>
#include "../vcpkg/installed/x86-windows/include/cpr/cpr.h"
#include "../vcpkg/installed/x86-windows/include/gumbo.h"
#include <istream>
#include <vector>
#include <map>
#include <string>
using namespace std;

struct WebScraper {
    WebScraper() {
        test = "";
    }
    string search_for_name(string webInfo, string name, string company) {
        string nameKey = "<a class=" + '"';
        nameKey += "app-aware-link" + '"';
        nameKey += " href=" + '"';
        string link = "https://www.linkedin.com/in/";
        string username;
        string companyKey = "<div class = " + '"';
        companyKey += "entity-result__primary-subtitle t-14 t-black t-normal";
        for (unsigned int i : webInfo) {
            if (webInfo.substr(i, 61) == (nameKey + link)) {
                username = "";
                for (unsigned int j = i + 61; j < webInfo.size(); j++) {
                    if (webInfo[j] == '"') {
                        break;
                    }
                    username += webInfo[j];
                }
            }
            if (webInfo.substr(i, 68) == companyKey) {
                for (unsigned int k = i + 69; k < webInfo.size(); k++) {
                    if (webInfo.substr(k, company.size() + 3) == "at " + company) {
                        return link + username;
                    }
                    else if (webInfo.substr(k, 6) == "</div>") {
                        break;
                    }
                }
            }
        }
        cout << "Error: user profile not found. Please ensure your input is accurate and case-sensitive for the name and company for this user" << endl;
        return "";
    }
    string extractSearchInfo(string searchName) {
        string addToURL = searchName;
        int index = addToURL.find(' ');
        addToURL.replace(index, index + 1, "%20");
        addToURL += searchName.substr(index + 1);
        cpr::Url url = cpr::Url{ "https://www.linkedin.com/search/results/people/?keywords=" + addToURL + "&origin=GLOBAL_SEARCH_HEADER&sid=2a2" };
        cpr::Response response = cpr::Get(url);
        //cout << response.text;
        return response.text;
    }
    string getLinkToConnections(string profileLink) {
        cpr::Url url = cpr::Url{ profileLink };
        cpr::Response response = cpr::Get(url);
        string htmlCode = response.text;
        int index = htmlCode.find("<a href=\"/search/results/people/?connectionOf");
        htmlCode = htmlCode.substr(index);
        index = htmlCode.find(" id=\"");
        htmlCode = htmlCode.substr(0, index);
        htmlCode = htmlCode.substr(9);
        htmlCode = "https://www.linkedin.com" + htmlCode;
        return htmlCode;
    }
    pair<pair<vector<string>, vector<string>>, vector<string>> getConnectionsAndLinks(string connectLink) {
        //first pair is name, company, second is link
        string name, company, link;
        pair<pair<vector<string>, vector<string>>, vector<string>> retVal;
        cpr::Url url = cpr::Url{ connectLink };
        cpr::Response response = cpr::Get(url);
        string htmlCode = response.text;
        int index = htmlCode.find("<a class=\"app-aware-link\" href=\"https://www.linkedin.com/in/");;
        int distToLink = 0;
        int endOfLink = 0;
        link = "https://www.linkedin.com/in/";
        while (index != string::npos) {
            name = "";
            company = "";
            htmlCode = htmlCode.substr(index);
            distToLink = htmlCode.find("https://");
            endOfLink = htmlCode.find('>');
            if (distToLink != string::npos) {
                htmlCode = htmlCode.substr(distToLink);
            }
            else {
                break;
            }
            retVal.second.push_back(htmlCode.substr(0, endOfLink));
            index = htmlCode.find("<span aria-hidden=\"true\"" + 25);
            if (index != string::npos) {
                htmlCode = htmlCode.substr(index);
                index = htmlCode.find('"');
                htmlCode = htmlCode.substr(index + 1);
                endOfLink = htmlCode.find('"');
                name = htmlCode.substr(0, endOfLink);
                retVal.first.first.push_back(name);
            }
            index = htmlCode.find("<div class =\"entity-result__primary-subtitle t-14 t-black t-normal\">");
            htmlCode = htmlCode.substr(index + 1);
            index = htmlCode.find(" at ");
            htmlCode = htmlCode.substr(index + 4);
            index = htmlCode.find('<');
            company = htmlCode.substr(0, index);
            retVal.first.second.push_back(company);
            index = htmlCode.find("<a class=\"app-aware-link\" href=\"https://www.linkedin.com/in/");
        }
        return retVal;
    }
    string test;
};
