#ifndef Webscraper
#define Webscraper
#endif

#pragma once
#include <iostream>
#include <fstream>
#include "vcpkg/packages/cpr_x64-osx/include/cpr/cpr.h"
#include "vcpkg/packages/gumbo_x64-osx/include/gumbo.h"
#include <istream>
#include <vector>
#include <map>
#include <string>
using namespace std;

struct WebScraper {
    WebScraper() {
        test = "";
    }
    //adds names of directors and writers to vector of names plus their profile links in a different vector from snippet of html
    void getDirAndWriter(vector<string>& names, string& webInfo, vector<string>& profileLinks){
        int linkFind, index2;
        int distToTableEnd = INT_MAX;//webInfo.find("h4");
        linkFind = 0;
        linkFind = webInfo.find("a href=") + 9;
        while (distToTableEnd > linkFind) {
            webInfo = webInfo.substr(linkFind);
            linkFind = webInfo.find("\"\n");
            profileLinks.push_back("https://www.imdb.com/" + webInfo.substr(0, linkFind));
            webInfo = webInfo.substr(linkFind + 4);
            index2 = webInfo.find("\n<");
            names.push_back(webInfo.substr(0, index2));
            distToTableEnd = webInfo.find("ast_list");
            linkFind = webInfo.find("a href=") + 9;
            //distToTableEnd = webInfo.find("Cast");
        }
        //just to debug:
        try {
            webInfo = webInfo.substr(distToTableEnd);
        }
        catch (std::out_of_range) {
            return;
        }
        //linkFind = webInfo.find("writer");
        //webInfo = webInfo.substr(linkFind);
        //linkFind = webInfo.find("table class=");
        //webInfo = webInfo.substr(linkFind);
        //distToTableEnd = webInfo.find("/table");
        //while (distToTableEnd > linkFind) {
        //    linkFind = webInfo.find("a href=") + 9;
        //    webInfo = webInfo.substr(linkFind);
        //    linkFind = webInfo.find('"');
        //    profileLinks.push_back("https://www.imdb.com/" + webInfo.substr(0, linkFind));
        //    webInfo = webInfo.substr(linkFind);
        //    index2 = webInfo.find('>');
        //    webInfo = webInfo.substr(index2);
        //    if (webInfo[0] == ' ') {
        //        webInfo = webInfo.substr(1);
        //    }
        //    index2 = webInfo.find(" </a>");
        //    names.push_back(webInfo.substr(0, index2));
        //    distToTableEnd = webInfo.find("/table");
        //}
    }
    //takes inputs of a snippet of html code for movie site, vectors for names and links to profiles to be added to (just actors)
    void getCastMembers(string& webInfo, vector<string>& names, vector<string>& profileLinks) {
        /*int index = webInfo.find("table class=");
        webInfo = webInfo.substr(index);*/
        int index = webInfo.find("tr class=");
        int endOfCast = webInfo.find("dataHeaderWithBorder");
        while (index < endOfCast && index > 0) {
            webInfo = webInfo.substr(index);
            index = webInfo.find("a href=") + 9;
            webInfo = webInfo.substr(index);
            index = webInfo.find('\"');
            profileLinks.push_back("https://www.imdb.com/" + webInfo.substr(0, index));
            index = webInfo.find("title=") + 7;
            webInfo = webInfo.substr(index);
            index = webInfo.find('\"');
            names.push_back(webInfo.substr(0, index));
            index = webInfo.find("tr class=");
            endOfCast = webInfo.find("dataHeaderWithBorder");
        }
        try {
            webInfo = webInfo.substr(endOfCast);
        }
        catch (std::out_of_range) {
            return;
        }
    }
    //input is vector of names for crew to be added to (alr has director/writer and actors), snippet
    //of html code, vector for profile page urls
    void getCrew(vector<string>& names, string& webInfo, vector<string>& profileLinks) {
        int bodyIndex = webInfo.find("tbody");
        if (bodyIndex == -1) {
            return;
        }
        webInfo = webInfo.substr(bodyIndex);
        int rowIndex, linkPos, nameEnd;
        rowIndex = webInfo.find("td class=");
        string link = "https://www.imdb.com/";
        while (rowIndex != string::npos) {
            webInfo = webInfo.substr(rowIndex);
            linkPos = webInfo.find("a href=") + 9;
            webInfo = webInfo.substr(linkPos);
            linkPos = webInfo.find('\"');
            profileLinks.push_back(link + webInfo.substr(0, linkPos));
            linkPos = webInfo.find("\n>") + 3;
            webInfo = webInfo.substr(linkPos);
            nameEnd = webInfo.find("</a>") - 1;
            names.push_back(webInfo.substr(0, nameEnd));
            rowIndex = webInfo.find("td class=");
        }
        names.pop_back();
        profileLinks.pop_back();
    }

    void getProfileMovieLinks(string linkToProfile, vector<string>& movieLinks) {
        string webInfo = cpr::Get(cpr::Url{ linkToProfile }).text;
        unsigned int index = webInfo.find("filmo-category-section");
        webInfo = webInfo.substr(index);
        string linkToMovie;
        unsigned int linkEndIndex;
        unsigned int endIndex = INT_MAX;
        endIndex = webInfo.find("archive_footage");
        index = webInfo.find("a href=");
        while (index < endIndex) {
            webInfo = webInfo.substr(index + 8);
            linkEndIndex = webInfo.find('\"');
            linkToMovie = webInfo.substr(0, linkEndIndex);
            movieLinks.push_back("https://www.imdb.com" + linkToMovie);
            index = webInfo.find("filmo-row");
            index = webInfo.find("a href=");
        }
    }
    
    vector<string> getMovieRoster(string& link, vector<string>& profileLinks) {
        /*int test1, test2;
        test1 = link.find("https://");
        test2 = link.rfind("https://");
        if (test1 != test2) {
            link = link.substr(link.rfind("tt"));
            int p = link.find("?");
            link = link.substr(0, p);
            link = "https://imdb.com/title/" + link;
        }*/
        
        vector<string> retVal;
        int test1 = link.find("pro.");
        int test2 = link.find("help.");
        int check3 = link.find("title");
        if ((test1 != -1) || (test2 != -1) || (check3 == -1)) {
            return retVal;
        }
        //vector<string> profileLinks;
        string fullCastLinkEnd = "fullcredits?ref_=tt_cl_sm";
        int index = link.find("?ref");
        string linkToFullCast = link.substr(0, index); //make sure this goes up to the / after the /title/ part of link
        if (linkToFullCast.back() != '/') {
            linkToFullCast += '/';
        }
        linkToFullCast += fullCastLinkEnd;
        string htmlCode;
        try {
            htmlCode = cpr::Get(cpr::Url{ linkToFullCast }).text;
            index = htmlCode.find("ullcredits_content");
        }
        catch (exception e) { return retVal; }
        int index2 = htmlCode.find("contribute-main-section");
        htmlCode = htmlCode.substr(index, index2); //all htmlCode for the cast/crew
        index = htmlCode.find("table class=");
        htmlCode = htmlCode.substr(index);
        getDirAndWriter(retVal, htmlCode, profileLinks);
        getCastMembers(htmlCode, retVal, profileLinks);
        getCrew(retVal, htmlCode, profileLinks);
        //will have a list of the entire cast for this movie plus a link to their profile at the same index
        //
        return retVal;

    }
    string extractTopThousand(string pageNum) {
        string link = "https://www.imdb.com/list/ls009131936/";
        if (pageNum != "1") {
            link += "?page=" + pageNum;
        }
        cpr::Url url = cpr::Url { link };
        string response = cpr::Get(url).text;
        return response;
    }
    vector<string> getLinksFromSearch(string webInfo) {
        vector<string> retVal;
        string linkKey = "lister-list";
        string linkBase = "https://www.imdb.com";
        //string linkEnd = "fullcredits/?ref_=tt_cl_sm";
        int index = webInfo.find(linkKey);
        int distToLinkEnd = 0;
        string htmlCode = webInfo.substr(index);
        linkKey = "lister-item-content";
        index = webInfo.find(linkKey);
        while (index != string::npos) {
            htmlCode = htmlCode.substr(index);
            htmlCode = htmlCode.substr(htmlCode.find("lister-item-index unbold text-primary"));
            htmlCode = htmlCode.substr(htmlCode.find("href="));
            htmlCode = htmlCode.substr(htmlCode.find('/'));
            distToLinkEnd = htmlCode.find('"');
            retVal.push_back(linkBase + htmlCode.substr(0, distToLinkEnd));
            index = htmlCode.find(linkKey);
        }
        return retVal;
    }
    string test;
};
