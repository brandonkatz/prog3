#include <iostream>
#include <utility>
#ifndef SEQUENCER_H
#define SEQUENCER_H
using namespace std;
class sequencer{
    public:
        sequencer(string a1, string a2, int a, int b, int c);
        int findCost(int i, int j, int tc);
    private:
        pair<int,bool> costs[][];
        string s1;
        string s2;
        int m;
        int c;
        int d;
        //int tc;     do we want this?
};      
#endif