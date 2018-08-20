/*
Problem :1025 A Doggo Recoloring
Panic is rising in the committee for doggo standardization — the puppies of the new brood have been born multi-colored! In total there are 26 possible colors of puppies in the nature and they are denoted by letters from 'a' to 'z' inclusive.

The committee rules strictly prohibit even the smallest diversity between doggos and hence all the puppies should be of the same color. Thus Slava, the committee employee, has been assigned the task to recolor some puppies into other colors in order to eliminate the difference and make all the puppies have one common color.

Unfortunately, due to bureaucratic reasons and restricted budget, there's only one operation Slava can perform: he can choose a color x
such that there are currently at least two puppies of color x and recolor all puppies of the color x into some arbitrary color y

. Luckily, this operation can be applied multiple times (including zero).

For example, if the number of puppies is 7
and their colors are represented as the string "abababc", then in one operation Slava can get the results "zbzbzbc", "bbbbbbc", "aaaaaac", "acacacc" and others. However, if the current color sequence is "abababc", then he can't choose x

='c' right now, because currently only one puppy has the color 'c'.

Help Slava and the committee determine whether it is possible to standardize all the puppies, i.e. after Slava's operations all the puppies should have the same color.
Input

The first line contains a single integer n
(1≤n≤105

) — the number of puppies.

The second line contains a string s
of length n consisting of lowercase Latin letters, where the i-th symbol denotes the i

-th puppy's color.
Output

If it's possible to recolor all puppies into one color, print "Yes".

Otherwise print "No".

Output the answer without quotation signs.

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

  vector<char> vect;

  string a;
  cin>>a;

int i =0;
  while(a[i] != '\0'){
    for(int j =0 ; j< vect.size() ; j++){
      if(a[i] == vect[j]){
        cout<<"Yes";
        return 0;
      }
    }
    vect.push_back(a[i]);

    // printf("%d\n",a[i]);
    i++;
  }
  if(vect.size() == 1){
    cout<<"Yes";
    return 0;
  }

  cout<<"No";
  return 0;
}
