#include<bits/stdc++.h>
#define NULL_VALUE -999999
#define INF 1000000000
#define WHITE 0
#define GREY 1
#define BLACK -1

using namespace std;

typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;



int main(){
    int m , n , ele , x;
    int  j, k;

    scanf("%d%d", &n , &m);
    vi a[m];
    vi U;

    bool *subsets = new bool[m];
	bool *notInFinal = new bool[n + 1];
	int *unCov = new int[m];

    int i=1;
    for(int j = 0 ; j< m ; j++){
        cin>>ele;
        while(1){
            U.push_back(i);
            a[j].push_back(ele);
            i++;
            if(cin.get() == '\n')
                break;
            else{
               cin>>ele;
               continue;
            }

        }

   }

//    for(int j=0 ; j< m ; j++){
//        for(int i = 0 ; i < a[j].size() ; i++){
//            cout<<a[j][i]<<"  ";
//        }
//        cout<<endl;
//    }




	for (i = 0; i < m; i++)
		subsets[i] = false;

	for (i = 0; i <= n; i++)
		notInFinal[i] = false;

	vector<int> ans;

	while (n)
	{
		x = 0; k = -1;
		for (i = 0; i < m; i++)
		{
			if (!subsets[i])
			{
				unCov[i] = 0;
				for (j = 0; j < a[i].size(); j++)
				{
					if (!notInFinal[a[i][j]])
						unCov[i]++;
				}

				if (x < unCov[i])
					x = unCov[i], k = i;
			}
		}

		subsets[k] = true; ans.push_back(k);
		n -= x;

		for (i = 0; i < a[k].size(); i++)
			notInFinal[a[k][i]] = true;
	}

	printf("%d\n", ans.size());
	for (i = 0; i < ans.size(); i++)
	{
		for (j = 0; j < a[ans[i]].size(); j++)
			printf("%d ", a[ans[i]][j]);

		printf("\n");
	}


// cout<<a.size()<<"  "<<a.front()<<"  "<<a.back()<<endl; //returns 1st and last elements
//    a.pop_back();
//    a.pop_back();
//
//    cout<<a.size()<<"  "<<a.front()<<"  "<<a.back()<<endl; //returns 1st and last elements
//
//    a.erase(a.begin()+3);
//    for(int i = 0 ; i < a.size() ; i++){
//        cout<<a[i]<<"  ";
//    }
//    cout<<endl;
//    a.erase(a.begin() , a.begin()+9); // Deletes 10 elements
//
//    for(int i = 0 ; i < a.size() ; i++){
//        cout<<a[i]<<"  ";
//    }
//
//    a.erase(a.begin() , a.begin()+ a.size()); //Deletes all elements
//    cout<<endl;
//    for(int i = 0 ; i < a.size() ; i++){
//        cout<<a[i]<<"  ";
//    }
//    a.assign(7, 0);
//
//    cout<<endl<<a.size()<<"  "<<a.front()<<"  "<<a.back()<<endl; //returns 1st and last elements
//
//    a.erase(a.begin() , a.end());
//
//    if(a.empty())
//        cout<<"Vector now empty\n";
//
//    std::vector<int> foo (3,100);   // three ints with a value of 100
//  std::vector<int> bar (5,200);   // five ints with a value of 200
//
//  foo.swap(bar);
//
//  a.swap(foo);
//    cout<<endl<<a.size()<<"  "<<a.front()<<"  "<<a.back()<<endl; //returns 1st and last elements
//
////a.insert(a.begin()+7, 9); // Cannot insert more than vector size
//a.insert(a.begin() , 9);///inserts an item
//    cout<<endl<<a.size()<<"  "<<a.front()<<"  "<<a.back()<<endl; //returns 1st and last elements
//
//    a[1] = 900; ///Replacesan item
////  Elements will swap
//    for(int i = 0 ; i < a.size() ; i++){
//        cout<<a[i]<<"  ";
//    }


}
