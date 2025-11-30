#ifndef MSTREE_H
#define MSTREE_H
#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

//Disjoint Set 구조
//- Kruskal 알고리즘에서 "사이클이 생기는지"를 빠르게 판별하기 위해 사용
//- 각 정점이 어떤 집합(connected component)에 속해 있는지 관리
//- parent 배열을 이용한 트리 구조 + union-by-size

class Sets {
public:
    //numberOfElements 개의 원소(정점)를 가지는 집합 구조 생성
    Sets(int);

    //두 집합 i, j를 "무게(크기)"를 고려하여 합치는 연산
    void WeightedUnion(int i, int j);

    //Find(i): 원소 i가 속한 집합의 root를 찾아 반환
    //parent[x] < 0이면 x는 root(음수값은 집합의 크기)
    //parent[i]가 음수가 될 때까지(=root를 찾을 때까지) 부모를 따라 위로 올라감 > root 인덱스 반환
    int Find(int i) { while (parent[i] >= 0) i = parent[i]; return i; }
private:
    int* parent; //각 원소의 부모 인덱스(root일 경우 음수)
    int n; //원소(정점) 개수
}; //5장의 program 5.23, 5.24

//생성자: 원소 개수만큼 parent 배열 할당, 모두 -1로 초기화
// > 처음에는 모든 원소가 '크기 1의 독립된 집합이라는 뜻'
Sets::Sets(int numberOfElements) {
    if (numberOfElements < 2) throw "Must have at least 2 elements.";
    n = numberOfElements;
    parent = new int[n];
    fill(parent, parent + n, -1);
}

//WeightedUnion(i, j)
//- i와 j는 각 집합의 root
//- parent[root]에는 "음수 크기"가 들어 있으므로,
//  더 작은(음수) 값을 가진 root 가 더 큰 집합을 의미.
//- 크기가 큰 집합의 root가 부모가 되도록 붙여서 트리 높이를 줄인다.
void Sets::WeightedUnion(int i, int j)
{
    int temp = parent[i] + parent[j]; //두 집합 크기 합(둘 다 음수)
    if (parent[i] > parent[j]) { //parent가 덜 음수인 쪽 = 더 작은 집합
        //i집합이 더 작으므로 i를 j에 붙인다.
        parent[i] = j; //i의 부모를 j로
        parent[j] = temp; //j집합의 크기를 두 집합 크기 합으로 갱신
    }
    else {//j 집합이 더 작거나 같으므로 j를 i에 붙인다.
        parent[j] = i;
        parent[i] = temp;
    }
}

//그래프의 정점 개수
//- 입력 파일에서 첫 줄로 읽어온다.
int NNODES; // #nodes(vertices) in the graph

//간선 구조체 Edge
//- v1, v2: 간선이 연결하는 두 정점 번호
//- weight: 간선의 가중치(비용)
//- 비교 연산자 ==, !=는 필요시 사용
struct Edge {
    int v1, v2;
    double weight;
    bool operator==(Edge& e2) { return (v1 == e2.v1 && v2 == e2.v2); }
    bool operator!=(Edge& e2) { return (v1 != e2.v1 || v2 != e2.v2); }
};

//간선 출력 연산자 오버로딩
//예: cout<<e; -> "(v1, v2) : weight" 형식으로 출력
ostream& operator<<(ostream& os, Edge& e) {
    os << "(" << e.v1 << "," << e.v2 << ") : " << e.weight << endl;
    return os;
}

//입력 스트림에서 한 개의 간선을 읽어오는 함수
//- 형식: v1, v2, weight
//- 정점 번호 범위 체크, 자기 자신과의 간선 금지
//- v2<v1인 경우 (작은 번호가 앞에 오도록) swap
//- 성공적으로 읽으면 true, 입력 종류/오류면 false
bool GetEdge(istream& is, Edge& e) {
    // make sure that node number is 0 to NNODES-1
    is >> e.v1 >> e.v2 >> e.weight; if (!is.good()) return false;
    if (e.v1 < 0 || e.v1 >= NNODES || e.v2 < 0 || e.v2 >= NNODES || e.v1 == e.v2)
        throw "Incorrect Edge";
    if (e.v2 < e.v1) swap(e.v1, e.v2); // low-numbered vertex first
    return true;
};

//priority_queue에서 사용될 비교 함수 객체
//- priority_queue< Edge, vector<Edge>, Compare> PQ; 에서 사용
//- 기본 priority_queue는 '가장 큰 값이 top'인 max-heap
//- 여기서는 weight가 작은 간선이 top에 오도록 Compare 연산을 >로 정의해서 min-heap 처럼 사용
class Compare {
public:
    bool operator() (Edge e1, Edge e2) { return e1.weight > e2.weight; }
};
#endif