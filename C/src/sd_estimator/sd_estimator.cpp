
#include "sd_estimator.h"
#include "sd_both_may_depth_2.h"
#include "sd_ball_collision_optimizer.h"
#include "sd_may_ozerov_optimizer.h"
#include "sd_dumer_optimizer.h"
#include "sd_stern_optimizer.h"
#include "sd_bjmm_optimizer.h"

#include "sd_helper.h"
#include <functional>
#include <iostream>
#include <utility>

template<class Optimizer>
std::pair<long double, long double>
optimize(Optimizer &Dec, long double rate, long double omega, int iterations, long double max_mem = 1) {

    Dec.set_rate(rate);
    Dec.set_omega(omega);
    Dec.set_max_mem(max_mem);

    long double interval[10];
    for (int i = 0; i < 10; ++i)
        interval[i] = 0.128715;

    for (int i = 0; i < iterations; ++i) {
        Dec.find(1);
        for (int j = 0; j < Dec.get_dimension(); ++j) {
            long double beg = Dec.get_var_opt(j) - interval[j] / 2;
            long double end = Dec.get_var_opt(j) + interval[j] / 2;
            if (beg <= 0) beg = 0.00001;
            Dec.set_ranges(beg, end, j);
        }

        for (int j = 0; j < Dec.get_dimension(); ++j) {
            interval[j] /= 1.04;
            if (interval[j] < 0.0001) {
                interval[j] = std::max(Dec.get_var_opt(j), (long double) 0.0001);
            }
        }
    }
    std::pair<long double, long double> out;
    out.first = Dec.get_min_val();
    out.second = Dec.get_memory_opt();
    return out;
}

extern "C" {
void
opt_bm_d2(float rate, float omega, int window_size, int iterations, float &time, float &mem, float max_mem,
          bool variant) {
    BM_D2_Optimizer Dec{window_size, variant};

    Dec.set_ranges(0, 0.05, 0);
    Dec.set_ranges(0, omega, 1);
    Dec.set_ranges(0, 0.2, 2);
    Dec.set_ranges(0, 0.2, 3);
    Dec.set_ranges(0, 0.2, 4);

    std::pair<long double, long double> a = optimize(Dec, rate, omega, iterations, max_mem);
    mem = a.second;
    time = a.first;
}


void
opt_mo(float rate, float omega, int window_size, int iterations, float &time, float &mem, float max_mem, bool variant) {
    MO_Optimizer Dec{window_size, variant};

    Dec.set_ranges(0, 0.4, 0);
    Dec.set_ranges(0, omega, 1);
    Dec.set_ranges(0, 0.1, 2);
    Dec.set_ranges(0, 0.1, 3);

    std::pair<long double, long double> a = optimize(Dec, rate, omega, iterations, max_mem);
    mem = a.second;
    time = a.first;
}

void
opt_bjmm(float rate, float omega, int window_size, int iterations, float &time, float &mem, float max_mem) {
    BJMM_Optimizer Dec{window_size};

    Dec.set_ranges(0, 0.4, 0);
    Dec.set_ranges(0, omega, 1);
    Dec.set_ranges(0, 0.1, 2);
    Dec.set_ranges(0, 0.1, 3);

    std::pair<long double, long double> a = optimize(Dec, rate, omega, iterations, max_mem);
    mem = a.second;
    time = a.first;
}

void
opt_ball_collision(float rate, float omega, int window_size, int iterations, float &time, float &mem, float max_mem) {

    Ball_Collision_Optimizer Dec{window_size};

    Dec.set_ranges(0, 0.5, 0);
    Dec.set_ranges(0, omega, 1);
    Dec.set_ranges(0, omega, 2);
    std::pair<long double, long double> a = optimize(Dec, rate, omega, iterations, max_mem);
    mem = a.second;
    time = a.first;
}

void opt_stern(float rate, float omega, int window_size, int iterations, float &time, float &mem, float max_mem) {

    Stern_Optimizer Dec{window_size};

    Dec.set_ranges(0, 0.5, 0);
    Dec.set_ranges(0, omega, 1);
    std::pair<long double, long double> a = optimize(Dec, rate, omega, iterations, max_mem);
    mem = a.second;
    time = a.first;
}

void
opt_dumer(float rate, float omega, int window_size, int iterations, float &time, float &mem, float max_mem) {
    Dumer_Optimizer Dec{window_size};

    Dec.set_ranges(0, 0.5, 0);
    Dec.set_ranges(0, omega, 1);

    std::pair<long double, long double> a = optimize(Dec, rate, omega, iterations, max_mem);
    mem = a.second;
    time = a.first;
}

void
opt_prange(float rate, float omega, int window_size, int iterations, float &time, float &mem, float max_mem) {
    mem = 0;
    time = binomH(1, omega) - binomH(1 - rate, omega);
}


void initialize() {
    compute_Hi(7);
}
}

int old_main_func() {


    int w_size = 10;


    compute_Hi(7);
    long double rate = 0.42;
    long double omega = Hi(1 - rate);
    float *time = new float;
    float *mem = new float;
    opt_bm_d2(rate, omega, w_size, 300, *time, *mem, 1, false);
    std::cout << "\n\njuppy " << *time << "   " << *mem << "\n\n";

    BM_D2_Optimizer Dec{w_size, true};

    std::vector<long double> var(5);
    Dec.set_rate(rate);
    Dec.set_omega(omega);
    var[0] = 0.1553;
    var[1] = 0.0373;
    var[2] = 0.02645 - var[1] / 2;
    var[3] = 0.0197;
    var[4] = 0.01765 - var[3] / 2;

    return 1;

}
