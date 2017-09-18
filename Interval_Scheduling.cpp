#include<iostream>
#include<stdio.h>

#define INFINITY 99999

using namespace std;

class Item{
public:

    int s;
    int f;
};

Item* Merge(Item a[] , int p , int q , int R){
    int n1 = q-p+1;
    int n2 = R - q;
    Item l[n1+1];
    Item r[n2+1];

    int j = p;
    for(int i=0 ; i<n1 ; i++){
        l[i].f = a[j].f;
        l[i].s = a[j].s;
        j++;
    }
    j = q+1;
    for(int i=0; i<n2 ; i++){
        r[i].f = a[j].f;
        r[i].s = a[j].s;
        j++;

    }
//    cout<<endl<<"Merged Array :"<<endl;
    l[n1].f = INFINITY;
    r[n2].f = INFINITY;

    int i=0;
    j=0;

    for(int k = p ; k<=R ; k++){
//        printf("(%d %d)",l[i].f , r[j].f);
        if(l[i].f <= r[j].f){
            a[k].s = l[i].s;
            a[k].f = l[i].f;
            i++;
//            printf("%d ",a[k].f);
        }
        else{
            a[k].s = r[j].s;
            a[k].f = r[j].f;
            j++;
//             printf("%d ",a[k].f);
        }

    }
    return a;
}


Item* MergeSort(Item a[] , int p , int r){
    int q;
    if(p < r){
    q = (p+r)/2 ;


    MergeSort(a , p ,q);

    MergeSort(a , q+1 ,r);

    return Merge(a , p , q , r);

    }
    return a;
}


int main(){

    int n;
    cout<<"Enter array size"<<endl;
    cin>>n;
    cout<<"Enter array Elements"<<endl;
    Item a[n];
    //int f[n];

    for(int i=0 ; i<n ;i ++){
        scanf("%d %d",&a[i].s,&a[i].f);
        //printf("Print - %d %d\n",a[i].s,a[i].f);
    }


    Item *p = MergeSort(a , 0 , n-1);


     int count = 0;
     int idx[n];
     idx[0] = count;
    count++;
    for(int i=1 ; i<n ; i++){
        //cout<<"("<<p[i].f<<" "<<p[i].s<<")-("<<p[i-1].f<<"-"<<p[i-1].s<<")";
        if(p[i].s >= p[idx[count-1]].f){
            idx[count] = i;
      //      cout<<p[i].s<<" - "<<count;
            count++;
        }

    }

    cout<<"Suitable Intervals are :"<<endl<<count<<endl;
    for(int i=0 ; i<count ; i++){
        cout<<p[idx[i]].s<<" "<<p[idx[i]].f<<endl;

    }


    return 0;

}
