#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

int find_median(const vector<int>&ws)
{
	priority_queue<int, vector<int>, greater<int> > ts(ws.begin(),ws.end());
	
	int s=ws.size();
	int n=(s%2==0)?(s/2):((s+1)/2);
	
	for(unsigned int i=0; i<n-1; i++)
		ts.pop();
	cout<<"m="<<ts.top()<<endl;
	
	return ts.top();
}


int main()
{
	ifstream in("Median.txt");
	
	vector<int> ws(0),ans(0);
	
	int tmp;
	
	while(in>>tmp)
	{
		ws.push_back(tmp);
		ans.push_back(find_median(ws));
	}
	
	int f=0;
	for (unsigned int i=0; i<ans.size(); i++)
		f+=ans[i];
	
	f=f%10000;
	
	cout<<f<<endl;
}