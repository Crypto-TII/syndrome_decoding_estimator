#ifndef SD_HELPER_H
#define SD_HELPER_H

#include <vector>
#include <math.h>
#include <algorithm>


long double H(long double x);
 long double binomH(long double n, long double m);
 long double max_zero(long double v);
void compute_Hi(int Hi_percision);

long double Hi(long double x);



 long double mo_nn(long double list_size,long double weight);

 long double indyk_motwani_nn(long double list_size,long double weight);

 long double mitm_nn(long double list_size,long double weight, long double length);


 long double time_nn(bool mo, long double list, long double vec_length, long double weight);

 long double time_nn_hybrid(long double list, long double vec_length, long double weight, long double exact);
//prob that two weight w1 vectors of length l sum to weight w2 vector
 long double sum_correct_weight(long double l,long double w1,long double w2);

//nearest neighbor on weight w were lists contain random weight-w1 vectors
 long double time_nn_w1(long double lam, long double l, long double w,long double w1, long double alpha);

//reps of weight p vector as sum of two p1 vectors of length l
 long double reps(long double p, long double p1, long double l);

#endif //SD_HELPER_H
