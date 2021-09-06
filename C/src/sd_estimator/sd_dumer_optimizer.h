#ifndef SD_DUMER_OPTIMIZER_H
#define SD_DUMER_OPTIMIZER_H

#include "sd_optimizer.h"


class Dumer_Optimizer : public Optimizer {

public:
    Dumer_Optimizer(int windows_size) : Optimizer(2, windows_size) {

    }

    bool conditions(const std::vector<long double> &var) override;

    long double time(const std::vector<long double> &var) override;

    void output(const std::vector<long double> &var);

    void output_opt();

    long double memory(const std::vector<long double> &var)override;


};

#endif //SD_DUMER_OPTIMIZER_H
