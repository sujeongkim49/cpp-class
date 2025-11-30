#include <iostream>
using namespace std;
#include "mstree.h"
priority_queue< Edge, vector<Edge>, Compare > PQ;
void kruskal() {
    Sets sets(NNODES);
    int nedges = 0; // #edges found up to now.
    while ((nedges < NNODES - 1) && !PQ.empty())
    {
        // 최소비용 간선e 선택
        // e를 PQ에서 삭제
        // 간선e의 각 점v1 과 v2가 어느 집합에 속했는지 Find.
        // e가 사이클을 만들지 않는다면
        // 두 집합을WeightedUnion, nedges 갯수 추가, 간선e 출력
        Edge e = PQ.top(); PQ.pop();
        int set1 = sets.Find(e.v1);
        int set2 = sets.Find(e.v2);
        if (set1 != set2) {
            sets.WeightedUnion(set1, set2);
            nedges++;
            cout << e;
        }
    }
}
void ReadEdges4kruskal(istream& is) {
    Edge e;
    while (GetEdge(is, e))
        PQ.push(e);
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
        ReadEdges4kruskal(is);
        kruskal();
    }
    catch (char const* str)
    {
        cerr << "Exception: " << str << endl; exit(1);
    }
}