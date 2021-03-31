#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <queue>
#define NIL -999999
#define INFINITY 999999

using namespace std;

class DisjointSet
{
    int parent[10000],rank[10000];

public:

    DisjointSet()
    {
        for(int i=0; i<10000; i++)
        {
            parent[i] = -1;
            rank[i] = -1;
        }
    }

    void MakeSet(int i)                                 ///O(1)
    {
        /*rank = new int[a];
        parent = new int[a];
        n = a;
        for(int i=0; i<n; i++)
        {
            parent[i] = i;
            rank[i] = 0;
        }*/

        parent[i] = i;
        rank[i] = 0;

    }

    void Link(int x,int y)
    {
        if( rank[x] > rank[y] )
            parent[y] = x;
        else
            parent[x] = y;

        if(rank[x] == rank[y])
        {
            parent[x] = y;
            rank[y]+=1;
        }
    }

    int FindSet(int i)                                  ///O(logn)
    {
        if(parent[i] == i)
            return i;
        else
        {
            int x = FindSet(parent[i]);
            parent[i] = x;
            return x;
        }
    }

    void Union(int x,int y)                                 ///O(1)
    {
        Link(FindSet(x),FindSet(y));
    }

    void print(int x)
    {
        for(int i=0; i<10000; i++)
        {
            if(parent[i] == parent[x])
                cout<<i<<" ";
        }
        cout<<endl;
    }

    int Min(int x)
    {
        int p = FindSet(x);
        int mini = INFINITY;

        for(int i=0; i<10000; i++)
        {
            if(parent[i] == p)
            {
                if(i<mini)
                    mini = i;
            }
        }
        return mini;
    }
};

class Edge
{
    int u,v,w;

public:

    void setSource(int x)
    {
        u = x;
    }
    void setDest(int x)
    {
        v = x;
    }
    void setWeight(int x)
    {
        w = x;
    }
    int getSource()
    {
        return u;
    }
    int getDest()
    {
        return v;
    }
    int getWeight()
    {
        return w;
    }
};

bool CompareEdge(Edge a, Edge b)
{
    if(a.getWeight()<b.getWeight())
        return (a.getWeight()<b.getWeight());
    //else
        //return (b.getWeight()<a.getWeight());
}

class Graph
{
    int nVertices;
    int nEdges;
    int k;
    Edge* edge;
    int *key;
    int *parent;
    int *visited;
    vector <pair<int,int> > *Adj;

public:

    Graph(int V,int E);
    bool addEdge(int u,int v,int w);
    void Prims(int source,ofstream &outFile);
    void Kruskals(ofstream &outFile);
    void PrintGraph();
    int searchEdge(int u,int v);
    int getWeight(int u,int v);
};

Graph::Graph(int V,int E)
{
    nVertices = V;
    nEdges = E;
    edge = new Edge[nEdges];
    k = 0;
    key = new int[nVertices];
    parent = new int[nVertices];
    visited = new int[nVertices];
    Adj = new vector <pair<int,int> >[nVertices];
}

bool Graph::addEdge(int u,int v,int w)
{
    if(k>nEdges)
        return false;
    if(u < 0 || u > nVertices)
        return false;
    if(v < 0 || v > nVertices)
        return false;

    edge[k].setSource(u);
    edge[k].setDest(v);
    edge[k].setWeight(w);
    k++;

    Adj[u].push_back(make_pair(v,w));
    //Weight[u].push_back(w);
    Adj[v].push_back(make_pair(u,w));
    //Weight[v].push_back(w);
    return true;
}

int Graph::searchEdge(int u,int v)
{
    for(int i=0; i<nEdges; i++)
    {
        if(edge[i].getSource() == u && edge[i].getDest() == v)
            return i;
    }
    return NIL;
}

void Graph::PrintGraph()
{
    for(int i=0; i<nVertices; i++)
    {
        cout<<"Vertex "<<i<<"-> ";
        for(int j=0; j < Adj[i].size(); j++)
        {
            cout<<Adj[i][j].first<<" ";
        }
        cout<<endl;
    }
    cout<<"Weights: "<<endl;
    for(int i=0; i<nVertices; i++)
    {
        cout<<"Vertex "<<i<<"-> ";
        for(int j=0; j < Adj[i].size(); j++)
        {
            cout<<Adj[i][j].second<<" ";
        }
        cout<<endl;
    }
}

int Graph::getWeight(int u,int v)
{
    int idx = searchEdge(u,v);

    if(idx != NIL)
        return Adj[u][idx].second;

    else return INFINITY;
}

void Graph::Prims(int source, ofstream &outFile)
{
    int MSTw = 0;

    for(int i=0; i<nVertices; i++)
    {
        key[i] = INFINITY;
        parent[i] = NIL;
        visited[i] = 0;
    }
    key[source] = 0;

    priority_queue <pair<int,int> > pq;

    pq.push(make_pair(0,source));

    while(!pq.empty())
    {
        int u = pq.top().second;
        //cout<<u<<endl;
        pq.pop();

        if(!visited[u])
        {
            int l = Adj[u].size();
            for(int v=0; v < l; v++)
            {
                if(!visited[Adj[u][v].first])
                if(Adj[u][v].second < key[Adj[u][v].first])
                {
                    //cout<<"U: "<<u<<" "<<"V: "<<Adj[u][v]<<endl;
                    parent[Adj[u][v].first] = u;
                    key[Adj[u][v].first] = Adj[u][v].second;
                    //cout<<"Parent of v: "<<parent[Adj[u][v]]<<endl;
                    //cout<<"Key of v: "<<key[Adj[u][v]]<<endl;
                    pq.push(make_pair(-key[Adj[u][v].first],Adj[u][v].first));
                }
            }
        }
        visited[u] = 1;
    }

    for(int i=0; i<nVertices; i++)
        MSTw = MSTw + key[i];

    outFile<<MSTw<<endl;
    outFile<<"Prim's Algorithm:"<<endl;
    outFile<<"Root Node: "<<source<<endl;

    for(int i=0; i<nVertices; i++)
    {
        if(parent[i] != NIL)
        {
            outFile<<i<<" "<<parent[i]<<endl;
        }
    }
}

void Graph::Kruskals(ofstream &outFile)
{
    outFile<<"Kruskal's Algorithm"<<endl;
    int u,v;
    DisjointSet T;

    for(int i=0; i<nVertices; i++)
        T.MakeSet(i);

    sort(edge,edge+nEdges,CompareEdge);             //Sorting the array of objects using CompareEdge function

    /*for(int i=0; i<nEdges; i++)
    {
        cout<<"u: "<<edge[i].getSource()<<" v: "<<edge[i].getDest()<<" w: "<<edge[i].getWeight()<<endl;
    }*/

    for(int i=0; i<nEdges; i++)
    {
            u = edge[i].getSource();
            v = edge[i].getDest();
            //cout<<"U :"<<u<<" V: "<<v<<endl;
            if(T.FindSet(u) != T.FindSet(v))
            {
                T.Union(T.FindSet(u),T.FindSet(v));
                outFile<<u<<" "<<v<<endl;
            }
    }
}

int main()
{
    srand(time(NULL));
    ifstream inFile;
    inFile.open("input.txt");

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

    int V,E,u,v,w;
    inFile>>V>>E;

    Graph g(V,E);

    for(int i=0; i<E; i++)
    {
        inFile>>u>>v>>w;
        g.addEdge(u,v,w);
    }

    g.Prims(rand()%V,outFile);
    outFile<<endl;
    g.Kruskals(outFile);
}

