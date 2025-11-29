#include "Graph.h"

int main1() {
	Graph g;

	// Load the built-in test graph for BFS
	g.loadBFSTestGraph();

	// ----- Test BFS -----
	queue<int> bfsOrder = g.bfs(5);
	cout << "[TEST] BFS Output: ";
	while (!bfsOrder.empty()) {
		cout << bfsOrder.front() << " ";
		bfsOrder.pop();
	}
	cout << endl;

	// ---- Test DFS ----
    	queue<int> dfsOrder = g.dfs(5);
    	cout << "[TEST] DFS Output: ";
    	while (!dfsOrder.empty()) {
		cout << dfsOrder.front() << " ";
		dfsOrder.pop();
    	}
    	cout << endl;

	// ---- Test getShortestPath ----
	int cost = 0;
	stack<int> path = g.getShortestPath(5, 8, cost);

	cout << "Shortest path from 5 to 8: ";
	while (!path.empty()) {
		cout << path.top() << " ";
		path.pop();
	}
	cout << "\nTotal cost = " << cost << endl;

	// ---- Test MST ----
	g.print();

    	return 0;
}

int main() {
	Graph g;
	g.loadMSTTestGraph();
	g.print();
	
	// ---- Test MST ----
	queue<Edge> mst = g.mst();

	cout << "[TEST] Mst edges selected:\n";
	while (!mst.empty()) {
		Edge e = mst.front();
		mst.pop();
		cout << " " << e.fromKey << " -> " << e.toKey << " (weight=" << e.weight << ")\n";
	}
	return 0;
}
