from sd_estimator.estimator import _sd_estimate, bjmm_depth_2_disjoint_weight_complexity, __concat_pretty_tables
import argparse
from math import log2, inf
from prettytable import PrettyTable
from sys import stdout
import warnings

warnings.filterwarnings("ignore", category=RuntimeWarning)

McEliece_level1 = {"name": "McEliece C1", "n": 3488, "k": 2720, "w": 64}
McEliece_level3 = {"name": "McEliece C3", "n": 4608, "k": 3360, "w": 96}
McEliece_level5a = {"name": "McEliece C5a", "n": 6688, "k": 5024, "w": 128}
McEliece_level5b = {"name": "McEliece C5b", "n": 6960, "k": 5413, "w": 119}
McEliece_level5c = {"name": "McEliece C5c", "n": 8192, "k": 6528, "w": 128}

BIKE_level1 = {"name": "BIKE C1", "n": 24646, "k": 12323, "w": 134, "w_k": 142}
BIKE_level3 = {"name": "BIKE C3", "n": 49318, "k": 24659, "w": 199, "w_k": 206}
BIKE_level5 = {"name": "BIKE C5", "n": 81946, "k": 40973, "w": 264, "w_k": 274}

HQC_level1 = {"name": "HQC C1", "n": 35338, "k": 17669, "w": 132, "w_e": 75}
HQC_level3 = {"name": "HQC C3", "n": 71702, "k": 35851, "w": 200, "w_e": 114}
HQC_level5 = {"name": "HQC C5", "n": 115274, "k": 57637, "w": 262, "w_e": 149}

McEliece_params = [McEliece_level1, McEliece_level3, McEliece_level5a, McEliece_level5b, McEliece_level5c]
BIKE_params = [BIKE_level1, BIKE_level3, BIKE_level5]
HQC_params = [HQC_level1, HQC_level3, HQC_level5]


def cr(x):
    if x != inf:
        return int(round(x))
    else:
        return inf


def estimate_set(par, p_range=[0, 25], key_sec=0, mem=inf,memory_access=0):
    """
    Compute estimates of subset of algorithms for given parameter set using _sd_estimate.

    """
    (n, k, w) = (par["n"], par["k"], par["w"]) if key_sec == 0 else (par["n"], par["k"], par["w_k"])
    est = _sd_estimate(n, k, w, 0, mem, 1, 1, ["dumer", "ball_collision", "BJMM-dw"], 0, 1, 1, 0, 96, 2.5,memory_access)
    print("Computing BJMM-dw estimate...", end='')
    stdout.flush()
    est["BJMM-dw"] = bjmm_depth_2_disjoint_weight_complexity(n, k, w, p_range=p_range, mem=mem - log2(n),memory_access=memory_access)
    est["BJMM-dw"]["time"] += log2(n)
    est["BJMM-dw"]["memory"] += log2(n)
    print("done!")
    return est


def output(tbls):
    """
    Output an array of PrettyTables as one joined table.

    """
    out = __concat_pretty_tables(str(tbls[0]), str(tbls[1]))
    for i in range(2, len(tbls)):
        out = __concat_pretty_tables(out, str(tbls[i]))
    print(out)


def create_table_array(params, estimates):
    """
    Create and fill array of PrettyTables including one table for names and one for each parameter set.

    """

    tbl_names = [i["name"] for i in params]
    alg_name = [i for i in estimates[0].keys()]
    tbls = []

    pt = PrettyTable(['algorithm'])
    pt.padding_width = 1
    pt.title = ' '
    for i in alg_name:
        pt.align['algorithm'] = "l"
        pt.add_row([i])
    tbls.append(pt)

    table_fields = ['time', 'memory']
    for i in tbl_names:
        pt = PrettyTable(table_fields)
        pt.align['time'] = "r"
        pt.align['memory'] = "r"
        pt.padding_width = 1
        pt.title = i
        tbls.append(pt)

    for i in estimates[0].keys():
        for j in range(len(estimates)):
            tbls[j + 1].add_row([cr(estimates[j][i]["time"]), cr(estimates[j][i]["memory"])])
    return tbls


def add_mem_restricted_estimate_to_tables(tbls, params, mem, p_range=0,memory_access=0, key_sec=0, quasi_cyclic=0):
    """
    Add memory restricted estimates to tables.

    """
    p_range = p_range if p_range != 0 else [[0, 25] for i in params]
    estimates = []
    for i in range(len(params)):
        print("Parameter Set", i + 1)
        estimates.append(estimate_set(params[i], p_range=p_range[i], mem=mem,memory_access=memory_access, key_sec=key_sec))
    if memory_access==0:
        tbls[0].add_row(["M < {}".format(mem)])
    elif memory_access==3:
        tbls[0].add_row(["Cubic-root memory access".format(mem)])
    elif memory_access==2:
        tbls[0].add_row(["Square-root memory access".format(mem)])
    elif memory_access==1:
        tbls[0].add_row(["Logarithmic memory access".format(mem)])
        
    best_algs = []
    for i in range(len(estimates)):
        time = min([estimates[i][j]["time"] for j in estimates[i].keys()])-key_sec*log2(k)-quasi_cyclic*log2(k)/2
        memory = estimates[i][[j for j in estimates[i].keys() if estimates[i][j]["time"] == time][0]]["memory"]
        best_algs.append([j for j in estimates[i].keys() if estimates[i][j]["time"] == time][0])
        tbls[i + 1].add_row([cr(time), cr(memory)])
    print(best_algs)


def estimate_list(params, p_range=0, quasi_cyclic=0, code_word_search=0):
    """
    Creates the tables containing estimates for all given parameter sets.

    """
    p_range = p_range if p_range != 0 else [[0, 25] for i in params]
    fac = 1 if code_word_search else 2
    estimates = []
    for i in range(len(params)):
        print("Parameter Set", i + 1)
        estimates.append(estimate_set(params[i], p_range=p_range[i], key_sec=code_word_search))
        for j in estimates[i].keys():
            estimates[i][j]["time"] -= (quasi_cyclic * log2(params[i]["k"]) / fac)
    return estimates


def estimate_mceliece():
    """
    Compute and output esitmates for McEliece parametersets.
    """
    print("Estimating McEliece")
    print("Unrestricted estimates")

    estimates = estimate_list(McEliece_params, [[10, 17], [12, 17], [18, 25], [18, 25], [16, 25]])
    McEliece_tbls = create_table_array(McEliece_params, estimates)

    print("\nMemory < 2^60 bit")
    add_mem_restricted_estimate_to_tables(McEliece_tbls, McEliece_params, 60, [[4, 11] for i in range(5)])
    print("\nMemory <= 2^80 bit")
    add_mem_restricted_estimate_to_tables(McEliece_tbls, McEliece_params, 80,
                                          [[12, 17], [12, 17], [10, 17], [10, 17], [10, 17]])
    
    print("\nLog memory access")
    add_mem_restricted_estimate_to_tables(McEliece_tbls, McEliece_params, inf,
                                          [[10, 17], [12, 17], [18, 25], [18, 25], [16, 25]],memory_access=1)
    print("\nCubic-root memory access")
    add_mem_restricted_estimate_to_tables(McEliece_tbls, McEliece_params, inf,
                                          [[2, 4], [2, 4], [2, 4], [2, 4], [2, 4]],memory_access=3)
    print("\nSquare-root memory access")
    add_mem_restricted_estimate_to_tables(McEliece_tbls, McEliece_params, inf,
                                          [[2, 4], [2, 4], [2, 4], [2, 4], [2, 4]],memory_access=2)
  
    print("\n")
    output(McEliece_tbls)


def estimate_bike_msg():
    """
    Compute and output esitmates for BIKE parametersets (message security).

    """
    print("Estimating BIKE (message security)")
    estimates = estimate_list(BIKE_params, [[2, 8] for i in range(3)], quasi_cyclic=1)
    BIKE_msg_tbls = create_table_array(BIKE_params, estimates)

    print("\nLog memory access")
    add_mem_restricted_estimate_to_tables(BIKE_msg_tbls, BIKE_params, inf,
                                          [[0, 8] for i in range(3)], memory_access=1, quasi_cyclic=1)
    print("\nCubic-root memory access")
    add_mem_restricted_estimate_to_tables(BIKE_msg_tbls, BIKE_params, inf,
                                          [[0, 8] for i in range(3)], memory_access=3, quasi_cyclic=1)
    print("\nSquare-root memory access")
    add_mem_restricted_estimate_to_tables(BIKE_msg_tbls, BIKE_params, inf,
                                          [[0, 8] for i in range(3)], memory_access=2, quasi_cyclic=1)

    print("\n")
    output(BIKE_msg_tbls)


def estimate_bike_key():
    """
    Compute and output esitmates for BIKE parametersets (key security).

    """
    print("Estimating BIKE (key security)")
    estimates = estimate_list(BIKE_params, [[2, 8] for i in range(3)], quasi_cyclic=1, code_word_search=1)
    BIKE_key_tbls = create_table_array(BIKE_params, estimates)
    
    print("\nLog memory access")
    add_mem_restricted_estimate_to_tables(BIKE_key_tbls, BIKE_params, inf,
                                          [[0, 8] for i in range(3)], memory_access=1, key_sec=1)
    print("\nCubic-root memory access")
    add_mem_restricted_estimate_to_tables(BIKE_key_tbls, BIKE_params, inf,
                                          [[0, 8] for i in range(3)], memory_access=3, key_sec=1)
    print("\nSquare-root memory access")
    add_mem_restricted_estimate_to_tables(BIKE_key_tbls, BIKE_params, inf,
                                          [[0, 8] for i in range(3)], memory_access=2, key_sec=1)

    print("\n")
    
    output(BIKE_key_tbls)


def estimate_hqc():
    """
    Compute and output esitmates for HQC parametersets.

    """

    print("Estimating HQC")
    estimates = estimate_list(HQC_params, [[2, 8] for i in range(3)], quasi_cyclic=1)
    HQC_tbls = create_table_array(HQC_params, estimates)
    
    print("\nLog memory access")
    add_mem_restricted_estimate_to_tables(HQC_tbls, HQC_params, inf,
                                          [[0, 8] for i in range(3)], memory_access=1, quasi_cyclic=1)
    print("\nCubic-root memory access")
    add_mem_restricted_estimate_to_tables(HQC_tbls, HQC_params, inf,
                                          [[0, 8] for i in range(3)], memory_access=3, quasi_cyclic=1)
    print("\nSquare-root memory access")
    add_mem_restricted_estimate_to_tables(HQC_tbls, HQC_params, inf,
                                          [[0, 8] for i in range(3)], memory_access=2, quasi_cyclic=1)
    print("\n")
    
    output(HQC_tbls)



parser = argparse.ArgumentParser(description='Estimate Security of Code-Based NIST PQC Schemes')

group = parser.add_mutually_exclusive_group()

group.add_argument('--McEliece', dest='compute', action='store_const',
                   const=estimate_mceliece, default=estimate_mceliece,
                   help='estimate security of McEliece parameter sets.')

group.add_argument('--BIKEmsg', dest='compute', action='store_const',
                   const=estimate_bike_msg, default=estimate_mceliece,
                   help='estimate security of BIKE parameter sets (message security).')

group.add_argument('--BIKEkey', dest='compute', action='store_const',
                   const=estimate_bike_key, default=estimate_mceliece,
                   help='estimate security of BIKE parameter sets (key security).')

group.add_argument('--HQC', dest='compute', action='store_const',
                   const=estimate_hqc, default=estimate_mceliece,
                   help='estimate security of HQC parameter sets.')

args = parser.parse_args()
args.compute()
