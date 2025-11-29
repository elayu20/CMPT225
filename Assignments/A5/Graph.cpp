#include <algorithm>
#include <stdexcept>
#include "Graph.h"

using std::find;
using std::sort;
using std::invalid_argument;
using std::priority_queue;

// **COMPLETE THIS SECTION**
// Graph Algorithms------------------------------------------------

	//PRE: startKey is in the graph
	//PARAM: startKey - the key of the start vertex for BFS
	//POST: performs a breadth-first search from startKey, returns a queue
	//      containing the keys of the vertices in the order they were visited	
queue<int> Graph::bfs(int startKey) const
{
	queue<int> toVisit;
	queue<int> result; // Return this
	unordered_map<int, bool> visited;

	// Mark start visited and enqueue it
	visited[startKey] = true;
	toVisit.push(startKey);

	while(!toVisit.empty()) {
		int p = toVisit.front();
		toVisit.pop();

		result.push(p);

		// For each edge, e, adjacent to p
		for (Edge &e : getNeigbours(p)) {
			// Gets the key value in edge
			int neighbour = e.toKey;

			// if not visited, mark it as visited and enqueue
			if (!visited[neighbour]) {
				visited[neighbour] = true;
				toVisit.push(neighbour);
			}
		}
	}

	return result;
}

//PRE: startKey is in the graph
//PARAM: startKey - the key of the start vertex for DFS
//POST: performs a depth-first search from startKey, returns a queue
//      containing the keys of the vertices in the order they were visited	
queue<int> Graph::dfs(int startKey) const
{
	stack<int> toVisit;
	queue<int> result;
	unordered_map<int, bool> visited;

	// Mark start visited and push to stack
	visited[startKey] = true;
	toVisit.push(startKey);

	while (!toVisit.empty()) {
		int p = toVisit.top();
		toVisit.pop();

		result.push(p);

		for (Edge &e : getNeigbours(p)) {
			int neighbour = e.toKey;

			if (!visited[neighbour]) {
				visited[neighbour] = true;
				toVisit.push(neighbour);
			}
		}
	}

	return result;
}

//PRE: startKey and endKey are in the graph
//PARAM: startKey - the key of the start vertex for Dijkstra's algorithm
//       endKey - the key of the end vertex for Dijkstra's algorithm
//POST: calls  dijkstra to generate shortest paths from startKey to
//      endKey, returns a stack containing the keys of the vertices in the
//      order they appear in the shortest path from startKey to endKey	
stack<int> Graph::getShortestPath(int startKey, int endKey, int& cost) const
{
	// To Do: Complete this method
	stack<int> path; // Return this
	
	unordered_map<int, SPResultRecord> results = dijkstra(startKey);

	// Check if endKey is NOT in results map
	// Set cost to infinity because can't reach, and return the empty stack
	if (results.count(endKey) == 0) {
		cost = INT_MAX;
		return path;
	}

	// Endkey in map
	cost = results.at(endKey).cost;

	// Backtrack from endKey to startKey from parents
	int current = endKey;
	while (current != -1) { // startKey parent is -1
		path.push(current);
		current = results.at(current).parentKey;
	}

	return path;
}

// Helper method for getShortestPath
	//PRE: startKey is in the graph
	//PARAM: startKey - the key of the start vertex for Dijkstra's algorithm
	//POST: generates the shortest path from the start vertex to all other 
	//      connected vertices in the graph using Dijkstra's algorithm, returns
	//      an unordered_map where the key is the vertex key and the value is
	//      a pathNode structure containing the cost to that node and its parent
unordered_map<int, SPResultRecord> Graph::dijkstra(int startKey) const
{
	// To Do: Complete this method
	
	// Set up containers
	unordered_map<int, int> bestCost;
	unordered_map<int, SPResultRecord> results; // return this
	priority_queue<PathRecord, vector<PathRecord>, PathRecordComparator> toVisit;

	// Initialize all vertices in bestCost to infinity
	for (auto &entry: vertices) {
		int v = entry.first;
		bestCost[v] = INT_MAX;
	}
	bestCost[startKey] = 0;

	// Push start record into priority queue
	toVisit.push(PathRecord(startKey, bestCost[startKey], -1));

	// Main loop
	while (!toVisit.empty()) {
		PathRecord current = toVisit.top();
		toVisit.pop();

		// If already recorded current path's shortest path, then skip it
		// OR if best cost is still better than current, then skip
		if (results.count(current.vKey) > 0 || current.cost > bestCost[current.vKey]) {
			continue;
		}
		// We know the current path has the lowest cost but not in results yet
		results[current.vKey] = SPResultRecord(current.cost, current.parentKey);

		// For each edge, e, adjacent to current vertex
		// Want to update costs of the neighbours
		for (Edge &e : getNeigbours(current.vKey)) {
			int neighbour = e.toKey;
			int weight = e.weight;
			int newCost = current.cost + weight;

			// If this path is better, update bestCost and push into priority queue
			if (newCost < bestCost[neighbour]) {
				bestCost[neighbour] = newCost;
				toVisit.push(PathRecord(neighbour, newCost, current.vKey));
			}
		}
	}
	
	return results;
}

// Helper method for sort
bool compareWeight(Edge a, Edge b) {
	return a.weight < b.weight;
}
//PRE:
//POST: generates the minimum spanning tree of the graph using Krsukal's
//      algorithm, returns a queue containing the edges in the MST
queue<Edge> Graph::mst() const
{
	// To Do: Complete this method
	
	// Pick edges one by one, from smallest weight up to largest weight
	// Each time, only add edge if it does not create a cycle
	// Check for cycle if two vertices are already in the same set
	// If safe, add the edge and merge the sets
	// Stop when we have V-1 edges in the MST

	queue<Edge> results;
	unordered_map<int, unordered_set<int>> groups; // setNum-> {all vertices in set}
	unordered_map<int, int> belongsTo; // a single vertex->setNum it belongs to
	
	// Copy edges into a vector to sort them
	vector<Edge> edgeList;
	// entry.second is a list of edge structs
	for (auto &entry : edges) {
		for (Edge e : entry.second) {
			edgeList.push_back(e);
		}
	}

	// Using the rule:
	// True if a.weight is less than b.weight, which sorts to increasing order
	sort(edgeList.begin(), edgeList.end(), compareWeight);

	// Initialize disjoint set so each vertex is its own set
	for (auto &entry : vertices) {
		// entry.first is the (int) key k
		int vertex = entry.first;

		// Create a set that contains itself for now
		unordered_set<int> newSet;
		newSet.insert(vertex);

		groups[vertex] = newSet;
		belongsTo[vertex] = vertex;
	}

	int edgesTaken = 0;
	int totalVertices = getNumVertices();
	int targetEdges = totalVertices - 1;

	// Loop through sorted list, union sets if it does not create a cycle
	for (Edge e : edgeList) {
		int u = e.fromKey;
		int v = e.toKey;

		// Cycle check, if they are in same set, skip
		if (belongsTo[u] == belongsTo[v]) {
			continue;
		}

		// Reached a safe edge 
		results.push(e);
		edgesTaken++;

		// Merge all vertices in v's set into u's set
		int setU = belongsTo[u];
		int setV = belongsTo[v];

		// Copy second set before we merge it
		unordered_set<int> secondSet = groups.at(setV);

		// Move everything from setV to setU
		for (int x : secondSet) {
			groups.at(setU).insert(x);
			belongsTo[x] = setU;
		}

		// Remove the old set since it's merged now
		groups.erase(setV);

		// Stop if MST is complete (we have V-1 edges
		if (edgesTaken == targetEdges) {
			break;
		}
	}

	return results;
}

// **END SECTION TO BE COMPLETED**---------------------------------
// 
// Constructors
Graph::Graph()
{
	numVertices = 0;
	numEdges = 0;
}

Graph::Graph(string fname)
{
	numVertices = 0;
	numEdges = 0;
	// NOT IMPLEMENTED
}

// Vertex and Edge insertion/removal methods-----------------------
void Graph::insertVertex(int key, string name)
{
	vertices.insert({ key, name });
	numVertices++;
}

void Graph::insertEdge(int v1, int v2, int cost)
{
	if(v1 == v2) {
		throw invalid_argument("error: self edge");
	}
	if (!hasVertex(v1) || !hasVertex(v2)) {
		throw invalid_argument("error: from / to vertex does not exist");
	}
	if(hasEdge(v1, v2)) {
		throw invalid_argument("error: edge already in graph");
	}

	edges[v1].push_back(Edge(v1, v2, cost));
	edges[v2].push_back(Edge(v2, v1, cost));
	numEdges++;
}

void Graph::loadBFSTestGraph()
{
	for(int i = 0; i < 12; i++) {
		insertVertex(i, "v" + std::to_string(i));
	}
	insertEdge(0, 1, 1);
	insertEdge(1, 2, 1);
	insertEdge(2, 3, 1);
	insertEdge(0, 5, 1);
	insertEdge(4, 5, 1);
	insertEdge(4, 7, 1);
	insertEdge(5, 6, 1);
	insertEdge(5, 7, 1);
	insertEdge(6, 9, 1);
	insertEdge(7, 8, 1);
	insertEdge(7, 10, 1);
	insertEdge(8, 10, 1);
	insertEdge(8, 9, 1);
	insertEdge(9, 11, 1);
}

void Graph::loadMSTTestGraph()
{
	for (int i = 0; i < 9; i++) {
		insertVertex(i, "v" + std::to_string(i));
	}
	insertEdge(0, 1, 8);
	insertEdge(0, 2, 4);
	insertEdge(1, 2, 10);
	insertEdge(1, 3, 1);
	insertEdge(1, 4, 9);
	insertEdge(2, 4, 19);
	insertEdge(2, 5, 12);
	insertEdge(3, 4, 6);
	insertEdge(3, 6, 3);
	insertEdge(4, 5, 2);
	insertEdge(5, 6, 5);
	insertEdge(5, 7, 7);
	insertEdge(6, 7, 14);
	insertEdge(6, 8, 11);
	insertEdge(7, 8, 13);
}

void Graph::removeEdge(int v1, int v2)
{
	// NOT IMPLEMENTED
}

void Graph::removeVertex(int v)
{
	// NOT IMPLEMENTED
}

// Vertex and Edge Query Methods-----------------------------------
int Graph::getNumVertices() const
{
	return numVertices;
}

int Graph::getNumEdges() const
{
	return numEdges;
}

bool Graph::empty() const
{
	return numVertices == 0;
}

bool Graph::hasVertex(int key) const
{
	return(vertices.find(key) != vertices.end());
}

bool Graph::hasEdge(int v1, int v2) const
{
	Edge target(v1, v2, 0);
	if (edges.find(v1) != edges.end() &&
		find(edges.at(v1).begin(), edges.at(v1).end(), target) != edges.at(v1).end()) {
		
		return true;
	}
	return false;
}

list<Edge> Graph::getNeigbours(int v) const
{
	return edges.at(v);
}

void Graph::print() const
{
	for (auto & ls : edges) {
		cout << ls.first << " (" <<  vertices.at(ls.first) << "): ";
		for (const Edge & e : ls.second) {
			cout << "{" << e.toKey << ' ' << e.weight << "} ";
		}
		cout << endl;
	}
}

// Graph Algorithm Print Methods For Testing-----------------------

//PRE: startKey is in the graph
//PARAM: startKey - the key of the start vertex for BFS
//POST: prints bfs from start
void Graph::printBFS(int startKey) const
{
	queue<int> q = bfs(startKey);

	cout << "BFS: ";
	while(!q.empty()) {
		cout << q.front() << " ";
		q.pop();
	}
}

//PRE: startKey is in the graph
//PARAM: startKey - the key of the start vertex for DFS
//POST: prints dfs from start
void Graph::printDFS(int startKey) const
{
	queue<int> q = dfs(startKey);

	cout << "DFS: ";
	while (!q.empty()) {
		cout << q.front() << " ";
		q.pop();
	}
}

//PRE: startKey and endKey are in the graph
//PARAM: startKey - the key of the start vertex for Dijkstra's algorithm
//       endKey - the key of the end vertex for Dijkstra's algorithm
//POST:  prints shortest path from start to end
void Graph::printShortestPath(int startKey, int endKey) const
{
	int totalCost;
	stack<int> sPaths = getShortestPath(startKey, endKey, totalCost);

	while(!sPaths.empty()) {
		cout << sPaths.top() << " ";
		sPaths.pop();
	}
	cout << endl << "Total Cost = " << totalCost << endl;
}

//PRE:
//POST: prints minimum spanning treein edge weight ascending order
void Graph::printMST() const
{
	queue<Edge> mstEdges = mst();

	while (!mstEdges.empty()) {
		cout << "from " << mstEdges.front().fromKey;
		cout << " to " << mstEdges.front().toKey;
		cout << ", weight = " << mstEdges.front().weight << endl;
		mstEdges.pop();
	}
}
