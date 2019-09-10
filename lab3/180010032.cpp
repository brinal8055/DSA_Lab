#include <bits/stdc++.h>

using namespace std;

ofstream f1;

class Heap
{
	vector <int> a;
	vector <int> heaps;
	int heap_size;

	public:
		Heap()
		{
			heap_size = 0;
		}
		int parent(int i)
		{
			return (i-1)/2;
		}
		int left_child(int i)
		{
			return 2*i+1;
		}
		int right_child(int i)
		{
			return 2*i+2;
		}
		void max_heapify(int i)
		{
			int largest = i;
			if(left_child(i)<heap_size and a[left_child(i)] > a[i])
				largest = right_child(i);
			if(right_child(i)<heap_size and a[right_child(i)] > a[i])
				largest = left_child(i);
			if(i!=largest)
			{
				swap(a[i],a[largest]);
				max_heapify(largest);
			}
		}
		void max_heapify2(int i,int heap_size2)
		{
			int largest = i;
			if(left_child(i)<heap_size2 and heaps[left_child(i)] > a[i])
				largest = right_child(i);
			if(right_child(i)<heap_size2 and heaps[right_child(i)] > a[i])
				largest = left_child(i);
			if(i!=largest)
			{
				swap(heaps[i],heaps[largest]);
				max_heapify2(largest,heap_size2);
			}
		}
		int increase_key(int i, int key)
		{
			if(a[i]<=key)
			{
				a[i] = key;
				while(i>0 and a[i] > a[parent(i)])
				{
					swap(a[i],a[parent(i)]);
					i = parent(i);
				}
				return 1;
			}
			else
			{
				return 0;
			}
		}
		void insert(int k)
		{
			heap_size++;
			a.push_back(-INT_MAX);
			increase_key(heap_size-1,k);
		}
		int maximum()
		{
			if(heap_size>0)
				return a[0];
			else
				return NULL;
		}
		int extract_max()
		{
			if(heap_size>0)
			{
				int max = a[0];
				a[0] = a[heap_size-1];
				heap_size -= 1;
				max_heapify(0);
				return max;
			}
			else
				return NULL;

		}
		vector <int> heap_sort()
		{
			int heap_size2 = heap_size;
			heaps = a;
			while(heap_size2>1)
			{
				swap(heaps[0],heaps[heap_size2-1]);
				heap_size2 -= 1;
				max_heapify2(0,heap_size2);

			}
			return heaps;
		}
};



int main(int argc, char **argv)
{
	ifstream input;
	f1.open("heap.txt");
	input.open(argv[1]);
	Heap test;
	char inp[20];

	while(input.getline(inp,20))
	{
		int i=0;
		
		char *line[15];
		
		line[i] = strtok(inp," ");
		
		while(line[i]!=NULL)
		{
		   line[++i] = strtok(NULL,"\n");
		}
		if (!strcmp(line[0],"insert"))
		{
			int k = atoi(line[1]);
			test.insert(k);
			cout<<k<<" inserted\n";
		}
		else if(!strcmp(line[0],"maximum"))
		{
			cout<<test.maximum()<<endl;
		}
		else if(!strcmp(line[0],"extract-max"))
		{
			cout<<test.extract_max()<<endl;
		}
		else if(!strcmp(line[0],"increase-key"))
		{
			int index = atoi(line[1]);
			int number = atoi(line[2]);
			if(test.increase_key(index,number)==1)
			{
				cout<<"Key at "<<index<<" changed to "<<number<<endl;
			}
			else
			{
				cout<<number<<" is less than the current key at "<<index<<endl;
			}
		}
		else if(!strcmp(line[0],"sort"))
		{
			vector <int> v = test.heap_sort();
			cout<<v[0];
			for(int i = 1;i<v.size();i++)
			{
				cout<<" "<<v[i];
			}
			cout<<endl;
		}
	}
	f1.close();
	return 0;
}