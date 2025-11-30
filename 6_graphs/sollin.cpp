/*Sollin 알고리즘
* 각 단계에서 여러 개의 간선을 선택
* 각 단계에서는 포리스트에 있는 각 트리에 대해 하나의 간선을 선택
* 이 간선은 오직 하나의 정점만 그 트리에 속한 최소 비용 간선
* 선택된 간선은 구축중인 신장트리에 추가
* 오직 하나의 트리만이 존재 or 더 이상 선택할 간선이 없을 때 종료
*/

#include "mstree.h"

// Sollin(Borůvka) 알고리즘에서 사용할 우선순위 큐 배열.
// PQ는 "루트(트리)별로 하나씩" 존재한다.
//
// - PQ[r]  :  현재 Disjoint Set에서 루트가 r인 트리가
//             바깥으로 나가는 간선 후보들을 담고 있는 min-heap.
// - Compare를 이용해 Edge.weight가 작은 간선이 top()에 오도록 한다.
//
// ReadEdges4sollin()에서 정점마다 하나씩 초기화하고,
// sollin()에서 컴포넌트(트리)가 합쳐질 때마다 PQ를 병합해서 사용한다.
priority_queue< Edge, vector<Edge>, Compare >* PQ;

// ======================================================================
// MoveEdgesBetweenPQ
// ======================================================================
// "두 트리가 합쳐졌을 때, 예전 루트 트리의 간선 후보들을
//  새 루트 트리의 PQ로 모두 옮기는 함수"이다.
//
// 매개변수:
//   - root1 : 예전 루트(더 이상 루트로 쓰지 않을 트리의 대표 인덱스)
//   - root2 : 새 루트(합쳐진 트리의 대표 인덱스)
//
// 역할:
//   - PQ[root1] 안에 있는 간선들을 모두 꺼내서 PQ[root2]에 푸시한다.
//   - 이렇게 하면 "루트 root2가 대표하는 트리 전체"가
//     가지는 모든 간선 후보가 PQ[root2] 안에 모이게 된다.
//
// 내부 간선(이미 같은 트리 내부를 잇게 된 간선)도 그냥 옮긴다.
// 나중에 Sollin 루프에서 PQ[root2]에서 꺼낼 때,
// Find()로 rootV1, rootV2를 다시 비교해서 내부 간선은 버릴 것이므로
// 여기에서 굳이 필터링할 필요는 없다.
void MoveEdgesBetweenPQ(int root1, int root2) {
    if (root1 == root2) return; // 같은 루트라면 옮길 필요 없음
    Edge e;
    // PQ[root1]가 빌 때까지 하나씩 꺼내서 PQ[root2]로 옮긴다.
    while (!PQ[root1].empty()) {
        e = PQ[root1].top();  // root1 트리의 후보 간선 하나
        PQ[root1].pop();
        PQ[root2].push(e);
    }
}

// ======================================================================
// ReadEdges4sollin
// ======================================================================
// Sollin 알고리즘에서 사용할 초기 데이터 구조들을 설정하는 함수.
//
// 역할:
//   1) 정점 수 NNODES 크기의 PQ 배열을 동적 할당한다.
//      → 각 정점이 "초기에는 자기 자신만의 트리"이므로,
//        정점 하나당 min-heap 하나씩을 만들어 놓는다.
//   2) 입력으로부터 간선을 하나씩 읽어들이면서,
//      그 간선을 양 끝 정점의 PQ에 모두 넣는다.
//
//  결과적으로:
//    - 처음에는 "각 정점이 자기만의 트리"이므로,
//    - PQ[v]에는 "정점 v에서 나가는 모든 간선들"이 들어있는 형태가 된다.
void ReadEdges4sollin(istream& is) {
    PQ = new priority_queue< Edge, vector<Edge>, Compare >[NNODES];
    Edge e;
    // 입력 스트림 is에서 간선을 하나씩 읽는다.
    // GetEdge(is, e)는 (v1, v2, weight)를 읽어 e에 넣고,
    // 범위 체크 후 true/false를 반환한다고 가정.
    while (GetEdge(is, e)) {
        // 간선 e는 정점 e.v1, e.v2 두 정점에 연결된다.
        // Sollin에서는 "각 트리를 대표하는 루트"가 변화할 수 있으므로,
        // 처음에는 정점 기준으로 PQ를 세팅한다.
        // e.v1이 루트인 초기 트리는 PQ[e.v1]에 e를 가진다.
        PQ[e.v1].push(e);
        // e.v2가 루트인 초기 트리는 PQ[e.v2]에 e를 가진다.
        PQ[e.v2].push(e);
    }
}


// ======================================================================
// sollin (Borůvka's MST Algorithm)
// ======================================================================
// Sollin 알고리즘(= Borůvka 알고리즘)의 핵심 아이디어:
//
// - 처음에는 모든 정점이 "각자 하나의 트리(컴포넌트)".
// - 각 트리(컴포넌트)마다, 그 트리에서 "밖으로 나가는 최소 비용 간선"을 하나씩 찾는다.
// - 그 최소 간선들을 "한 번에" MST에 추가하면서 트리들을 합친다.
// - 합쳐진 새 트리에 대해 다시 이 과정을 반복.
// - 더 이상 합칠 수 없거나, 간선 수가 (정점 수 - 1)이 되면 종료.
//
// 이 구현에서는:
//  - Disjoint Set(Sets)을 사용해서 트리/컴포넌트 관리
//  - 각 루트별 PQ[r]를 사용해서 "그 트리에서 나가는 후보 간선" 관리
void sollin() {
    // Disjoint Set 초기화:
    // - 처음에는 각 정점이 "자기 자신만 포함하는 트리"
    //   즉, NNODES개의 독립된 트리가 있는 상태.
    Sets sets(NNODES);

    // 현재까지 MST에 포함된 간선 수.
    int nedges = 0;

    // MST는 항상 (정점 수 - 1)개의 간선을 가진다.
    // nedges < NNODES - 1 이면 아직 MST가 완성되지 않은 상태.
    while (nedges < NNODES - 1) {

        // 이 라운드(while 한 바퀴) 시작 전에 선택된 간선 수를 저장해 둔다.
        // - 이 값과 라운드 끝의 nedges를 비교해서,
        //   "이번 라운드에 실제로 새로운 간선을 하나도 못 골랐다"면
        //   -> 더 이상 MST를 확장할 수 없다는 것을 알 수 있다.
        int nedges_before = nedges;

        // 0 ~ NNODES-1 까지 순회하면서
       // "현재 진짜 루트인 정점 r"에 대해서만 최소 간선을 찾는다.
        for (int r = 0; r < NNODES; ++r) {

            // sets.Find(r)가 r이 아니면, r은 더 이상 루트가 아니다.
            // (즉, 다른 트리에 속한 노드인 상태)
            // Sollin에서는 "트리(컴포넌트)" 단위로 처리해야 하므로,
            // 실제 루트가 아닌 정점은 스킵한다.
            if (sets.Find(r) != r) continue;

            // 이제 r은 현재 어떤 트리의 루트이다.
            // 이 트리가 바깥으로 나가는 최소 간선을 찾기 위해
            // PQ[r] 안의 간선들을 본다.
            while (!PQ[r].empty()) {
                // PQ[r]는 min-heap이므로, top()에 있는 간선이
                // "이 트리에서 나가는 간선 후보 중 가장 가벼운 것"이다.
                Edge e = PQ[r].top();
                PQ[r].pop();  // 일단 꺼내서 검사해 본다.

                // 이 간선 e의 양 끝 정점이 현재 어느 트리에 속해 있는지 확인한다.
                int rootV1 = sets.Find(e.v1);
                int rootV2 = sets.Find(e.v2);

                // 만약 rootV1 == rootV2 라면,
                // 이 간선은 이미 "같은 트리 내부를 연결하는 간선"이 되어버린 상태.
                // MST에 추가하면 사이클이 생기므로, 이 간선은 버리고 다음 간선을 본다.
                if (rootV1 == rootV2) continue;

                // 여기까지 왔다는 것은:
                // - e.v1 이 속한 트리(rootV1)
                // - e.v2 가 속한 트리(rootV2)
                // 가 서로 다른 트리이며,
                // 이 간선 e는 "루트 r를 대표로 하는 트리에서 바깥으로 나가는
                // 가장 가벼운 간선"이라는 뜻이다.
                //
                // 따라서 이 간선 e는 Sollin 알고리즘에서 말하는
                // "이 트리의 최소 외부 간선"이 된다.

                // 두 다른 트리 rootV1, rootV2를 연결하는 간선이므로
                // MST에 포함해도 사이클이 생기지 않는다.
                // 따라서 두 트리를 WeightedUnion으로 합친다.
                sets.WeightedUnion(rootV1, rootV2);

                // MST에 간선이 하나 추가되었으므로 갯수 증가.
                nedges++;
                cout << e;

                // Union 이후의 "새 루트"를 구한다.
                // - WeightedUnion 호출 이후, rootV1과 rootV2 둘 중 하나가
                //   혹은 전혀 다른 값이 새 루트가 될 수 있으므로,
                //   Find(rootV1) 또는 Find(rootV2)를 다시 호출해서
                //   최신 루트를 얻는다.
                int newRoot = sets.Find(rootV1);

                // newRoot가 rootV1였다면,
                //   rootV2 쪽이 옛 루트(otherRoot)가 된다.
                // 반대로 newRoot가 rootV2라면,
                //   rootV1 쪽이 otherRoot가 된다.
                //
                // 즉, otherRoot는 "이제 더 이상 루트가 아닌 트리의 대표"이고,
                // 이쪽 PQ에 들어있던 간선들을 newRoot의 PQ로 옮겨야 한다.
                int otherRoot = (newRoot == rootV1) ? rootV2 : rootV1;

                // 옛 루트 otherRoot 의 PQ 안에 있던 간선들을
                // 새 루트 newRoot 의 PQ로 모두 옮긴다.
                //
                // 이렇게 하면:
                // - newRoot 가 대표하는 새 트리는
                //   "원래 rootV1 트리 + rootV2 트리"를 합친 것인데,
                // - PQ[newRoot] 안에는 이 큰 트리에서 나가는
                //   모든 간선 후보들이 모이게 된다.
                MoveEdgesBetweenPQ(otherRoot, newRoot);
                break;
            }
        }
        if (nedges == nedges_before) throw "No Spanning Tree Exists.";
    }
    //nedges 값 확인하여 tree가 1개로 되었다면 다음 반복을 중단한다
    //각 노드가 트리(포리스트) 이므로
    //각 트리에 속한 최소 edge를 구한다. //단, 트리가 WeightedUnion 되므로 루트 v를 Find하고 최소 edge를 검색한다. //WeightedUnion된 트리의 루트 r을 Find 하여
    //r의 PQ로 r과 다른 루트 (rootV1 or rootV2)의 PQ에 속한 edges를 옮긴다.
    //다른 루트의 PQ에 속한 edges를 r의 PQ로 옮기는 함수가 필요함!
}
int main(int argc, char* argv[]) {
    ifstream is;
    if (argc == 1) is.open("kin.txt");
    else is.open(argv[1]);
    if (!is) { cerr << "No such input file\n"; exit(1); }
    is >> NNODES;
    if (NNODES < 2) { cerr << "#nodes must be 2.." << endl; exit(1); }
    try {
        ReadEdges4sollin(is);
        sollin();
    }
    catch (char const* str)
    {
        cerr << "Exception: " << str << endl; exit(1);
    }
}