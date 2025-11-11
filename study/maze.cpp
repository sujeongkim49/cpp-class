#include <iostream>
#include <stack>
using namespace std;

const int MAXSIZE = 100;
bool maze[MAXSIZE + 2][MAXSIZE + 2];
bool mark[MAXSIZE + 1][MAXSIZE + 1];
enum directions {N, NE, E, SE, S, SW, W, NW};
struct offsets{
    int a, b;
} movea[8] = { (-1,0), (-1,1), (0,1), (1,1), (1,0), (1,-1), (0,-1), (-1,-1) };
struct Items {
    Items(int xx = 0, int yy=0, int dd=0) : x(xx), y(yy), dir(dd) {}
    int x, y, dir;
};

template <class T>
ostream& operator<<(ostream& os, stack<T>& s) {
    stack<T> tempStack = s;
    stack<T> reverseStack;
    while (!tempStack.empty()) {
        reverseStack.push(tempStack.top());
        tempStack.pop();
    }
    while (!reverseStack.empty()) {
        os << reversStack.top();
        reversStack.pop();
        if (!reverseStack.empty()) os << " -> ";
    }
    return os;
}

ostream& operator<<(ostream& os, Items& item) {
    static int count = 0;
    os << "(" << item.x << ", " << item.y << ")";
    count++; if ((count % 5) == 0) cout << endl;
    return os;
}

void Path(const int m, const int p) {
    mark[1][1] = 1;
    stack<Items> stack;
    Items temp(1, 1, E);
    stack.push(temp);
    while (!stack.empty()) {
        temp = stack.top(); stack.pop();
        int i = temp.x;
        int j = temp.y;
        int d = temp.dir;
        while (d < 8) {
            int g = i + movea[d].a;
            int h = j + movea[d].b;
            if ((g == m) && (h == p)) {
                cout << stack;
                Items item(i, j, d);
                cout << " -> " << item;
                item.x = m; item.y = p;
                cout << " -> " << item << endl;
                return;
            }
            if (!maze[g][h] && !mark[g][h]) {
                mark[g][h] = 1;
                temp.x = i; temp.y = j, temp.dir = d + 1;
                stack.push(temp);
                i = g; j = h; d = N;
            }
            else d++;
        }
    }
    cout << endl;
}

void getdata(istream& is, int& m, int& p) {
    is >> m >> p;
    for (int i = 0; i < m + 2; i++) { maze[i][0] = 1; maze[i][p + 1] = 1; }
    for (int j = 1; j <= p; j++) { maze[0][j] = 1; maze[m + 1][j] = 1; }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= p; j++) is >> maze[i][j];
    }
}