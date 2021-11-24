#include <iostream>
#include <utility>
#include <vector>
#ifndef SEQUENCER_H
#define SEQUENCER_H
using namespace std;
class sequencer{
    public:
        sequencer(string a1, string a2, float mm, float cc, float dd);
        float findCost(int i, int j, float tc);
        float sendResult(int i, int j);
    private:
        int dimension;
        //pair<int,bool> costs[dimension][dimension];      fine, use vector of vectors instead
        vector<vector<pair<float,bool> > > costs; ////might have a major problem with this templating
        string s1;
        string s2;
        float m;
        float c;
        float d;
        //int tc;     do we want this?
};      
#endif