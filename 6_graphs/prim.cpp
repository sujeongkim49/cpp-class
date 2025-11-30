/*Prim 알고리즘
* 한 번에 한 간선씩 추가해가면서 최소 비용 신장 트리를 구축
* 새로 선택된 정점은 TV에 추가한다.
* 새로 선택된 간선은 트리 T에 추가한다.(T에는 사이클이 없어야 함)
* 최소 비용 간선 (u, v)에 대해 T U {(u, v)}가 트리를 유지하면 T에 추가
* T에 n-1개의 간선이 포함될 때까지 간선의 추가 단계를 반복
* 추가된 간선이 사이클을 형성하지 않도록 각 단계에서 간선 (u,v)를 선택할 때 u 또는 v중 오직 하나만 TV에 속한 것을 고른다.
*/

TV = { 0 };
for (T = null; T가 n - 1개 미만의 간선을 포함; (u, v)를 T에 추가) {
    Let(u, v) be a least - cost edge such that u belongs to TV and v doesnt belong to TV;
    if (there is no such edge) break;
    add v to TV;
}
if (T가 n - 1개 미만의 간선을 포함) cout << "신장 트리 없음" << endl;

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#include "mstree.h"

//Q[v]: 각 정점 v에 대해 그 정점에 인접한 간선들을 저장하는 큐
//PQ: 모든 간선 중 현재까지 트리에 포함된 정점들에서 바깥으로 나가는 간선들만 모아 놓은 우선순위 큐
// > weight가 가장 작은 간선을 PQ.top()으로 얻을 수 있음
//Sets: 어떤 정점들이 이미 같은 트리(컴포넌트)에 속해 있는지 관리
// > Find(x)는 x의 루트(대표 정점)
// > WeightedUnion(a, b)는 두 트리를 하나로 합침
priority_queue< Edge, vector<Edge>, Compare > PQ;
queue< Edge >* Q; // each vertex has a queue

//정점 v의 큐 Q[v]에 들어있는 "모든 간선"을 PQ로 옮기는 함수.
//Q[v]는 "정점 v에 인접한 간선들의 창고" 역할.
//어떤 시점에 v가 MST 트리에 편입되면,
//그때서야 Q[v]에 있던 간선들을 PQ로 꺼내서
//"트리에서 나가는 후보 간선" 목록에 추가한다.
void MoveIntoPQ_EdgesOfNodes(int v)
{
    // Move all edges of vertex 'v' in the queue Q into PQ
    Edge e;
    while (!Q[v].empty()) {
        e = Q[v].front();
        Q[v].pop();
        PQ.push(e);
    }
}

//Prim 본체
void prim()
{
    // Disjoint Set(Union-Find) 구조.
    //처음에는 각 정점이 "자기 자신만 포함하는 트리" 상태.
    //나중에 간선을 선택할 때, 두 정점이
    //같은 집합인지(이미 같은 트리인지) 검사하는 데 사용.
    Sets sets(NNODES);
    int nedges = 0; // 지금까지 MST에 포함된 간선 개수
    while (nedges < NNODES - 1)
    {
        if (PQ.empty()) throw "No Spanning Tree Exists.";

        // PQ에서 현재 "가장 가중치가 작은 간선"을 하나 꺼낸다.
        Edge e = PQ.top(); PQ.pop(); // 우선순위가 가장 높은(= weight가 제일 작은) 간선

        // 이 간선의 두 끝점 v1, v2가 각각 어느 집합(트리)에 속해있는지 확인.
        int set1 = sets.Find(e.v1);
        int set2 = sets.Find(e.v2);

        if (set1 != set2) // e is a valid edge
        {
            // 두 트리를 WeightedUnion으로 합친다.
            // 더 큰 집합이 부모가 되도록 합쳐서 트리 높이를 줄이려는 목적.
            sets.WeightedUnion(set1, set2);

            // MST에 간선이 하나 추가되었으므로 개수 증가.
            nedges++;
            cout << e;

            // 이제 간선 e를 통해 새로 트리에 편입된 정점들의
            // "인접 간선"들을 PQ로 옮긴다.
            // 처음에는 정점 0의 간선만 PQ에 있었음.
            // e를 통해 새로운 정점(예: v2)이 트리에 합류하면
            // 그 정점 주변의 간선도 PQ에 넣어서
            // "트리에서 바깥으로 나가는 후보 간선" 목록을 확장한다.
            MoveIntoPQ_EdgesOfNodes(e.v1);
            MoveIntoPQ_EdgesOfNodes(e.v2);
        }
        // 현재 선택된 edge e의 두 점(노드)들의 루트를 구한다.
        // PQ 꺼낸 e가 자격이 있으면, 두 집합 WeightedUnion, nedges 갯수추가, e출력
        // 트리에 연결 처리된 e의 두 점에 연결된 edge들을 PQ로 옮긴다. }
    }
}

//입력 단계
// > Q 배열을 만들고, 각 간선을 두 끝 정점 v1, v2의 큐를 넣는다
// > 시작 정점 0에 인접한 간선들만 먼저 PQ로 옮긴다
void ReadEdges4prim(istream & is)
{
    Edge e;
    // NNODES개 각 점(vertex)를 위한 queue들을 배열로 생성.
    // Q[v]는 "정점 v에 인접한 모든 간선들"을 저장하는 큐.
    // 나중에 해당 정점 v가 MST에 편입될 때,
    // 그 큐 안의 간선을 PQ로 옮기기 위해 사용.
    Q = new queue< Edge >[NNODES];
    while (GetEdge(is, e))
    {
        // 읽은 간선 e를
        // 두 점(vertex 또는 노드)의 큐에 각각 넣어준다.
        // 한 edge에 연결된 점은 두 개 (e.v1, e.v2)
        // 이렇게 해야 나중에 e.v1이 트리에 들어올 때도,
        // e.v2가 트리에 들어올 때도, 둘 다 이 간선을 PQ에 넣을 수 있다.
        Q[e.v1].push(e);
        Q[e.v2].push(e);
    }

    // Prim 알고리즘의 시작점으로 정점 0을 선택.
    // "현재 트리 T = {0}" 이라고 생각.
    // 정점 0에 인접한 간선들을 PQ로 옮겨서,
    // "트리에서 바깥으로 나가는 후보 간선들" 목록을 초기화.
    MoveIntoPQ_EdgesOfNodes(0); // 시작 점 0의 edge들을 PQ 로 이동한다. 
}

int main(int argc, char* argv[])
{
    ifstream is;
    if (argc == 1) is.open("kin.txt");
    else is.open(argv[1]);
    if (!is) { cerr << "No such input file\n"; exit(1); }
    is >> NNODES;
    if (NNODES < 2) { cerr << "#nodes must be 2.." << endl; exit(1); }
    try {
        ReadEdges4prim(is);
        prim();
    }
    catch (char const* str)
    {
        cerr << "Exception: " << str << endl; exit(1);
    }
}