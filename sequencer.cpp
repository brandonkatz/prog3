#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include "sequencer.h"
using namespace std;
sequencer::sequencer(string a1, string a2, float mm, float cc, float dd){
    s1 = a1;
    s2 = a2;
    m = mm;
    c = cc;
    d = dd;
    dimension=max(s1.length(),s2.length());//might not be needed, but can't hurt for now
    costs.resize(dimension+1);
    for(int i = 0; i<dimension+1; i++){
        costs[i].resize(dimension+1);/////////////////////DIMENSION +1????????
    }
    //cout<<costs[0][0].second<<endl; this proves that initialize to false
    ///NOW HAVE AN NxN VECTOR OF PAIR<int,bool> ???
    //pair<int,bool> costs[dimension][dimension];///will this declaration give us an error?
}
float sequencer::findCost(int i, int j, float tc){
    //cout<<"in the function: ";
   // cout<<"i: "<<i<<", j: "<<j<<", tc: "<<tc<<endl;
     //first check to see if this node is already reached in table, or if we are at base case end of sequences
    //cout<<"RIGHT BEFORE SEG FAULT??\n";
    if(i==s1.length() && j==s2.length()){//length() or length()-1? length means we have already processed the last element or each and now would be out of bounds
       // cout<<"hit end of path\n";
        return tc;//// is this correct or do we need to change the value in table. won't i and j already be beyond table bounds //CASSE WHERE INT RETURNED
    }
    //else if(){//temporary else if for catching seg fault?

    //}
    else if(costs[i][j].second==true){///THIS CAN ALSO CAUSE ILLEGAL ACCESS
       // cout<<"RIGHT BEFORE SEG FAULT??\n";
        if(s1[i]==s2[j]){
            if(tc > costs[i][j].first){
                costs[i][j].first=tc;//here we reach an already visited i,j node, but we replace it with a more optimal head
                return findCost(i+1, j+1, tc+m);
            }
        }
        else
            return costs[i][j].first; ////////////////CASE WHERE A TRUE INT IS RETURNED
    }
    else{/////here we assume that node i,j has not been matched in any previous solution head
       // cout<<"RIGHT BEFORE SEG FAULT??\n";
        if(s1[i]==s2[j]){//STILL NEED AN IF STATEMENT BEFORE THIS TO PREVENT ILLEGAL ACCESS???:?
            costs[i][j].first=tc;
            costs[i][j].second=true;//solid node i,j now has been visited
            return findCost(i+1,j+1,tc+m); 
        }
        else{///do we need to do a bound validity test before each of these calls?? 
            //obviously we can not do a deletion if a sequence is already at its tail
            //we cant deal with invalid access by returning a signal integer because this integer could always be naturally reached through combinations of actions
          //  cout<<"in last big else\n";
            if(i+1>s1.length() && j+1<=s2.length()){///SKIP j at end
             //   cout<<"in first\n";
                return findCost(i,j+1,tc+d);//s1 would go out of bounds, so we skip s2 and end with a '_' for s1
            }
            else if(j+1>s2.length() && i+1<=s1.length()){////SKIP i at end
              //  cout<<"in 2nd\n";
                //cout<<"d: "<<d<<endl;
                return findCost(i+1,j,tc+d);
            }
           // else if(j+1>s2.length() && i+1>s1.length() && ){//this catches it so that else statement is fine ...?
                //if(i<j)//this might not be enough, trying to account for which sequence to add trailing __
                    //skip j
                
        
            //}
            
            else{///careful with the 3rd one (c)
               // cout<<"in last else statement\n";
                //float skipj=findCost(i,j+1,tc+d);
                //float skipi=findCost(i+1,j,tc+d);
                //float replace=findCost(i+1,j+1,tc+c);
                //cout<<skipj<<" "<<skipi<<" "<<replace<<endl;
                return max({findCost(i,j+1,tc+d), findCost(i+1,j,tc+d), findCost(i+1,j+1,tc+c)});///recur for each way of deleting, and replacing base
            }//temporary cout statements above
        }
    }

}