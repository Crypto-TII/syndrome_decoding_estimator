
#include "sd_optimizer.h"


class BJMM_Optimizer : public Optimizer {

public:
    BJMM_Optimizer(int windows_size) : Optimizer(4, windows_size) {

    }


    bool conditions(const std::vector<long double> &var) override;

    long double time(const std::vector<long double> &var) override;

    void output(const std::vector<long double> &var);

    void output_opt();

    long double memory(const std::vector<long double> &var)override;


};
