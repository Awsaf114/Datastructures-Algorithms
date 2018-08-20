
#include<iostream>
#include<vector>
#include<stdio.h>
#define INFINITY 999999



using namespace std;

class Coins{
public:
    int total;
    vector<int> denom;

};

int subsetSum(vector<int> coin , int m , int V){

    Coins *b;
    b = new Coins[V+1];
    b[0].total = 0;

    int notenumber[m+1];

    for(int i = 1; i <=V ;i++){
        b[i].total = INFINITY;
    }
    for(int i = 1 ; i<=V ; i++){

        for(int j = 0 ; j < m;j++)
        {
            bool flag = true;
                if( coin[j] <= i){
                    int num = b[i-coin[j]].total;

                    vector<int> temp = b[i-coin[j]].denom;
                    if(num != INFINITY && num + 1 < b[i].total ){
                        b[i].denom.clear();

                        for(int k =0 ; k< temp.size() ; k++){
//                            cout<<temp[k]<<" ";
                            if(temp[k] != coin[j])
                            {
                            b[i].denom.push_back(temp[k]);

                            }
                            else{
                                b[i].denom.clear();
                                    flag = false;
                            }

                        }

//                        if(flag){
                            b[i].total = num+1;
                        b[i].denom.push_back(coin[j]);

//                        }

                      }
                }
        }


//        cout<<endl;
    }
//    cout<<endl<<endl;

for(int i = 0 ; i < b[V].denom.size() ; i++){
    cout<<b[V].denom[i]<<" ";
}

//cout<<b[V].total;
return b[V].total;


}

int main(){


    int  n , t , c;
    vector<int> num;

    int count = 0;
    scanf("%d%d",&n, &t);
    for(int i=0 ; i< n ; i++){
        scanf("%d",&c  );
        count += c;
        num.push_back(c);
    }

    if(t > count)
    {
        cout<<"False";
        return 0;
    }

    if(subsetSum(num, n , t) > 0 ){
     cout<<"\n\n True";
    }




}
