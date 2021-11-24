#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include "sequencer.h"
#include <float.h>
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
    for(int i=0;i<dimension;i++){
        for(int j=0;j<dimension;j++){
        costs[i][j].first=FLT_MIN;
      }
    }
}
float sequencer::sendResult(int i, int j){
    cout<<"optimal cost retrieved from table: "<<costs[i][j].first<<endl;
}
float sequencer::findCost(int i, int j, float tc){
    //if(i==2&&j==6){
        //cout<<"               HERE's THE: 2,6 tc: "<<tc<<endl;
    //}
    //cout<<"in the function: ";
    //cout<<"i: "<<i<<", j: "<<j<<", tc: "<<tc<<endl;
    //first check to see if this node is already reached in table, or if we are at base case end of sequences
    if(i==s1.length() && j==s2.length()){
        //length() or length()-1? length means we have already processed the last element or each and now would be out of bounds
        cout<<"hit end of path: "<<i<<", "<<j<<" returning to max() with tc = "<<tc<<endl;
        costs[i][j].first=tc;
        return tc;//// is this correct or do we need to change the value in table. won't i and j already be beyond table bounds //CASSE WHERE INT RETURNED
    }
    else if(costs[i][j].second==true){///THIS CAN ALSO CAUSE ILLEGAL ACCESS
       // cout<<"RIGHT BEFORE SEG FAULT??\n";
      // cout<<"arriving at an already accessed node, "<<i<<","<<j<<endl;
        //if(s1[i]==s2[j]){///they are a match
            if(tc > costs[i][j].first){
           //     cout<<"OVERWRITING WITH CURRENT TC: "<<tc<<endl;
                cout<<"matchingoverwrite: "<<i<<","<<j<<" current is: "<<costs[i][j].first<<"  new is: "<<tc<<endl;
                cout<<"s1[i]: "<<s1[i]<<", s2[j]: "<<s2[j]<<endl;
                costs[i][j].first=tc+m;//here we reach an already visited i,j node, but we replace it with a more optimal head                
                return findCost(i+1, j+1, tc+m);
            }
        //}
        else{
          //  cout<<"reusing since it is better\n";
            cout<<"REUSED: "<<costs[i][j].first<<endl;
            return costs[i][j].first; ////////////////CASE WHERE A TRUE INT IS RETURNED
        }
    }
    else{/////here we assume that node i,j has not been matched in any previous solution head
        if(s1[i]==s2[j]){//STILL NEED AN IF STATEMENT BEFORE THIS TO PREVENT ILLEGAL ACCESS???:?
            costs[i][j].first=tc+m;
            costs[i][j].second=true;//solid node i,j now has been visited
            cout<<"matching: "<<i<<","<<j<<"  new is: "<<tc<<endl;
            return findCost(i+1,j+1,tc+m); ///here we assume that matching is optimal and would never consider alternative when match is possible
        }
        else{///do we need to do a bound validity test before each of these calls?? 
            //obviously we can not do a deletion if a sequence is already at its tail
            //we cant deal with invalid access by returning a signal integer because this integer could always be naturally reached through combinations of actions
          //  cout<<"in last big else\n";
            if(i+1>s1.length() && j+1<=s2.length()){///SKIP j at end
             //   cout<<"in first\n";
                costs[i][j].first=tc+d;
                costs[i][j].second=true;
                return findCost(i,j+1,tc+d);//s1 would go out of bounds, so we skip s2 and end with a '_' for s1
            }
            else if(j+1>s2.length() && i+1<=s1.length()){////SKIP i at end
              //  cout<<"in 2nd\n";
                //cout<<"d: "<<d<<endl;
                costs[i][j].first=tc+d;
                costs[i][j].second=true;
                return findCost(i+1,j,tc+d);
            }
           // else if(j+1>s2.length() && i+1>s1.length() && ){//this catches it so that else statement is fine ...?
                //if(i<j)//this might not be enough, trying to account for which sequence to add trailing __
                    //skip j
                
            //}
            
            else{///careful with the 3rd one (c)
               // cout<<"in last else statement\n";
                float skipj=findCost(i,j+1,tc+d);
                float skipi=findCost(i+1,j,tc+d);
                float replace=findCost(i+1,j+1,tc+c);
                cout<<"i,j: "<<i<<","<<j<<" tc: "<<tc<<endl;
                cout<<skipj<<" "<<skipi<<" "<<replace<<endl;
               // costs[i][j].first= max({skipj,skipi,replace});
                if(max({skipj,skipi,replace})==skipj ){
                    costs[i][j].first=tc+d;
                    costs[i][j].second=true;
                    return findCost(i,j+1,tc+d);
                }
                if(max({skipj,skipi,replace})==skipi ){
                    costs[i][j].first=tc+d;
                    costs[i][j].second=true;
                    return findCost(i+1,j,tc+d);
                }
                if(max({skipj,skipi,replace})==replace ){
                    costs[i][j].first=tc+c;
                    costs[i][j].second=true;
                    return findCost(i+1,j+1,tc+c);
                }

                costs[i][j].second=true;
                //return max({skipj,skipi,replace});// SHOULD THIS HAVE +TC or NOT?????????
                //return max({findCost(i,j+1,tc+d), findCost(i+1,j,tc+d), findCost(i+1,j+1,tc+c)});///recur for each way of deleting, and replacing base
            }//temporary cout statements above
        }
    }

}