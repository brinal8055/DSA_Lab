#include <bits/stdc++.h>

using namespace std;

ofstream f1;

class Tree
{
	struct Node
	{
		int data;
		Node *left;
		Node *right;
		Node *top;
		Node(int k)
		{
			data = k;
			left = NULL;
			right = NULL;
			top = NULL;
		}
	};

public:
	Node *root;
	vector <int> v;
	Tree()
	{
		root = NULL;
	}
	void insert(Node *x)
	{
		Node *p=NULL;
		Node *y = root;

		if (y == NULL)
		{
			root = x;
		}
		else
		{
			while(y!= NULL)
			{
				p = y;
				if(x->data<y->data)
				{
					y = y->left;
				}
				else
				{
					y = y->right;
				}
			}
			x->top = p;
			if(x->data<p->data)
			{
				p->left = x;
			}
			else
			{
				p->right = x;
			}
		}

	}
	void insertnew(int k)
	{
		Node *new_node;
		new_node = new Node(k);
		insert(new_node);
		f1<<k<<" inserted\n";
	}
	Node * search(Node* t, int k)
	{
		Node *x = t;

		while(x != NULL and x->data != k)
		{
			if(k<x->data)
			{
				return search(x->left,k);
			}
			return search(x->right,k);
		}
		return x;
	}
	vector<int> inorder(Node *t)
	{
		Node *x = t;
		if(x!=NULL)
		{
			inorder(x->left);
			v.push_back(x->data);
			inorder(x->right);
		}
		return v;
	}
	vector<int> preorder(Node* t)
	{
		Node *x = t;
		if (x!=NULL)
		{
			v.push_back(x->data);
			preorder(x->left);
			preorder(x->right);
		}
		return v;
	}
	vector<int> postorder(Node *t)
	{
		Node *x = t;
		if(x!=NULL)
		{
			postorder(x->left);
			postorder(x->right);
			v.push_back(x->data);
		}
		return v;
	}
	Node * minimum(Node *t)
	{
		Node *x = t;
		while(x->left!=NULL)
		{
			x = x->left;
		}
		return x;
	}
	Node * maximum(Node *t)
	{
		Node *x = t;
		while(x->right!=NULL)
		{
			x = x->right;
		}
		return x;
	}
	Node * predecessor(Node *x)
	{
		if(x->left!=NULL)
			return maximum(x->left);
		else
		{
			Node *y = x->top;
			while(y!=NULL and y->left==x)
			{
				x = y;
				y = y->top;
			}
			return y;
		}
	}
	Node* successor(Node *x)
	{
		if(x->right!=NULL)
		{
			return minimum(x->right);
		}
		else
		{
			Node* y = x->top;
			while(y!=NULL and y->right==x)
			{
				x=y;
				y = y->top;
			}
			return y;
		}

	}
	void transplant(Node *u, Node* v)
	{
		if(u->top == NULL)
		{
			root = v;
		}
		else if(u->top->left==u)
		{
			u->top->left = v;
		}
		else
		{
			u->top->right = v;
		}
		if(v!=NULL)
		{
			v->top = u->top;
		}
	}

	void deleter(Node *z)
	{
		if(z->left==NULL)
		{
			transplant(z,z->right);
		}
		else if (z->right==NULL)
		{
			transplant(z,z->left);
		}
		else
		{
			Node *y = minimum(z->right);
			if(y->top!=z)
			{
				transplant(y,y->right);
				y->right = z->right;
				y->right->top = y;
			}
			transplant(z,y);
			y->left = z->left;
			y->left->top = y;
		}
	}


};



int main(int argc, char **argv)
{
	ifstream input;
	f1.open("bst.txt");
	input.open(argv[1]);
	Tree test;
	char inp[20];

	while(input.getline(inp,20))
	{
		int i=0;
		
		char *line[15];
		
		//f1<<inp<<endl;
		line[i] = strtok(inp," ");

		while(line[i]!=NULL)
		{
		   line[++i] = strtok(NULL,"\n");
		}
		//f1<<line<<endl;
		
		if (!strcmp(line[0],"insert"))
		{
			int k = atoi(line[1]);
			test.insertnew(k);	
		}
		else if(!strcmp(line[0],"search"))
		{			
			int k = atoi(line[1]);
			if(test.search(test.root,k)!=NULL)
			{
				f1<<k<<" found"<<endl;
			}
			else
			{
				f1<<k<<" not found\n";
			}
		}
		else if(!strcmp(line[0],"inorder"))
		{
			test.v.clear();
			test.v = test.inorder(test.root);
			if(test.v.size()>=1)
			{
				f1<<test.v[0];
				for(auto i = test.v.begin()+1;i!=test.v.end();i++)
				{
					f1<<" "<<*i;
				}
			}
			f1<<endl;
		}
		else if(!strcmp(line[0],"preorder"))
		{
			test.v.clear();
			test.v =test.preorder(test.root);
			if(test.v.size()>=1)
			{
				f1<<test.v[0];
				for(auto i = test.v.begin()+1;i!=test.v.end();i++)
				{
					f1<<" "<<*i;
				}
			}
			f1<<endl;
		}
		else if(!strcmp(line[0],"postorder"))
		{
			test.v.clear();
			test.v = test.postorder(test.root);
			if(test.v.size()>=1)
			{
				f1<<test.v[0];
				for(auto i = test.v.begin()+1;i!=test.v.end();i++)
				{
					f1<<" "<<*i;
				}
			}
			f1<<endl;
		}
		else if(!strcmp(line[0],"minimum"))
		{
			if(test.root!=NULL)
			{
				f1<<test.minimum(test.root)->data;
			}
			f1<<endl;
		}
		else if(!strcmp(line[0],"maximum"))
		{
			if(test.root!=NULL)
			{
				f1<<test.maximum(test.root)->data;
			}
			f1<<endl;
		}
		else if(!strcmp(line[0],"predecessor"))
		{
			int k = atoi(line[1]);
			if(test.search(test.root,k)!=NULL)
			{
				if(test.predecessor(test.search(test.root,k))!=NULL)
				{
					f1<<test.predecessor(test.search(test.root,k))->data<<endl;
				}
				else
				{
					f1<<"predecessor of "<<k<<" does not exist\n";
				}
			}
			else
			{
				f1<<k<<" does not exist\n";
			}
		}
		else if(!strcmp(line[0],"successor"))
		{
			int k = atoi(line[1]);
			if(test.search(test.root,k)!=NULL)
			{
				if(test.successor(test.search(test.root,k))!=NULL)
				{
					f1<<test.successor(test.search(test.root,k))->data<<endl;
				}
				else
				{
					f1<<"successor of "<<k<<" does not exist\n";
				}
			}
			else
			{
				f1<<k<<" does not exist\n";
			}
		}
		else if(!strcmp(line[0],"delete"))
		{
			int k = atoi(line[1]);
			if(test.search(test.root,k)!=NULL)
			{
				test.deleter(test.search(test.root,k));
				f1<<k<<" deleted\n";
			}
			else
			{
				f1<<k<<" does not exist\n";
			}
		}

	}
	f1.close();
	return 0;
}