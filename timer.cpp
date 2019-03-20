#include <iostream>
#include <ctime>
using namespace std;
int main()
{
	while(true)
	{
		clock_t start = clock();
		if((double)(clock()-start)*1000*1000==1)
		{
			start=clock();
			cout<<1;
		}
	}
	return 1;
}
