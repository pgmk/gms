#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <queue>
using namespace std;

void BRV(int k);

struct Edge {
	int source;
	int destination;
};

class Graph
{
public:
	vector<vector<int>> adjList;
	Graph(vector<Edge> const& edges, int n);
	void addEdges(vector<Edge> const& edges, int nodes);
	int numberOfNodes = 0;
};

Graph::Graph(vector<Edge> const& edges, int n) {
	adjList.resize(n);
	numberOfNodes = n;
	for (auto& edge : edges)
	{
		adjList[edge.source].push_back(edge.destination);
		adjList[edge.destination].push_back(edge.source);
	}
}

void Graph::addEdges(vector<Edge> const& edges, int nodes) {
	adjList.resize(nodes);
	for (auto& edge : edges)
	{
		adjList[edge.source].push_back(edge.destination);
		adjList[edge.destination].push_back(edge.source);
	}
	this->numberOfNodes = nodes;
}

void printGraph(Graph const& graph, int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << i << " => ";
		for (int v : graph.adjList[i]) {
			cout << v << " ";
		}
		cout << endl;
	}
}

int main()
{
	int model;
	while (scanf_s("%d", &model)!= EOF)
	{
		switch (model)
		{
			// Barabasi–Ravasz–Vicsek parametrem jest ilość iteracji
		case 0:
		{
			int k; // ilość iteracji
			scanf_s("%d", &k);
			BRV(k);
			break;
		}
		// Lu–Su–Guo parametrem modelu jest liczba wierzchołków
		case 1:
		{
			cout << "0"<< endl;
			break;
		}
		// Wzrostowo-iteracyjny
		case 3:
		{
			cout << "0" << endl;
			break;
		}
		// DCN parametrem modelu jest liczba wierzchołków
		case 4:
		{
			cout << "0" << endl;
			break;
		}
		// Kronecker parametrami modelu są potęga oraz graf zapisany za pomocą macierzy sąsiedztwa od lewej do prawej bez spacji
		case 6:
		{
			cout << "0" << endl;
			break;
		}
		}
	}
	return 0;
}

int breadthFirstSearch(const Graph& graph, const int root) {
	std::vector<bool> visited(graph.adjList.size(), false);
	std::vector<int> distances(graph.adjList.size(), 0);
	std::queue<int> queue;
	visited[root] = true;

	queue.push(root);
	while (!queue.empty()) {
		int currentNode = queue.front();
		queue.pop();
		for (const auto& adj : graph.adjList[currentNode])
		{
			if (visited[adj])
			{
				continue;
			}
			visited[adj] = true;
			distances[adj] = distances[currentNode] + 1;
			queue.push(adj);
		}
	}

	int sum = 0;
	for (const auto& distance : distances) {
		sum += distance;
	}
	return sum;
}

int sumShortestDistances(const Graph& g) {
	int sum = 0;
	for (int node = 0; node < g.numberOfNodes; node++)
	{
		sum += breadthFirstSearch(g, node);
	}
	return sum / 2;
}

void BRV(int k) {
	int nodes = 1; // ilosc wierzcholkow
	vector<Edge> edges;
	if (k == 0) {
		printf_s("0");
		return;
	}
	else if (k == 1) {
		edges.push_back({ 0, 1 });
		nodes++;
		edges.push_back({ 0, 2 });
		nodes++;
		Graph graph(edges, nodes);
		printf_s("2");
		return;
	}
	else {
		edges.push_back({ 0, 1 });
		edges.push_back({ 0, 2 });
		nodes = 3;
		int oldNodes = nodes;
		for (int i = 2; i <= k; i++)
		{
			oldNodes = nodes;
			int edgesCount = edges.size();
			for (int i = 0; i < edgesCount; i++)
			{
				edges.push_back({ edges[i].source + nodes, edges[i].destination + nodes });
				edges.push_back({ edges[i].source + 2 * nodes, edges[i].destination + 2 * nodes });
			}
			if (i == 2) {
				edges.push_back({ edges[0].source, edges[0].destination + nodes });
				edges.push_back({ edges[0].source, edges[0].destination + nodes + 1 });
				edges.push_back({ edges[0].source, edges[0].destination + 2 * nodes });
				edges.push_back({ edges[0].source, edges[0].destination + 2 * nodes + 1 });
			}
			nodes = nodes * 3;
		}

		for (int i = 0; i < nodes; i++)
		{
			// Pomijamy niektóre wierzcholki, reszte łączymy z korzeniem
			if (i % 3 != 0 && i!=1 && i !=2 && i!=4 && i!=5 && i!=7 && i!=8 &&//1,2
				!(i % (nodes / (3*(k-2))) == 1 || i % (nodes / (3*(k-2))) == 2) //1,2,10,11,19,20...
				) 
			{
				edges.push_back({ 0, i });
			}
		}

		Graph graph(edges, nodes);
		printGraph(graph, nodes);
		cout << sumShortestDistances(graph) << endl;
		cout << "nodes: " << nodes << endl;
		cout << "edges: " << edges.size() << endl;
	}

}

// lista do macierzy
vector<vector<int> > convert(vector<vector<int>> adj,
	int V)
{
	vector<vector<int> > matrix(V,
		vector<int>(V, 0));

	for (int i = 0; i < V; i++) {
		for (auto j : adj[i])
			matrix[i][j] = 1;
	}
	return matrix;
}

