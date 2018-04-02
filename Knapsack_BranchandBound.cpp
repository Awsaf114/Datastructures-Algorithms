#include <bits/stdc++.h>

using namespace std;

int main()
{
	int x, hh, mm;
	scanf("%d%d%d", &x , &hh , &mm);

    int fsth = hh/10;
    int sndh = hh%10;

    int fstm = mm/10;
    int sndm = mm%10;
    int count = 0 ;

    while(fsth != 7 && sndh !=7 && fstm!=7 && sndm!=7){
        mm -= x;

		if(mm<0){
			mm = 60 + mm;
			hh -= 1;
			if(hh <0 ){hh = 23;}
		}
        fsth = hh/10;
		sndh = hh%10;

		fstm = mm/10;
		sndm = mm%10;
		count++;

//		cout<<fsth<<" "<<sndh<<" "<<fstm<<" "<<sndm;
    }

    cout<<count;
	return 0;
}
