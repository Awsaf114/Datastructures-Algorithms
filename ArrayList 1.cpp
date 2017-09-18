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

    for(int j =0 ; j<items;j++){
    cout<<List[j]<<" ";
    }
    cout<<endl;

}


void insertItemAtPos(int a , int pos){

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
//    cout<<a<<pos;
    for(int i= items ; i> pos ; i--){
        List[i] = List[i-1];
    }
    List[pos] = a;
    items ++;



    for(int j =0 ; j<items;j++){
    cout<<List[j]<<" ";
    }
    cout<<endl;

}
void deleteItem(){
    items--;

    for(int j =0 ; j<items;j++){
    cout<<List[j]<<" ";
    }
    cout<<endl;


}

void deleteFirstItem(int a){
    for( int i=0; i<items; i++){
        if(List[i] == a){
            for(int j =i ; j<items-1 ;j++){
                List[j] = List[j+1];
            }
            items --;
            break;

        }

    }
    for(int j =0 ; j<items;j++){
    cout<<List[j]<<" ";
    }
    cout<<endl;


}

void deleteLastItem(int a){
    cout<<items<<endl;
    for(int i = items-1 ; i>=0 ;i--){
//        cout<<i<<" At :"<<List[i]<<endl;
        if(List[i] == a){
//             cout<<"Found "<<List[i]<<" At "<<i<<endl;
            for(int j=i ; j<items -1 ;j++){
                List[j] = List[j+1];
            }
            items--;
            break;
        }
    }
    for(int j =0 ; j<items;j++){
    cout<<List[j]<<" ";
    }
    cout<<endl;

}

bool clearList(){
    if(items == 0){
        return false;
    }
    else{
        for(int i=0 ; i<items ; i++){
            List[i] = 'null';
        }
        items = 0;
        return true;
    }

}

int searchItem(int a){
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
    char c[20];
    int item  , pos , i=0 , counter = 0;
    char action[10];

    gets(action);
    sscanf( action , "%s %d %d",c  ,&item , &pos );

    while( action[0] != 'T'){
        i=0;
        counter = 0;
        while(action[i] != '\0'){
            if(action[i]==' '){
            counter++;
            }
        i++;
        }
            i=0;
        if( action[0] == 'C')
        {
            if(a1.clearList()){
                cout<<"Clear Completed"<<endl;
            }
            else{
                cout<<"Empty List"<<endl;
            }

        }
        else if( action[0] == 'I'){

            if(counter==1){
            a1.insertItem(item);
            }
            else{
                a1.insertItemAtPos(item , pos);
            }
        }
        else if( action[0] == 'S' ){

            int x = a1.searchItem(item);
            if(x == -1){
                cout<<"Element not found"<<endl;
            }
            else{
                cout<<"Found at position "<<x<<endl;
            }

        }
        else if( action[0] == 'D'){
            bool flag = true;
            if(counter>=1){
            sscanf( action , "%s %*s %d",c   , &pos );
            }
                if(action[2]== 'L'){
//                cout<<"Del Last.."<<pos<<endl;
                a1.deleteLastItem(pos);

                flag = false;

                }
                else if ( action[2] == 'F'){
//                cout<<"Del first.."<<endl;
                a1.deleteFirstItem(pos);
                flag = false;

                }

            if(flag){
            a1.deleteItem();
            }


        }

        gets(action);
        sscanf( action , "%s %d %d",c  ,&item , &pos );
//        cout<<item<<"Hello ... "<<pos;
    }



    return 0;
}
