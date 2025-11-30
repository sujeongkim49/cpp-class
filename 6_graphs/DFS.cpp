/*깊이-우선 탐색(DFS; Depth-First Search)
* (1) 출발 정점 v를 방문
* (2) v에 인접하고 방문하지 않은 한 정점 w를 선택
* (3) w를 시작점으로 다시 DFS 수행
* (4) 모든 인접 정점을 방문한 정점 u에 도달하면,
* 최근에 방문한 정점 중 아직 방문하지 않은 정점 w와 인접하고 있는 정점으로 되돌아감
* (5) 정점 w로부터 다시 깊이 우선 탐색 시작
* (6) 방문을 한 정점들로부터 방문하지 않은 정점으로 더 이상 갈 수 없을 때 종료
*/

virtual void::DFS()
//Driver > visited 배열을 동적 생성하여 모든 정점을 '미방문(false)'로 초기화
//시작 정점 0을 기준으로 DFS 탐색 시작
//모든 탐색이 끝난 후 visited 메모리 해제
{
    visited = new bool[n]; 
    fill(visited, visited + n, false); //fill 함수(algorithm 포함 함수): [visited, visited+n) 영역을 flase로 채움
    DFS(0);
    delete[] visited;
}
virtual void Graph::DFS(const int v) 
//Workhorse > 정점 v 방문 체크(visited[v] = true)
//v와 인접한 모든 정점 w에 대해 아직 방문하지 않았으면 (visited[w]==false) > 재귀적으로 DFS(w) 호출
//재귀 호출을 통한 구조
{
    visited[v] = true;
    for (each vertex w adjacent to v)
        if (!visited[w]) DFS(w);
}
/*DFS 분석
* Adjacency list 사용 경우: O(e)
* Adjacency matrix 사용 경우: O(n^2)
*/

class Graph {
private:
    int n;
    bool* visited;
    vector<vector<int>> adj;

public:
    //생성자: 정점 개수 n을 받아서 인접 리스트 크기 설정
    Graph(int n) : n(n) {
        adj.resize(n);
    }

    //간선 추가
    void addEdge(int u, int v) {
        adj[u].push_back(v);//u -> v
        adj[v].push_back(u);//무방향 그래프이므로 v -> u도 추가
    }

    //DFS Driver
    void DFS() {
        visited = new bool[n];
        fill(visited, visited + n, false);
        DFS(0);
        delete[] visited;
    }

    //DFS Workhorse
    void DFS(const int v) {
        visited[v] = true;
        
        for (int w : adj[v]) {
            if (!visited[w]) {
                DFS(w);
            }
        }
    }
};

/* ================================================================
   ★ 예시 그래프 ★
   정점: 0, 1, 2, 3, 4
   간선:
        (0 - 1)
        (0 - 2)
        (1 - 3)
        (2 - 4)

   즉 그래프 형태는 그림으로 보면:

              0
            /   \
           1     2
           |     |
           3     4

   ----------------------------------------------------------------
   ★ DFS 탐색 과정 (시작 정점 = 0)
   ----------------------------------------------------------------
   1) DFS(0) 호출
      - visited[0] = true
      - 인접: {1, 2}

   2) w = 1 → 방문 안 함 → DFS(1)
      - visited[1] = true
      - 인접: {0, 3}
      - 0은 이미 방문됨 → 패스
      - 3 방문 안 함 → DFS(3)

   3) DFS(3)
      - visited[3] = true
      - 인접: {1}
      - 1은 이미 방문됨 → 종료

   (3에서 더 갈 곳 없음 → 1로 되돌아감 → 0으로 되돌아감)

   4) 다시 DFS(0) 진행, 이번엔 w = 2
      - 방문 안 함 → DFS(2)
      - visited[2] = true
      - 인접: {0, 4}
      - 0은 이미 방문됨 → 패스
      - 4 방문 안 함 → DFS(4)

   5) DFS(4)
      - visited[4] = true
      - 인접: {2}
      - 2는 이미 방문됨 → 종료

   ----------------------------------------------------------------
   ★ 최종 DFS 방문 순서 (시작 정점 0 기준)
   ----------------------------------------------------------------
   0 → 1 → 3 → 2 → 4

   이 순서는 인접 리스트 adj[u]에 어떤 순서로 넣었는지에 따라 달라질 수 있음.
   위 예시는 adj를 push_back하는 순서대로 탐색한다고 가정한 결과임.
   ================================================================ */