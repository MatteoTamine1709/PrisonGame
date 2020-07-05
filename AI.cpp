#include "AI.h"

void AI::getPath(void)
{
    aStarSearch(*m_map->grid, pos, dest);
}

AI::AI(Map &map)
    : m_map(&map)
{
}

AI::AI(void)
{
}

bool AI::isValid(int row, int col)
{
    return (row >= 0) && (row < m_map->ROW) &&
        (col >= 0) && (col < m_map->COL);
}

bool AI::isUnBlocked(Arr2D grid, int row, int col)
{
    if (grid[row][col] == 1)
        return (true);
    return (false);
}

bool AI::isDestination(int row, int col, Pair dest)
{
    if (row == dest.first && col == dest.second)
        return (true);
    return (false);
}

double AI::calculateHValue(int row, int col, Pair dest)
{
    return ((double)sqrt((row - dest.first) * (row - dest.first)
        + (col - dest.second) * (col - dest.second)));
}

void AI::tracePath(std::vector<std::vector<cell>> cellDetails, Pair dest)
{
    printf("\nThe Path is ");
    int row = dest.first;
    int col = dest.second;

    while (!(cellDetails[row][col].parent_i == row
        && cellDetails[row][col].parent_j == col)) {
        Path.push(std::make_pair(row, col));
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }
    Path.push(std::make_pair(row, col));
    while (!Path.empty())
    {
        std::pair<int, int> p = Path.top();
        Path.pop();
        printf("-> (%d,%d) ", p.first, p.second);
    }
}

bool AI::checkCell(int i, int j, int pi, int pj, std::vector<std::vector<cell>> &cellDetails, std::set<pPair>& openList,
    std::vector<std::vector<bool>>& closedList, Arr2D& grid, float val)
{
    double gNew, hNew, fNew;

    if (isValid(i, j) == true) {
        if (isDestination(i, j, dest) == true) {
            cellDetails[i][j].parent_i = pi;
            cellDetails[i][j].parent_j = pj;
            //printf("The destination cell is found\n");
            //tracePath(cellDetails, dest);
            return (true);
        } else if (closedList[i][j] == false &&
            isUnBlocked(grid, i, j) == true) {
            gNew = cellDetails[pi][pj].g + val;
            hNew = calculateHValue(i, j, dest);
            fNew = gNew + hNew;
            if (cellDetails[i][j].f == FLT_MAX ||
                cellDetails[i][j].f > fNew) {
                openList.insert(std::make_pair(fNew, std::make_pair(i, j)));
                cellDetails[i][j].f = fNew;
                cellDetails[i][j].g = gNew;
                cellDetails[i][j].h = hNew;
                cellDetails[i][j].parent_i = pi;
                cellDetails[i][j].parent_j = pj;
            }
        }
    }
    return(false);
}

void AI::aStarSearch(Arr2D& grid, Pair& src, Pair& dest)
{
    int ROW = m_map->ROW;
    int COL = m_map->COL;
    if (isValid(src.first, src.second) == false) {
        printf("Source is invalid\n");
        return;
    }
    if (isValid(dest.first, dest.second) == false) {
        return;
    }
    if (isUnBlocked(grid, src.first, src.second) == false ||
        isUnBlocked(grid, dest.first, dest.second) == false) {
        printf("Source or the destination is blocked\n");
        return;
    }
    if (isDestination(src.first, src.second, dest) == true) {
        printf("We are already at the destination\n");
        return;
    }
    std::vector<std::vector<bool>> closedList;
    for (int i = 0; i < ROW; i++) {
        std::vector<bool> b;
        for (int j = 0; j < COL; j++) {
            b.push_back(false);
        }
        closedList.push_back(b);
    }
    std::vector<std::vector<cell>> cellDetails;

    int i, j;

    for (i = 0; i < ROW; i++) {
        std::vector<cell> c;
        for (j = 0; j < COL; j++) {
            cell ce;
            ce.f = FLT_MAX;
            ce.g = FLT_MAX;
            ce.h = FLT_MAX;
            ce.parent_i = -1;
            ce.parent_j = -1;
            c.push_back(ce);
        }
        cellDetails.push_back(c);
    }
    i = src.first, j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;
    std::set<pPair> openList;
    openList.insert(std::make_pair(0.0, std::make_pair(i, j)));
    bool foundDest = false;

    while (!openList.empty()) {
        pPair p = *openList.begin();
        openList.erase(openList.begin());
        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;
        if (checkCell(i - 1, j, i, j, cellDetails, openList, closedList, grid, 1.0f) ||
            checkCell(i + 1, j, i, j, cellDetails, openList, closedList, grid, 1.0f) ||
            checkCell(i, j - 1, i, j, cellDetails, openList, closedList, grid, 1.0f) ||
            checkCell(i, j + 1, i, j, cellDetails, openList, closedList, grid, 1.0f) ||
            checkCell(i - 1, j - 1, i, j, cellDetails, openList, closedList, grid, 1.414f) ||
            checkCell(i + 1, j - 1, i, j, cellDetails, openList, closedList, grid, 1.414f) ||
            checkCell(i - 1, j + 1, i, j, cellDetails, openList, closedList, grid, 1.414f) ||
            checkCell(i + 1, j + 1, i, j, cellDetails, openList, closedList, grid, 1.414f)) {
            return;
        }
    }
    printf("Failed to find the Destination Cell\n");

    return;
}
