#include <algorithm>
#include <vector>
#include <iostream>
#include "sd_helper.h"
#include "sd_ball_collision_optimizer.h"


bool Ball_Collision_Optimizer::conditions(const std::vector<long double> &var) {
    long double l = var[0];
    long double p = var[1];
    long double pl = var[2];

    if (memory(var) > max_mem)
        return false;
    if (1 - kn - l < omega - p - pl || kn < p || l < pl || p+pl>=omega)
        return false;
    return true;
};


long double Ball_Collision_Optimizer::time(const std::vector<long double> &var) {
    long double l = var[0];
    long double p = var[1];
    long double pl = var[2];
    long double solutions = max_zero(binomH(1, omega) - (1 - kn));
    long double L0 = binomH(kn / 2, p / 2) + binomH(l / 2, pl / 2);
    long double L1 = 2 * L0 - l;
    long double Perm = max_zero(
            binomH(1, omega) - (binomH(kn, p) + binomH(l, pl) + binomH(1 - kn - l, omega - p - pl)) - solutions);
    return std::max(L0, L1) + Perm;
}

void Ball_Collision_Optimizer::output(const std::vector<long double> &var) {
    long double l = var[0];
    long double p = var[1];
    long double pl = var[2];

    long double L0 = binomH(kn / 2, p / 2) + binomH(l / 2, pl / 2);
    long double L1 = 2 * L0 - l;
    long double Perm = binomH(1, omega) - (binomH(kn, p) + binomH(l, pl) + binomH(1 - kn - l, omega - p - pl));
    std::cout << "\n" << L0 << " " << L1 << " " << Perm << " ";
}

void Ball_Collision_Optimizer::output_opt() {
    output(var_opt);
}

long double Ball_Collision_Optimizer::memory(const std::vector<long double> &var) {
    long double l = var[0];
    long double p = var[1];
    long double pl = var[2];

    long double L0 = binomH(kn / 2, p / 2) + binomH(l / 2, pl / 2);
    return L0;
}

