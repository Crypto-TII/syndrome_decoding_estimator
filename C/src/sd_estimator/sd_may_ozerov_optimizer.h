#ifndef SD_MAY_OZEROV_OPTIMIZER_H
#define SD_MAY_OZEROV_OPTIMIZER_H

#include "sd_optimizer.h"

class MO_Optimizer : public Optimizer {

public:
    MO_Optimizer(int windows_size, bool nn_mo) : Optimizer(4, windows_size) {
        variant = nn_mo;
    }

    bool conditions(const std::vector<long double> &var) override;

    long double time(const std::vector<long double> &var) override;

    void output(const std::vector<long double> &var);

    void output_opt();

    long double memory(const std::vector<long double> &var)override;

protected:
    bool variant;

};

#endif //SD_MAY_OZEROV_OPTIMIZER_H
