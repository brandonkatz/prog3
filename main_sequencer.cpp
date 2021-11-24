#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include "sequencer.h"
using namespace std;
//int findCost(int i, int j, int tc, string s1, string s2);
int main(){
    /////input style will need to be changed later, but we can roll with it now for early implementing and testing purposes
    float m=2;//points added for a match
    float c=-.2;//points for a change/replacement (negative value)
    float d=-1.5;//points for deletion/skipping a base (negative value)
    //string s1="CTGGG";
    //string s2="ATTTGGGGGGGG"; archive these strings since they show an interesting bug when trailing G is increased
    string s1="ACATGAGACAGACAGACCCCCAGAGACAGACCCCTAGACACAGAGAGAGTATGCAGGACAGGGTTTTTGCCCAGGGTGGCAGTATG";
    string s2="AGGATTGAGGTATGGGTATGTTCCCGATTGAGTAGCCAGTATGAGCCAGAGTTTTTTACAAGTATTTTTCCCAGTAGCCAGAGAGAGAGTCACCCAGTACAGAGAGC";////WORRY ABOUT THE MISMATCH T,C at the START!!!!!!!!!!!! The continuous output starts at the last trailing G
    int i=0;
    int j=0;//iterators for s1 and s2, respectively
    //int dimension=max(s1.length(),s2.length());//do this in the class def
    ///MAKE SURE THAT THE BOOLS IN THE MATRIX BELOW START AS FALSE
    //pair<int,bool> costs[dimension][dimension];//hopefully this prevents illegal access? do we need to initialize all indices?
    float tc=0;
    //cout<<max({-3,-3,-3});
    //findCost(i,j,tc,s1,s2);  
    sequencer a(s1,s2,m,c,d);
    float answer = a.findCost(0,0,tc); //dont even need to pass "tc" cause it starts at 0?
    cout<<"optimal sequencing value: "<< answer<<endl;

    a.sendResult(s1.length(),s2.length());
}
