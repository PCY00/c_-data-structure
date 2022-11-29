#include <iostream>
#include <vector>

using namespace std;

int n, m;
int s, e;
vector<vector<int>> adjArray;
vector<int> visited;

void AddEdge(int start, int end);
void printGraph();
void aDFS(int v);
void DFS();

int main() {
	cin >> n >> m;
	adjArray.resize(n + 1);
	visited.resize(n + 1);
	
	for (int i = 0; i < m; i++) {
		cin >> s >> e;
		AddEdge(s, e);
	}

	printGraph();
	DFS();
}

void AddEdge(int start, int end) {
	adjArray[start].push_back(end);
	adjArray[end].push_back(start);
}

void printGraph() {
	for (int i = 1; i <= n; i++) {
		cout << i << ": ";
		for (int j = 0; j < adjArray[i].size(); j++) {
			cout << adjArray[i][j] << " ";
		}
		cout << '\n';
	}
}

void aDFS(int v) {
	visited[v] = 1;
	printf("%d ", v);
	for (int i = 0; i < adjArray[v].size(); i++) {
		int x = adjArray[v][i];
		if (visited[x] == 0) {
			aDFS(x);
		}
	}
}

void DFS() {
	for (int v = 1; v <= n; v++) {
		visited[v] = 0;
	}
	for (int v = 1; v <= n; v++) {
		if (visited[v] == 0) {
			aDFS(v);
		}
	}
}