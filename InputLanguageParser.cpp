//
// Created by mina on 5/5/21.
//
#include <iostream>
#include "InputLanguageParser.h"

InputLanguageParser::InputLanguageParser() = default;

InputLanguageParser::InputLanguageParser(map<set<int>, map<string, set<int>>> dfaGraph,
                                         map<set<int>, string> dfaAcceptedStates, set<int> StartState) {
    graph = dfaGraph;
    dfaAccepted = dfaAcceptedStates;
    Start = StartState;
}

vector<Token> InputLanguageParser::search(const string &line) {
    vector<Token>answer;
    int old=0,i=0;
    string type;
    //TODO start state initialize
    set<int> CurrentState = Start;
    while(i<line.size())
    {
        if(graph[CurrentState].find(string(1,line.at(i))) != graph[CurrentState].end())
            CurrentState=graph[CurrentState][string(1,line.at(i))];
        else
        {
            answer.emplace_back(type,line.substr(old,i-old));
            if(string(1,line.at(i))==" " ||string(1,line.at(i))=="\t")
                old = i+1;
            else
            {
                old = i;
                --i;
            }
            CurrentState=Start;
        }
        if(dfaAccepted.find(CurrentState)!=dfaAccepted.end())
            type=dfaAccepted[CurrentState];
        ++i;
    }
    type=dfaAccepted[CurrentState];
    answer.emplace_back(type,line.substr(old,i-old));
    return answer;
}

vector<Token> InputLanguageParser::parseFile(const string &Path) {
    vector<Token> answer;
    fstream file;
    file.open(Path, ios::in);
    string line;
    while(getline(file, line))
    {
        for(const Token& t:search(line))
            answer.emplace_back(t);
    }
    return answer;
}