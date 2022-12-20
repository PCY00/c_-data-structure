#pragma warning(disable:4996)
#include <iostream>
#include <vector>

using namespace std;

const int INSTALLED = 2;		//설치됨
const int DEFENDED = 1;			//설치되지 않았지만, 하위 노드중 1개에 설치되어 있어 방어됨
const int NOT_DEFENDED = 0;		//방어되지않음

int save = 0;
int n, m;						// n = 정점의 개수, m = 간선의 개수
int s, e;						// s = 시작 정점, e = 끝 정점
vector<vector<int>> adjArray;
vector<int> visited;

int numTuret = 0;

void AddEdge(int start, int end);
int aDFS(int v);
void DFS();

int main()
{
	//freopen("input.txt", "r", stdin);
	int T;
	cin >> T;

	for (int i = 0; i < T; i++) {
		numTuret = 0;
		adjArray.clear();
		visited.clear();

		cin >> n >> m;

		adjArray.resize(n + 1);
		visited.resize(n + 1);

		for (int j = 0; j < m; j++) {
			cin >> s >> e;
			AddEdge(s, e);
		}
		DFS();
		printf("%d\n", numTuret);
	}
}

void AddEdge(int start, int end) {
	adjArray[start].push_back(end);
	adjArray[end].push_back(start);
}

int aDFS(int v) {
	visited[v] = 1;
	for (int i = 0; i < adjArray[v].size(); i++) {
		int x = adjArray[v][i];
		if (visited[x] == 0) {
			save = aDFS(x);
		}
	}
	for (int i = 0; i < adjArray[v].size(); i++) {
		int x = adjArray[v][i];
		if ((visited[v] == 1 && visited[x] == 1) || (visited[v] == 1 && visited[x] == 3) || (visited[v] == 3 && visited[x] == 1)){
			numTuret++;
			visited[v] = 3;
			visited[x] = 2;
			return INSTALLED;
		}else if ((visited[v] == 1 && visited[x] == 2) || (visited[v] == 2 && visited[x] == 1)) {
			visited[v] = 3;
			return DEFENDED;
		}
		else if (visited[v] == 3 && visited[x] == 3) {
			return NOT_DEFENDED;
		}
	}
}
// visited 2 설치 3 보호 1 설치 안됨

void DFS() {
	for (int v = 1; v <= n; v++) {
		visited[v] = 0;
	}
	for (int v = 1; v <= n; v++) {
		int cnt = 0;
		for (int i = 1; i <= n; i++) {
			if (visited[i] == 1 || visited[i] == 2 || visited[i] == 3) {
				cnt++;
			}
		}
		if (cnt == n) return;
		save = aDFS(v);
		if (save == NOT_DEFENDED) {
			numTuret++;
		}
	}
}

