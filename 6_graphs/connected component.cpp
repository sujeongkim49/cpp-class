/* 연결요소(connected component)
* 방문하지 않은 정점 v에 대해 DFS(v) 또는 BFS(v)를 반복 호출로 구함
*/

virtual void Graph::Components() {
    visited = new bool[n];
    fill(visited, visited + n, false);
    for (i = 0; i < n; i++) {
        if (!visited[i]) {
            DFS(i);
            OutputNewComponent();
        }
    }
    delete[] visited;
}

/*연결 요소 분석
* 인접리스트로 표현: O(n + e)
* 인접행렬로 표현: O(n^2)
*/