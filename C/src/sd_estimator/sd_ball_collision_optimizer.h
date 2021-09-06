#ifndef SD_BALL_COLLISION_OPTIMIZER_H
#define SD_BALL_COLLISION_OPTIMIZER_H


#include "sd_optimizer.h"


class Ball_Collision_Optimizer : public Optimizer {

public:
    Ball_Collision_Optimizer(int windows_size) : Optimizer(3, windows_size) {

    }


    bool conditions(const std::vector<long double> &var) override;


    long double time(const std::vector<long double> &var) override;

    void output(const std::vector<long double> &var);

    void output_opt();

    long double memory(const std::vector<long double> &var)override;



};

#endif //SD_BALL_COLLISION_OPTIMIZER_H
