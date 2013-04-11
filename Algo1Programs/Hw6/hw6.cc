#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ifstream in("HashInt.txt");
	
	bool a[4001];
	int tmp;
	for (int i=0; i<4001; i++)
   	 a[i]=false;
	
	if (!in.is_open())
	{
		cout<<"File open failed !!!";
		abort();
	}
	
	while(in>>tmp)
	{
		if (tmp<0)
		{
			cerr<<"Reading neg numbers !!! \n";
			abort();
		}
		else if (tmp<=4000)
			a[tmp] = true;
	}
	
	ofstream out("tmp.txt");
	for (int i=0; i<4001; i++)
		out<<a[i]<<endl;
	
	int count = 0;
	
	for (int t=2500; t<=4000; t++)
	{
		for (int i=0; i<t/2; i++)
			if (a[i]*a[t-i]>0)
		{
			cout<<"t="<<t<<" i="<<i<<endl;
			count++;
			break;
		}
	}
	  
	cout<<"The count is: "<<count<<endl;
}