#include <iostream>
#include <vector>
#include <utility>
#include "sequencer.h"
using namespace std;
//int findCost(int i, int j, int tc, string s1, string s2);
int main(){
    /////input style will need to be changed later, but we can roll with it now for early implementing and testing purposes
    int m=4;//points added for a match
    int c=-2;//points for a change/replacement (negative value)
    int d=-3;//points for deletion/skipping a base (negative value)
    string s1="AATT";
    string s2="AATT";
    //cin>>m;
    //cin>>c;
    //cin>>d;
    int i=0;
    int j=0;//iterators for s1 and s2, respectively
    //int dimension=max(s1.length(),s2.length());//do this in the class def
    ///MAKE SURE THAT THE BOOLS IN THE MATRIX BELOW START AS FALSE
    //pair<int,bool> costs[dimension][dimension];//hopefully this prevents illegal access? do we need to initialize all indices?
    int tc=0;
    //findCost(i,j,tc,s1,s2);  
    sequencer a(s1,s2,m,c,d);
    int answer = a.findCost(i,j,0); //dont even need to pass "tc" cause it starts at 0?
}
