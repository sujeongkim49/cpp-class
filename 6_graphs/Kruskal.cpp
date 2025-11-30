/*Kruskal 알고리즘
* 한 번에 하나씩 T에 간선을 추가해가면서 최소비용 신장트리 T를 구축
* T에 포함될 간선을 비용의 크기순으로 선택
* 이미 T에 포함된 간선들과 사이클을 형성하지 않는 간선만을 T에 추가
* G는 연결되어 있고, n>0개의 정점을 가지므로 정확하게 n-1개의 간선만이 T에 포함됨
*/

while ((T가 n - 1개 미만의 간선을 포함) && (E not empty)) {
    E에서 최소 비용 간선(v, w) 선택;
    E에서(v, w) 삭제;
    if (v, w)가 T에서 사이클을 만들지 않으면 T에(v, w)추가;
    else discard(v, w);
}
if (T가 n - 1개 미만의 간선을 포함) cout << "신장 트리 없음" << endl;

#include <iostream>
using namespace std;
#include "mstree.h"

//Kruskal에서 사용할 우선순위 큐
//- 모든 간선을 PQ에 넣어 둔다 > Compare 사용해서 가중치가 작은 간선이 PQ.top에 오도록
//  > Kruskal 알고리즘에서 가장 작은 간선부터 꺼내 쓴다.
priority_queue< Edge, vector<Edge>, Compare > PQ;
void kruskal() {
    //1. 초기에는 각 정점이 자기 자신만 포함하는 집합 > 총 NNODES개의 독립된 컴포넌트
    Sets sets(NNODES);
    int nedges = 0; //지금까지 선택된 간선 수

    //2. MST의 간선 수는 (정점-1)이면 충분하므로, nedges < NNODES-1 동안 반복, 또한 PQ가 빌 때까지
    while ((nedges < NNODES - 1) && !PQ.empty())
    {
        // 최소비용 간선e 선택
        // e를 PQ에서 삭제
        // 간선e의 각 점v1 과 v2가 어느 집합에 속했는지 Find.
        // e가 사이클을 만들지 않는다면
        // 두 집합을WeightedUnion, nedges 갯수 추가, 간선e 출력
        
        //3. 현재 PQ에서 가장 가중치가 작은 간선 e를 꺼낸다.
        Edge e = PQ.top(); PQ.pop();

        //4. 간선 e의 두 끝점 v1, v2가 각각 어느 집합에 속하는지 확인
        int set1 = sets.Find(e.v1);
        int set2 = sets.Find(e.v2);

        //5. set1 != set2 이면, 서로 다른 컴포넌트 > 이 간선을 선택해도 사이클이 생기지 않는다.
        if (set1 != set2) {
            sets.WeightedUnion(set1, set2);
            nedges++;
            cout << e;
        }
        //6. set1==set2 이면, 아무것도 안함
    }
    //while 종료 > MST 완성
}

//간선 입력 함수
//- 입력 스트림 'is'에서 간선을 계속 읽어서 PQ에 넣는 역할
//- 파일에는 "v1 v2 weight" 줄들이 여러개 있다고 가정
void ReadEdges4kruskal(istream & is) {
    Edge e;
    while (GetEdge(is, e)) //한 줄 읽어서 e에 저장, 실패하면 false
        PQ.push(e); //성공적으로 읽은 간선을 PQ에 넣음
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