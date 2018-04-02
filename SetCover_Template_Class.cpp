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

int m , n , ele , x;
int i, j, k;

bool *subsets = new bool[m];
bool *notInFinal = new bool[n + 1];
int *unCov = new int[m];


struct Node{
    int level ,
    totalsets ,
    lowerBound;
};

vi SetCover(vi *a){

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


//    for(int j=0 ; j< m ; j++){
//        for(int i = 0 ; i < a[j].size() ; i++){
//            cout<<a[j][i]<<"  ";
//        }
//        cout<<endl;
//    }

    return ans;
}

int main(){

    scanf("%d%d", &n , &m);
    vi a[m];
    vi U;


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


	for (i = 0; i < m; i++)
		subsets[i] = false;

	for (i = 0; i <= n; i++)
		notInFinal[i] = false;

    vi ans = SetCover(a);


	printf("%d\n", ans.size());
	for (i = 0; i < ans.size(); i++)
	{
		for (j = 0; j < a[ans[i]].size(); j++)
			printf("%d ", a[ans[i]][j]);

		printf("\n");
	}


}

