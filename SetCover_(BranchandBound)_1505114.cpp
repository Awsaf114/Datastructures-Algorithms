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
//int i, j, k;

bool *subsets = new bool[m];
bool *notInFinal = new bool[n + 1];
int *unCov = new int[m];


class Node
{
public:
   int level;
   float lowerbound;
   vi setcover;
   vi uncovered;
   Node(int _lvl , float _lowerbound , vi _setcover , vi _uncovered)
   {
      level = _lvl;
      lowerbound = _lowerbound;
      setcover = _setcover;
      uncovered = _uncovered;
   }
   float getBound() const { return lowerbound; }

};

// To compare two points
class myComparator
{
public:
    float operator() (const Node& p1, const Node& p2)
    {
        return p1.getBound() > p2.getBound();
    }
};


int main(){

    scanf("%d%d", &n , &m);
    vi a[m];
    vi U ;

    for(int j = 0 ; j< m ; j++){
        cin>>ele;
        while(1){
            a[j].push_back(ele);
            if(cin.get() == '\n')
                break;
            else{
               cin>>ele;
               continue;
            }
        }
    }
    for(int i = 1 ; i<=n ; i++)
        U.push_back(i);

    int max  = 0;
    for (int i = 0; i < m; i++){
//      subsets[i] = false;
//      cardinality.push_back(a[i].size());
      if(a[i].size() > max)
        max = a[i].size();

    }

    float lb = 0 + (n/(max*1.0));
    cout<<lb<<m<<max<<endl;

    priority_queue <Node, vector<Node>, myComparator > pq;

    vi empty;
    pq.push(Node(0 , lb , empty , U));

    int i = 0;
    while (pq.empty() == false)
    {
        cout<<"\n---------------------------------------\n";

        Node p = pq.top();
        vi U = p.uncovered;
        i = p.level;
        cout << "Parent ->(" << p.level << ", " << p.lowerbound<<" "<<U.size()<<" "<<p.setcover.size()<< ")\n";

        if(U.size() == 0){
            cout<<endl<<p.setcover.size()<<endl;
            for(int j = 0 ; j< p.setcover.size() ; j++){
                for(int k = 0 ; k< a[p.setcover[j]].size() ; k++){
                    printf("%d ", a[p.setcover[j]][k]);
                }
                cout<<endl;
            }
            break;
//            pq.pop();
//            continue;
        }

        vi uncov;
        for(int j=0 ; j<U.size() ; j++){
            bool found = false;
            for(int k = 0 ; k<a[i].size() ; k++){
                if(U[j] == a[i][k])
                    found = true;
            }
            if(!found)
                uncov.push_back(U[j]);

        }

        printf("%d %d\n", uncov.size() , U.size());

//        if(a[i].size() != max){
//
//            float lb = p.setcover.size() + U.size()/(max*1.0);
//            pq.push(Node(p.setcover.size() , lb , p.setcover , p.uncovered ));
//            printf("(%f ,%d)\n" ,lb , p.setcover.size() );
//
//            p.setcover.push_back(i);
//            lb = p.setcover.size()+ uncov.size()/(max*1.0);
//            pq.push(Node(p.setcover.size() , lb , p.setcover , uncov));
//            printf("(%f ,%d)\n" ,lb , p.setcover.size() );
//
//        }
//        else{
            max = 1;
            for (int j = i+1; j < m; j++){
              if(a[j].size() > max)
                max = a[j].size();
            }
            float lb = p.setcover.size() + U.size()/(max*1.0);
            pq.push(Node(i+1 , lb , p.setcover , p.uncovered ));
            printf("(%f ,%d)\n" ,lb , p.setcover.size() );

            p.setcover.push_back(i);
            lb = p.setcover.size() + uncov.size()/(max*1.0);
            pq.push(Node(i+1 , lb , p.setcover , uncov));
            printf("(%f ,%d)\n" ,lb , p.setcover.size());

//        }

        pq.pop();
        i++;
    }


    cout<<"\n---------------------------------------\n";
//	for (i = 0; i < m; i++)
//	{
//		for (int j = 0; j < a[i].size(); j++)
//			printf("%d ", a[i][j]);
//
//		printf("\n");
//	}


}

