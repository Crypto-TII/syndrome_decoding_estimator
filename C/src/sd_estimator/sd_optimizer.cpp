#include "sd_optimizer.h"

void Optimizer::find(int iterations){
    std::vector<long double> var(dimension);
    std::vector<long double> steps(dimension);
    for (int k = 0; k < iterations; ++k) {

        //Set initial variables and step size
        for (int i = 0; i < dimension; ++i) {
            var[i] = ranges[i].first;
            steps[i] = (ranges[i].second - ranges[i].first) / w_size;
        }

        //find minimum in that interval
        long double value;

        bool stop = false;
        while (!(stop)) {
            if (conditions(var)) {
                value = time(var);
                if (value < min_val) {
                    min_val = value;
                    for (int i = 0; i < dimension; ++i)
                        var_opt[i] = var[i];
                }
            }
            var[0] += steps[0];
            for (int i = 0; i < dimension; ++i) {
                if (var[i] > ranges[i].second) {
                    var[i] = ranges[i].first;
                    if (i != (dimension - 1))
                        var[i + 1] += steps[i + 1];
                    else
                        stop = true;
                } else
                    break;
            }

        }

        //adjust ranges and steps
        for (int i = 0; i < dimension; ++i) {
            if ((var_opt[i] - steps[i]) >= ranges[i].first)
                ranges[i].first = var_opt[i] - steps[i];
            if ((var_opt[i] + steps[i]) <= ranges[i].second)
                ranges[i].second = var_opt[i] + steps[i];
            if ((var_opt[i] - steps[i]) >= 0)
                ranges[i].first = var_opt[i] - steps[i];
        }
    }
}