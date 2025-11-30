/*너비 우선 탐색(BFS; Breadth-First Search)
* (1) 시작 정점 v를 방문
* (2) v에 인접한 모든 정점들을 방문
* (3) 새롭게 방문한 정점들에 인접하면서 아직 방문하지 못한 정점들을 방문
*/

virtual void Graph::BFS(int v) {
    visited = new bool[n];
    fill(visited, visited + n, false);
    visited[v] = true;
    queue<int> q;
    q.push(v);
    while (!q.IsEmpty()) { //큐가 빌 때까지 반복
        v = q.front(); //큐의 맨 앞 정점을 꺼내서 현재 정점 v로 사용
        q.pop();
        for (v에 인접한 모든 정점 w에 대해) { //실제 코드는 반복자 사용
            if (!visited[w]) { //w를 아직 방문하지 않았다면
                q.push(w); //큐에 w 추가
                visited[w] = true; //w 방문 체크
            }
        }
    }
    delete[] visited;
}

/*BFS 분석
* Adjacency matrix 표현: O(n^2)
* 인접 리스트 표현: O(e)
*/

class Graph {
private:
    int n;
    bool* visited;
    vector<vector<int>> adj;

public:
    Graph(int n) : n(n) {
        adj.resize(n);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void BFS(int start) {
        visited = new bool[n];
        fill(visited, visited + n, false);

        queue<int> q;
        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int w : adj[v]) {
                if (!visited[w]) {
                    visited[w] = true;
                    q.push(w);
                }
            }
        }
        delete[] visited;
    }
};