#ifndef SD_BOTH_MAY_DEPTH_2_H
#define SD_BOTH_MAY_DEPTH_2_H

#include "sd_optimizer.h"
class BM_D2_Optimizer : public Optimizer{

public:
    BM_D2_Optimizer(int windows_size,bool nn_mo) : Optimizer(5, windows_size) {
        variant=nn_mo;
    }


    bool conditions(const std::vector<long double> &var) override;
    long double time(const std::vector<long double> &var) override;
    void output(const std::vector<long double> &var);
    long double memory(const std::vector<long double> &var) override;

protected:
    bool variant;


};


#endif //SD_BOTH_MAY_DEPTH_2_H
