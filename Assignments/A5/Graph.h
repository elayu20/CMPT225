#pragma once

#include <ostream>
#include <iostream>
#include <climits> //INT_MAX
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>

using std::cout;
using std::endl;
using std::ostream;
using std::string;
using std::vector;
using std::list;
using std::queue;
using std::stack;
using std::unordered_map;
using std::unordered_set;

const int INT_INFINITY = INT_MAX;

// Edge structure to represent an edge in the graph
struct Edge
{
	int weight;
	int fromKey;
	int toKey;

	// Constructors
	Edge() : fromKey(0), toKey(0), weight(0) { ; }
	Edge(int fk, int tk, int w) : fromKey(fk), toKey(tk), weight(w) { ; }

	
	// Overloaded comparison operators for Edge
	// This is kind of ugly but will allow us to use STL data structures
	bool operator==(const  Edge& e) const { return fromKey == e.fromKey && toKey == e.toKey; }
	bool operator<(const  Edge& e) const { return weight < e.weight; }
};

// Records to store path information for Dijkstra's algorithm
struct PathRecord
{
	int vKey;  // vertex key
	int cost;
	int parentKey;
	
	// Constructors
	PathRecord() : vKey(-1), cost(INT_INFINITY), parentKey(-1) { ; }
	PathRecord(int v, int c, int pk) : vKey(v), cost(c), parentKey(pk) { ; }
};

// For priority queue ordering of PathRecords (min-heap based on cost)
struct PathRecordComparator
{
	int operator() (const PathRecord & pr1, const PathRecord & pr2)
	{
		return pr1.cost > pr2.cost;
	}
};

// Struct to store results for Dijkstra's algorithm
struct SPResultRecord
{
	int cost;
	int parentKey;

	// Constructors
	SPResultRecord() : cost(INT_INFINITY), parentKey(-1) { ; }
	SPResultRecord(int c, int pk) : cost(c), parentKey(pk) { ; }
};

class Graph
{
public:
	// DO NOT MODIFY THE PUBLIC INTERFACE (METHODS) IN ANY WAY

	// Constructors-----------------------------------------------------
	//PRE:
	//POST: creates an empty graph
	Graph();

	//PRE: fname is the name of a file in the correct format
	//POST: creates a graph based on data from the file fname
	Graph(string fname);

	// Vertex and Edge insertion/removal methods------------------------

	//PRE: v.key is unique, not already in the graph
	//PARAM: v - the vertex to be inserted
	//POST: v is added to the graph
	void insertVertex(int key, string name);

	//PRE: v1.key and v2.key are in the graph
	//PARAM: v1 - key of the starting vertex
	//       v2 - key of the ending vertex
	//       cost - the weight of the edge to be inserted
	//POST: an edge from v1 to v2 with weight cost is added to the graph
	void insertEdge(int v1, int v2, int cost);

	//PRE: 
	//POST: loads a test graph for BFS and DFS into the graph object
	void loadBFSTestGraph();

	//PRE: 
	//POST: loads a test graph for shortest path and MST into the graph object
	void loadMSTTestGraph();

	//PRE: v1.key and v2.key are in the graph
	//PARAM: v1 - key of the starting vertex
	//       v2 - key of the ending vertex
	//       the edge from v1 to v2 is removed from the graph
	void removeEdge(int v1, int v2);

	//PRE: v.key is in the graph
	//PARAM: v - key of the vertex to be removed
	//POST: the vertex v and all edges to/from v are removed from the graph
	void removeVertex(int v);
	
	// Vertex and Edge Query Methods-----------------------------------

	//PRE:
	//POST: returns the number of vertices in the graph
	int getNumVertices() const;

	//PRE:
	//POST: returns the number of edges in the graph
	int getNumEdges() const;

	//PRE:
	//POST: returns true if the graph is empty, false otherwise
	bool empty() const;

	//PRE:
	//PARAM: key - the key of the vertex to be checked
	//POST: returns true if the vertex with key is in the graph, false otherwise
	bool hasVertex(int key) const;

	//PRE: v1 and v2 are in the graph
	//PARAM: v1 - key of the starting vertex
	//       v2 - key of the ending vertex
	//POST: returns true if there is an edge from v1 to v2, false otherwise
	bool hasEdge(int v1, int v2) const;

	//PRE: v is in the graph
	//PARAM: v - key of vertex to find neighbours of
	//POST: returns true if there is an edge from v1 to v2, false otherwise
	list<Edge> getNeigbours(int v) const;

	//PRE:
	//POST: prints the graph to standard output
	void print() const;

	// **IMPLEMENT THESE METHODS IN THE .cpp FILE**
	// Graph Algorithms------------------------------------------------

	//PRE: startKey is in the graph
	//PARAM: startKey - the key of the start vertex for BFS
	//POST: performs a breadth-first search from startKey, returns a queue
	//      containing the keys of the vertices in the order they were visited	
	queue<int> bfs(int startKey) const;

	//PRE: startKey is in the graph
	//PARAM: startKey - the key of the start vertex for DFS
	//POST: performs a depth-first search from startKey, returns a queue
	//      containing the keys of the vertices in the order they were visited	
	queue<int> dfs(int startKey) const;

	//PRE: startKey and endKey are in the graph
	//PARAM: startKey - the key of the start vertex for Dijkstra's algorithm
	//       endKey - the key of the end vertex for Dijkstra's algorithm
	//POST: calls  dijkstra to generate shortest paths from startKey to
	//      endKey, returns a queue containing the keys of the vertices in the
	//      order they appear in the shortest path from startKey to endKey	
	stack<int> getShortestPath(int startKey, int endKey, int & cost) const;

	//PRE:
	//POST: generates the minimum spanning tree of the graph using Krsukal's
	//      algorithm, returns a queue containing the edges in the MST
	queue<Edge> mst() const;

	// Graph Algorithm Print Methods For Testing-----------------------

	//PRE: startKey is in the graph
	//PARAM: startKey - the key of the start vertex for BFS
	//POST: prints bfs from start
	void printBFS(int startKey) const;

	//PRE: startKey is in the graph
	//PARAM: startKey - the key of the start vertex for DFS
	//POST: prints dfs from start
	void printDFS(int startKey) const;

	//PRE: startKey and endKey are in the graph
	//PARAM: startKey - the key of the start vertex for Dijkstra's algorithm
	//       endKey - the key of the end vertex for Dijkstra's algorithm
	//POST:  prints shortest path from start to end
	void printShortestPath(int startKey, int endKey) const;

	//PRE:
	//POST: prints minimum spanning tree
	void printMST() const;

private:
	// DO NOT MODIFY THE EXISTING METHODS OR ATTRIBUTES

	int numEdges;
	int numVertices;

	// The vertex with key k is stored at vertices[k]
	unordered_map<int, string> vertices;

	// The edges *from* vertex with (int) key k are stored in edges[k]
	unordered_map<int, list<Edge>> edges;

	// **COMPLETE THIS SECTION IN THE .cpp FILE**
	// Graph Algorithm Helper Methods----------------------------------

	// Helper method for getShortestPath
	//PRE: startKey is in the graph
	//PARAM: startKey - the key of the start vertex for Dijkstra's algorithm
	//POST: generates the shortest path from the start vertex to all other 
	//      connected vertices in the graph using Dijkstra's algorithm, returns
	//      an unordered_map where the key is the vertex key and the value is
	//      a pathNode structure containing the cost to that node and its parent
	unordered_map<int, SPResultRecord> dijkstra(int startKey) const;

	// YOU MAY ADD YOUR OWN PRIVATE METHODS HERE
};

