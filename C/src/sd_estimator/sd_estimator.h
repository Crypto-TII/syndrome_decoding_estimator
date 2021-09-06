#ifndef SD_ESTIMATOR_H
#define SD_ESTIMATOR_H

extern "C" {

void
opt_bm_d2(float rate, float omega, int window_size, int iterations, float &time, float &mem, float max_mem,
          bool variant);

void
opt_mo(float rate, float omega, int window_size, int iterations, float &time, float &mem, float max_mem, bool variant);

void
opt_bjmm(float rate, float omega, int window_size, int iterations, float &time, float &mem, float max_mem);

void
opt_ball_collision(float rate, float omega, int window_size, int iterations, float &time, float &mem, float max_mem);

void opt_stern(float rate, float omega, int window_size, int iterations, float &time, float &mem, float max_mem);

void
opt_dumer(float rate, float omega, int window_size, int iterations, float &time, float &mem, float max_mem);

void
opt_prange(float rate, float omega, int window_size, int iterations, float &time, float &mem, float max_mem);

void initialize();
}


#endif //SD_ESTIMATOR_H
