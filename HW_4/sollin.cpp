#include "mstree.h"
priority_queue< Edge, vector<Edge>, Compare >* PQ;
// 필요함수를 정의 및 구현하시오
// 다른 루트 v의 PQ에 속한 edges를 r의 PQ로 옮기는 함수가 필요함!
void MoveEdgesBetweenPQ(int root1, int root2) {
    if (root1 == root2) return;
    Edge e;
    while (!PQ[root1].empty()) {
        e = PQ[root1].top();
        PQ[root1].pop();
        PQ[root2].push(e);
    }
}

void ReadEdges4sollin(istream& is) {
    //각 점(tree) 마다 연결된 간선들의 minheap이 필요함.
    // NNODES개의 minheap을 갖고 있는 PQ 배열을 생성하시오.
    //PQ = new ....
    PQ = new priority_queue< Edge, vector<Edge>, Compare >[NNODES];
    Edge e;
    while (GetEdge(is, e)) {
        PQ[e.v1].push(e);
        PQ[e.v2].push(e);
    }
}
void sollin() {
    Sets sets(NNODES);
    int nedges = 0;
    while(nedges < NNODES -1) {
        int nedges_before = nedges;
        for (int r = 0; r < NNODES; ++r) {
            if (sets.Find(r) != r) continue;
            while (!PQ[r].empty()) {
                Edge e = PQ[r].top();
                PQ[r].pop();

                int rootV1 = sets.Find(e.v1);
                int rootV2 = sets.Find(e.v2);

                if (rootV1 == rootV2) continue;

                sets.WeightedUnion(rootV1, rootV2);
                nedges++;
                cout << e;

                int newRoot = sets.Find(rootV1);
                int otherRoot = (newRoot == rootV1) ? rootV2 : rootV1;

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