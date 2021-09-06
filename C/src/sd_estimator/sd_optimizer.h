#ifndef SD_OPTIMIZER_H
#define SD_OPTIMIZER_H

#include <utility>
#include <vector>
#include <functional>

class Optimizer {

public:
    Optimizer(int d, int window_size) {
        dimension = d;
        min_val = 50000;
        ranges.resize(d);
        var_opt.resize(d);
        w_size = window_size;
    }

    void find(int iterations);


    virtual long double time(const std::vector<long double> &var) { return 0; };

    virtual long double memory(const std::vector<long double> &var) { return 0; };

    virtual bool conditions(const std::vector<long double> &var) { return false; };

    void output(const std::vector<long double> &var) {
    }

    void output_opt() {
        output(var_opt);
    }

    void set_ranges(long double first, long double second, int i) {
        ranges[i].first = first;
        ranges[i].second = second;
    };

    int get_dimension() {
        return dimension;
    }

    long double get_var_opt(int i) {
        return var_opt[i];
    }

    long double get_min_val() {
        return min_val;
    }

    void set_omega(long double w) {
        omega = w;
    }

    void set_rate(long double R) {
        kn = R;
    }

    void set_max_mem(long double m) {
        this->max_mem = m;
    }

    long double get_memory_opt() {
        return memory(var_opt);
    }

protected:

    int dimension;
    long double w_size;
    std::vector<std::pair<long double, long double> > ranges;
    std::vector<long double> var_opt;
    long double min_val;
    long double omega;
    long double kn;
    long double max_mem = 1;

private:
    Optimizer();
};

#endif //SD_OPTIMIZER_H
