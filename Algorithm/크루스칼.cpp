#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef struct {
	int start;
	int end;
	int weight;
} Edge;

bool operator>(Edge a, Edge b) {
	return (a.weight > b.weight);
}

priority_queue<Edge, vector<Edge>, greater<Edge>> minHeap;

int n, m;
int s, e, w;
vector<int> p;
vector<int> ranks;
vector<Edge> result;

void Make_Set(int x) {
	p[x] = x;
	ranks[x] = 0;
}

int Find_Set(int x) {
	if (p[x] != x) {
		p[x] = Find_Set(p[x]);
	}

	return p[x];
}

void Union(int x, int y) {
	int x1 = Find_Set(x);
	int y1 = Find_Set(y);
	
	if (ranks[x1] > ranks[y1]) {
		p[y1] = x1;
	}
	else {
		p[x1] = y1;
		if (ranks[x1] == ranks[y1]) {
			ranks[y1] = ranks[y1] + 1;
		}
	}
}

void Kruskal() {
	for (int i = 0; i <= n; i++) {
		Make_Set(i);
	}

	while (result.size() < n - 1) {
		int start = minHeap.top().start;
		int end = minHeap.top().end;

		if (Find_Set(start) != Find_Set(end)) {
			Union(start, end);
			result.push_back(minHeap.top());
		}
		minHeap.pop();
	}
}

int main() {
	cin >> n >> m;
	p.resize(n + 1);
	ranks.resize(n + 1);

	Edge edge;
	for (int i = 0; i < m; i++) {
		cin >> s >> e >> w;
		edge.start = s;
		edge.end = e;
		edge.weight = w;
		minHeap.push(edge);
	}

	Kruskal();

	int cost = 0;
	for (int i = 0; i < result.size(); i++) {
		cout << result[i].start << "," << result[i].end << "(" << result[i].weight << ")" << '\n';
		cost += result[i].weight;
	}
	cout << "Total Cost: " << cost;
}