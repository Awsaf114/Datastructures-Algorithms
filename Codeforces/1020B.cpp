/*
Problem :1020B. Badge
In Summer Informatics School, if a student doesn't behave well, teachers make a hole in his badge. And today one of the teachers caught a group of n

students doing yet another trick.

Let's assume that all these students are numbered from 1
to n. The teacher came to student a and put a hole in his badge. The student, however, claimed that the main culprit is some other student pa

.

After that, the teacher came to student pa
and made a hole in his badge as well. The student in reply said that the main culprit was student ppa

.

This process went on for a while, but, since the number of students was finite, eventually the teacher came to the student, who already had a hole in his badge.

After that, the teacher put a second hole in the student's badge and decided that he is done with this process, and went to the sauna.

You don't know the first student who was caught by the teacher. However, you know all the numbers pi
. Your task is to find out for every student a, who would be the student with two holes in the badge if the first caught student was a

.
Input

The first line of the input contains the only integer n
(1≤n≤1000

) — the number of the naughty students.

The second line contains n
integers p1, ..., pn (1≤pi≤n), where pi indicates the student who was reported to the teacher by student i

.
Output

For every student a
from 1 to n print which student would receive two holes in the badge, if a was the first student caught by the teacher.

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
