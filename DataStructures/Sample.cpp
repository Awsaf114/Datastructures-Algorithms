#include<iostream>
#include<string>
#include <map>
#include<vector>
#include <sstream>
#include <cmath>

#define N 3

using namespace std;

string documents[N][2]={{"A","the mouse played with the cat"},
                      {"B","The quick brown fox jumps over the lazy dog"},
                      {"C","dog 1 and dog 2 ate the hot dog"}};

map <string, double> tf[3];
map <string, double> idf;

vector<string> split(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

void calculateTFIDF(){
    for(int j =0 ; j<N ; j++){
            cout<<endl<<documents[j][0]<<" =>"<<endl;
        int count = 0;
        vector<string> s =  split( documents[j][1] , ' ');
        for(int i = 0 ; i < s.size() ; i++){
            cout<<s[i]<<" -> ";
            if (tf[j].find(s[i]) != tf[j].end()){
//                cout << "map contains key world!\n";
//                cout<<tf[0][s[i]];
                count = tf[j][s[i]];
                count++;
              }
              else{
//                cout <<"not exist"<<endl;
                count=1;
              }
              cout<<count<<endl;
            tf[j][s[i]] = count;

           ///For idf
            if (idf.find(s[i]) != idf.end()){
                count = idf[s[i]];
                count++;
              }
              else{
                count=1;
              }
            idf[s[i]] = count;

        }


    }
    cout<<"\nPrinting idf------\n";
    for(map<string,double>::iterator it=idf.begin(); it!=idf.end(); ++it)
    {
        cout << it->first << " => " << it->second << '\n';
    }


}

double findMatch(map<string, double> query, int documentNo){

   return 0;
}

string findDocument(string query){

//    map<string, double>
    vector<string> s =  split( query , ' ');
    vector<int> v ;
    vector<int> files[3];
    int count =0;

    for(int i = 0 ; i < s.size() ; i++){

        if (idf.find(s[i]) != idf.end()){
           count = idf[s[i]];
          }
          else{
            count=0;

          }
          v.push_back(count);

          for(int j = 0 ; j<3 ;j++){

            if (tf[j].find(s[i]) != tf[j].end()){
               count = tf[j][s[i]];
              }
              else{
                count=0;
              }
              files[j].push_back(count);

          }



     }
     int dotproduct , max=0 , index;
     for(int j =0 ; j<3 ; j++){
         dotproduct = 0;

         for(int i=0 ; i< v.size() ; i++){

             dotproduct += v[i]*files[j][i];
         }
         if(dotproduct >= max){
            max = dotproduct;
            index = j;
         }
     }

//    for(map<string,double>::iterator it=idf.begin(); it!=idf.end(); ++it)
//    {
//        cout << it->first << " => " << it->second << '\n';
//    }

   return documents[index][0];
}


int main(){

    calculateTFIDF();
    string str;

    cin>>str;

    cout<<endl<<findDocument(str);


/*
    map <string, double> m;
    m["foo"] = 42;

    for(int i=0 ; i< 3 ; i++){
        for(int j = 0 ; j<2 ; j++){

        }
    }


      if (m.find("foo") != m.end()){
        cout << "map contains key world!\n";
        cout<<m["foo"];
      }
      else{
        cout <<"not exist"<<endl;
      }




    for(map<string,double>::iterator it=m.begin(); it!=m.end(); ++it)
    {
        cout << it->first << " => " << it->second << '\n';
    }

*/

    return 0;
}
