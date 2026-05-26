#include "algorithms.h"
#include <queue>
#include <stack>
#include <cmath>

struct Node {
    int r, c;
    int dist;
    Node* parent;
};

int dr[] = {-1,1,0,0};
int dc[] = {0,0,-1,1};

std::vector<Cell*> reconstruct(Node* node, Grid& grid) {
    std::vector<Cell*> path;
    while (node) {
        path.push_back(&grid.getCell(node->r,node->c));
        node = node->parent;
    }
    return path;
}

// BFS
std::vector<Cell*> Algorithms::BFS(Grid& grid, Cell* start, Cell* end) {
    bool vis[ROWS][COLS]={0};
    std::queue<Node*> q;
    q.push(new Node{start->row,start->col,0,nullptr});

    while(!q.empty()){
        auto cur=q.front(); q.pop();

        if(vis[cur->r][cur->c]) continue;
        vis[cur->r][cur->c]=1;

        if(cur->r==end->row && cur->c==end->col)
            return reconstruct(cur,grid);

        grid.getCell(cur->r,cur->c).type = VISITED;

        for(int i=0;i<4;i++){
            int nr=cur->r+dr[i], nc=cur->c+dc[i];
            if(nr>=0&&nc>=0&&nr<ROWS&&nc<COLS &&
               !vis[nr][nc] && grid.getCell(nr,nc).type!=WALL){
                q.push(new Node{nr,nc,0,cur});
            }
        }
    }
    return {};
}

// DFS
std::vector<Cell*> Algorithms::DFS(Grid& grid, Cell* start, Cell* end) {
    bool vis[ROWS][COLS]={0};
    std::stack<Node*> st;
    st.push(new Node{start->row,start->col,0,nullptr});

    while(!st.empty()){
        auto cur=st.top(); st.pop();

        if(vis[cur->r][cur->c]) continue;
        vis[cur->r][cur->c]=1;

        if(cur->r==end->row && cur->c==end->col)
            return reconstruct(cur,grid);

        grid.getCell(cur->r,cur->c).type = VISITED;

        for(int i=0;i<4;i++){
            int nr=cur->r+dr[i], nc=cur->c+dc[i];
            if(nr>=0&&nc>=0&&nr<ROWS&&nc<COLS &&
               !vis[nr][nc] && grid.getCell(nr,nc).type!=WALL){
                st.push(new Node{nr,nc,0,cur});
            }
        }
    }
    return {};
}

// Dijkstra & A* simplified (same for grid)
std::vector<Cell*> Algorithms::Dijkstra(Grid& g, Cell* s, Cell* e){
    return BFS(g,s,e);
}

std::vector<Cell*> Algorithms::AStar(Grid& g, Cell* s, Cell* e){
    return BFS(g,s,e);
}
