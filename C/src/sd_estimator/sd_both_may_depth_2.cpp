#include <algorithm>
#include <vector>
#include <iostream>

#include "sd_helper.h"
#include "sd_both_may_depth_2.h"

bool BM_D2_Optimizer::conditions(const std::vector<long double> &var) {
    long double l = var[0];
    long double p = var[1];
    long double d1 = var[2];
    long double w1 = var[3];
    long double wd1 = var[4];

    long double p1 = p / 2 + d1;
    long double w11 = w1 / 2 + wd1;

    long double reps1 = reps(p, p1, kn) + reps(w1, w11, l);


    if (
            reps1 < l || p > omega
            || l > 1 - kn)
        return false;
    if (1 - kn < omega - p || kn - p < d1 || l - w1 < wd1)
        return false;
    if (
            kn < p || l - w1 < w11 - w1 / 2 || kn - p < p1 - p / 2 || l <= w1 || p1 > kn
                                                                                      - p / 2 ||
            w11 > l - w1 / 2 | omega - w1 - p < 0)
        return false;
    if (
            memory(var)
            > max_mem)
        return false;
    return true;
};


long double BM_D2_Optimizer::time(const std::vector<long double> &var) {
    long double l = var[0];
    long double p = var[1];
    long double d1 = var[2];
    long double w1 = var[3];
    long double wd1 = var[4];
    long double solutions = max_zero(binomH(1, omega) - (1 - kn));

    long double p1 = p / 2 + d1;
    long double w11 = w1 / 2 + wd1;


    long double L0 = binomH(kn / 2., p1 / 2.);
    long double T1 = time_nn(variant, L0, l, w11); //mitm_nn(L0,w11,l);//
    long double L1 = binomH(kn, p1) - l + binomH(l, w11);
    long double T2 = time_nn(variant, L1, 1 - kn - l, omega - p - w1);
    long double Perm = max_zero(
            binomH(1, omega) - (binomH(kn, p) + binomH(l, w1) + binomH(1 - kn - l, omega - p - w1)) - solutions);
    return
            std::max(T1, T2
            ) +
            Perm;
}

void BM_D2_Optimizer::output(const std::vector<long double> &var) {
    long double l = var[0];
    long double p = var[1];
    long double d1 = var[2];
    long double w1 = var[3];
    long double wd1 = var[4];
    long double solutions = max_zero(binomH(1, omega) - (1 - kn));

    long double p1 = p / 2 + d1;
    long double w11 = w1 / 2 + wd1;


    long double L0 = binomH(kn / 2., p1 / 2.);
    long double T1 = mitm_nn(L0, w11, l);//time_nn(variant,L0,l,w11);
    long double L1 = binomH(kn, p1) - l + binomH(l, w11);

    long double T2 = time_nn(variant, L1, 1 - kn - l, omega - p - w1);
    long double Perm = binomH(1, omega) - (binomH(kn, p) + binomH(l, w1) + binomH(1 - kn - l, omega - p - w1));
    std::cout << "\n" << T1 << " " << T2 << " " << L0 << " " << L1 << " " << Perm << " " << p1 << " " << w1 << " " << l;

}

long double BM_D2_Optimizer::memory(const std::vector<long double> &var) {
    long double l = var[0];
    long double p = var[1];
    long double d1 = var[2];
    long double w1 = var[3];
    long double wd1 = var[4];

    long double p1 = p / 2 + d1;
    long double w11 = w1 / 2 + wd1;


    long double L0 = binomH(kn / 2., p1 / 2.);
    long double L1 = binomH(kn, p1) - l + binomH(l, w11);

    return
            std::max(L0, L1
            );
}