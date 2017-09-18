#include<iostream>
#include<stdio.h>
#include<stdlib.h>

using namespace std;



class ArrayList{
    int *List;
    int SIZE , items ;


public:
    ArrayList(){
        SIZE = 100;
        List = new int[SIZE];
        items = 0;

    }
void insertItem(int a){
  if(SIZE == items){
        SIZE *= 2;
        int newarr[SIZE];
        for(int j=0;j<items;j++){
            newarr[j] = List[j];
        }
        delete []List;
        List = new int[SIZE];
        for(int j=0;j<items;j++){
             List[j]= newarr[j] ;
        }
    }

    List[items] = a;
    items ++;

//    for(int j =0 ; j<items;j++){
//    cout<<List[j]<<" ";
//    }
//    cout<<endl;

}


void deleteItem(){
    List[items-1] = 'null';
    items--;
//    for(int j =0 ; j<items;j++){
//    cout<<List[j]<<" ";
//    }
//    cout<<endl;


}

bool searchItem(int a){
    if(List[items-1] == a)
    {
        return true;
    }

    return false;
}

bool isEmpty(){
    if(items == 0){
        return true;
    }
    else{
        return false;
    }
}



};

int main(){

    ArrayList a1;

    string brackets;
    cin>>brackets;
    int i=0;
    while(brackets[i] != '\0'){
        if( brackets[i] == '(' || brackets[i] == '{' || brackets[i] == '[')
        {
           a1.insertItem(brackets[i]);
        }
        else{
           if(a1.isEmpty())
           {
               cout<<"Not Balanced"<<endl;
               return 0;
           }
            else{
                if( brackets[i] == '}' && a1.searchItem('{') || brackets[i] == ')' && a1.searchItem('(') || brackets[i] == ']' && a1.searchItem('['))
                {
                    a1.deleteItem();
//                    cout<<brackets[i-1]<<brackets[i]<<endl ;
                }
                else{
                    cout<<"Not Balanced"<<endl;
//                    cout<<a1.searchItem(brackets[i])<<brackets[i]<<endl ;
                    return 0;
                }
            }
        }
        i++;

    }
    if(!a1.isEmpty()){
        cout<<"Not Balanced"<<endl;
    }
    else{
        cout<<"Balanced"<<endl;
    }

    return 0;
}

