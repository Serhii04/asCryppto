# Tests

from math import sqrt

NORMAL_DISTRIBUTION_QUANTILE = {
        0.001:	-3.0902,
        0.005:	-2.5758,
        0.010:	-2.3263,
        0.025:	-1.9600,
        0.050:	-1.6449,
        0.100:	-1.2816,
        0.250:	-0.6745,
        0.500:	0,
        0.750:	0.6745,
        0.900:	1.2816,
        0.950:	1.6449,
        0.975:	1.9600,
        0.990:	2.3263,
        0.995:	2.5758,
        0.999:	3.0902
    }

def normal_quantile(alpha):
    if NORMAL_DISTRIBUTION_QUANTILE.get(alpha) != None:
        return NORMAL_DISTRIBUTION_QUANTILE[alpha];

    return 0

def chi_2_quantile(alpha, l = 255):
    res = sqrt(2 * l) * normal_quantile(alpha) + l;

    return res;

def signs_equality(rv, alpha):
    observed_quantity = dict()

    for i in rv:
        if observed_quantity.get(i) != None:
            observed_quantity[i] += 1;
        else:
            observed_quantity[i] = 1;

    n_j = len(rv) / 256;
    stat = 0;
    for key in observed_quantity:
        # // std::cout << x.first << " => " << x.second << '\n';
        stat += pow(observed_quantity[key] - n_j, 2) / n_j;

    quantile = chi_2_quantile(1 - alpha);

    if stat <= quantile:
        return True;

    return False;


def independence_of_signs(rv, alpha):
    vij = dict();
    aj = dict();
    vi = dict();

    for i  in range(0, len(rv) // 2): #calculate vij, vi, aj
        v1 = rv[2 * i];
        v2 = rv[2 * i + 1];

        if vij.get(v1) == None:
            vij[v1] = dict()
            vi[v1] = 0;
        
        vi[v1] += 1;

        if vij[v1].get(v2) == None:
            vij[v1][v2] = 1;
            aj[v2] = 1;
        else:
            vij[v1][v2] += 1;
            aj[v2] += 1;

    stat = 0;
    for v_key in vi:
        for a_key in aj:
            if vij.get(v_key) == None:
                vij[v_key] = dict()
                vij[v_key][a_key] = 0
            
            if vij[v_key].get(a_key) == None:
                vij[v_key][a_key] = 0

            stat += pow(vij[v_key][a_key], 2) / (vi[v_key] * aj[a_key]) - 1;

    stat = stat * len(rv);

    quantile = chi_2_quantile(1 - alpha, pow(255, 2));

    if stat <= quantile:
        return True;

    return False;

def binary_sequence_uniformity(rv, alpha, r=10):
    vij = dict()
    aj = dict()
    vi = dict()

    m_ = len(rv) // r;

    j_max = len(rv) // r; 
    for j in range(0, j_max):
        vij[j] = dict()
        for i in range(0, r):
            if vij[j].get(rv[j * r + i]) == None:
                vij[j][rv[j * r + i]] = 0;

            vij[j][rv[j * r + i]] += 1;

            if vi.get(rv[j * r + i]) == None:
                vi[rv[j * r + i]] = 0;

            vi[rv[j * r + i]] += 1;

    stat = 0;
    for j_segment_key in vij:
        for v_key in vij[j_segment_key]:
            stat += pow(vij[j_segment_key][v_key], 2) / (vi[v_key] * m_) - 1;

    stat = stat * len(rv);

    quantile = chi_2_quantile(1 - alpha, 255 * (r - 1));

    if stat <= quantile:
        return True

    return False

