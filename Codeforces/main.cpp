/*
Problem :1025 A Doggo Recoloring


*/

#include<bits/stdc++.h>
#include<iostream>
#include<vector>

#define NULL_VALUE -999999
// #define INFINITY 999999

// typedef vector<int> vi;
// typedef pair<int,int> ii;
// typedef vector<ii> vii;

using namespace std;


int main()
{
  int n;
  cin>>n;

  vector<int> vect , output;
  vector<int> sorted(n, 0);

  for(int i =0 ; i<n ; i++){
    int a;
    scanf("%d", &a);
    vect.push_back(a);
  }

  for(int i = 0 ; i<n ; i++){
    sorted[i] = sorted[i]+1;
    int temp = vect[i];
    temp--;
    while(1){
      sorted[temp] = sorted[temp]+1;
      if(sorted[temp] >1){
        break;
      }
      temp = vect[temp];
      temp--;
    }
    // for(int i=0 ; i< sorted.size() ; i++){
    //   cout<<sorted[i]<<" ";
    // }
    // cout<<endl;
    fill(sorted.begin(), sorted.end(), 0);
    //Getting max element
    output.push_back(temp+1);
  }

  for(int i=0 ; i< output.size() ; i++){
    cout<<output[i]<<" ";
  }

  return 0;
}
