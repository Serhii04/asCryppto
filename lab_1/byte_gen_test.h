#pragma once

#include <iostream>
#include <math.h>
#include <vector>
#include <map>


std::map<double, double> NORMAL_DISTRIBUTION_QUANTILE = {
        {0.001,	-3.0902},
        {0.005,	-2.5758},
        {0.010,	-2.3263},
        {0.025,	-1.9600},
        {0.050,	-1.6449},
        {0.100,	-1.2816},
        {0.250,	-0.6745},
        {0.500,	0},
        {0.750,	0.6745},
        {0.900,	1.2816},
        {0.950,	1.6449},
        {0.975,	1.9600},
        {0.990,	2.3263},
        {0.995,	2.5758},
        {0.999,	3.0902}};

double normal_quantile(double alpha){
    if (NORMAL_DISTRIBUTION_QUANTILE.find(alpha) != NORMAL_DISTRIBUTION_QUANTILE.end()) {
        return NORMAL_DISTRIBUTION_QUANTILE[alpha];
    }

    return 0;
}

double chi_2_quantile(double alpha){
    int l = 255;
    double res = sqrt(2 * l) * normal_quantile(alpha) + l;

    return res;
}

bool signs_equality(std::vector<unsigned short int> rv, double alpha){
    std::map<unsigned short int, unsigned int> observed_quantity;

    for(auto i: rv){
        if (observed_quantity.find(i) != observed_quantity.end()) {
            observed_quantity[i] += 1;
        }
        else {
            observed_quantity[i] = 1;
        } 
    }

    double n_j = rv.size() / 256;
    double stat = 0;
    for(auto x: observed_quantity) {
        // std::cout << x.first << " => " << x.second << '\n';
        stat += pow(x.second - n_j, 2) / n_j;
    }  

    double quantile = chi_2_quantile(1 - alpha);

    if(stat <= quantile){
        return true;
    }

    return false;
}