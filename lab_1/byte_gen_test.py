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
        if observed_quantity.get(i) == None:
            observed_quantity[i] = 0
        
        observed_quantity[i] += 1

    n_j = len(rv) / 256

    stat = 0
    for key in observed_quantity:
        stat += pow(observed_quantity[key] - n_j, 2) / n_j

    quantile = chi_2_quantile(1 - alpha)

    if stat <= quantile:
        return True

    return False


def independence_of_signs(rv, alpha):
    vij = dict()
    vi = dict()
    aj = dict()

    for i  in range(0, len(rv) // 2):
        v1 = rv[2 * i]
        v2 = rv[2 * i + 1]

        if vij.get(v1) == None:
            vij[v1] = dict()
            vi[v1] = 0
        

        if vij[v1].get(v2) == None:
            vij[v1][v2] = 0
            aj[v2] = 0

        vij[v1][v2] += 1
        vi[v1] += 1
        aj[v2] += 1

    stat = 0
    for v in vij:
        for a in vij[v]:
            stat += pow(vij[v][a], 2) / (vi[v] * aj[a])

    stat = (len(rv) // 2) * (stat - 1)

    quantile = chi_2_quantile(1 - alpha, pow(255, 2));

    # print(f"<{stat} (-) {quantile}>")

    if stat <= quantile:
        return True;

    return False;

def binary_sequence_uniformity(rv, alpha, r=10):
    vij = dict()
    vi = dict()

    m_ = len(rv) // r

    for j in range(0, r):
        vij[j] = dict()
        for i in range(0, m_):
            if vij[j].get(rv[j * m_ + i]) == None:
                vij[j][rv[j * m_ + i]] = 0
            
            if vi.get(rv[j * m_ + i]) == None:
                vi[rv[j * m_ + i]] = 0

            vij[j][rv[j * m_ + i]] += 1
            vi[rv[j * m_ + i]] += 1

    stat = 0
    for j_segment_key in vij:
        for v_key in vij[j_segment_key]:
            stat += pow(vij[j_segment_key][v_key], 2) / (vi[v_key] * m_)

    stat = len(rv) * (stat - 1)

    quantile = chi_2_quantile(1 - alpha, 255 * (r - 1))

    # print(f"<{stat} (-) {quantile}>")

    if stat <= quantile:
        return True

    return False

