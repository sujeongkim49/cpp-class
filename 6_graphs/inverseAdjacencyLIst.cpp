/*역인접리스트(inverse adjacency list)란 그래프의 각 정점에 대해 그 정점으로 들어오는 간선들을 저장하는 자료구조입니다.
* 즉, 각 정점에 대해 해당 정점으로 향하는 간선들의 출발 정점들을 연결리스트 형태로 저장합니다.
* Undirected Graph의 경우 각 간선이 양방향이므로, 역인접리스트는 일반 인접리스트와 동일하게 동작합니다. > adjacencyList만으로도 충분
* Directed graph의 경우, 가령 in-degree of a vertex를 알려면 adjacency list외에 inverce adjacency list가 필요합니다.
* 역인접리스트는 다음과 같은 특징이 있습니다:
* 1. 각 정점에 대해 그 정점으로 들어오는 간선들의 출발 정점들을 연결리스트 형태로 저장합니다.
* 2. Directed graph에서 특정 정점으로 들어오는 간선들을 효율적으로 찾을 수 있습니다.
* 3. 메모리 사용량이 인접행렬에 비해 효율적입니다.
*/