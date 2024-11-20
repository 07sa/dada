#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROW 5
#define COL 5
#define INF 9999

typedef struct {
    int row, col;
} Node;

typedef struct {
    int g_cost, h_cost, f_cost;
    Node parent;
    int is_visited;
    int is_obstacle;
} Cell;

Cell grid[ROW][COL];

int heuristic(Node a, Node b) {
    // Using Manhattan distance as heuristic
    return abs(a.row - b.row) + abs(a.col - b.col);
}

void print_path(Node start, Node goal) {
    Node current = goal;
    printf("Path:\n");
    while (!(current.row == start.row && current.col == start.col)) {
        printf("(%d, %d) <- ", current.row, current.col);
        current = grid[current.row][current.col].parent;
    }
    printf("(%d, %d)\n", start.row, start.col);
}

void a_star(Node start, Node goal) {
    Node open_list[ROW * COL];
    int open_count = 0;

    grid[start.row][start.col].g_cost = 0;
    grid[start.row][start.col].h_cost = heuristic(start, goal);
    grid[start.row][start.col].f_cost = grid[start.row][start.col].h_cost;

    open_list[open_count++] = start;

    while (open_count > 0) {
        int current_index = 0;
        for (int i = 1; i < open_count; i++) {
            Node n = open_list[i];
            Node current = open_list[current_index];
            if (grid[n.row][n.col].f_cost < grid[current.row][current.col].f_cost) {
                current_index = i;
            }
        }

        Node current = open_list[current_index];

        if (current.row == goal.row && current.col == goal.col) {
            print_path(start, goal);
            return;
        }

        // Remove current from open list
        open_list[current_index] = open_list[--open_count];
        grid[current.row][current.col].is_visited = 1;

        // Neighboring cells
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; i++) {
            int nr = current.row + dr[i];
            int nc = current.col + dc[i];

            if (nr >= 0 && nr < ROW && nc >= 0 && nc < COL && !grid[nr][nc].is_obstacle) {
                if (grid[nr][nc].is_visited) continue;

                int tentative_g = grid[current.row][current.col].g_cost + 1;

                if (tentative_g < grid[nr][nc].g_cost) {
                    grid[nr][nc].g_cost = tentative_g;
                    grid[nr][nc].h_cost = heuristic((Node){nr, nc}, goal);
                    grid[nr][nc].f_cost = grid[nr][nc].g_cost + grid[nr][nc].h_cost;
                    grid[nr][nc].parent = current;

                    // Add to open list if not already present
                    int in_open = 0;
                    for (int j = 0; j < open_count; j++) {
                        if (open_list[j].row == nr && open_list[j].col == nc) {
                            in_open = 1;
                            break;
                        }
                    }
                    if (!in_open) {
                        open_list[open_count++] = (Node){nr, nc};
                    }
                }
            }
        }
    }
    printf("No path found.\n");
}

int main() {
    Node start = {0, 0};
    Node goal = {4, 4};

    // Initialize grid
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            grid[i][j].g_cost = INF;
            grid[i][j].h_cost = INF;
            grid[i][j].f_cost = INF;
            grid[i][j].is_visited = 0;
            grid[i][j].is_obstacle = 0;
        }
    }

    // Add some obstacles
    grid[1][1].is_obstacle = 1;
    grid[1][2].is_obstacle = 1;
    grid[2][2].is_obstacle = 1;
    grid[3][3].is_obstacle = 1;

    a_star(start, goal);
    return 0;
}
