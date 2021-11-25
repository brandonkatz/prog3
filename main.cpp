#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <string.h>
#include <fstream>
#include <sstream>
#include <streambuf>
using namespace std;
void reverseStr(string& str){
    int n = str.length();
    // Swap character starting from two
    // corners
    for (int i = 0; i < n / 2; i++)
        swap(str[i], str[n - i - 1]);
}
int main(int argc, char* argv[]){

    //this fills every index of the dp vector
    //sequencer only fills at matched node index?
    ///VALUES BELOW ARE DEFINED AS DEFAULT, DO NOT CHANGE
    float m=2;//points added for a match
    float c=-0.5;//points for a change/replacement (negative value)
    float d=-1.0;//points for deletion/skipping a base (negative value)
    string M="none";
    string C="none";
    string D="none";
    string s1="";
    string s2="";
    string file1="";
    string file2="";
    //cout<<"argc = "<<argc<<endl;
    for(int i=1; i<argc-1; i++){
        //cout<<i<<","<<argv[i]<<endl;
        if(!strcmp(argv[i], "-d")){
            D=argv[i+1];
            ++i;
        }
        else if(!strcmp(argv[i], "-c")){
            C=argv[i+1];
            ++i;
        }
        else if(!strcmp(argv[i], "-m")){
            M=argv[i+1];
            ++i;
        }
        else if(!strcmp(argv[i], "-1")){
            file1=argv[i+1];
            ++i;
        }
        else if(!strcmp(argv[i], "-2")){
            file2=argv[i+1];
            ++i;
        }
       
    }
    //cout<<"file1: "<<file1<<endl;
    //cout<<"M= "<<M<<endl;
    //cout<<"D= "<<D<<endl;
    //cout<<"C= "<<C<<endl;
    //cout<<file2<<endl;
    if(M!="none")
        m=stof(M);//need ifstatments for override?
    if(D!="none")
        d=stof(D);
    if(C!="none")
        c=stof(C);
    
    //cout<<"m= "<<m<<endl;
    //cout<<"d= "<<d<<endl;
    //cout<<"c= "<<c<<endl;
    //pull file contents from string names
    ifstream t(file1);
    std::stringstream buffer;
    buffer << t.rdbuf();
    s1=buffer.str();
    ifstream t1(file2);
    std::stringstream buffer1;
    buffer1 << t1.rdbuf();
    s2=buffer1.str();
    //cout<<s1<<endl;
    //cout<<s2<<endl;
    int l1=s1.length();//important that this is here and not above
    int l2=s2.length();
    //cout<<"s1: "<<s1<<endl;
    //cout<<"s2: "<<s2<<endl;
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
   
    for(int i=1;i<=l1;++i){
        for(int j=1;j<=l2;++j) {
            if(s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1]+m;
            } else {
                dp[i][j] = max({dp[i-1][j]+d, dp[i][j-1]+d, dp[i-1][j-1]+c});
            }
        } 
    }
    //cout<<"m= "<<m<<endl;
    //cout<<"d= "<<d<<endl;
    //cout<<"c= "<<c<<endl;
    cout <<dp[s1.length()][s2.length()]<<endl;
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

    reverseStr(s1out);
    reverseStr(s2out);
    cout<<s1out<<endl;//return these after debug
    cout<<s2out<<endl;
    
    return 0;

}