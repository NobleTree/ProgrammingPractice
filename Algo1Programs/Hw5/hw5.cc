#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>

using namespace std;

vector<vector<int> > read_file(const string& f_name, const unsigned int n) 
{ 
  vector<vector<int> > le(n, vector<int>(n));
		
  ifstream in(f_name.c_str());
  for (unsigned int i=0; i<n; i++)
    {
      string s;
      getline(in, s);
      stringstream ss(s);
      int v_node;
			
      ss>>v_node;
			
      int t_node;
      while(ss>>t_node)
	{
	  int l;
	  char c;
	  ss>>c>>l;

	  le[v_node-1][t_node-1]=l;
	}
    }
		
  return le;
}


pair<int, int> get_smallest(vector<int>& adj_row)
{
  int value = 1e6;
  int small = -1;

  for (unsigned int i=0; i<adj_row.size(); i++)
    if ((adj_row[i]>0)&&(adj_row[i]<value))
      {
	value = adj_row[i];
	small = i;
      }
  
  return make_pair(small, value);
}


vector<int> dijkstra_path(vector<vector<int> >& adj_list, const int n)
{
  vector<int> x, a(n);
  x.push_back(0);
  a[0] = 0;

  while(true)
    {
      int node = -1, length = 1e6;

      for(unsigned int j=0; j<x.size(); j++)
	{
	  pair<int, int> ans = get_smallest(adj_list[x[j]]);
	  if (a[x[j]]+ans.second<length)
	    {
	      length = ans.second+a[x[j]];
	      node = ans.first;
	    }
	}
      
      if (node==-1)
	break;
      
      for (unsigned int j=0; j<x.size(); j++)
	{
	  adj_list[x[j]][node]=0;
	  adj_list[node][x[j]]=0;
	}
      
      x.push_back(node);
      a[node] = length;
    }

  for (int i=1; i<n; i++)
    if (a[i] == 0)
      a[i] = 1e6;

  return a;
}


int main()
{
  string f_name("dijkstraData.txt");
  unsigned int n=200;

  vector<vector<int> >adj_list = read_file(f_name, n);	
  vector<int> sp = dijkstra_path(adj_list, n);

  //int is[]={2,3,4,5};
 
  int is[]={7,37,59,82,99,115,133,165,188,197};
  for(unsigned int i=0; i<10; i++)
    --is[i];

  cout<<"the shortest paths are: \n";
  for (unsigned int i=0; i<10; i++)
    cout<<sp[is[i]]<<",";
  
  cout<<endl;
}
