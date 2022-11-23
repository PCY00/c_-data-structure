#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, m;
int s, e;
vector<vector<int>> adjArray;
vector<int> visited;

void AddEdge(int start, int end);
void printGraph();
void BFS(int start);


int main() {
	cin >> n >> m;
	adjArray.resize(n + 1);
	visited.resize(n + 1);
	
	for (int i = 0; i < m; i++) {
		cin >> s >> e;
		AddEdge(s, e);
	}

	printGraph();
	BFS(1);
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

void BFS(int start) {
	queue<int> bfs;
	visited[start] = 1;
	cout << start << " ";
	bfs.push(start);

	while (!bfs.empty()) {
		int save = bfs.front();
		bfs.pop();
		for (int i = 0; i < adjArray[save].size(); i++) {
			if (visited[adjArray[save][i]] == 0) {
				visited[adjArray[save][i]] = 1;
				cout << adjArray[save][i] << " ";
				bfs.push(adjArray[save][i]);
			}
		}
	}
}

