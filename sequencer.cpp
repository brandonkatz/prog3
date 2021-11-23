#include <iostream>
#include "sequencer.h"
using namespace std;
sequencer::sequencer(string a1, string a2, int a, int b, int c){
    s1 = a1;
    s2 = a2;
    m = a;
    c = b;
    d = c;
    int dimension=max(s1.length(),s2.length());
    pair<int,bool> costs[max][max];///will this declaration give us an error?
}
int sequencer::findCost(int i, int j, int tc){
     //first check to see if this node is already reached in table, or if we are at base case end of sequences
     
    if(i==s1.length() && j==s2.length())//length() or length()-1? length means we have already processed the last element or each and now would be out of bounds
        return tc;//// is this correct or do we need to change the value in table. won't i and j already be beyond table bounds?
    else if(costs[i][j].second==true){
        if(s1[i]==s2[j]){
            if(tc > costs[i][j]){
                costs[i][j]=tc;//here we reach an already visited i,j node, but we replace it with a more optimal head
                return findCost(i+1, j+1, tc+m);
            }
        }
        else
            return costs[i][j];
    }
    else{/////here we assume that node i,j has not been matched in any previous solution head
        if(s1[i]==s2[j]){
            costs[i][j]=tc;
            costs[i][j].second=true;//solid node i,j now has been visited
            return findCost(i+1,j+1,tc+m); 
        }
        else{///do we need to do a bound validity test before each of these calls?? 
            //obviously we can not do a deletion if a sequence is already at its tail
            //we cant deal with invalid access by returning a signal integer because this integer could always be naturally reached through combinations of actions
            if(i+1>s1.length() && j+1<=s2.length())
                return findCost(i,j+1,tc+d);//s1 would go out of bounds, so we skip s2 and end with a '_' for s1
            else if(j+1>s2.length() && i+1<=s1.length())
                return findCost(i+1,j,tc+d);
            else
                return min(findCost(i,j+1,tc+d), findCost(i+1,j,tc+d), findCost(i+1,j+1,tc+c));///recur for each way of deleting, and replacing base
        }
    }

}