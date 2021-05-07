//
// Created by mina on 5/5/21.
//

#include <fstream>
#include "InputLanguageParser.h"

map<set<int>, string> dfaAccepted;
map<set<int>, map<set<int>, set<int>>> graph;
set<int> Start;

vector<Token> search(const string& line)
{
    vector<Token>answer;
    int old=0,temp = 0,i=0;
    string type;
    //TODO start state initialize
    set<int> CurrentState = Start;
    while(i<line.size())
    {
        if(graph[CurrentState].find(set<int>{line.at(i)}) != graph[CurrentState].end())
            CurrentState=graph[CurrentState][set<int>{line.at(i)}];
        else
        {
            answer.emplace_back(type,line.substr(old,temp+1));
            temp = i;
            old = i;
            --i;
            CurrentState=Start;
        }
        if(dfaAccepted.find(CurrentState)!=dfaAccepted.end())
        {
            type=dfaAccepted[CurrentState];
            temp = i;
        }
        ++i;
    }
    if(i == temp + 1)
    {
        type=dfaAccepted[CurrentState];
        answer.emplace_back(type,line.substr(old,i));
    }
    return answer;
}

vector<Token>parseFile(const string& Path,Dfa minimizedDFA)
{
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
