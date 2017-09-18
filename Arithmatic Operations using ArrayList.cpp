#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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
//    cout<<items<<endl;
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

int oper( char a){
    int op=0;
    for(int i=items -1 ; i >=0 ; i--){
        if(a == '+'){
            op += List[i];
        }
        else if(a == '-' && i!= items -1){
            op -= List[i];
        }
        else if(a == '-' && i== items -1){
            op = List[i];
        }
        else if(a== '*' && i!=items -1){
            op *= List[i];
        }
        else if(a == '*' && i== items -1){
            op = List[i];
        }
        else if(a == '/' && i!=items -1){
            op /= List[i];
        }
        else if(a == '/' && i== items -1){
            op = List[i];
        }
    }

    return op;


}

int fstitem(){
    return List[0];
}



};

int main()
{
    char c[200];
    ArrayList a1;

    gets(c);


    for(int i= strlen(c)-1 ; i>=0 ; i--)
    {
        if(c[i] == '+' || c[i]=='-'|| c[i]=='*'|| c[i]=='/'){
            int n = a1.oper(c[i]);
            a1.clearList();
            a1.insertItem(n);
        }
        else{
        a1.insertItem(c[i] - '0');
        }


    }

    cout<<"Answer is :"<<a1.fstitem()<<endl;



    return 0;
}
