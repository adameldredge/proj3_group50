#include <iostream>
#include <SFML/Graphics.hpp>
#include "NEWadjList.h"
using namespace std;

int main()
{
    //change this variable to get different screens
    int degreesOfSeparation = 6;

    AdjacencyList* Graph = new AdjacencyList;
    Graph->addEdge("ladybug","coob");
    vector<AdjacencyList::Person*> fakeOutput;
    vector<AdjacencyList::Person*> output;
    float djTime;
    float dfsTime;

    int enterCount = 0;

    sf::RenderWindow window(sf::VideoMode(2000, 1500), "IMDB Degrees of Separation");

    //creates the new window with correct title
    sf::RectangleShape inputRec1;
    inputRec1.setSize(sf::Vector2f(100, 600));
    inputRec1.rotate(90);
    inputRec1.setPosition(640, 270);
    inputRec1.setOutlineColor(sf::Color::Cyan);
    inputRec1.setOutlineThickness(5);
    inputRec1.setFillColor(sf::Color::Transparent);

    sf::RectangleShape inputRec2;
    inputRec2.setSize(sf::Vector2f(100, 600));
    inputRec2.rotate(90);
    inputRec2.setPosition(1960, 270);
    inputRec2.setOutlineColor(sf::Color::Cyan);
    inputRec2.setOutlineThickness(5);
    inputRec2.setFillColor(sf::Color::Transparent);

    sf::RectangleShape dosRectangle;
    dosRectangle.setSize(sf::Vector2f(120, 80));
    dosRectangle.setPosition(940, 525);
    dosRectangle.setOutlineColor(sf::Color::Red);
    dosRectangle.setOutlineThickness(5);
    dosRectangle.setFillColor(sf::Color::Transparent);

    sf::RectangleShape firstBottomRectangle;
    firstBottomRectangle.setSize(sf::Vector2f (380, 75));
    firstBottomRectangle.setPosition(60, 1350);
    firstBottomRectangle.setOutlineColor(sf::Color::Yellow);
    firstBottomRectangle.setOutlineThickness(5);
    firstBottomRectangle.setFillColor(sf::Color::Transparent);

    sf::RectangleShape secondBottomRectangle;
    secondBottomRectangle.setSize(sf::Vector2f (380, 75));
    secondBottomRectangle.setPosition(560, 1350);
    secondBottomRectangle.setOutlineColor(sf::Color::Yellow);
    secondBottomRectangle.setOutlineThickness(5);
    secondBottomRectangle.setFillColor(sf::Color::Transparent);

    sf::RectangleShape thirdBottomRectangle;
    thirdBottomRectangle.setSize(sf::Vector2f (380, 75));
    thirdBottomRectangle.setPosition(1060, 1350);
    thirdBottomRectangle.setOutlineColor(sf::Color::Yellow);
    thirdBottomRectangle.setOutlineThickness(5);
    thirdBottomRectangle.setFillColor(sf::Color::Transparent);

    sf::RectangleShape fourthBottomRectangle;
    fourthBottomRectangle.setSize(sf::Vector2f (380, 75));
    fourthBottomRectangle.setPosition(1560, 1350);
    fourthBottomRectangle.setOutlineColor(sf::Color::Yellow);
    fourthBottomRectangle.setOutlineThickness(5);
    fourthBottomRectangle.setFillColor(sf::Color::Transparent);

    sf::RectangleShape rectangleCo1;
    rectangleCo1.setSize(sf::Vector2f(800, 90));
    rectangleCo1.setPosition(40, 450);
    rectangleCo1.setOutlineColor(sf::Color::Cyan);
    rectangleCo1.setOutlineThickness(5);
    rectangleCo1.setFillColor(sf::Color::Transparent);

    sf::RectangleShape rectangleCo2;
    rectangleCo2.setSize(sf::Vector2f(800, 90));
    rectangleCo2.setPosition(1160, 450);
    rectangleCo2.setOutlineColor(sf::Color::Cyan);
    rectangleCo2.setOutlineThickness(5);
    rectangleCo2.setFillColor(sf::Color::Transparent);

    sf::RectangleShape oneThirdBox;
    oneThirdBox.setSize(sf::Vector2f(500, 75));
    oneThirdBox.setPosition(56, 1350);
    oneThirdBox.setOutlineColor(sf::Color::Yellow);
    oneThirdBox.setOutlineThickness(5);
    oneThirdBox.setFillColor(sf::Color::Transparent);

    sf::RectangleShape twoThirdBox;
    twoThirdBox.setSize(sf::Vector2f(500, 75));
    twoThirdBox.setPosition(732, 1350);
    twoThirdBox.setOutlineColor(sf::Color::Yellow);
    twoThirdBox.setOutlineThickness(5);
    twoThirdBox.setFillColor(sf::Color::Transparent);

    sf::RectangleShape threeThirdBox;
    threeThirdBox.setSize(sf::Vector2f(500, 75));
    threeThirdBox.setPosition(1430, 1350);
    threeThirdBox.setOutlineColor(sf::Color::Yellow);
    threeThirdBox.setOutlineThickness(5);
    threeThirdBox.setFillColor(sf::Color::Transparent);

    sf::RectangleShape oneHalfBox;
    oneHalfBox.setSize(sf::Vector2f(500, 75));
    oneHalfBox.setPosition(1430, 1350);
    oneHalfBox.setOutlineColor(sf::Color::Yellow);
    oneHalfBox.setOutlineThickness(5);
    oneHalfBox.setFillColor(sf::Color::Transparent);

    sf::RectangleShape oneBigBox;
    oneBigBox.setSize(sf::Vector2f(1900, 75));
    oneBigBox.setPosition(50, 1350);
    oneBigBox.setOutlineColor(sf::Color::Yellow);
    oneBigBox.setOutlineThickness(5);
    oneBigBox.setFillColor(sf::Color::Transparent);


    sf::RectangleShape oneFifthBox;
    oneFifthBox.setSize(sf::Vector2f(500, 75));
    oneFifthBox.setPosition(56, 1050);
    oneFifthBox.setOutlineColor(sf::Color::Yellow);
    oneFifthBox.setOutlineThickness(5);
    oneFifthBox.setFillColor(sf::Color::Transparent);

    sf::RectangleShape fiveFifthBox;
    fiveFifthBox.setSize(sf::Vector2f(500, 75));
    fiveFifthBox.setPosition(1430, 1050);
    fiveFifthBox.setOutlineColor(sf::Color::Yellow);
    fiveFifthBox.setOutlineThickness(5);
    fiveFifthBox.setFillColor(sf::Color::Transparent);

    sf::RectangleShape djBox;
    djBox.setSize(sf::Vector2f(200,50));
    djBox.setPosition(565,820);
    djBox.setOutlineColor(sf::Color::Red);
    djBox.setOutlineThickness(5);
    djBox.setFillColor(sf::Color::Transparent);

    sf::RectangleShape dfsBox;
    dfsBox.setSize(sf::Vector2f(200,50));
    dfsBox.setPosition(1250,820);
    dfsBox.setOutlineColor(sf::Color::Red);
    dfsBox.setOutlineThickness(5);
    dfsBox.setFillColor(sf::Color::Transparent);


    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Font font2;
    font2.loadFromFile("abelFont.ttf");

    sf::Text downArrow1;
    downArrow1.setString("-------------------------->");
    downArrow1.rotate(90);
    downArrow1.setFont(font);
    downArrow1.setPosition(130,400);
    downArrow1.setFillColor(sf::Color::Yellow);
    downArrow1.setCharacterSize(100);

    sf::Text upArrow1;
    upArrow1.setString("<--------------------------");
    upArrow1.rotate(90);
    upArrow1.setFont(font);
    upArrow1.setPosition(2000,400);
    upArrow1.setFillColor(sf::Color::Yellow);
    upArrow1.setCharacterSize(100);

    sf::Text downArrow2;
    downArrow2.setString("----------------->");
    downArrow2.rotate(90);
    downArrow2.setFont(font);
    downArrow2.setPosition(130,400);
    downArrow2.setFillColor(sf::Color::Yellow);
    downArrow2.setCharacterSize(100);

    sf::Text downArrow3;
    downArrow3.setString("-------->");
    downArrow3.rotate(90);
    downArrow3.setFont(font);
    downArrow3.setPosition(100,1150);
    downArrow3.setFillColor(sf::Color::Yellow);
    downArrow3.setCharacterSize(50);

    sf::Text upArrow2;
    upArrow2.setString("<-----------------");
    upArrow2.rotate(90);
    upArrow2.setFont(font);
    upArrow2.setPosition(2000,400);
    upArrow2.setFillColor(sf::Color::Yellow);
    upArrow2.setCharacterSize(100);

    sf::Text upArrow3;
    upArrow3.setString("<--------");
    upArrow3.rotate(90);
    upArrow3.setFont(font);
    upArrow3.setPosition(1960,1150);
    upArrow3.setFillColor(sf::Color::Yellow);
    upArrow3.setCharacterSize(50);

    sf::Text arrow41;
    arrow41.setString("--->");
    arrow41.setFont(font);
    arrow41.setPosition(460, 1350);
    arrow41.setFillColor(sf::Color::Yellow);
    arrow41.setCharacterSize(50);

    sf::Text arrow42;
    arrow42.setString("--->");
    arrow42.setFont(font);
    arrow42.setPosition(960, 1350);
    arrow42.setFillColor(sf::Color::Yellow);
    arrow42.setCharacterSize(50);

    sf::Text arrow43;
    arrow43.setString("--->");
    arrow43.setFont(font);
    arrow43.setPosition(1460, 1350);
    arrow43.setFillColor(sf::Color::Yellow);
    arrow43.setCharacterSize(50);

    sf::Text arrow31;
    arrow31.setString("------>");
    arrow31.setFont(font);
    arrow31.setPosition(580, 1350);
    arrow31.setFillColor(sf::Color::Yellow);
    arrow31.setCharacterSize(50);

    sf::Text arrow32;
    arrow32.setString("------>");
    arrow32.setFont(font);
    arrow32.setPosition(1260, 1350);
    arrow32.setFillColor(sf::Color::Yellow);
    arrow32.setCharacterSize(50);

    sf::Text arrow21;
    arrow21.setString("---------------------------->");
    arrow21.setFont(font);
    arrow21.setPosition(580, 1330);
    arrow21.setFillColor(sf::Color::Yellow);
    arrow21.setCharacterSize(80);

    sf::Text arrow11;
    arrow11.setString("---------------------->");
    arrow11.setFont(font);
    arrow11.setPosition(675, 260);
    arrow11.setColor(sf::Color::Yellow);
    arrow11.setCharacterSize(80);

    sf::Text arrow01;
    arrow01.setString("<--------------------->");
    arrow01.setFont(font);
    arrow01.setPosition(665, 260);
    arrow01.setColor(sf::Color::Yellow);
    arrow01.setCharacterSize(80);

    sf::Text header;
    header.setString("IMDB Connection Path");
    header.setFont(font);
    header.setCharacterSize(100);
    header.setFillColor(sf::Color::Cyan);
    header.setStyle(sf::Text::Bold | sf::Text::Underlined);
    header.setPosition(485, 35);

    sf::Text input1;
    input1.setString("Source Actor:");
    input1.setFont(font2);
    input1.setFillColor(sf::Color::Cyan);
    input1.setCharacterSize(50);
    input1.setPosition(50, 200);

    sf::Text input2;
    input2.setString("Destination Actor:");
    input2.setFont(font2);
    input2.setFillColor(sf::Color::Cyan);
    input2.setCharacterSize(50);
    input2.setPosition(1600, 200);

    sf::Text company1;
    company1.setString("Company 1:");
    company1.setFont(font2);
    company1.setFillColor(sf::Color::Cyan);
    company1.setCharacterSize(40);
    company1.setPosition(50, 385);

    sf::Text company2;
    company2.setString("Company 2:");
    company2.setFont(font2);
    company2.setFillColor(sf::Color::Cyan);
    company2.setCharacterSize(40);
    company2.setPosition(1800, 385);

    sf::Text degreesOfSep;
    degreesOfSep.setString("Degrees of Separation:");
    degreesOfSep.setFont(font2);
    degreesOfSep.setFillColor(sf::Color::Red);
    degreesOfSep.setCharacterSize(75);
    degreesOfSep.setPosition(676, 400);

    sf::Text degreesOfSep6;
    degreesOfSep6.setString("6");
    degreesOfSep6.setFont(font2);
    degreesOfSep6.setFillColor(sf::Color::Red);
    degreesOfSep6.setCharacterSize(70);
    degreesOfSep6.setPosition(985, 520);

    sf::Text degreesOfSep5;
    degreesOfSep5.setString("5");
    degreesOfSep5.setFont(font2);
    degreesOfSep5.setFillColor(sf::Color::Red);
    degreesOfSep5.setCharacterSize(70);
    degreesOfSep5.setPosition(985, 520);

    sf::Text degreesOfSep4;
    degreesOfSep4.setString("4");
    degreesOfSep4.setFont(font2);
    degreesOfSep4.setFillColor(sf::Color::Red);
    degreesOfSep4.setCharacterSize(70);
    degreesOfSep4.setPosition(985, 520);

    sf::Text degreesOfSep3;
    degreesOfSep3.setString("3");
    degreesOfSep3.setFont(font2);
    degreesOfSep3.setFillColor(sf::Color::Red);
    degreesOfSep3.setCharacterSize(70);
    degreesOfSep3.setPosition(985, 520);

    sf::Text degreesOfSep2;
    degreesOfSep2.setString("2");
    degreesOfSep2.setFont(font2);
    degreesOfSep2.setFillColor(sf::Color::Red);
    degreesOfSep2.setCharacterSize(70);
    degreesOfSep2.setPosition(985, 520);

    sf::Text degreesOfSep1;
    degreesOfSep1.setString("1");
    degreesOfSep1.setFont(font2);
    degreesOfSep1.setFillColor(sf::Color::Red);
    degreesOfSep1.setCharacterSize(70);
    degreesOfSep1.setPosition(985, 520);

    sf::Text degreesOfSep0;
    degreesOfSep0.setString("0");
    degreesOfSep0.setFont(font2);
    degreesOfSep0.setFillColor(sf::Color::Red);
    degreesOfSep0.setCharacterSize(70);
    degreesOfSep0.setPosition(985, 520);

    sf::Text djText;
    djText.setString("Time to run Dijkstra's:");
    djText.setFont(font2);
    djText.setFillColor(sf::Color::Red);
    djText.setCharacterSize(45);
    djText.setPosition(480, 750);

    sf::Text dfsText;
    dfsText.setString("Time to run DFS:");
    dfsText.setFont(font2);
    dfsText.setFillColor(sf::Color::Red);
    dfsText.setCharacterSize(45);
    dfsText.setPosition(1210, 750);

    string str;
    string str2;
    string company1String;
    string company2String;
    //gets put into str. can use str to manipulate
    sf::Text text;
    sf::Text djTimer;
    sf::Text dfsTimer;
    sf::Text inputText2;
    sf::Text company1Text;
    sf::Text company2Text;
    bool input1BoxClicked = false;
    bool input2BoxClicked = false;
    bool company1BoxClicked = false;
    bool company2BoxClicked = false;

    while (window.isOpen())
    {
        window.clear();
        sf::Event event;


        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed){
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                //cout << mousePosition.x << ", " << mousePosition.y << endl;

                if(mousePosition.x >= 40 && mousePosition.x <= 645 && mousePosition.y >=270 && mousePosition.y <= 375){
                    input1BoxClicked = true;
                }
                else{
                    input1BoxClicked = false;
                }
                if(mousePosition.x >= 1360 && mousePosition.x <= 1965 && mousePosition.y >=270 && mousePosition.y <= 375){
                    input2BoxClicked = true;
                }
                else{
                    input2BoxClicked = false;
                }
                if(mousePosition.x >= 1160 && mousePosition.x <= 1960 && mousePosition.y >=450 && mousePosition.y <= 545){
                    company2BoxClicked = true;
                }
                else{
                    company2BoxClicked = false;
                }
                if(mousePosition.x >= 40 && mousePosition.x <= 840 && mousePosition.y >=450 && mousePosition.y <= 545){
                    company1BoxClicked = true;
                }
                else{
                    company1BoxClicked = false;
                }

            }
            if(input1BoxClicked){
                if(event.type == sf::Event::TextEntered){
                    if(event.text.unicode < 128){
                        str += static_cast<char>(event.text.unicode);
                        text.setString(str);
                        text.setFont(font);
                        text.setCharacterSize(40);
                        text.setPosition(65, 300);
                    }
                }
                if (event.key.code == sf::Keyboard::BackSpace) {
                    if (!str.empty())
                        str.pop_back();// as Laurent pointed out
                        //input_text.erase(--input_text.end());
                }
                if (event.key.code == sf::Keyboard::Return){
                    input1BoxClicked = false;
                    enterCount++;
                }
            }
            if(input2BoxClicked){
                if(event.type == sf::Event::TextEntered){
                    if(event.text.unicode < 128){
                        str2 += static_cast<char>(event.text.unicode);
                        inputText2.setString(str2);
                        inputText2.setFont(font);
                        inputText2.setCharacterSize(40);
                        inputText2.setPosition(1380, 300);
                    }
                }
                if (event.key.code == sf::Keyboard::BackSpace) {
                    if (!str2.empty())
                        str2.pop_back();// as Laurent pointed out
                        //input_text.erase(--input_text.end());
                }
                if (event.key.code == sf::Keyboard::Return){
                    input2BoxClicked = false;
                    enterCount++;
                }
            }
            if (enterCount == 2)
            {
                clock_t time;
                time = clock();
                output = Graph->dijkstra(Graph->nodes, Graph->nodes[str],Graph->nodes[str2]);
                time = clock() - time;
                djTime = (float)time/CLOCKS_PER_SEC;

                djTimer.setString(to_string(djTime));
                djTimer.setFont(font2);
                djTimer.setFillColor(sf::Color::Red);
                djTimer.setCharacterSize(30);
                djTimer.setPosition(610, 825);

                time = clock();
                fakeOutput = Graph->DFSvsBFS(Graph->nodes);
                time = clock() - time;
                dfsTime = (float)time/CLOCKS_PER_SEC;

                dfsTimer.setString(to_string(djTime));
                dfsTimer.setFont(font2);
                dfsTimer.setFillColor(sf::Color::Red);
                dfsTimer.setCharacterSize(30);
                dfsTimer.setPosition(1295, 825);

                enterCount++;
            }



        }

        degreesOfSeparation = 6;
        //stuff always there:
        window.draw(header);
        window.draw(input1);
        window.draw(input2);
        window.draw(inputRec1);
        window.draw(inputRec2);
        window.draw(degreesOfSep);
        window.draw(dosRectangle);
        window.draw(text);
        window.draw(djBox);
        window.draw(dfsBox);
        window.draw(djTimer);
        window.draw(dfsTimer);
        window.draw(dfsText);
        window.draw(djText);
        window.draw(inputText2);

        if(degreesOfSeparation == 5){
            // Create text for indices 1 - 4
            window.draw(degreesOfSep5);
            window.draw(firstBottomRectangle);
            window.draw(secondBottomRectangle);
            window.draw(thirdBottomRectangle);
            window.draw(fourthBottomRectangle);
            window.draw(downArrow1);
            window.draw(upArrow1);
            window.draw(arrow41);
            window.draw(arrow42);
            window.draw(arrow43);

            sf::Text first;
            first.setString(output.at(1)->name);
            first.setFont(font2);
            first.setFillColor(sf::Color::White);
            first.setCharacterSize(45);
            first.setPosition(1210, 750);

            sf::Text second;
            second.setString(output.at(2)->name);
            second.setFont(font2);
            second.setFillColor(sf::Color::White);
            second.setCharacterSize(45);
            second.setPosition(1210, 750);

            sf::Text third;
            third.setString(output.at(3)->name);
            third.setFont(font2);
            third.setFillColor(sf::Color::White);
            third.setCharacterSize(45);
            third.setPosition(1210, 750);

            sf::Text fourth;
            fourth.setString(output.at(4)->name);
            fourth.setFont(font2);
            fourth.setFillColor(sf::Color::White);
            fourth.setCharacterSize(45);
            fourth.setPosition(1210, 750);

            window.draw(first);
            window.draw(second);
            window.draw(third);
            window.draw(fourth);
        }
        else if(degreesOfSeparation == 4){
            // Create text for indices 1-3
            window.draw(degreesOfSep4);
            window.draw(downArrow1);
            window.draw(upArrow1);
            window.draw(oneThirdBox);
            window.draw(twoThirdBox);
            window.draw(threeThirdBox);
            window.draw(arrow31);
            window.draw(arrow32);

            sf::Text first;
            first.setString(output.at(1)->name);
            first.setFont(font2);
            first.setFillColor(sf::Color::White);
            first.setCharacterSize(45);
            first.setPosition(1210, 750);

            sf::Text second;
            second.setString(output.at(2)->name);
            second.setFont(font2);
            second.setFillColor(sf::Color::White);
            second.setCharacterSize(45);
            second.setPosition(1210, 750);

            sf::Text third;
            third.setString(output.at(3)->name);
            third.setFont(font2);
            third.setFillColor(sf::Color::White);
            third.setCharacterSize(45);
            third.setPosition(1210, 750);

            window.draw(first);
            window.draw(second);
            window.draw(third);
        }
        else if(degreesOfSeparation == 3){
            // Create text for indices 1-2
            window.draw(degreesOfSep3);
            window.draw(downArrow1);
            window.draw(upArrow1);
            window.draw(oneThirdBox);
            window.draw(threeThirdBox);
            window.draw(arrow21);

            sf::Text first;
            first.setString(output.at(1)->name);
            first.setFont(font2);
            first.setFillColor(sf::Color::White);
            first.setCharacterSize(45);
            first.setPosition(1210, 750);

            sf::Text second;
            second.setString(output.at(2)->name);
            second.setFont(font2);
            second.setFillColor(sf::Color::White);
            second.setCharacterSize(45);
            second.setPosition(1210, 750);

            window.draw(first);
            window.draw(second);
        }
        else if(degreesOfSeparation == 2){
            // Create text for index 1
            window.draw(degreesOfSep2);
            window.draw(downArrow1);
            window.draw(upArrow1);
            window.draw(oneBigBox);


            sf::Text first;
            first.setString(output.at(1)->name);
            first.setFont(font2);
            first.setFillColor(sf::Color::White);
            first.setCharacterSize(45);
            first.setPosition(1210, 750);

            window.draw(first);
        }
        else if(degreesOfSeparation == 1){
            window.draw(degreesOfSep1);
            window.draw(arrow11);
        }
        else if(degreesOfSeparation == 0){
            window.draw(degreesOfSep0);
            window.draw(arrow01);
        }
        else if(degreesOfSeparation == 6){
            // Create text for indices 1-5
            sf::Text first;
            first.setString(output.at(1)->name);
            first.setFont(font2);
            first.setFillColor(sf::Color::White);
            first.setCharacterSize(50);
            first.setPosition(125, 1055);

            sf::Text second;
            second.setString(output.at(2)->name);
            second.setFont(font2);
            second.setFillColor(sf::Color::White);
            second.setCharacterSize(50);
            second.setPosition(125, 1355);

            sf::Text third;
            third.setString(output.at(3)->name);
            third.setFont(font2);
            third.setFillColor(sf::Color::White);
            third.setCharacterSize(50);
            third.setPosition(815, 1355);

            sf::Text fourth;
            fourth.setString(output.at(4)->name);
            fourth.setFont(font2);
            fourth.setFillColor(sf::Color::White);
            fourth.setCharacterSize(50);
            fourth.setPosition(1515, 1355);

            sf::Text fifth;
            fifth.setString(output.at(5)->name);
            fifth.setFont(font2);
            fifth.setFillColor(sf::Color::White);
            fifth.setCharacterSize(50);
            fifth.setPosition(1515, 1055);

            window.draw(degreesOfSep6);

            window.draw(first);
            window.draw(second);
            window.draw(third);
            window.draw(fourth);
            window.draw(fifth);
            window.draw(oneThirdBox);
            window.draw(twoThirdBox);
            window.draw(threeThirdBox);
            window.draw(oneFifthBox);
            window.draw(fiveFifthBox);
            window.draw(arrow31);
            window.draw(arrow32);
            window.draw(downArrow2);
            window.draw(upArrow2);
            window.draw(upArrow3);
            window.draw(downArrow3);
        }










        window.display();

    }
}
