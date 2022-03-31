#include <bits/stdc++.h>
#include "../Datatype.h"
using namespace std;

#define MAX_WIDTH 100
#define MAX_HEIGHT 100

class AStar : IPathFinding {
    public:
        AStar(string mapFile) {
            cin.tie(0)->sync_with_stdio(0);
            freopen(mapFile.c_str(), "r", stdin);
            cin >> this->width >> this->height;
            cin >> this->startX >> this->startY;
            cin >> this->endX >> this->endY;
            for (int i = 0; i < width; i++) {
                for (int j = 0; j < height; j++) {
                    char c;
                    cin >> c;
                    grid[i][j] = *(new Node(i, j, 0, 0, c != 'w'));
                }
            }
        }
        vector<Node> findPath() {
            Node *start = &grid[startX][startY];
            start->setG(0);
            start->setH(calculateH(startX, startY));
            open.push(*start);
            start->setVisited(true);
            int delta[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

            while (!open.empty()) {
                Node current = open.top();
                open.pop();
                closed.push_back(current);
                current.setVisited(true);
                current.setG(calculateG(current.getX(), current.getY()));
                current.setH(calculateH(current.getX(), current.getY()));
                if (current.getX() == endX && current.getY() == endY)
                    return this->retracePath(grid[startX][startY], grid[endX][endY]);
                for (int i = 0; i < 8; i++) {
                    int neighbourX = current.getX() + delta[i][0];
                    int neighbourY = current.getY() + delta[i][1];
                    Node *neighbour = &grid[neighbourX][neighbourY]; 
                    if (!neighbour->isWalkable() || neighbour->isVisited())
                        continue;
                    int newCost = current.getG() + getDistance(current, *neighbour);
                    if (newCost < neighbour->getG() || !neighbour->isVisited()) {
                        neighbour->setG(newCost);
                        neighbour->setH(calculateH(neighbourX, neighbourY));
                        neighbour->setParentLocation(current.getX(), current.getY());
                        if (!neighbour->isVisited()) {
                            open.push(*neighbour);
                            neighbour->setVisited(true);
                        }
                    }
                }
            }
            return {};
        }
        void visualize(vector<Node> path) {
            char map[width][height];
            for (int i = 0; i < width; i++) {
                for (int j = 0; j < height; j++) {
                    map[i][j] = grid[i][j].isWalkable() ? ' ' : 'w';
                }
            }
            for (Node node : path) {
                map[node.getX()][node.getY()] = '.';
            }
            for (int i = 0; i < width; i++) {
                for (int j = 0; j < height; j++) {
                    cout << map[i][j] << " ";
                }
                cout << "\n";
            }
        }
    private:
        Node grid[MAX_WIDTH][MAX_HEIGHT];
        priority_queue<Node, vector<Node>, LowerCost> open;
        vector<Node> closed;
        int calculateG(int x, int y) {
            return getDistance(grid[x][y], grid[startX][startY]);
        }
        int calculateH(int x, int y) {
            return getDistance(grid[x][y], grid[endX][endY]);
        }
        vector<Node> retracePath(Node &start, Node &end) {
            vector<Node> path = {end};
            for (Node node = grid[end.getX()][end.getY()]; 
                node.getX() != start.getX() || node.getY() != start.getY(); 
                node = grid[node.getParentX()][node.getParentY()]) {
                    path.push_back(node);
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            return path;
        }
};

int main() {
    system("cls");
    AStar astar("Map.maze");
    astar.visualize(astar.findPath());
    return 1;
}