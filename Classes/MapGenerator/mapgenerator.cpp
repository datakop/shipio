#include "MapGenerator.h"


using namespace std;

vector<pair<double, double> >  MapGenerator::main(const cocos2d::Size screenSize,
                                                  const cocos2d::Size shipSize) {

    this->screen_weight = screenSize.width - 100;
    this->screen_height = screenSize.height - 100;

    this->ship_x = shipSize.width;
    this->ship_y = shipSize.height;

    //printf("%d %d %lf %lf", height, weight, new_screen_height, new_screen_weight);
    //exit(0);
    //printf("%lf %lf %lf %lf", delta_x, delta_y, square_x, square_y);
    //exit(0);
    A.resize(height);
    used.resize(height);
    for (int i = 0; i < height; i++) {
        A[i].resize(weight, 0);
        used[i].resize(weight);
    }
    srand(time(NULL));
    int pair_side = get_rand(1000) % 2;
    struct point start_point(0, 0);
    struct point end_point(0, 0);
    if (pair_side == 0) // get top
    {
        //struct point start_point(0, );
        start_point.x = 0;
        start_point.y = get_rand(weight);

        //struct point end_point(weight - 1, );
        end_point.x = height - 1;
        end_point.y = get_rand(weight);
    }
    else if (pair_side == 1) // get bottom
    {
        //struct point start_point(, 0);
        //struct point end_point(, weight - 1);
        start_point.x = get_rand(height);
        start_point.y = 0;

        end_point.x = get_rand(height);
        end_point.y = weight - 1;
    }
    //print_point(start_point);
    //print_point(end_point);
    //exit(0);
    vector<vector<int> > answer;
    vector<vector<int> > now;
    vector<struct point> seq;
    now.resize(height);
    for (int i = 0; i < height; i++)
        now[i].resize(weight, 0);
    //print_result(now);
    int max_depth = 0;
    while (max_depth < 10) {
        get_zeros(now);
        pair<vector<vector<int> >, pair<vector<struct point>, int> > A;
        vector<struct point> new_seq;
        A = dfs(start_point, end_point, start_point, now, 0, new_seq);
        //printf("ALL GOOD");
        //print_result(A.f);
        if (A.s.s > max_depth) {
            max_depth = A.s.s;
            answer = A.f;
            seq = A.s.f;
        }
    }
    print_vect(seq);
    printf("\n\n");
    //print_result(answer);
    vector<pair<double, double> > B;
    for (int i = 0; i < seq.size(); i++)
        B.push_back(get_square_center_coordinates(seq[i]));
    print_vect_double(B);

    return B;
}


int MapGenerator::get_rand(int range) {
    return (int) (range * (double) (rand() / (RAND_MAX + 1.0)));
}


pair<double, double>
MapGenerator::get_square_center_coordinates(struct point A) {
    double x = (double) A.y;
    double y = (double) (height - A.x);
    return mp(x * square_x + delta_x, y * square_y + delta_y);
}


int
MapGenerator::bfs(struct point now_point, struct point end_point, vector<vector<int> > vect) {
    if (now_point.x == end_point.x && now_point.y == end_point.y)
        return 1;
    deque<struct point> S;
    S.push_front(now_point);
    while (!S.empty()) {
        struct point now_point = S.back();
        int x = now_point.x;
        int y = now_point.y;
        if (x + 1 < height && !vect[x + 1][y]) {
            S.push_front(point(x + 1, y));
            vect[x + 1][y] = 1;
        }
        if (x - 1 >= 0 && !vect[x - 1][y]) {
            S.push_front(point(x - 1, y));
            vect[x - 1][y] = 1;
        }
        if (y - 1 >= 0 && !vect[x][y - 1]) {
            S.push_front(point(x, y - 1));
            vect[x][y - 1] = 1;
        }
        if (y + 1 < weight && !vect[x][y + 1]) {
            S.push_front(point(x, y + 1));
            vect[x][y + 1] = 1;
        }
        S.pop_back();
    }
    return vect[end_point.x][end_point.y];
}

pair<vector<vector<int> >, pair<vector<struct point>, int> >
MapGenerator::dfs(struct point start_point,
                  struct point end_point,
                  struct point now_point,
                  vector<vector<int> > now_state_map,
                  int depth,
                  vector<struct point> answer) {
    now_state_map[now_point.x][now_point.y] = depth + 1;
    //print_result(now_state_map);
    //print_point(start_point);
    //print_point(end_point);
    //print_point(now_point);
    if ((now_point.x == end_point.x) && (now_point.y == end_point.y))
        return mp(now_state_map, mp(answer, depth));

    vector<struct point> possible_points;
    int x = now_point.x;
    int y = now_point.y;
    if (x + 1 < height && now_state_map[x + 1][y] == 0 && bfs(point(x + 1, y), end_point, now_state_map))
        possible_points.push_back(point(x + 1, y));
    if (x - 1 >= 0 && now_state_map[x - 1][y] == 0 && bfs(point(x - 1, y), end_point, now_state_map))
        possible_points.push_back(point(x - 1, y));
    if (y + 1 < weight && now_state_map[x][y + 1] == 0 && bfs(point(x, y + 1), end_point, now_state_map))
        possible_points.push_back(point(x, y + 1));
    if (y - 1 >= 0 && now_state_map[x][y - 1] == 0 && bfs(point(x, y - 1), end_point, now_state_map))
        possible_points.push_back(point(x, y - 1));
    //print_vect(possible_points);
    int pos = get_rand(1000) % possible_points.size();
    //printf("%d\n", pos);
    //print_point(point(possible_points[pos].x, possible_points[pos].y));
    answer.push_back(point(possible_points[pos].x, possible_points[pos].y));
    return dfs(start_point, end_point, point(possible_points[pos].x, possible_points[pos].y), now_state_map, depth + 1,
               answer);
}

void MapGenerator::get_zeros(vector<vector<int> > &A) {
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < A[i].size(); j++) {
            A[i][j] = 0;
        }
    }
}

void MapGenerator::print_result(vector<vector<int> > A) {
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < A[i].size(); j++) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

void MapGenerator::print_vect(vector<struct point> A) {
    for (int i = 0; i < A.size(); i++)
        printf("%d %d   ", A[i].x, A[i].y);
    printf("\n");
}

void MapGenerator::print_vect_double(vector<pair<double, double> > A) {
    for (int i = 0; i < A.size(); i++)
        printf("%lf %lf  ", A[i].f, A[i].s);
    printf("\n\n");
}

void MapGenerator::print_point(struct point p) {
    printf("%d %d\n", p.x, p.y);
}
