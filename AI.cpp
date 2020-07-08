#include "AI.h"
#include "Math.h"
#include "Log.h"

void AI::getPath(void)
{
    while (!Path.empty())
        Path.pop();
    if (m_map == nullptr)
        return;
    aStarSearch(*m_map->grid, Pos, Dest);
    if (LOG.LogIf(LogLevel_e::All))
        printPath();
    if (!Path.empty()) {
        Pair p = Path.top();
        Dest.x = p.first;
        Dest.y = p.second;
        float d = Math::dist(Pos.x, Pos.y, Dest.x, Dest.y);
        if (d == 0)
            d = 1;
        m_dir.x = (Dest.x - Pos.x) / d * m_speed;
        m_dir.y = (Dest.y - Pos.y) / d * m_speed;
        Path.pop();
    }
}

void AI::setMap(Map* map)
{
    m_map = map;
    if (m_map == nullptr)
        return;
    int ROW = m_map->ROW;
    int COL = m_map->COL;
    int i = 0, j = 0;
    m_cellDetails.clear();
    m_cellDetails.reserve(sizeof(std::vector<cell>) * ROW);
    for (i = 0; i < ROW; i++) {
        std::vector<cell> v;
        v.reserve(sizeof(cell) * COL);
        for (j = 0; j < COL; j++) {
            cell c;
            v.push_back(c);
        }
        m_cellDetails.push_back(v);
    }
    m_closedList.reserve(sizeof(std::vector<bool>)* ROW);
    for (int i = 0; i < ROW; i++) {
        std::vector<bool> b;
        b.reserve(sizeof(bool) * COL);
        for (int j = 0; j < COL; j++)
            b.push_back(false);
        m_closedList.push_back(b);
    }
}

AI::AI(Map &map)
    : m_map(&map)
{
    setMap(m_map);
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

void AI::tracePath(std::vector<std::vector<cell>> m_cellDetails, Pair dest)
{
    int row = dest.first;
    int col = dest.second;

    while (!(m_cellDetails[row][col].parent_i == row
        && m_cellDetails[row][col].parent_j == col)) {
        Path.push(std::make_pair(col * 10, row * 10));
        int temp_row = m_cellDetails[row][col].parent_i;
        int temp_col = m_cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }
}

void AI::printPath(void)
{
    if (Path.empty())
        return;
    std::stack<Pair> temp;
    std::cout << "Path for AI\n";
    while (!Path.empty()) {
        std::pair<int, int> p = Path.top();
        Path.pop();
        printf("-> (%d,%d) ", p.first, p.second);
        temp.push(p);
    }
    while (!temp.empty()) {
        std::pair<int, int> p = temp.top();
        temp.pop();
        Path.push(p);
    }
    std::cout << "\n\n";
}

void AI::move(void)
{
    if (m_dir.x != 0 || m_dir.y != 0)
        Pos += m_dir;
    if (Path.size() == 1 && (Math::dist(Pos.x, Pos.y, Dest.x, Dest.y) <= 1)) {
        Pair p = Path.top();
        Pos.x = p.first;
        Pos.y = p.second;
        Dest.x = p.first;
        Dest.y = p.second;
        Path.pop();
    }
    if (!Path.empty()) {
        if (Math::dist(Pos.x, Pos.y, Dest.x, Dest.y) <= m_speed) {
            Pair p = Path.top();
            Dest.x = p.first;
            Dest.y = p.second;
            float d = Math::dist(Pos.x, Pos.y, Dest.x, Dest.y);
            m_dir.x = (Dest.x - Pos.x) / d * m_speed;
            m_dir.y = (Dest.y - Pos.y) / d * m_speed;
            Path.pop();
        }
    } else {
        m_dir = { 0, 0 };
    }
}

bool AI::checkCell(int i, int j, int pi, int pj, std::vector<std::vector<cell>> &m_cellDetails, std::set<pPair>& openList,
    Arr2D& grid, float val, Pair& dest)
{
    double gNew, hNew, fNew;

    if (isValid(i, j) == true) {
        if (isDestination(i, j, dest) == true) {
            m_cellDetails[i][j].parent_i = pi;
            m_cellDetails[i][j].parent_j = pj;
            tracePath(m_cellDetails, dest);
            return (true);
        } else if (m_closedList[i][j] == false &&
            isUnBlocked(grid, i, j) == true) {
            gNew = m_cellDetails[pi][pj].g + val;
            hNew = calculateHValue(i, j, dest);
            fNew = gNew + hNew;
            if (m_cellDetails[i][j].f == FLT_MAX ||
                m_cellDetails[i][j].f > fNew) {
                openList.insert(std::make_pair(fNew, std::make_pair(i, j)));
                m_cellDetails[i][j].f = fNew;
                m_cellDetails[i][j].g = gNew;
                m_cellDetails[i][j].h = hNew;
                m_cellDetails[i][j].parent_i = pi;
                m_cellDetails[i][j].parent_j = pj;
            }
        }
    }
    return(false);
}

void AI::aStarSearch(Arr2D& grid, sf::Vector2f& srcA, sf::Vector2f& destA)
{
    std::pair<int, int> src = std::make_pair(srcA.y / 10, srcA.x / 10);
    std::pair<int, int> dest = std::make_pair(destA.x / 10, destA.y / 10);
    int ROW = m_map->ROW;
    int COL = m_map->COL;
    if (isValid(src.first, src.second) == false) {
        LOG.Warn("Source is invalid");
        return;
    }
    if (isValid(dest.first, dest.second) == false) {
        Dest = Pos;
        return;
    }
    if (isUnBlocked(grid, src.first, src.second) == false ||
        isUnBlocked(grid, dest.first, dest.second) == false) {
        Dest = Pos;
        return;
    }
    if (isDestination(src.first, src.second, dest) == true) {
        Dest = Pos;
        return;
    }

    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++)
            m_closedList[i][j] = false;
    int i, j;

    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            m_cellDetails[i][j].f = FLT_MAX;
            m_cellDetails[i][j].g = FLT_MAX;
            m_cellDetails[i][j].h = FLT_MAX;
            m_cellDetails[i][j].parent_i = -1;
            m_cellDetails[i][j].parent_j = -1;
        }
    }
    i = src.first, j = src.second;
    m_cellDetails[i][j].f = 0.0;
    m_cellDetails[i][j].g = 0.0;
    m_cellDetails[i][j].h = 0.0;
    m_cellDetails[i][j].parent_i = i;
    m_cellDetails[i][j].parent_j = j;
    std::set<pPair> openList;
    openList.insert(std::make_pair(0.0, std::make_pair(i, j)));
    bool foundDest = false;

    while (!openList.empty()) {
        pPair p = *openList.begin();
        openList.erase(openList.begin());
        i = p.second.first;
        j = p.second.second;
        m_closedList[i][j] = true;
        if (checkCell(i - 1, j, i, j, m_cellDetails, openList, grid, 1.0f, dest) ||
            checkCell(i + 1, j, i, j, m_cellDetails, openList, grid, 1.0f, dest) ||
            checkCell(i, j - 1, i, j, m_cellDetails, openList, grid, 1.0f, dest) ||
            checkCell(i, j + 1, i, j, m_cellDetails, openList, grid, 1.0f, dest) ||
            checkCell(i - 1, j - 1, i, j, m_cellDetails, openList, grid, 1.414f, dest) ||
            checkCell(i + 1, j - 1, i, j, m_cellDetails, openList, grid, 1.414f, dest) ||
            checkCell(i - 1, j + 1, i, j, m_cellDetails, openList, grid, 1.414f, dest) ||
            checkCell(i + 1, j + 1, i, j, m_cellDetails, openList, grid, 1.414f, dest)) {
            return;
        }
    }
    printf("Failed to find the Destination Cell\n");

    return;
}
