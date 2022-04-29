#include <bits/stdc++.h>
#include "../Datatype.h"
using namespace std;

template<typename T>
class GraphAStar : GraphPathFinding<T> {
    public:
        GraphAStar(string graphFile) {
            cin.tie(0)->sync_with_stdio(true);
            freopen(graphFile.c_str(),  "r", stdin);
            T startValue, endValue;
            cin >> this->totalNodes >> this->totalEdges;
            cin >> startValue >> endValue;
            T from, to;
            int cost;
            for (int i = 0; i < this->totalEdges; i++) {
                cin >> from >> to >> cost;
                this->graph[from].setValue(from);
                this->graph[to].setValue(to);
                this->graph[from].linkNode(&this->graph[to], cost);
            }
            // view all nodes
            for (auto i = this->graph.begin(); i != this->graph.end(); i++) {
                cout << i->first << ": " << i->second << endl;
            }
        }
        vector<GraphNode<T>> findPath() {
            
        }
        void visualize(vector<GraphNode<T>> path) {

        }
};

int main() {
    system("cls");
    // node must be unique
    GraphAStar<int> pathfinding("../Data/Graph.inp");
    // pathfinding.visualize(pathfinding.findPath());
    return 0;
}