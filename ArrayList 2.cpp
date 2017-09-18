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
  if(SIZE == items+1){
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
    if(items != 0){
    for(int j =items ; j>0;j--){

    if(a <= List[j-1]){
        while(a < List[j-1] && j >=0){
                List[j] = List[j-1];
                j--;
        }
//    for(int k=j; k>=1; k--){
//        List[k] = List[k-1];
//    }

        List[j+1] = a;
        items ++;
        break;
    }
    else{
        List[j] = a;
        items ++;
        break;
    }


    }
    }
    else{
        List[items] = a;
        items ++;
    }

    for(int j =0 ; j<items;j++){
    cout<<List[j]<<" ";
    }
    cout<<endl;

}

void deleteItem(){
    if( items == 0){
        cout<<"Empty List"<<endl;
        return;
    }
    items--;
    for(int j =0 ; j<items;j++){
    cout<<List[j]<<" ";
    }
    cout<<endl;
}

int findItem(int a){
    for(int i=0 ; i <items ; i++){
        if( a == List[i]){
            return i;
        }
    }

    return -1;
}

};

int main(){

    ArrayList a1;
    char action , c;
    int item ;


    cin>>action;

    while( action != 'T'){
        if( action == 'I'){

        cin>>item;

        a1.insertItem(item);

        }
        else if( action == 'F' ){
            cin>>item;
            int x = a1.findItem(item);
            if(x == -1){
                cout<<"Element not found"<<endl;
            }
            else{
                cout<<"Found at position "<<x<<endl;
            }

        }
        else if( action == 'D'){
            a1.deleteItem();
        }
        cin>>action;

    }


    return 0;
}


