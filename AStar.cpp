// can/should be edited to also print the path length
#include <cmath>
#include <iostream>
#include <limits>
#include <set>
#include <stack>
#include <utility>
#include <vector>
int ROW;
int COL;

typedef std::pair<int, int> Pair;
typedef std::pair<double, std::pair<int, int>> pPair;

struct cell {
  int pi, pj;
  double f, g, h;
};

bool isValid(int r, int c) {
  return (r >= 0) && (r < ROW) && (c >= 0) && (c < COL);
}

bool isFree(std::vector<std::vector<int>> &g, int r,
            int c) { // g may need to be edited to work properly
  return (g[r][c] == 1);
}

bool destinationReached(int r, int c, Pair d) {
  return (r == d.first) && (c == d.second);
}

double HValue(int r, int c, Pair d) {
  return ((double)std::sqrt(std::pow((r - d.first), 2) +
                            std::pow((c - d.second), 2)));
}

void trace(std::vector<std::vector<cell>> &details, Pair d) {
  int r = d.first;
  int c = d.second;

  std::stack<Pair> Path;

  while (!(details[r][c].pi == r && details[r][c].pj == c)) {
    Path.push(std::make_pair(r, c));
    int tmpr = details[r][c].pi;
    int tmpc = details[r][c].pj;
    r = tmpr;
    c = tmpc;
  }

  Path.push(std::make_pair(r, c));

  while (!Path.empty()) {
    std::pair<int, int> p = Path.top();
    Path.pop();
    std::cout << "(" << p.first << ", " << p.second << ")" << std::endl;
  }

  return;
}

void AStar(std::vector<std::vector<int>> &g, Pair s, Pair d) {
  if (!isValid(s.first, s.second)) {
    std::cout << "Source is not valid" << std::endl;
    return;
  }
  if (!isValid(d.first, d.second)) {
    std::cout << "Destination is not valid" << std::endl;
    return;
  }
  if (!isFree(g, s.first, s.second) || !isFree(g, d.first, d.second)) {
    std::cout << "Source and/or Destination are blocked" << std::endl;
    return;
  }
  if (destinationReached(s.first, s.second, d)) {
    std::cout << "Source equals Destination" << std::endl;
    return;
  }
  std::vector<std::vector<bool>> closed(ROW, std::vector<bool>(COL, false));

  std::vector<std::vector<cell>> details(ROW, std::vector<cell>(COL));
  for (int i = 0; i < ROW; i++) {
    for (int j = 0; j < COL; j++) {
      details[i][j].f = std::numeric_limits<float>::max();
      details[i][j].g = std::numeric_limits<float>::max();
      details[i][j].h = std::numeric_limits<float>::max();
      details[i][j].pi = -1;
      details[i][j].pj = -1;
    }
  }

  details[s.first][s.second].f = 0.0;
  details[s.first][s.second].g = 0.0;
  details[s.first][s.second].h = 0.0;
  details[s.first][s.second].pi = s.first;
  details[s.first][s.second].pj = s.second;

  std::set<pPair> open;
  open.insert(std::make_pair(0.0, std::make_pair(s.first, s.second)));

  bool finished = false;

  while (!open.empty()) {
    pPair p = *open.begin();
    open.erase(open.begin());
    int i = p.second.first;
    int j = p.second.second;
    closed[i][j] = true;
    double g2, h2, f2;

    if (isValid(i - 1, j)) {
      if (destinationReached(i - 1, j, d)) {
        details[i - 1][j].pi = i;
        details[i - 1][j].pj = j;
        std::cout << "Destination found" << std::endl;
        trace(details, d);
        finished = true;
        return;
      } else if (closed[i - 1][j] == false && isFree(g, i - 1, j)) {
        g2 = details[i][j].g + 1;
        h2 = HValue(i - 1, j, d);
        f2 = g2 + h2;
        if (details[i - 1][j].f == std::numeric_limits<float>::max() ||
            details[i - 1][j].f > f2) {
          open.insert(std::make_pair(f2, std::make_pair(i - 1, j)));
          details[i - 1][j].f = f2;
          details[i - 1][j].g = g2;
          details[i - 1][j].h = h2;
          details[i - 1][j].pi = i;
          details[i - 1][j].pj = j;
        }
      }
    }
    if (isValid(i + 1, j)) {
      if (destinationReached(i + 1, j, d)) {
        details[i + 1][j].pi = i;
        details[i + 1][j].pj = j;
        std::cout << "Destination found" << std::endl;
        trace(details, d);
        finished = true;
        return;
      } else if (closed[i + 1][j] == false && isFree(g, i + 1, j)) {
        g2 = details[i][j].g + 1;
        h2 = HValue(i + 1, j, d);
        f2 = g2 + h2;
        if (details[i + 1][j].f == std::numeric_limits<float>::max() ||
            details[i + 1][j].f > f2) {
          open.insert(std::make_pair(f2, std::make_pair(i + 1, j)));
          details[i + 1][j].f = f2;
          details[i + 1][j].g = g2;
          details[i + 1][j].h = h2;
          details[i + 1][j].pi = i;
          details[i + 1][j].pj = j;
        }
      }
    }
    if (isValid(i, j + 1)) {
      if (destinationReached(i, j + 1, d)) {
        details[i][j + 1].pi = i;
        details[i][j + 1].pj = j;
        std::cout << "Destination found" << std::endl;
        trace(details, d);
        finished = true;
        return;
      } else if (closed[i][j + 1] == false && isFree(g, i, j + 1)) {
        g2 = details[i][j].g + 1;
        h2 = HValue(i, j + 1, d);
        f2 = g2 + h2;
        if (details[i][j + 1].f == std::numeric_limits<float>::max() ||
            details[i][j + 1].f > f2) {
          open.insert(std::make_pair(f2, std::make_pair(i, j + 1)));
          details[i][j + 1].f = f2;
          details[i][j + 1].g = g2;
          details[i][j + 1].h = h2;
          details[i][j + 1].pi = i;
          details[i][j + 1].pj = j;
        }
      }
    }
    if (isValid(i, j - 1)) {
      if (destinationReached(i, j - 1, d)) {
        details[i][j - 1].pi = i;
        details[i][j - 1].pj = j;
        std::cout << "Destination found" << std::endl;
        trace(details, d);
        finished = true;
        return;
      } else if (closed[i][j - 1] == false && isFree(g, i, j - 1)) {
        g2 = details[i][j].g + 1;
        h2 = HValue(i, j - 1, d);
        f2 = g2 + h2;
        if (details[i][j - 1].f == std::numeric_limits<float>::max() ||
            details[i][j - 1].f > f2) {
          open.insert(std::make_pair(f2, std::make_pair(i, j - 1)));
          details[i][j - 1].f = f2;
          details[i][j - 1].g = g2;
          details[i][j - 1].h = h2;
          details[i][j - 1].pi = i;
          details[i][j - 1].pj = j;
        }
      }
    }
    if (isValid(i - 1, j + 1)) {
      if (destinationReached(i - 1, j + 1, d)) {
        details[i - 1][j + 1].pi = i;
        details[i - 1][j + 1].pj = j;
        std::cout << "Destination found" << std::endl;
        trace(details, d);
        finished = true;
        return;
      } else if (closed[i - 1][j + 1] == false && isFree(g, i - 1, j + 1)) {
        g2 = details[i][j].g + 1.414;
        h2 = HValue(i - 1, j + 1, d);
        f2 = g2 + h2;
        if (details[i - 1][j + 1].f == std::numeric_limits<float>::max() ||
            details[i - 1][j + 1].f > f2) {
          open.insert(std::make_pair(f2, std::make_pair(i - 1, j + 1)));
          details[i - 1][j + 1].f = f2;
          details[i - 1][j + 1].g = g2;
          details[i - 1][j + 1].h = h2;
          details[i - 1][j + 1].pi = i;
          details[i - 1][j + 1].pj = j;
        }
      }
    }
    if (isValid(i - 1, j - 1)) {
      if (destinationReached(i - 1, j - 1, d)) {
        details[i - 1][j - 1].pi = i;
        details[i - 1][j - 1].pj = j;
        std::cout << "Destination found" << std::endl;
        trace(details, d);
        finished = true;
        return;
      } else if (closed[i - 1][j - 1] == false && isFree(g, i - 1, j - 1)) {
        g2 = details[i][j].g + 1.414;
        h2 = HValue(i - 1, j - 1, d);
        f2 = g2 + h2;
        if (details[i - 1][j - 1].f == std::numeric_limits<float>::max() ||
            details[i - 1][j - 1].f > f2) {
          open.insert(std::make_pair(f2, std::make_pair(i - 1, j - 1)));
          details[i - 1][j - 1].f = f2;
          details[i - 1][j - 1].g = g2;
          details[i - 1][j - 1].h = h2;
          details[i - 1][j - 1].pi = i;
          details[i - 1][j - 1].pj = j;
        }
      }
    }
    if (isValid(i + 1, j + 1)) {
      if (destinationReached(i + 1, j + 1, d)) {
        details[i + 1][j + 1].pi = i;
        details[i + 1][j + 1].pj = j;
        std::cout << "Destination found" << std::endl;
        trace(details, d);
        finished = true;
        return;
      } else if (closed[i + 1][j + 1] == false && isFree(g, i + 1, j + 1)) {
        g2 = details[i][j].g + 1.414;
        h2 = HValue(i + 1, j + 1, d);
        f2 = g2 + h2;
        if (details[i + 1][j + 1].f == std::numeric_limits<float>::max() ||
            details[i + 1][j + 1].f > f2) {
          open.insert(std::make_pair(f2, std::make_pair(i + 1, j + 1)));
          details[i + 1][j + 1].f = f2;
          details[i + 1][j + 1].g = g2;
          details[i + 1][j + 1].h = h2;
          details[i + 1][j + 1].pi = i;
          details[i + 1][j + 1].pj = j;
        }
      }
    }
    if (isValid(i + 1, j - 1)) {
      if (destinationReached(i + 1, j - 1, d)) {
        details[i + 1][j - 1].pi = i;
        details[i + 1][j - 1].pj = j;
        std::cout << "Destination found" << std::endl;
        trace(details, d);
        finished = true;
        return;
      } else if (closed[i + 1][j - 1] == false && isFree(g, i + 1, j - 1)) {
        g2 = details[i][j].g + 1.414;
        h2 = HValue(i + 1, j - 1, d);
        f2 = g2 + h2;
        if (details[i + 1][j - 1].f == std::numeric_limits<float>::max() ||
            details[i + 1][j - 1].f > f2) {
          open.insert(std::make_pair(f2, std::make_pair(i + 1, j + 1)));
          details[i + 1][j - 1].f = f2;
          details[i + 1][j - 1].g = g2;
          details[i + 1][j - 1].h = h2;
          details[i + 1][j - 1].pi = i;
          details[i + 1][j - 1].pj = j;
        }
      }
    }
  }

  if (!finished) {
    std::cout << "Destination not found" << std::endl;
  }

  return;
}

int main() {
  ROW = 9;
  COL = 10;
  std::vector<std::vector<int>> g(9, std::vector<int>());
  g[0] = {1, 0, 1, 1, 1, 1, 0, 1, 1, 1};
  g[1] = {1, 1, 1, 0, 1, 1, 1, 0, 1, 1};
  g[2] = {1, 1, 1, 0, 1, 1, 0, 1, 0, 1};
  g[3] = {0, 0, 1, 0, 1, 0, 0, 0, 0, 1};
  g[4] = {1, 1, 1, 0, 1, 1, 1, 0, 1, 0};
  g[5] = {1, 0, 1, 1, 1, 1, 0, 1, 0, 0};
  g[6] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 1};
  g[7] = {1, 0, 1, 1, 1, 1, 0, 1, 1, 1};
  g[8] = {1, 1, 1, 0, 0, 0, 1, 0, 0, 1};

  Pair source = std::make_pair(8, 0);
  Pair destination = std::make_pair(0, 9);

  AStar(g, source, destination);

  return 0;
}
