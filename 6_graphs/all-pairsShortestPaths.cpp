/*All-pairs shortest paths
* 목표: u!=v인 모든 정점 쌍 (u,v)에 대해 최단 경로 길이를 한 번에 구하고 싶다.
* 이전까지 했던 것
* Dijkstra/Bellman-Ford: 한 시작점 v에서 다른 모든 정점까지
* 바뀐 것: 시작점, 도착점을 고정하지 않고 모든 i,j쌍
* 그래프는 인접 행렬 length[i][j]로 표현되어 있고 length[i][j]는 i->j 간선의 길이
* 
* A^k[i][j]: 중간에 지나는 정점들의 번호가 k보다 크지 않도록 제한했을 때 i에서 j까지 갈 수 있는 최단 경로 길이
* A^0[i][j]: i에서 j로 가는 직접 간선의 길이 length[i][j] (간선이 없으면 무한대)
* 
* 최단 경로 설정
* 경로가 정점 k를 지나지 않는 경우: A^(k-1)[i][j]
* 경로가 정점 k를 지나는 경우: A^(k-1)[i][k] + A^(k-1)[k][j]
* 따라서 점화식: A^k[i][j] = min{ A^(k-1)[i][j], A^(k-1)[i][k] + A^(k-1)[k][j] }
*/

void MatrixWDigraph::AllLengths(const int n)
{
    // length[i][j] : 인접 행렬 (직접 가는 간선 비용, 없으면 INF)
    // a[i][j]      : i와 j 사이의 최단 경로 길이를 저장하는 작업용 행렬

    // 1단계: A^-1 = length 를 a에 복사
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = length[i][j];

    // 2단계: k를 0..n-1까지 증가시키면서
    //        A^k를 만들어 감 (결국 A^{n-1}이 됨)
    for (int k = 0; k < n; k++) {        // 새로 허용하는 중간 정점 k
        for (int i = 0; i < n; i++) {    // 모든 출발 정점 i
            for (int j = 0; j < n; j++) { // 모든 도착 정점 j

                // 점화식: a[i][j] = min( a[i][j], a[i][k] + a[k][j] );
                if (a[i][k] + a[k][j] < a[i][j])
                    a[i][j] = a[i][k] + a[k][j];
            }
        }
    }

    // 이제 a[i][j] = A^{n-1}[i][j] = i에서 j까지의 최단 경로 길이
}