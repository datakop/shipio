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
    pair <vector<pair<double, double> >, pair <pair<double, double>, pair<double, double> > >  main(const cocos2d::Size screenSize,
                                       const cocos2d::Size shipSize);

private:
    double screen_height, screen_width;
    double ship_x, ship_y;
    int height;
    int width;

    double new_screen_height;
    double new_screen_width;

    double delta_y;
    double delta_x;

    double square_y;
    double square_x;
    int type;

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
    vector <struct point > convert_vector(vector <struct point>);
    int now_type(struct point A, struct point B);
    pair <float, float> get_coordinte(int number, int x, int y);
};


struct point {
    int x, y;

    point(int a, int b) {
        x = a;
        y = b;
    }
};


#endif //SHIPIO_MAPGENERATOR_H
