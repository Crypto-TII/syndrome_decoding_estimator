#include "test_sd_estimator.h"
#include "../../main/constants.h"
#include "../../src/sd_estimator/sd_estimator.h"
#include "../../src/sd_estimator/sd_helper.h"

int test_sd_estimator_bm_d2() {
    compute_Hi(7);
    long double rate = 0.42;
    long double omega = Hi(1 - rate);
    float *time = new float;
    float *mem = new float;
    opt_bm_d2(rate, omega, 7, 300, *time, *mem, 1, true);

    if ((*time)<0.0982 and (*mem)<0.0718 and (*time)>0.097 and (*mem)>0.07)
        return TEST_SUCCESS;
    return TEST_FAILURE;
}

int test_sd_estimator_stern() {
    compute_Hi(7);
    long double rate = 0.445;
    long double omega = Hi(1 - rate);
    float *time = new float;
    float *mem = new float;
    opt_stern(rate, omega, 10, 150, *time, *mem, 1);

    if ((*time)<0.1166 and (*mem)<0.034 and (*time)>0.0116 and (*mem)>0.033)
        return TEST_SUCCESS;
    return TEST_FAILURE;
}


int test_sd_estimator_dumer() {
    compute_Hi(7);
    long double rate = 0.445;
    long double omega = Hi(1 - rate);
    float *time = new float;
    float *mem = new float;
    opt_dumer(rate, omega, 10, 150, *time, *mem, 1);

    if ((*time)<0.1163 and (*mem)<0.0387 and (*time)>0.0116 and (*mem)>0.038)
        return TEST_SUCCESS;
    return TEST_FAILURE;
}


int test_sd_estimator_bjmm() {
    compute_Hi(7);
    long double rate = 0.426;
    long double omega = Hi(1 - rate);
    float *time = new float;
    float *mem = new float;
    opt_bjmm(rate, omega, 10, 150, *time, *mem, 1);

    if ((*time)<0.102 and (*mem)<0.079 and (*time)>0.101 and (*mem)>0.078)
        return TEST_SUCCESS;
    return TEST_FAILURE;
}

int test_sd_estimator_mo() {
    compute_Hi(7);
    long double rate = 0.43;
    long double omega = Hi(1 - rate);
    float *time = new float;
    float *mem = new float;
    opt_mo(rate, omega, 10, 150, *time, *mem, 1,true);

    if ((*time)<0.097 and (*mem)<0.088 and (*time)>0.095 and (*mem)>0.08)
        return TEST_SUCCESS;
    return TEST_FAILURE;
}

int test_sd_estimator_ball_collision() {
    compute_Hi(7);
    long double rate = 0.446;
    long double omega = Hi(1 - rate);
    float *time = new float;
    float *mem = new float;
    opt_ball_collision(rate, omega, 7, 150, *time, *mem, 1);

    if ((*time)<0.1163 and (*mem)<0.0358 and (*time)>0.116 and (*mem)>0.0357)
        return TEST_SUCCESS;
    return TEST_FAILURE;
}
