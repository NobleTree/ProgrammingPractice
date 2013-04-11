#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>

class QSortBase
{
public:
  QSortBase():count(0){}

  void quick_sort(int* A, const int n);
  int get_count(){return count;}
  void reset_count(){count=0;}

protected:
  virtual
  int choose_pivot(int* A, const int n)=0;

  int partition_array(int* A, const int n);

private:
  int count;
};


int QSortBase::partition_array(int* A, const int n)
{
  int i=0;

  for (int j=1; j<n; j++)
    {
      if(A[j]<A[0])
	{
	  std::swap(A[j], A[i+1]);
	  i++;
	}
    }

  std::swap(A[0], A[i]);

  return i;
}


void QSortBase::quick_sort(int* A, const int n)
{
  if (n==1)
    return;
  
  count+=(n-1);

  int p=choose_pivot(A, n); //choose pivot, swap to head, return value as p 
  int i=partition_array(A, n); //p always head, return location of p in the partioned
  
  if(i>0)
    quick_sort(&A[0], i);

  if(i<n-1)
    quick_sort(&A[i+1], n-i-1);
}


class QSortFirst : public QSortBase
{ 
protected:
  virtual
  int choose_pivot(int* A, int n){ 
    return *A; //naive implementation, return head
  }
};


class QSortLast : public QSortBase
{
protected:
  virtual
  int choose_pivot(int* A, int n){
    std::swap(A[0], A[n-1]);
    return *A; //actually return tail of (original) array
  }
};


struct PairComp{
  bool operator()(std::pair<int, int> x, std::pair<int, int> y){return (x.first<y.first);}
}comp;

class QSortMedianThree : public QSortBase
{
protected:
  virtual
  int choose_pivot(int* A, int n){
    int m=(n+1)/2-1; //it is the median position of the array

    // if (((A[m]>A[0])&&(A[m]<A[n-1]))||((A[m]>A[n-1])&&(A[m]<A[0])))
    //   std::swap(A[0], A[m]);

    
    // if (((A[n-1]>A[0])&&(A[n-1]<A[m]))||((A[n-1]>A[m])&&(A[n-1]<A[0])))
    //   std::swap(A[0], A[n-1]);

    std::vector<std::pair<int, int> > B(0);
    //std::cout<<"+++A[0]="<<A[0]<<" A["<<m<<"]="<<A[m]<<" A["<<n-1<<"]="<<A[n-1]<<std::endl;
    
    std::pair<int, int> pair1=std::make_pair(A[0],0);
    B.push_back(pair1);
    pair1=std::make_pair(A[m],m);
    B.push_back(pair1);
    pair1=std::make_pair(A[n-1],n-1);
    B.push_back(pair1);

    // std::cout<<"+++A[0]="<<A[0]<<" A["<<m<<"]="<<A[m]<<" A["<<n-1<<"]="<<A[n-1]<<std::endl;

    std::sort(B.begin(), B.end(), comp);
    std::swap(A[0], A[B[1].second]);

    //std::cout<<"---A[0]="<<A[0]<<" A["<<m<<"]="<<A[m]<<" A["<<n-1<<"]="<<A[n-1]<<std::endl;

    return *A; //actually return tail of (original) array
  }
};


using namespace std;

int main()
{
  ifstream in("QuickSort.txt");

  const int n=std::count(std::istreambuf_iterator<char>(in), 
			 std::istreambuf_iterator<char>(), 
			 '\n');
  in.seekg(0, in.beg);

  int* A=new int(n);
  int count=0;

  for(int i=0; i<n; i++){
      in>>A[i];
    }
  
  QSortMedianThree qs;
  qs.reset_count();
  qs.quick_sort(A, n);

  cout<<"\n The array is: \n";
  for (int i=0; i<n; i++)
    cout<<A[i]<<" ";
  cout<<endl;

  cout<<"The count is: "<<qs.get_count()<<endl;
}
