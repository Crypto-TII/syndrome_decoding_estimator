#include "sd_helper.h"
std::vector<std::pair<long double, long double> > Hi_lookup;

long double Hi(long double x) {
    if (x == 0)
        return 0;
    std::vector<std::pair<long double, long double> >::iterator it = std::lower_bound(Hi_lookup.begin(),
                                                                                      Hi_lookup.end(),
                                                                                      x,
                                                                                      [](std::pair<long double, long double> g1,
                                                                                         const long double g2) {
                                                                                          if (g1.first < g2)
                                                                                              return true;
                                                                                          return false;
                                                                                      });
    return (*it).second;
}

long double H(long double x) {
    if (x == 0 || x == 1)
        return 0;
    return -x * log2(x) - (1 - x) * log2(1 - x);
}
 long double binomH(long double n, long double m) {
    return n*H(m / n);
}

 long double max_zero(long double v)
{
    return std::max((long double )0, v);
}

void compute_Hi(int Hi_percision) {
    //compute Hi
    Hi_lookup.resize(pow(10, Hi_percision));
    long double s = 1.0 / pow(10, Hi_percision);
    Hi_lookup[0].first = 0;
    Hi_lookup[0].second = 0;
    int a = 1;
    for (long double i = s; i < 1-0.0001; i += s) {
        Hi_lookup[a].first = H(i);
        Hi_lookup[a].second = i;
        a++;
    }
}


 long double mo_nn(long double list_size,long double weight){
    long double d = Hi(1-list_size);
    if (weight <=2*d*(1-d))
        return (1-weight)*(1-H((d-weight/2)/(1-weight)));
    else
        return 2*list_size+H(weight)-1;
}
 long double indyk_motwani_nn(long double list_size,long double weight){
    long double alpha = std::min(list_size, 1-2*weight);
    if(alpha<0) alpha=0;
    return (binomH(1,alpha)-binomH(1-weight,alpha)+std::max(2*list_size-alpha,list_size));
}
 long double mitm_nn(long double list_size,long double weight, long double length){
    long double L1=binomH(length/2,weight/2)+list_size;
    return std::max(L1,2*L1-length);
}


 long double time_nn(bool mo, long double list, long double vec_length, long double weight){


    long double n_size=std::min(list/vec_length,(long double) 0.99999);
    long double n_weight=weight/vec_length;
    if (weight==0)
        return std::max(2*list-vec_length,list);
    if (n_weight>0.5)
        n_weight=1-n_weight;

    if (mo)
        return mo_nn(n_size,n_weight)*vec_length;
    else
        //return mitm_nn(list,weight,vec_length);
        return indyk_motwani_nn(n_size,n_weight)*vec_length;

}

 long double time_nn_hybrid(long double list, long double vec_length, long double weight, long double exact)
{
    //naive
    long double alpha = std::min(list-exact, 1-2*weight);
    if(alpha<0) alpha=0;
    return binomH(vec_length,alpha)-binomH(vec_length-weight,alpha)+std::max(2*list-alpha-exact,list);

    //MO
    //if(list-exact<0)
    //    return list;
    //else
    //return time_nn(list-exact,vec_length,weight)+exact
}
//prob that two weight w1 vectors of length l sum to weight w2 vector
 long double sum_correct_weight(long double l,long double w1,long double w2)
{
    return -binomH(l,w1)+binomH(l-w1,w2/2)+binomH(w1,w1-w2/2);
}

//nearest neighbor on weight w were lists contain random weight-w1 vectors
 long double time_nn_w1(long double lam, long double l, long double w,long double w1, long double alpha)
{
    return binomH(l,alpha)-binomH(l-w,alpha)+std::max(lam,2*lam-(log2(1.0/(1-(2*(1-w1)*w1)))*alpha));
}

//reps of weight p vector as sum of two p1 vectors of length l
 long double reps(long double p, long double p1, long double l)
{
    if (p==0 || p1==0 || l==0)
        return 0;
    return binomH(p,p/2)+binomH(l-p,p1-p/2);
}