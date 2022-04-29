#include <bits/stdc++.h>
using namespace std;
#ifndef DATATYPE_H
#define DATATYPE_H
#endif

class Node {
    public:
        Node() {}
        // getters
        bool isVisited() const { return this->visited; }
        bool isWalkable() const { return this->walkable; }
        // setters
        void setVisited(bool visited) { this->visited = visited; }
        void setWalkable(bool walkable) { this->walkable = walkable; }
    private:
        bool walkable = true;
        bool visited = false;
};
class MazeNode : public Node {
    public:
        MazeNode() {}
        MazeNode(int x, int y, int g, int h, bool walkable) {
            this->x = x;
            this->y = y;
            this->g = g;
            this->h = h;
            this->setWalkable(walkable);
        }
        // getters
        int getX() const { return x; }
        int getY() const { return y; }
        int getG() const { return g; }
        int getCost() const {
            if (this->isWalkable()) g + h;
            return __INT_MAX__;
        }
        int getParentX() const { return this->parentX; }
        int getParentY() const { return this->parentY; }
        
        // setters
        void setParentLocation(int x, int y) { 
            this->parentX = x;
            this->parentY = y;
        }
        void setG(int g) { this->g = g; }
        void setH(int h) { this->h = h; }
    private:
        int x, y;
        int g, h;
        int parentX, parentY;
};

bool operator < (const MazeNode &a, const MazeNode &b) {return a.getCost() < b.getCost(); }
bool operator > (const MazeNode &a, const MazeNode &b) {return a.getCost() > b.getCost(); }
bool operator == (const MazeNode &a, const MazeNode &b) {
    return a.getX() == b.getX() && a.getY() == b.getY();
}
struct MazeNode_LowerCost {
    bool operator()(const MazeNode &a, const MazeNode &b) const {
        return a.getCost() > b.getCost();
    }
};

template<typename T>
class GraphNode : public Node {
    public:
        GraphNode() {}
        GraphNode(T value) {
            this->value = value;
        }
        // getters
        T getValue() { return this->value; }
        int getCostTo(GraphNode<T>* toNode) {
            if (this->linkedNodes.find(toNode) == this->linkedNodes.end()) return -1;
            return this->linkedNodes[toNode];
        }
        // setters
        void setValue(T value) { this->value = value; }
        void linkNode(GraphNode<T>* node, int cost) { this->linkedNodes[node] = cost;}
    private:
        T value;
        unordered_map<GraphNode<T>*, int> linkedNodes;
};
template<typename T>
ostream& operator << (ostream &out, const GraphNode<T> &node) {
    out << node.getValue();
    return out;
}

template<typename T>
class IPathFinding {
    public:
        virtual vector<T> findPath() = 0;
        virtual void visualize(vector<T> path) = 0;
};
template<typename T>
class GraphPathFinding : IPathFinding<GraphNode<T>> {
    protected:
        GraphNode<T>* start;
        GraphNode<T>* end;
        int totalEdges, totalNodes;
        unordered_map<T, GraphNode<T>> graph; 
        void addEdge(T from, T to, int cost) {
            this->graph[from].linkNode(&this->graph[to], cost);
        }
};
class MazePathFinding : IPathFinding<MazeNode> {
    protected:
        int width, height;
        int startX, startY;
        int endX, endY;
        int getDistance(MazeNode a, MazeNode b) {
            int distX = abs(a.getX() - b.getX());
            int distY = abs(a.getY() - b.getY());
            if (distX > distY)
                return 14 * distY + 10 * (distX - distY);
            return 14 * distX + 10 * (distY - distX);
        }
};