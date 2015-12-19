#include "MapGenerator.h"


using namespace std;

vector<pair<double, double> >  MapGenerator::main(const cocos2d::Size screenSize,
                                                  const cocos2d::Size shipSize) {


    screen_height = screenSize.height;
    screen_width = screenSize.width;
    ship_x = max(shipSize.width, shipSize.height);
    ship_y = max(shipSize.width, shipSize.height);


    height = (int) (screen_height / ship_y);
    width = (int) (screen_width / ship_x);

    new_screen_height = ship_y * height;
    new_screen_width = ship_x * width;

    delta_y = new_screen_height / height / 2.0;
    delta_x = new_screen_width / width / 2.0;

    square_y = new_screen_height / height;
    square_x = new_screen_width / width;



    CCLOG("WIDTH AND WIDTH %d %d", width, height);

    A.resize(height);
    used.resize(height);
    for (int i = 0; i < height; i++) {
        A[i].resize(width, 0);
        used[i].resize(width);
    }
    srand(time(NULL));
    int pair_side = get_rand(1000) % 2;
    struct point start_point(0, 0);
    struct point end_point(0, 0);
    if (pair_side == 0) // get top
    {
        //struct point start_point(0, );
        start_point.x = 0;
        start_point.y = get_rand(width);

        //struct point end_point(weight - 1, );
        end_point.x = height - 1;
        end_point.y = get_rand(width);
    }
    else if (pair_side == 1) // get bottom
    {
        //struct point start_point(, 0);
        //struct point end_point(, weight - 1);
        start_point.x = get_rand(height);
        start_point.y = 0;

        end_point.x = get_rand(height);
        end_point.y = width - 1;
    }
    print_point(start_point);
    print_point(end_point);
    //exit(0);
    vector<vector<int> > answer;
    vector<vector<int> > now;
    vector<struct point> seq;
    vector <struct point> old_seq;
    now.resize(height);
    for (int i = 0; i < height; i++)
        now[i].resize(width, 0);
    //print_result(now);
    int max_depth = 0;
    while (max_depth < 45) {
        get_zeros(now);
        pair<vector<vector<int> >, pair<vector<struct point>, int> > A;
        vector<struct point> new_seq;
        new_seq.push_back(start_point);
        A = dfs(start_point, end_point, start_point, now, 0, new_seq);
        //printf("ALL GOOD");
        //print_result(A.f);
        if (A.s.s > max_depth) {
            max_depth = A.s.s;
            answer = A.f;
            seq =  convert_vector(A.s.f);
            old_seq = A.s.f;
        }
    }
    print_vect(seq);
    //print_vect(old_seq);
    printf("\n\n");
    //print_result(answer);
    vector<pair<double, double> > B;
    for (int i = 0; i < seq.size(); i++)
        B.push_back(get_square_center_coordinates(seq[i]));
    print_vect_double(B);

    if (pair_side == 0)
        type = 3;
    else if(pair_side == 1)
        type = 1;
    vector <pair <float, float> > first_line;
    vector <pair<float, float> > second_line;
    for (int i = 0; i < seq.size(); i++)
    {
        if (first_line.size() == 0) {
            if (type == 1)
            {
               // first_line.push_back();
                //second_line.push_back();
            }
            else if (type == 3)
            {
                //first_line.push_back();
                //second_line.push_back();
            }
        }
    }

    return B;
}


int MapGenerator::get_rand(int range) {
    return (int) (range * (double) (rand() / (RAND_MAX + 1.0)));
}


pair<double, double>
MapGenerator::get_square_center_coordinates(struct point A) {
    double x = (double) A.x;
    double y = (double) A.y;
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
        if (y + 1 < width && !vect[x][y + 1]) {
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
    if (y + 1 < width && now_state_map[x][y + 1] == 0 && bfs(point(x, y + 1), end_point, now_state_map))
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

vector<struct point > MapGenerator::convert_vector(vector<point> vector1) {
    vector <struct point > result;
    for (int i = 0; i < vector1.size(); i++)
    {
        struct point A(vector1[i].y, height - vector1[i].x-1);
        result.push_back(A);
    }
    return result;
}

int MapGenerator::now_type(struct point A, struct point B) {
    int x1 = A.x;
    int y1 = A.y;
    int x2 = B.x;
    int y2 = B.y;
    if (x1 == x2)
    {
        if (y2 > y1)
            return 4;
        else
            return 3;
    }
    else if(y1 == y2)
    {
        if (x2 > x1)
            return 1;
        else
            return 2;
    }
}

pair<float, float> MapGenerator::get_coordinte(int number, int x, int y) {
    if (number == 1)
    {
        return mp(x * square_x, y * square_y);
    }
    else if (number == 2)
    {
        return mp(x * square_x, y * square_y + square_y);
    }
    else if (number == 3)
    {
        return mp(x * square_x + square_x, y * square_y + square_y);
    }
    else if (number == 4)
    {
        return mp(x * square_x + square_x, y * square_y);
    }
}
