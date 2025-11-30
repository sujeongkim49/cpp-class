/*인접다중리스트(Adjacency Multilists)
* 간선 (u,v)는 두 개의 엔트리로 표현: u를 위한 리스트, v를 위한 리스트에 나타남
* 무방향 그래프의 간선을 한 번만 저장하면서도 양 정점에서 접근이 가능하다.
*/

struct Edge {
    int u, v;
    Edge* next_u;
    Edge* next_v;
};

struct Vertex {
    Edge* edgeList = nullptr;
};

class MultiListGraph {
public:
    int n;
    Vertex* vertices;

    MultiListGraph(int n) : n(n) {
        vertices = new Vertex[n+1];
    }

    //무방향 그래프에서 간선 추가
    void addEdge(int a, int b) {
        Edge* e = new Edge{ a, b, nullptr, nullptr }; //새 간선 노드 생성

        //정점 a리스트에 연결
        e->next_u = vertices[a].edgeList;
        vertices[a].edgeList = e;

        //정점 b리스트에 연결
        e->next_v = vertices[b].edgeList;
        vertices[b].edgeList = e;
    }
    /*무방향 그래프에서(1, 2)라는 간선이 있다고 하면, 우리가 흔히 쓰는 일반 인접 리스트는 간선을 두 번 중복 저장
    * 즉, 같은 내용의 간선을 두 번 저장하는 비효율성이 존재
    * 이걸 해결하기 위해 인접 다중 리스트에서는 이 두 개를 하나로 합친다
    * > [Edge(1,2)] 라는 하나의 간선 노드를 만들고, 이 노드를 정점 1과 정점 2의 리스트에 각각 연결
    * 대신 두 정점 리스트에서 모두 보이도록 두 방향 연결 포인터를 둔다.
    */


    //정점 x에 연결된 간선 출력
    void printAdj(int x) {
        cout << "Vertex" << x << ": ";
        Edge* cur = vertices[x].edgeList;

        while (cur != nullptr) {
            int other = (cur->u == x ? cur->v : cur->u);
            cout << other << " ";

            //다음 간선 이동
            cur = (cur->u == x ? cur->next_u : cur->next_v)
        }
        cout << endl;
    }
};

int main() {
    MultiListGraph g(4);
    g.addEdge(1, 2);//리스트가 삽입되며 뒤로 밀려서 나중에 printAdj에서 출력이 나중에 나옴
    g.addEdge(1, 3);//새 간선 리스트 > 앞에 삽입 > 나중에 printAdj에서 출력이 먼저 나옴
    g.addEdge(2, 4);

    g.printAdj(1); // Vertex1: 3 2
    g.printAdj(2); // Vertex2: 4 1
    g.printAdj(3); // Vertex3: 1
    g.printAdj(4); // Vertex4: 2
}