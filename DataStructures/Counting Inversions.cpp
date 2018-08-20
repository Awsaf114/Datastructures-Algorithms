#include<iostream>
#include<stdio.h>

#define INFINITY 99999

using namespace std;



//int count =0 ;
int Merge(int a[] , int p , int q , int R){
    int count =0;
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
            if(l[i]!= INFINITY){
                count += n1-i;
            }
            a[k] = r[j];
            j++;
        }

    }
    return count;
}


int MergeSort(int a[] , int p , int r){
    int count = 0;
    int q;
    if(p < r){
    q = (p+r)/2 ;


    count+= MergeSort(a , p ,q);

    count+= MergeSort(a , q+1 ,r);

    count+= Merge(a , p , q , r);

    }
    return count;
}


int main(){

    int n;
    cout<<"Enter array size"<<endl;
    cin>>n;
    cout<<"Enter array Elements"<<endl;
    int a[n];

    for(int i=0 ; i<n ;i ++){
        cin>>a[i];
    }

//    cout<<"Sorted Array : "<<endl;

    int count = MergeSort(a , 0 , n-1);

//    for(int i=0 ; i<n ; i++){
//    cout<<a[i]<<" ";
//    }
    cout<<"\nNumber of Inversions: "<<count<<endl;
    return 0;

}
