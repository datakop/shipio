#ifndef SHIPIO_MAPGENERATOR_H
#define SHIPIO_MAPGENERATOR_H

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <ctime>
#include <deque>

#include "cocos2d.h"


#define mp make_pair
#define f first
#define s second


using namespace std;


struct point;


class MapGenerator {
public:
    vector<pair<double, double> > main(const cocos2d::Size screenSize,
                                       const cocos2d::Size shipSize);

private:
    double screen_height = 780.0, screen_weight = 1200.0;
    double ship_x = 50, ship_y = 50;
    int height = screen_height / ship_y - 1;
    int weight = screen_weight / ship_x - 1;
    double new_screen_height = height * ship_y;
    double new_screen_weight = weight * ship_x;

    double delta_y = new_screen_height / height / 2;
    double delta_x = new_screen_weight / weight / 2;

    double square_y = new_screen_height / height;
    double square_x = new_screen_weight / weight;
    
    vector<vector<int> > A;
    vector<vector<int> > used;

    pair<vector<vector<int> >, pair<vector<struct point>, int> >
            dfs(struct point start_point,
                struct point end_point,
                struct point now_point,
                vector<vector<int> > now_state_map,
                int depth,
                vector<struct point> answer);

    int bfs(struct point now_point,
            struct point end_point,
            vector<vector<int> > vect);

    pair<double, double> get_square_center_coordinates(struct point A);

    void print_point(struct point p);

    void print_result(vector<vector<int> > A);

    void print_vect(vector<struct point> A);

    void print_vect_double(vector<pair<double, double> > A);

    int get_rand(int range);

    void get_zeros(vector<vector<int> > &A);
};


struct point {
    int x, y;

    point(int a, int b) {
        x = a;
        y = b;
    }
};


#endif //SHIPIO_MAPGENERATOR_H
