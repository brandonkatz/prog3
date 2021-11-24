#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include "sequencer.h"
#include <string>
using namespace std;
void reverseStr(string& str){
    int n = str.length();
    // Swap character starting from two
    // corners
    for (int i = 0; i < n / 2; i++)
        swap(str[i], str[n - i - 1]);
}
int main(){
    //this fills every index of the dp vector
    //sequencer only fills at matched node index?
    float m=2;//points added for a match
    float c=-.2;//points for a change/replacement (negative value)
    float d=-1.5;//points for deletion/skipping a base (negative value)
    string s1="ACATGAGACAGACAGACCCCCAGAGACAGACCCCTAGACACAGAGAGAGTATGCAGGACAGGGTTTTTGCCCAGGGTGGCAGTATG";
    string s2="AGGATTGAGGTATGGGTATGTTCCCGATTGAGTAGCCAGTATGAGCCAGAGTTTTTTACAAGTATTTTTCCCAGTAGCCAGAGAGAGAGTCACCCAGTACAGAGAGC";
    int l1=s1.length();
    int l2=s2.length();
    
    vector<vector<float>> dp(l1+1, vector<float>(l2+1,0));
    for(int i=0;i<=l1;++i){//initializing values
        for(int j=0;j<=l2;++j){//what if l2==0??????? THESE BOUNDS MIGHT CAUSE PROBLEMS LATER
           // cout<<"i="<<i<<" j="<<j<<endl;
            if(j==0) {
               // cout<<"int the jskip if? d="<<d<<endl;
                dp[i][j] = d*i;
            }
            else if(i==0)
                dp[i][j] = d*j;
        }
    } 
    /*for(int i=0;i<=l1;++i){//print the initialize table
        for(int j=0;j<=l2;++j) {
            cout<<dp[i][j]<<" ";
        }
        cout<<endl;
    }*/

    for(int i=1;i<=l1;++i){
        for(int j=1;j<=l2;++j) {
            if(s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1]+m;
            } else {
                dp[i][j] = max({dp[i-1][j]+d, dp[i][j-1]+d, dp[i-1][j-1]+c});
            }
        } 
    }

    cout << "answer: "<<dp[s1.length()][s2.length()]<<endl;
    ///print out to analyze the rows of the dp table, maybe max in each indicates the action we do at that index?
    //to find the order of actions, just trace through diagonally
    /*for(int i=0;i<=l1;++i){
        for(int j=0;j<=l2;++j) {
            cout<<dp[i][j]<<" ";
        }
        cout<<endl;
    }*/
    int i=l1;
    int j=l2;
    //cout<<"s1 length: "<<l1<<endl;
    //cout<<"s2 length: "<<l2<<endl;
    //string s1out=s1;//is this a copied string? or a reference
    //string s2out=s2;
    string s1out="";//is this a copied string? or a reference
    string s2out="";


    while(i>0||j>0){//will likely run out of bounds
        //check the best valid operation at the given index
        if(i>0 && j>0){//both are still valid/skippable?
        //BELOW IF STATEMENT NOT SUFFICIENT, ALSO CHECK THE VALUES?
        //"PREVIOUS MATCH MIGHT BE OPTIMAL VALUE, BUT IS IT A REAL NODE?"
            if((dp[i-1][j-1]+m == dp[i][j])&&s1[i-1]==s2[j-1]){//got to this node by making previous match
                //dont need to change the strings, just increment
                cout<<"matching                   "<<i<<","<<j<<endl;
                s1out+=s1[i-1];
                s2out+=s2[j-1];
                i--;
                j--;
            }
            else if(dp[i-1][j-1]+c == dp[i][j]){//last step was replace
                //s2out.replace(j-1,1,"R");
                s1out+=s1[i-1];
                s2out+="R";
                i--;
                j--;
            }
            else if(dp[i][j-1]+d == dp[i][j]){//skipped j
                s1out+="_";
                s2out+=s2[j-1];
                j--;
                //s1out.insert(i-1,"_");//insert ruins index system                
            }
            else{//skipped i
                s2out+="_";
                s1out+=s1[i-1];
                i--;
                //s2out.insert(j-1,"_");
            }
        }
        else if(i==0){//skip j
            s1out+="_";
            s2out+=s2[j-1];
            j--;
                //s1out.insert(i,"_");//at i or i-1?WAS THIS THE FIX?
        }
        else{//j==0
            s2out+="_";
            s1out+=s1[i-1];
            i--;
                //s2out.insert(j,"_");//at j or j-1?
        }
    }

    //need to reverse the strings after this?
    /*while(i>0||j>0){
        if(s1[i-1]==s2[j-1]){//there is a match at this node? jump back
            //no need to modify the string?
            i--;
            j--;
        }
        else if(i>0){//i is
            int j=0;
        }
    }*/
    /*while(i<l1 || j<l2){//ending early,, TRY OR INSTEAD OF AND
        //cout<<"i: "<<i<<", j: "<<j<<endl;
        int matchorReplace;
        int skipj;
        int skipi;
        int maxOf;
        if(j>=l2){//j not skippable
            skipi= dp[i+1][j];
            maxOf=skipi;
        }
        else if(i>=l1){//i not skippable
            skipj= dp[i][j+1];
            maxOf=skipj;
        }
        else{
            //consider all cases
            matchorReplace= dp[i+1][j+1];
            skipi= dp[i+1][j];
            skipj= dp[i][j+1];
            maxOf= max({matchorReplace,skipj,skipi});
        }
        if(maxOf==matchorReplace){
            //increment both outside of below statements
            if(maxOf==dp[i][j]+m){///we have a match
                s1out+=s1[i];//can we access strings like this? or substr
                s2out+=s2[j];
            }
            else{//we have a replacement
                s1out+=s1[i];
                s2out+="R";
            }
            i++;
            j++;
        }
        else if(maxOf==skipj){
            //increment j
            s1out+="_";
            s2out+=s2[j];
            j++;
        }
        else{
            //increment i
            s1out+=s1[i];
            s2out+="_";
            i++;
        }
    }*/
    reverseStr(s1out);
    reverseStr(s2out);
    cout<<s1out<<endl;
    cout<<s2out<<endl;
    //cout<<s1<<endl;
    //cout<<s2<<endl;
    return 0;

}