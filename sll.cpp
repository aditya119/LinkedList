#include<iostream>
#include<cstdlib>
#include<fstream>

using namespace std;

struct record
{
	int data;
	struct record *next;
};

typedef struct record rec;

/*rec* create(rec *q)
{
	rec *curr;
	curr = (rec*)malloc(sizeof(rec));
	q = curr;
	char ch;
	do
	{
		curr->next = (rec*)malloc(sizeof(rec));
		cin >> curr->data;
		curr = curr->next;
		cout << "another node?\n";
		cin >> ch;
	}
	while(ch == 'y');
	curr->next = NULL;
	return q;
}*/

void view(rec *q)
{
	system("clear");
	rec *temp;
	temp = q;
	if(temp == NULL)
	{
		cout << "List Empty\n";
		return;
	}
	do
	{
		cout << temp->data << endl;
		temp = temp->next;
	}while(temp != NULL);
}

rec* insert(rec *q)
{
	system("clear");
	rec *node, *naya, *temp;
	naya = (rec*)malloc(sizeof(rec));
	if(!naya)
	{
		cout << "Memory Error\n";
		return 0;
	}
	node = q;
	if(q == NULL)
	{
		cout << "enter data for new node:\n";
		cin >> naya->data;
		naya->next = node;
		q = naya;
		return q;
	}
	else
	{
		cout << "enter data for new node:\n";
		int x;
		cin >> x;
		if((q->data) > x)
		{
			naya->data = x;
			naya->next = q;
			q = naya;
			return q;
		}
		else
		{
			rec *temp;
			if(node->next == NULL)
			{
				temp = node;
				node = node->next;
				temp->next = naya;
				naya->next = node;
				naya->data = x;
				return q;
			}	
			while(node->next->data < x)
			{
				temp = node;
				node = node->next;
				if(node->next == NULL)
				{
					temp = node;
					node = node->next;
					temp->next = naya;
					naya->next = node;
					naya->data = x;
					return q;
				}

			}
			naya->next = node->next;
			node->next = naya;
			naya->data = x;
			return q;
		}
	}
}

rec* remove(rec *q)
{
	system("clear");
	rec *node;
	if(q == NULL)
	{
		cout << "List empty\n";
		return NULL;
	}
	node = q;
	cout << "enter data of node to be deleted:\n";
	int x;
	cin >> x;
	if(q->data == x)
	{
		if(q->next == NULL)
		{
			free(q);
			q = NULL;
			return q;
		}
		q = q->next;
		free(node);
		return q;
	}
	else
	{
		rec *prev;
		while(node->data != x)
		{
			prev = node;
			node = node->next;
			if(node == NULL)
			{
				cout << "Node does not exist\n";
				return q;
			}
		}
		prev->next = node->next;
		free(node);
		return q;
	}
}

void update(rec *q)
{
	system("clear");
	rec *node;
	node = q;
	if(q == NULL)
	{
		cout << "List empty\n";
		return;
	}
	cout << "enter data of the node to be updated:\n";
	int x;
	cin >> x;
	while(node->data != x)
	{
		node = node->next;
		if(node == NULL)
		{
			cout << "Node does not exist\n";
			return;
		}
	}
	cout << "enter new data for the node:\n";
	cin >> node->data;
}

void count(rec *q)
{
	system("clear");
	rec *current;
	current = q;
	int count = 0;
	if(q !=  NULL)
	{
		while(1)
		{
			if(current == NULL)
			{
				count = 2 * count;
				break;
			}
			else if(current->next == NULL)
			{
				count = 2 * count + 1;
				break;
			}
			current = current->next->next;
			count++;
		}
	}
	cout << "Number of nodes in list = " << count << endl << endl;
}

rec* reverse(rec *q)
{
	if(q == NULL || q->next == NULL)
		return q;
	rec *current, *prev = NULL, *next = NULL;
	current = q;
	while(current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	return prev;
}

bool isEmptyFile(ifstream& file)
{
    return file.peek() == ifstream::traits_type::eof();
}

rec* readFile()
{
	ifstream dbi("database", ios :: in);
	int count = 0;
	rec *q, *node;
	if(isEmptyFile(dbi))
	{
		q = NULL;
		cout << count << " nodes retrieved\n\n";
		dbi.close();
		return q;
	}
	char ch;
	node = (rec*)malloc(sizeof(rec));
	q = node;
	rec *temp, *temp1;
	dbi.seekg(0);
	while(!dbi.eof())
	{
		node->next = (rec*)malloc(sizeof(rec));
		dbi >> node->data;
		temp1 = temp;
		temp = node;
		node = node->next;
		count++;
	}
	temp1->next = NULL;
	free(node);
	free(temp);
	count--;
	cout << count << " nodes retrieved\n\n";
	dbi.close();
	return q;
}

void writeFile(rec *q)
{
	rec *node;
	node = q;
	ofstream dbo("database", ios::trunc);
	int count = 0;
	if(q == NULL)
	{
		cout << count << " nodes added\nlist empty\n";
		return;
	}
	while(node != NULL)
	{
		dbo << node->data << endl;
		node = node->next;
		count++;
	}
	cout << count << " nodes added\n\n";
	dbo.close();
}

int main()
{
	rec *start;
	start = NULL;
	//start = create(start);
	start = readFile();
	char ch;
	system("clear");
	do
	{
		cout << "what do you want to do?\n(V)iew List\n(I)nsert Node\n(D)elete Node\n(U)pdate Node\n(C)ount Nodes\n(R)everse List\n(E)xit\n";
		cin >> ch;
		switch(ch)
		{
			case 'V': view(start); break;
			case 'I': start = insert(start); break;
			case 'D': start = remove(start); break;
			case 'U': update(start); break;
			case 'C': count(start); break;
			case 'R': start = reverse(start); view(start); break;
		}
	}
	while(ch != 'E');
	writeFile(start);
	return  0;
}