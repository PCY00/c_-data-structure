#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define INF INT_MAX

typedef struct {
	int vertex;
	int weight;
} Node;

bool operator>(Node a, Node b) {
	return (a.weight > b.weight);
}

priority_queue<Node, vector<Node>, greater<Node>> minHeap;

int n, m;
int s, e, w;
vector<vector<Node>> adjArray;
vector<bool> selected;
vector<int> d;
vector<int> pre;

void Prim(int s) {
	int numSelectedNode = 0;
	Node node;
	d[s] = 0;
	node.vertex = s;
	node.weight = 0;
	minHeap.push(node);

	while (numSelectedNode < n) {
		int u = minHeap.top().vertex;
		minHeap.pop();

		if (selected[u] == true) {
			continue;
		}
		selected[u] = true;
		numSelectedNode++;
		cout << u << "," << pre[u] << "(" << d[u] << ")" << '\n';

		for (int j = 0; j < adjArray[u].size(); j++) {
			int v = adjArray[u][j].vertex;
			int w = adjArray[u][j].weight;
			if (selected[v] == false && w < d[v]) {
				d[v] = w;
				pre[v] = u;
				node.vertex = v;
				node.weight = w;
				minHeap.push(node);
			}
		}
	}
}

int main() {
	cin >> n >> m;
	adjArray.resize(n + 1);
	selected.resize(n + 1, false);
	d.resize(n + 1, INF);
	pre.resize(n + 1, -1);

	Node node;
	for (int i = 0; i < m; i++) {
		cin >> s >> e >> w;
		node.vertex = e;
		node.weight = w;
		adjArray[s].push_back(node);

		node.vertex = s;
		node.weight = w;
		adjArray[e].push_back(node);
	}
	Prim(1);
	int cost = 0;
	for (int i = 1; i <= n; i++) {
		cost += d[i];
	}
	cout << "Total Cost: " << cost;
}