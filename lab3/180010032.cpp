#include <bits/stdc++.h>

using namespace std;

ofstream f1;

class Heap
{
	vector<int> a;
	vector<int> heaps;
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
			int largest=i;
			if(left_child(i)<heap_size and a[left_child(i)] > a[largest])
				largest = left_child(i);
			if(right_child(i)<heap_size and a[right_child(i)] > a[largest])
				largest = right_child(i);
			if(i!=largest)
			{
				swap(a[i],a[largest]);
				max_heapify(largest);
			}
		}
		void max_heapify2(int i,int heap_size2)
		{
			int largest=i;
			if(left_child(i)<heap_size2 and heaps[left_child(i)] > heaps[largest])
				largest = left_child(i);
			if(right_child(i)<heap_size2 and heaps[right_child(i)] > heaps[largest])
				largest = right_child(i);
			if(i!=largest)
			{
				swap(heaps[i],heaps[largest]);
				max_heapify2(largest,heap_size2);
			}
		}
		int increase_key(int i, int key)
		{
			if(a[i] <= key)
			{
				a[i] = key;
				while(i > 0 and a[i] > a[parent(i)])
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
		void maximum()
		{
			if(heap_size>0)
				f1<<a[0];
			f1<<endl;
		}
		void extract_max()
		{
			if(heap_size>0)
			{
				int max = a[0];
				a[0] = a[heap_size-1];
				heap_size -= 1;
				a.pop_back();
				max_heapify(0);
				f1<<max;
			}
			f1<<endl;

		}
		void heap_sort()
		{
			int heap_size2 = heap_size;
			heaps.clear();
			heaps = a;
			while(heap_size2>1)
			{
				swap(heaps[0],heaps[heap_size2-1]);
				heap_size2 -= 1;
				max_heapify2(0,heap_size2);

			}
			if(heap_size>0)
			{
				f1<<heaps[0];
				for(int i=1;i<heap_size;i++)
				{
					f1<<" "<<heaps[i];
				}
			}
			f1<<endl;
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
		// f1<<line[0]<<endl;
		if (!strcmp(line[0],"insert"))
		{
			int k = atoi(line[1]);
			test.insert(k);
			f1<<k<<" inserted\n";
		}
		else if(!strcmp(line[0],"maximum"))
		{
			test.maximum();
		}
		else if(!strcmp(line[0],"extract-max"))
		{
			test.extract_max();
		}
		else if(!strcmp(line[0],"increase-key"))
		{
			// f1<<line[1]<<endl;
			int index = atoi(line[1]);
			// f1<<index<<endl;
			int number = atoi(line[1]+2);
			// f1<<number<<endl;
			if(test.increase_key(index,number))
			{
				f1<<"Key at "<<index<<" changed to "<<number<<endl;
			}
			else
			{
				f1<<number<<" is less than the current key at "<<index<<endl;
			}
		}
		else if(!strcmp(line[0],"sort"))
		{
			// f1<<"Inside sort"<<endl;
			test.heap_sort();
			// f1<<"After heap sort"<<endl;
			// f1<<v[0];
			// for(int i = 1;i<v.size();i++)
			// {
			// 	f1<<" "<<v[i];
			// }
		}
	}
	f1.close();
	return 0;
}