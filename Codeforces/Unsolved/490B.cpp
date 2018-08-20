/*
Problem :490B Queue
----------------------
During the lunch break all n Berland State University students lined up in the food court. However, it turned out that the food court, too, has a lunch break and it temporarily stopped working.

Standing in a queue that isn't being served is so boring! So, each of the students wrote down the number of the student ID of the student that stands in line directly in front of him, and the student that stands in line directly behind him. If no one stands before or after a student (that is, he is the first one or the last one), then he writes down number 0 instead (in Berland State University student IDs are numerated from 1).

After that, all the students went about their business. When they returned, they found out that restoring the queue is not such an easy task.

Help the students to restore the state of the queue by the numbers of the student ID's of their neighbors in the queue.
Input

The first line contains integer n (2 ≤ n ≤ 2·105) — the number of students in the queue.

Then n lines follow, i-th line contains the pair of integers ai, bi (0 ≤ ai, bi ≤ 106), where ai is the ID number of a person in front of a student and bi is the ID number of a person behind a student. The lines are given in the arbitrary order. Value 0 is given instead of a neighbor's ID number if the neighbor doesn't exist.

The ID numbers of all students are distinct. It is guaranteed that the records correspond too the queue where all the students stand in some order.
Output

Print a sequence of n integers x1, x2, ..., xn — the sequence of ID numbers of all the students in the order they go in the queue from the first student to the last one.
------------------------------------------------
Test Case :
9
50 80
3 118
86 76
79 50
0 90
114 86
90 79
76 3
80 0

*/

#include<bits/stdc++.h>
#include<iostream>
#include<vector>

using namespace std;

#define NULL_VALUE -999999
// #define INFINITY 999999

typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef set<int> st;


int main()
{
  // std::vector<vii>::iterator it;

  int n;
  cin>>n;

  int a , b;

  vector<vii> vect , vect2;

  for(int i = 0 ; i< n ;i++){
      scanf("%d %d", &a , &b);
      //set<int> myset;
      // if(a !=0)
      //   myset.insert(a);
      // if(b !=0)
      //   myset.insert(b);
      vii v;
      v.push_back(make_pair(a,b));
      vect.push_back(v);
  }


  for(int i =0 ; i< vect.size() ; i++){
      for(int j = i ; j< vect.size() ; j++){

        // for (int k = 0; k < vect[i].size(); k++) {
        //   /* code */
        //   cout<<vect[i][k].first<<"-"<<vect[i][k].second<<" ";
        // }
        // std::cout << '\n';

          if(vect[i][0].first == vect[j][0].second && vect[i][0].first !=0){
            // vect[j].push_back(vect[i][0]);
            vector<ii>::iterator it;

            it = vect[j].end();
            it = vect[j].insert ( it , vect[i].begin() , vect[i].end() );
            fill(vect[i].begin(), vect[i].end(), make_pair(0,0));
            while (vect[i].size() != 1) {vect[i].pop_back();}
            // vect.erase(vect.begin()+i);
            break;
          }
        if(vect[i].size() == 1){
          if(vect[j][0].first == vect[i][0].second && vect[j][0].first != 0){
              vector<ii>::iterator it;

            it = vect[j].begin();
            it = vect[j].insert ( it , vect[i].begin() , vect[i].end() );
            // vect.erase(vect.begin()+i);
            fill(vect[i].begin(), vect[i].end(), make_pair(0,0));
            while (vect[i].size() != 1) {vect[i].pop_back();}
            break;

          }
      }
      else{

        if(vect[j][0].first == vect[i][vect[i].size()-1].second && vect[j][0].first != 0){
            vector<ii>::iterator it;

          it = vect[j].begin();
          it = vect[j].insert ( it , vect[i].begin() , vect[i].end() );
          fill(vect[i].begin(), vect[i].end(), make_pair(0,0));
          while (vect[i].size() != 1) {vect[i].pop_back();}
          break;

        }

      }

      }
      // std::cout << '\n';

  }

  vector<int> sorted;
  // for (int i = 0; i < n; i++) {
  //
  //   if(vect[i][0].first != 0 && vect[i][0].second !=0){
  //     vii v;
  //     for (int k = 0; k < vect[i].size(); k++) {
  //       cout<<vect[i][k].first<<"-"<<vect[i][k].second<<" ";
  //       v.push_back(vect[i][k]);
  //     }
  //     vect2.push_back(v);
  //   }
  // }



  if(vect2[1][0].first == 0 && vect2[1][0].second != 0){

    for(int i =0 ; i< n ; i++){
      int idx1 = i;
      int idx2 = i;

      if(!(i >= vect2[0].size())){
        sorted.push_back(vect2[0][idx1].first);

      }
      if(!(i >= vect2[1].size()) && vect2[1][idx2].second != 0){
        sorted.push_back(vect2[1][idx2].second);

      }

    }
    if(vect2[0][vect[0].size()-1].second!= 0){
      sorted.push_back(vect2[0][vect[0].size()-1].second);
    }
    // if(vect[vect.size()-1][vect[vect.size()-1].size()-1].second!= 0){
    //   sorted.push_back(vect[0][vect[0].size()-1].second);
    // }

  }
  else{
    for(int i =0 ; i< n ; i++){
      int idx1 = i;
      int idx2 = i;

      if(!(i >= vect2[1].size())){
        sorted.push_back(vect2[1][idx1].first);

      }
      if(!(i >= vect2[0].size())){
        sorted.push_back(vect2[0][idx2].second);

      }

    }
    if(vect2[1][vect[1].size()-1].second!= 0){
      sorted.push_back(vect[1][vect[1].size()-1].second);
    }

  }

for(int i =0 ; i<n ; i++){
  cout<<sorted[i]<<" ";
}
    // std::cout << '\n';
  //
  // }


  return 0;
}
