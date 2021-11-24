#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include "sequencer.h"
using namespace std;
int main(){
    float m=2;//points added for a match
    float c=-.2;//points for a change/replacement (negative value)
    float d=-1.5;//points for deletion/skipping a base (negative value)
    string s1="ACATGAGACAGACAGACCCCCAGAGACAGACCCCTAGACACAGAGAGAGTATGCAGGACAGGGTTTTTGCCCAGGGTGGCAGTATG";
    string s2="AGGATTGAGGTATGGGTATGTTCCCGATTGAGTAGCCAGTATGAGCCAGAGTTTTTTACAAGTATTTTTCCCAGTAGCCAGAGAGAGAGTCACCCAGTACAGAGAGC";
    int l1=s1.length();
    int l2=s2.length();
    
    vector<vector<float>> dp(l1+1, vector<float>(l2+1,0));
    for(int i=0;i<l1;++i){
        for(int j=0;j<l2;++j) {
            if(j==0) dp[i][j] = d*i;
            if(i==0) dp[i][j] = d*j;
        }
    } 

    for(int i=1;i<=l1;++i){
        for(int j=1;j<=l2;++j) {
            if(s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1]+m;
            } else {
                dp[i][j] = max({dp[i-1][j]+d, dp[i][j-1]+d, dp[i-1][j-1]+c});
            }
        } 
    }

    cout << dp[s1.length()][s2.length()];
    return 0;

}