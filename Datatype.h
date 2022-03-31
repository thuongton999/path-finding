#include <bits/stdc++.h>
using namespace std;
#ifndef DATATYPE_H
#define DATATYPE_H
#endif

class Node{
    public:
        Node() {}
        Node(int x, int y, int g, int h, bool walkable) {
            this->x = x;
            this->y = y;
            this->g = g;
            this->h = h;
            this->walkable = walkable;
        }
        // getters
        int getX() const { return x; }
        int getY() const { return y; }
        int getG() const { return g; }
        int getCost() const {
            if (walkable) return g + h;
            return __INT_MAX__;
        }
        int getParentX() const { return this->parentX; }
        int getParentY() const { return this->parentY; }
        bool isVisited() const { return visited; }
        bool isWalkable() const { return walkable; }
        // setters
        void setParentLocation(int x, int y) { 
            this->parentX = x;
            this->parentY = y;
        }
        void setG(int g) { this->g = g; }
        void setH(int h) { this->h = h; }
        void setVisited(bool visited) { this->visited = visited; }
    private:
        int x, y;
        int g, h;
        bool walkable;
        bool visited = false;
        int parentX, parentY;
};

bool operator < (const Node &a, const Node &b) {
    return a.getCost() < b.getCost();
}
bool operator > (const Node &a, const Node &b) {
    return a.getCost() > b.getCost();
}
bool operator == (const Node &a, const Node &b) {
    return a.getX() == b.getX() && a.getY() == b.getY();
}
struct LowerCost {
    bool operator()(const Node &a, const Node &b) const {
        return a.getCost() > b.getCost();
    }
};

class IPathFinding {
    public:
        virtual vector<Node> findPath() = 0;
        virtual void visualize(vector<Node> path) = 0;
    protected:
        int width, height;
        int startX, startY;
        int endX, endY;
        int getDistance(Node a, Node b) {
            int distX = abs(a.getX() - b.getX());
            int distY = abs(a.getY() - b.getY());
            if (distX > distY)
                return 14 * distY + 10 * (distX - distY);
            return 14 * distX + 10 * (distY - distX);
        }
};