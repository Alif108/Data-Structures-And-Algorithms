#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <algorithm>
#include <string>

#define INF 99999

using namespace std;

struct Node
{
	int level;
	int cost;
	int city;
	int **reducedMatrix;
	vector<pair<int, int> > path;
};

struct comp {
    bool operator()(const Node* x, const Node* y) const
    {
        return x->cost > y->cost;
    }
};


 class TSP
 {
 	int N;

 public:
 	TSP(int x);
 	Node* createNewNode(int **parentMatrix, int level, vector<pair<int, int> > const &path, int i, int j);
 	void row_reduction(int **reducedMatrix, int *row);
 	void column_reduction(int **reducedMatrix, int *column);
 	int calculate_cost(int **reducedMatrix);
 	int solve(int **costMatrix);
 	void PrintPath(vector<pair<int, int> > const &list);
 };

 TSP::TSP(int x)
 {
 	N = x;
 }

Node* TSP::createNewNode(int **parentMatrix, int level, vector<pair<int, int> > const &path, int i, int j)
{
	Node* node = new Node;

	node->path = path;

	node->reducedMatrix = new int*[N];
	for(int i=0; i<N; i++)
        node->reducedMatrix[i] = new int[N];

	if(level != 0)
	{
		node->path.push_back(make_pair(i,j));
	}

	for(int m = 0; m < N; m++)																	//copying parentMatrix to reducedMatrix..
		for(int n = 0; n<N; n++)
		{
			node->reducedMatrix[m][n] = parentMatrix[m][n];
		}

	for(int k = 0; level!=0 && k<N; k++)
	{
		node->reducedMatrix[i][k] = INF;
		node->reducedMatrix[k][j] = INF;
	}

	node->reducedMatrix[j][0] = INF;

	node->level = level;
	node->city = j;

	return node;
}

void TSP::PrintPath(vector<pair<int, int> > const &list)
{
    for (int i = 0; i < list.size(); i++)
        cout << list[i].first << " -> "
             << list[i].second << endl;
}

void TSP::row_reduction(int **reducedMatrix, int *row)
{
	for(int i=0; i<N; i++)
	{
		row[i] = INF;
	}

	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			if(reducedMatrix[i][j] < row[i])
				row[i] = reducedMatrix[i][j];
		}
	}

	for(int i=0; i<N; i++)
		for(int j=0; j<N; j++)
		{
			if(reducedMatrix[i][j] != INF && row[i] != INF)
				reducedMatrix[i][j] -= row[i];
		}
}

void TSP::column_reduction(int **reducedMatrix, int *column)
{
	for(int i=0; i<N; i++)
	{
		column[i] = INF;
	}

	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			if(reducedMatrix[i][j] < column[j])
				column[j] = reducedMatrix[i][j];
		}
	}

	for(int i=0; i<N; i++)
		for(int j=0; j<N; j++)
		{
			if(reducedMatrix[i][j] != INF && column[j] != INF)
				reducedMatrix[i][j] -= column[j];
		}
}

int TSP::calculate_cost(int **reducedMatrix)
{
	int cost = 0;

	int *row = new int[N];
	int *column = new int[N];

	row_reduction(reducedMatrix, row);
	column_reduction(reducedMatrix, column);

	for(int i=0; i<N; i++)
	{
		if(row[i] != INF)
			cost += row[i];
		else
			cost += 0;
	}

	for(int i=0; i<N; i++)
	{
		if(column[i] != INF)
			cost += column[i];
		else
			cost += 0;
	}

	return cost;
}

int TSP::solve(int **costMatrix)
{
	priority_queue<Node*, std::vector<Node*>, comp> pq;

	vector<pair<int, int> > v;

	Node *root = createNewNode(costMatrix, 0, v, -1, 0);

	root->cost = calculate_cost(root->reducedMatrix);

	pq.push(root);

	while(!pq.empty())
	{
		Node* min_cost_node = pq.top();
		pq.pop();

		int i = min_cost_node->city;

		if(min_cost_node->level == N-1)										//if we touched a leaf node...
		{
			min_cost_node->path.push_back(make_pair(i, 0));
			PrintPath(min_cost_node->path);

			return min_cost_node->cost;
		}

		for(int j=0; j<N; j++)
		{
			if(min_cost_node->reducedMatrix[i][j] != INF)
			{
				Node *child = createNewNode(min_cost_node->reducedMatrix, min_cost_node->level + 1,  min_cost_node->path, i, j);

				child->cost = min_cost_node->cost + min_cost_node->reducedMatrix[i][j] + calculate_cost(child->reducedMatrix);

				pq.push(child);
			}
		}
	}
}

class TSP_Brute_Force
{
	int N;

public:
	TSP_Brute_Force(int x)
	{
		N = x;
	}

	int solve_brute_force(int **costMatrix)
	{
		int final_cost = INF;
		int cost = 0;

		int *permutation = new int[N];

		for(int i=0; i<N; i++)
		{
			permutation[i] = i;
		}

		for(int i=0; i<N-1; i++)
		{
			cost += costMatrix[permutation[i]][permutation[i+1]];
		}
		cost += costMatrix[permutation[N-1]][0];

		if(final_cost > cost)
			final_cost = cost;

		while(next_permutation(permutation + 1 , permutation + N))
		{
			cost = 0;

			for(int i=0; i<N-1; i++)
			{
				cost += costMatrix[permutation[i]][permutation[i+1]];
			}
			cost += costMatrix[permutation[N-1]][0];

			if(final_cost > cost)
				final_cost = cost;
		}

		return final_cost;
	}
};

int main()
{
	int **costMatrix;

	ifstream inFile;
    inFile.open("data10.txt");

    ofstream outFile;
    outFile.open("output.txt");

    if(inFile.fail())
    {
        cerr<<"Couldn't Open Input File";
        exit(1);
    }
    if(outFile.fail())
    {
        cerr<<"Couldn't Open Output File";
        exit(1);
    }

    int N;
    string line;

    getline(inFile, line);
    inFile>>N;

    costMatrix = new int*[N];
	for(int i=0; i<N; i++)
        costMatrix[i] = new int[N];

    for(int i=0; i<N; i++)
    {
    	for(int j=0; j<N; j++)
        {
    		inFile>>costMatrix[i][j];
        }
    }

    cout<<line<<endl;
    cout<<N<<endl;

    for(int i=0; i<N; i++)
    {
    	for(int j=0; j<N; j++)
    		if(costMatrix[i][j] == -1)
    			costMatrix[i][j] = INF;
    }

    for(int i=0; i<N; i++)
    {
    	for(int j=0; j<N; j++)
    		cout<<costMatrix[i][j]<<" ";
    	cout<<endl;
    }

    // TSP_Brute_Force t(5);
    // cout<<t.solve_brute_force(costMatrix)<<endl;
}
