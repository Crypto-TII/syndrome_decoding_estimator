
#include <algorithm>
#include <vector>
#include "sd_may_ozerov_optimizer.h"
#include "sd_helper.h"


bool MO_Optimizer::conditions(const std::vector<long double> &var) {
    long double l = var[0];
    long double p = var[1];
    long double d1 = var[2];
    long double d2 = var[3];

    long double p2 = p / 2 + d2;
    long double p1 = p2 / 2 + d1;
    long double reps1 = reps(p2, p1, kn + l);
    long double reps2 = reps(p, p2, kn + l);


    if (reps2 < l || reps2 < reps1 || p > omega)
        return false;
    if (1 - kn - l < omega - p || kn + l - p < d2 || kn + l - p < d1)
        return false;
    if (kn + l < p || p2 > kn + l - p / 2 || p1 > kn + l - p2 / 2)
        return false;
    if (memory(var) > max_mem)
        return false;
    return true;
};


long double MO_Optimizer::time(const std::vector<long double> &var) {
    long double l = var[0];
    long double p = var[1];
    long double d1 = var[2];
    long double d2 = var[3];
    long double p2 = p / 2 + d2;
    long double p1 = p2 / 2 + d1;
    long double solutions = max_zero(binomH(1, omega) - (1 - kn));

    long double reps1 = reps(p2, p1, kn + l);
    long double reps2 = reps(p, p2, kn + l);

    long double L0 = binomH((kn + l) / 2, p1 / 2);
    long double T1 = std::max(2 * L0 - reps1, L0);
    long double L1 = binomH((kn + l), p1) - reps1;
    long double T2 = std::max(2 * L1 - (l - reps1), L1);
    long double L2 = binomH((kn + l), p2) - l;
    long double T3 = time_nn(variant, L2, 1 - kn - l, omega - p);
    long double Perm = max_zero(binomH(1, omega) - (binomH(kn + l, p) + binomH(1 - kn - l, omega - p)) - solutions);
    return std::max(std::max(T1, T2), T3) + Perm;
}

void MO_Optimizer::output(const std::vector<long double> &var) {
    long double l = var[0];
    long double p = var[1];
    long double d1 = var[2];
    long double d2 = var[3];

    long double p2 = p / 2 + d2;
    long double p1 = p2 / 2 + d1;
    long double reps1 = reps(p2, p1, kn + l);
    long double reps2 = reps(p, p2, kn + l);

    long double L0 = binomH((kn + l) / 2, p1 / 2);
    long double T1 = std::max(2 * L0 - reps1, L0);
    long double L1 = binomH((kn + l), p1) - reps1;
    long double T2 = std::max(2 * L1 - (l - reps1), L1);
    long double L2 = binomH((kn + l), p2) - l;
    long double T3 = time_nn(variant, L2, 1 - kn - l, omega - p);
    long double Perm = binomH(1, omega) - (binomH(kn + l, p) + binomH(1 - kn - l, omega - p));

}

void MO_Optimizer::output_opt() {
    output(var_opt);
}

long double MO_Optimizer::memory(const std::vector<long double> &var) {
    long double l = var[0];
    long double p = var[1];
    long double d1 = var[2];
    long double d2 = var[3];

    long double p2 = p / 2 + d2;
    long double p1 = p2 / 2 + d1;
    long double reps1 = reps(p2, p1, kn + l);

    long double L0 = binomH((kn + l) / 2, p1 / 2);
    long double L1 = binomH((kn + l), p1) - reps1;
    long double L2 = binomH((kn + l), p2) - l;

    return std::max(std::max(L0, L1), L2);
}


