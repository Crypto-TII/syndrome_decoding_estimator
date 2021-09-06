#include <algorithm>
#include <vector>
#include <iostream>
#include "sd_stern_optimizer.h"
#include "sd_helper.h"

    bool Stern_Optimizer::conditions(const std::vector<long double> &var) {
        long double l = var[0];
        long double p = var[1];

        if (memory(var)>max_mem)
            return false;
        if (1-kn-l < omega-p || kn<p)
            return false;
        return true;
    };


    long double Stern_Optimizer::time(const std::vector<long double> &var){
        long double l = var[0];
        long double p = var[1];
        long double solutions=max_zero(binomH(1,omega)-(1-kn));

        long double L0 = binomH(kn / 2, p / 2);
        long double L1 = 2 * L0 -l;
        long double Perm = max_zero(binomH(1, omega) - (binomH(kn, p) + binomH(1 - kn - l, omega - p))-solutions);
        return std::max(L0, L1) + Perm;
    }

    void Stern_Optimizer::output(const std::vector<long double> &var) {
        long double l = var[0];
        long double p = var[1];

        long double L0 = binomH(kn / 2, p / 2);
        long double L1 = 2 * L0 -l;
        long double Perm = binomH(1, omega) - (binomH(kn, p) + binomH(1 - kn - l, omega - p));
        std::cout << "\n" << L0 << " " << L1 << " " << Perm<<" ";
    }

    void Stern_Optimizer::output_opt() {
        output(var_opt);
    }

    long double Stern_Optimizer::memory(const std::vector<long double> &var){
        long double l = var[0];
        long double p = var[1];

        long double L0 = binomH(kn / 2, p / 2);
        return L0;
    }

