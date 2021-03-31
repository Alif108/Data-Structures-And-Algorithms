#include <iostream>
#include <fstream>
#include <queue>
#include <cstdlib>
#define NIL -999999
#define INFINITY 999999

using namespace std;

int Min(int a, int b)
{
    if(a<b)
        return a;
    else return b;
}


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
    void changeFlow(int x)
    {
        w = x;
    }
};

class Graph
{
    int nVertices;
    int nEdges;
    int j,k;
    Edge* flow;
    bool directed;

public:
    vector <pair<int,int> > *Adj;
    Edge* edge;
    Graph(int V,int E, bool dir = false);
    bool addEdge(int u,int v,int c);
    int getnVertices();
    int getnEdges();
    int searchEdge(int u,int v);
    int searchResFlow(int u,int v);
    int getCapacity(int u,int v);
    int getResFlow(int u, int v);
    void increase_flow(int u, int v, int x);
    void printGraph();
    void printFlow(ofstream& outFile);
};

Graph::Graph(int V,int E, bool dir)
{
    nVertices = V;
    nEdges = E;
    j = 0;
    k = 0;
    edge = new Edge[nEdges];
    flow = new Edge[2*nEdges];
    directed = dir;
    Adj = new vector <pair<int,int> >[nVertices];

    for(int i=0; i<2*nEdges; i++)
    {
        flow[i].setSource(-1);
        flow[i].setDest(-1);
        flow[i].setWeight(-1);
    }
}

bool Graph::addEdge(int u,int v,int c)
{
    if(k>nEdges)
        return false;
    if(u < 0 || u > nVertices)
        return false;
    if(v < 0 || v > nVertices)
        return false;

    edge[k].setSource(u);
    edge[k].setDest(v);
    edge[k].setWeight(c);
    k++;

    int idx = searchResFlow(u,v);
    if(idx==NIL)                                                                ///if there isn't a parallel edge
    {
        flow[j].setSource(u);
        flow[j].setDest(v);
        flow[j].setWeight(c);
        j++;
        flow[j].setSource(v);
        flow[j].setDest(u);
        flow[j].setWeight(0);
        j++;
    }

    else                                                                        ///if there is a parallel edge
    {
        flow[idx].setWeight(flow[idx].getWeight() + c);
        j++;
    }

    Adj[u].push_back(make_pair(v,c));

    if(!directed)
        Adj[v].push_back(make_pair(u,c));

    return true;
}

int Graph::getnVertices()
{
    return nVertices;
}

int Graph::getnEdges()
{
    return nEdges;
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

int Graph::searchResFlow(int u,int v)
{
    for(int i=0; i<2*nEdges; i++)
    {
        if(flow[i].getSource() == u && flow[i].getDest() == v)
            return i;
    }
    return NIL;
}

int Graph::getCapacity(int u,int v)
{
    int idx = searchEdge(u,v);

    if(idx != NIL)
        return edge[idx].getWeight();

    else return INFINITY;
}

int Graph::getResFlow(int u, int v)
{
    int idx = searchResFlow(u,v);
    if(idx != NIL)
        return flow[idx].getWeight();

    else return INFINITY;
}

void Graph::increase_flow(int u,int v, int x)
{
    int idx = searchResFlow(u,v);
    flow[idx].changeFlow(x);
}

void Graph::printGraph()
{
    for(int i=0; i<nVertices; i++)
    {
        cout<<i<<": ";
        for(int m=0; m < Adj[i].size(); m++)
        {
            cout<<Adj[i][m].first<<" ";
            cout<<Adj[i][m].second<<"   ";
        }
        cout<<endl;
    }
}

void Graph::printFlow(ofstream& outFile)
{
    for(int i=0; i<nEdges; i++)
    {
        int u = edge[i].getSource();
        int v = edge[i].getDest();
        //cout<<u<<" "<<v<<" "<<getCapacity(u,v)-getResFlow(u,v)<<"/"<<getCapacity(u,v)<<endl;
        outFile<<u<<" "<<v<<" "<<getCapacity(u,v)-getResFlow(u,v)<<"/"<<getCapacity(u,v)<<endl;
    }
}


bool bfs(Graph g, int p[], int s, int t)
{
    int n = g.getnVertices();
    bool visited[n];

    for(int i=0; i<n; i++)
    {
        visited[i] = false;
    }

    queue <int> Q;
    Q.push(s);
    visited[s] = true;
    p[s] = -1;

    while(!Q.empty())
    {
        int u = Q.front();
        Q.pop();

        for(int i=0; i<g.Adj[u].size(); i++)
        {
            int v = g.Adj[u][i].first;

            if(g.getResFlow(u,v) == 0)
                continue;

            else if(!visited[v])
            {
                p[v] = u;
                visited[v] = true;
                Q.push(v);
            }
        }
    }
    if(visited[t])
        return true;
    else return false;
}

int FF(Graph g, int s, int t, ofstream& outFile)                                   ///This uses Edmond-Karp
{                                                               ///O(VE^2)
    Graph res(g.getnVertices(), g.getnEdges());

    for(int i=0; i<g.getnEdges(); i++)
    {
        int u = g.edge[i].getSource();
        int v = g.edge[i].getDest();
        int c = g.edge[i].getWeight();
        res.addEdge(u,v,c);
    }

    int parent[g.getnVertices()];

    int max_flow = 0;

    while(bfs(res, parent, s, t))
    {
        int res_capacity = INFINITY;

        for(int v=t; v!=s; v=parent[v])
        {
            int u = parent[v];
            res_capacity = Min(res_capacity, res.getResFlow(u,v));
        }

        for(int v=t; v!=s; v=parent[v])
        {
            int u = parent[v];
            res.increase_flow(u, v, res.getResFlow(u,v) - res_capacity);
            res.increase_flow(v, u, res.getResFlow(v,u) + res_capacity);
        }

        max_flow += res_capacity;
    }
    outFile<<max_flow<<endl;
    //cout<<max_flow<<endl;
    res.printFlow(outFile);
    return max_flow;
}


int main()
{
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

    int N,M;
    inFile>>N>>M;

    //cin>>N>>M;

    Graph g(N,M,true);

    int u,v,c;

    for(int i=0; i<M; i++)
    {
        //cin>>u>>v>>c;
        inFile>>u>>v>>c;
        g.addEdge(u,v,c);
    }
    int s,t;
    //cin>>s>>t;
    inFile>>s>>t;
    FF(g, s, t, outFile);
}
