#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector> 

using namespace std;

struct Edge {
	int src, dest, weight;
};

struct Graph {
	int V, E;

	struct Edge* edge;
};

struct Graph* createGraph(int V, int E)
{
	struct Graph* graph = new Graph;
	graph->V = V;
	graph->E = E;
	graph->edge = new Edge[E];
	return graph;
}

int main(int argc, char* argv[])
{
	ifstream inputFile(argv[1]); 
	if(!inputFile){
		cout << "Error: Unable to open input file" << endl; 
	}

	int V; 
	inputFile >> V;
	int Graph[V][V]; 
	//initialising the graph matrix
	for(int i = 0; i < V; i++){
		for(int j = 0; j < V; j++){
			Graph[i][j] = INT_MAX;
		}
	}
	int a, b, c, E = 0; 
	//populating the graph matrix
	while(inputFile >> a >> b >> c){
		Graph[a][b] = c;
		E++;

	}

	struct Graph* graph = createGraph(V, E);
	inputFile.clear();
	inputFile.seekg(0, inputFile.beg);
	int temp;
	inputFile >> temp; 
	int counter = 0;
	//making a list of edges in the graph struct
	while(inputFile >> a >> b >> c){
		graph->edge[counter].src = a;
		graph->edge[counter].dest = b;
		graph->edge[counter].weight = c;
	}
	inputFile.close();
	int dist[V];
	int src = 0;
	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX;
	dist[src] = 0;

	//relax all edges |V| - 1 times. A simple shortest path from src to any other vertex can have at-most |V| - 1 edges
	for (int i = 1; i <= V - 1; i++) {
		for (int j = 0; j < E; j++) {
			int u = graph->edge[j].src;
			int v = graph->edge[j].dest;
			int weight = graph->edge[j].weight;
			if (dist[u] != INT_MAX
				&& dist[u] + weight < dist[v])
				dist[v] = dist[u] + weight;
		}
	}

	//check for negative-weight cycles
	for (int i = 0; i < E; i++) {
		int u = graph->edge[i].src;
		int v = graph->edge[i].dest;
		int weight = graph->edge[i].weight;
		if (dist[u] != INT_MAX
			&& dist[u] + weight < dist[v]) {
			printf("Graph contains negative weight cycle");
			return 1; //return if negative cycle is detected
		}
	}

	ofstream outputFile(argv[2]);
	if(!outputFile){
		cout << "Error: Unable to open the output file" << endl;
	}
	outputFile << "Vertex Distance from Source\n" << endl;
	for (int i = 0; i < V; ++i){
		//printf("%d \t\t %d\n", i, dist[i]);
        outputFile << i << " \t\t " << dist[i] << endl;
    }
	outputFile.close();
	
	return 0;
}
