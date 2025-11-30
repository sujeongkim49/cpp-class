/*단일 출발점/모든 종점: 음이 아닌 간선 비용
* 문제: 출발 정점 v에서부터 G의 모든 다른 정점까지의 최단경로를 구하는 것
*/


//n: 정점의 수
//v: 출발 정점
void MatrixWdigraph::ShortestPath(const int n, const int v)
{
    //dist[j], 0<=j<n은 n개의 정점을 가진 방향 그래프 G에서 정점 v에서 정점 j까지의
    //최단경로 길이로 설정됨. 간선의 길이는 lengh[i][j]로 주어짐
    
    //1. 초기화 단계
    for (int i = 0; i < n; i++) {
        s[i] = false; //아직 어떤 정점도 확정되지 않음
        dist[i] = length[v][i]; //v에서 바로 가는 간선 비용으로 초기화
        //직접 가는 간선이 없으면 무한대 값이 들어있음
    }

    s[v] = true; //출발 정점 v는 확정
    dist[v] = 0; //자기 자신(v-v)까지의 거리는 0

    //2. 나머지 정점들에 대해 반복(최대 n-1개의 정점 확정, 이 중 이미 v는 확정됨)
    for (i = 0; i < n - 2; i++) {
        
        //2-1. dist[] 중에서 가장 작은 값을 갖는 정점 u를 선택
        int u = Choose(n); //Dijkstra: "가장 가까운" 미확정 정점 선택
        
        //2-2. 정점 u를 확정 집합에 추가
        s[u] = true;
        
        //2-3. u에서 나가는 모든 간선을 이용해 인접 정점 w의 dist를 갱신
        for (int w = 0; w < n; w++) {
            //아직 확정되지 않은 정점 w에 대해서 검사
            //만약 v->u->w 경로가 기존 v->w 경로보다 짦으면 dist[w]
            if (!s[w] && dist[u] + length[u][w] < dist[w]) //dist[u]=지금까지 알고 있는 v->u의 최단 경로, length=정점 u에서 정점 w로 한 번에 가는 간선의 길이
                dist[w] = dist[u] + length[u][w];
        }
    }
}

/*단일 출발점/모든 종점: 일반적 가중치
* 음수 길이 사이클이 존재할 경우 최단 길이 경로가 존재하지 않는다
* 동적 프로그래밍 방법: 모든 u에 대해 dist^(n-1)[u]를 구함
* dist^(k)[u]: min{dist^(k-1)[u], min over all i {dist^(k-1)[i] + length[i][u]}}
*/

//Bellman-Ford 알고리즘
void MatrixWDigraph::BellmanFord(const int n, const int v)
{
    //1단계: 초기화
    //dist[i]를 '간선 1개만 사용해서 v에서 i로 가는 거리'로 세팅
    //직접 연결된 간선의 길이, 없으면 무한대
    for (int i = 0; i < n; i++)
        dist[i] = length[v][i];

    //2단계: 간선 수가 2,3,...,n개인 경로까지 확장해 가며 갱신
    //k: 사용할 수 있는 최대 간선 개수
    //dist[u]는 "간선 개수가 k이하인 v->u 최단 거리"로 갱신
    for(int k=2;k<=n;k++)

        //모든 정점 u에 대해 검사
        //u != v: 자기 자신으로 가는 경로는 고려하지 않음
        for (each u such that u!=v and u has at least one incoming edge)
            
            //u로 들어오는 모든 간선 (i,u)에 대해 검사
            for(each<i,u> in the graph)
                
                //i에서 u로 가는 간선을 사용해서 v->u 경로를 개선할 수 있는지 검사
                //dist[i]: 지금까지 알고 있는 v->i 최단 경로
                //length[i][u]: i에서 u로 가는 간선의 길이
                //만약 v->i->u 경로가 기존 v->u 경로보다 짦으면 dist[u] 갱신
                if(dist [u]>dist[i]+length[i][u])
                    dist[u] = dist[i] + length[i][u];
}

/*Bellman-Ford 분석
* 인접행렬: O(n^3)
* 인접리스트: O(n*e)
*/

// 공부용 예시 코드 (MatrixWDigraph 클래스 안이라고 가정)
//
// 멤버:
//   int length[MAXN][MAXN];  // i -> j 간선 비용, 없으면 INF
//   int dist[MAXN];          // v에서 각 정점까지의 최단거리 추정값
// 상수:
//   const int INF = 1e9;     // "무한대" 역할을 하는 충분히 큰 값

void MatrixWDigraph::BellmanFord(const int n, const int v)
{
    // 1. 초기화: 간선 1개만 사용한 거리로 세팅
    for (int i = 0; i < n; i++) {
        dist[i] = length[v][i];   // v -> i 직접 간선 비용 (없으면 INF)
    }
    dist[v] = 0;                  // 자기 자신까지는 0

    // 2. 간선 개수를 2,3,...,n까지 늘려가며 반복 갱신
    //    (최대 n-1개의 간선을 가진 경로까지 고려)
    for (int k = 2; k <= n; k++) {

        // 각 정점 u에 대해
        for (int u = 0; u < n; u++) {
            if (u == v) continue;   // 출발 정점은 건너뜀

            // u로 들어오는 간선이 있는지 먼저 확인 (옵션)
            bool hasIncoming = false;
            for (int i = 0; i < n; i++) {
                if (length[i][u] < INF) {   // i -> u 간선이 존재
                    hasIncoming = true;
                    break;
                }
            }
            if (!hasIncoming) continue;     // 들어오는 간선 없으면 스킵

            // 이제 실제로 u로 들어오는 모든 간선 (i -> u)을 보면서 relax
            for (int i = 0; i < n; i++) {
                // 간선 (i -> u)가 없다면 패스
                if (length[i][u] >= INF) continue;

                // 아직 i까지 도달하지 못한다면 패스
                if (dist[i] >= INF) continue;

                // relax 조건: v->i + i->u 가 현재 v->u 보다 짧으면 갱신
                if (dist[u] > dist[i] + length[i][u]) {
                    dist[u] = dist[i] + length[i][u];
                }
            }
        }
    }
}

//다른 책에서 언급되는 평범한 Bellman-Ford 알고리즘
struct Edge {
    int from, to;
    int cost;
};

vector<Edge> edges;  // 그래프의 모든 간선을 한 리스트에 모아 둠
int dist[MAXN];
const int INF = 1e9;

void BellmanFord_ListForm(const int n, const int v)
{
    // 1. 초기화
    for (int i = 0; i < n; i++)
        dist[i] = INF;
    dist[v] = 0;

    // 2. n-1번 전체 간선을 반복해서 relax
    for (int k = 1; k <= n - 1; k++) {
        for (auto& e : edges) {         // e: from -> to, cost
            if (dist[e.from] == INF)    // from에 아직 도달 못했으면 패스
                continue;
            if (dist[e.to] > dist[e.from] + e.cost) {
                dist[e.to] = dist[e.from] + e.cost;
            }
        }
    }

    // (옵션) 3. 한 번 더 돌려서 값이 줄어들면
    //         음의 사이클 존재 여부도 체크 가능
}