#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

class Articulation {
private:
	vector<int> depth, low, parent;
	vector<vector<int>> g;
	int n;

	void dfs(int cur, int d) {
		low[cur] = depth[cur] = d;
		int children = 0;
		bool isArticulation = false;

		for (int next: g[cur]) {
			if (depth[next] == -1) {
				parent[next] = cur;
				children++;
				dfs(next, d + 1);

				if (low[next] >= depth[cur]) {
					isArticulation = true;
					if (low[next] != depth[cur]) {
						bridges.emplace_back(min(cur, next), max(cur, next));
					}
				}

				low[cur] = min(low[cur], low[next]);
			} else if (next != parent[cur]) {
				low[cur] = min(low[cur], depth[next]);
			}
		}

		if ((parent[cur] != -1 && isArticulation) || (parent[cur] == -1 && children > 1)) {
			points.push_back(cur);
		}
	}

public:
	vector<int> points;
	vector<ii> bridges;

	Articulation(int numNode, vector<vector<int>>& adjList) : parent(numNode, -1), depth(numNode, -1), low(numNode, 0) {
		n = numNode;
		g = adjList;

		for (int i = 0; i < n; i++) {
			if (depth[i] == -1) {
				dfs(i, 0);
			}
		}
	}
};

int main() {
	vector<vector<int>> adj(10);
	adj[0].push_back(1);
	adj[1].push_back(0);
	adj[1].push_back(2);
	adj[2].push_back(1);
	adj[2].push_back(0);
	adj[0].push_back(2);
	adj[2].push_back(3);
	adj[3].push_back(2);
	adj[3].push_back(4);
	adj[4].push_back(3);
	adj[4].push_back(5);
	adj[5].push_back(4);
	adj[5].push_back(3);
	adj[3].push_back(5);

	Articulation articulation(6, adj);
	for (int point: articulation.points) {
		cout << point << '\n';
	}

	for (ii bridge: articulation.bridges) {
		cout << bridge.first << ' ' << bridge.second << '\n';
	}
}