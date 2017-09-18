#include<iostream>
#include<stdio.h>

#define INFINITY 99999

using namespace std;



//int count =0 ;
int* Merge(int a[]  , int p , int q , int R){
   // int count =0;
    int n1 = q-p+1;
    int n2 = R - q;
    int l[n1+1];
    int r[n2+1];

    int j = p;
    for(int i=0 ; i<n1 ; i++){
        l[i] = a[j];
        j++;
    }
    j = q+1;

    for(int i=0; i<n2 ; i++){
        r[i] = a[j];
        j++;

    }
    l[n1] = INFINITY;
    r[n2] = INFINITY;

    int i=0;
    j=0;

    for(int k = p ; k<=R ; k++){
        int val = a[k];
        if(l[i]<= r[j]){
            a[k] = l[i];
            i++;

        }
        else{

            a[k] = r[j];
            j++;
        }

    }
    return a;
}


int* MergeSort(int a[] , int p , int r , int n){
    int count = 0;
    int q;
    if(p < r){
    q = (p+r)/2 ;


 MergeSort(a , p ,q , n);

 MergeSort(a , q+1 ,r , n);

 return Merge(a , p , q , r );

    }
    return a;
}

int main(){
    int arrays;

    cin>>arrays;
    int n;
    cout<<"Enter array size"<<endl;
    cin>>n;

    int size = arrays*n;
   // cout<<size<<endl;
    int a[size];

    for(int k = 0 ; k<arrays*n ; k++){
    //cout<<"Enter array "<<k+1<<endl;
        cin>>a[k];
  }

  int * p = MergeSort(a , 0 , arrays*n , n);
  for(int i =0 ; i<arrays*n ; i++){
    cout<<p[i]<<" ";
  }

    return 0;

}

