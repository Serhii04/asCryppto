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

double chi_2_quantile(double alpha, int l = 255){
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

bool independence_of_signs(std::vector<unsigned short int> rv, double alpha){
    std::map<unsigned short int, std::map<unsigned short int, unsigned int>> vij;
    std::map<unsigned short int, unsigned int> aj;
    std::map<unsigned short int, unsigned int> vi;

    for(int i = 0; i < rv.size() / 2; ++i){ //calculate vij, vi, aj
        unsigned short int v1 = rv[2 * i];
        unsigned short int v2 = rv[2 * i + 1];

        if(vij.find(v1) == vij.end()){
            vij[v1] = std::map<unsigned short int, unsigned int>{};
            vi[v1] = 1;
        }
        else{
            vi[v1] += 1;
        }

        if(vij[v1].find(v2) == vij[v1].end()){
            vij[v1][v2] = 1;
            aj[v2] = 1;
        }
        else{
            vij[v1][v2] += 1;
            aj[v2] += 1;
        }
    }

    double stat = 0;
    for(auto v: vi){
        for(auto a: aj){
            stat += pow(vij[v.first][a.first], 2) / (v.second * a.second) - 1;
        }
    } 
    stat = stat * rv.size();

    double quantile = chi_2_quantile(1 - alpha, pow(255, 2));

    if(stat <= quantile){
        return true;
    }

    return false;
}

bool binary_sequence_uniformity(std::vector<unsigned short int> rv, double alpha, int r=10){
    std::map<unsigned short int, std::map<unsigned short int, unsigned int>> vij;
    std::map<unsigned short int, unsigned int> aj;
    std::map<unsigned short int, unsigned int> vi;

    int m_ = rv.size() / r;

    int j_max = rv.size() / r; 
    for(int j = 0; j < j_max; j += 1){
        vij[j] = std::map<unsigned short int, unsigned int>{};
        for(int i = 0; i < r; ++i){
            if(vij[j].find(rv[j * r + i]) == vij[j].end()){
                vij[j][rv[j * r + i]] = 0;

            }
            vij[j][rv[j * r + i]] += 1;

            if(vi.find(rv[j * r + i]) == vi.end()){
                vi[rv[j * r + i]] = 0;
            }
            vi[rv[j * r + i]] += 1;
        }
    }

    double stat = 0;
    for(auto j_segment: vij){
        for(auto v: j_segment.second){
            stat += pow(v.second, 2) / (vi[v.first] * m_) - 1;
        }
    } 
    stat = stat * rv.size();

    double quantile = chi_2_quantile(1 - alpha, 255 * (r - 1));

    if(stat <= quantile){
        return true;
    }

    return false;
}

