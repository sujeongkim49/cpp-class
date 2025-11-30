/*인접리스트 표현 방법
* 인접행렬의 n행들을 n개의 연결리스트로 표현
* 각 행의 연결리스트는 해당 행에서 1로 표시된 열의 번호들을 저장
* data와 link 필드
* c++선언문: n개의 linked list를 저장할 수 있는 배열
* 장점: 메모리 절약, 간선 추가/삭제 용이
*/

Chain<int>* adjList[5]; // 5개의 정점을 가지는 그래프의 인접리스트 선언
LinkedGraph(const int vertices = 0); n(vertices), e(0)
{
    adjList = new Chain<int>[n];
}

/* n개의 정점, e개의 간선의 Undirected Graph를 인접리스트로 표현
* n개의 헤드노드, 2e개의 리스트 노드 필요
* Directed Graph의 경우 e개의 리스트 노드 필요
*/