from ctypes import cdll, c_float, c_int, c_bool, POINTER
from os import listdir


directory="usr/local/lib"
for f in listdir(directory):
    if "lib_SyndromeDecodingEstimator" in f:
        name=f
lib = cdll.LoadLibrary(name)
lib.initialize()

_prange_workfactor_c_func = lib.opt_prange
_stern_workfactor_c_func = lib.opt_stern
_dumer_workfactor_c_func = lib.opt_dumer
_ball_collision_workfactor_c_func = lib.opt_ball_collision
_bjmm_wokfactor_c_func = lib.opt_bjmm
_may_ozerov_workfactor_c_func = lib.opt_mo
_both_may_workfactor_c_func = lib.opt_bm_d2

_prange_workfactor_c_func.argtypes = (c_float, c_float, c_int, c_int, POINTER(c_float), POINTER(c_float), c_float)
_stern_workfactor_c_func.argtypes = (c_float, c_float, c_int, c_int, POINTER(c_float), POINTER(c_float), c_float)
_dumer_workfactor_c_func.argtypes = (c_float, c_float, c_int, c_int, POINTER(c_float), POINTER(c_float), c_float)
_ball_collision_workfactor_c_func.argtypes = (
    c_float, c_float, c_int, c_int, POINTER(c_float), POINTER(c_float), c_float)
_bjmm_wokfactor_c_func.argtypes = (c_float, c_float, c_int, c_int, POINTER(c_float), POINTER(c_float), c_float)
_may_ozerov_workfactor_c_func.argtypes = (
    c_float, c_float, c_int, c_int, POINTER(c_float), POINTER(c_float), c_float, c_bool)
_both_may_workfactor_c_func.argtypes = (
    c_float, c_float, c_int, c_int, POINTER(c_float), POINTER(c_float), c_float, c_bool)


def prange_workfactor(rate, omega, grid_percision=20, grid_iterations=150, max_mem=1):
    """
    Computes the workfactor (time and memory) of Pranges algorithm via gridsearch (1 parameter).

    INPUT:

    - ``rate`` -- rate of the code (k/n)
    - ``omega`` -- weight of the error
    - ``grid_percision`` -- amount of intervals initial parameter range is seperated in (default: 20)
    - ``grid_iterations`` -- number of times best parameter set in current range is searched and ranges updated (default: 150)
    - ``max_mem`` -- maximum memory-workfactor (default: 1, no limitation)
    """

    WF_mem = c_float(0)
    WF_time = c_float(0)
    _prange_workfactor_c_func(rate, omega, grid_percision, grid_iterations, WF_time, WF_mem, max_mem)
    return WF_time.value, WF_mem.value


def stern_workfactor(rate, omega, grid_percision=20, grid_iterations=150, max_mem=1):
    """
    Computes the workfactor (time and memory) of Sterns' algorithm via gridsearch (2 parameters).

    INPUT:

    - ``rate`` -- rate of the code (k/n)
    - ``omega`` -- weight of the error
    - ``grid_percision`` -- amount of intervals initial parameter range is seperated in (default: 20)
    - ``grid_iterations`` -- number of times best parameter set in current range is searched and ranges updated (default: 150)
    - ``max_mem`` -- maximum memory-workfactor (default: 1, no limitation)
    """

    WF_mem = c_float(0)
    WF_time = c_float(0)
    _stern_workfactor_c_func(rate, omega, grid_percision, grid_iterations, WF_time, WF_mem, max_mem)
    return WF_time.value, WF_mem.value


def dumer_workfactor(rate, omega, grid_percision=20, grid_iterations=150, max_mem=1):
    """
    Computes the workfactor (time and memory) of Dumers' algorithm via gridsearch (2 parameters).

    INPUT:

    - ``rate`` -- rate of the code (k/n)
    - ``omega`` -- weight of the error
    - ``grid_percision`` -- amount of intervals initial parameter range is seperated in (default: 20)
    - ``grid_iterations`` -- number of times best parameter set in current range is searched and ranges updated (default: 150)
    - ``max_mem`` -- maximum memory-workfactor (default: 1, no limitation)
    """

    WF_mem = c_float(0)
    WF_time = c_float(0)
    _dumer_workfactor_c_func(rate, omega, grid_percision, grid_iterations, WF_time, WF_mem, max_mem)
    return WF_time.value, WF_mem.value


def ball_collision_workfactor(rate, omega, grid_percision=15, grid_iterations=150, max_mem=1):
    """
    Computes the workfactor (time and memory) of the Ball Collision Decoding algorithm via gridsearch (3 parameters).

    INPUT:

    - ``rate`` -- rate of the code (k/n)
    - ``omega`` -- weight of the error
    - ``grid_percision`` -- amount of intervals initial parameter range is seperated in (default: 15)
    - ``grid_iterations`` -- number of times best parameter set in current range is searched and ranges updated (default: 150)
    - ``max_mem`` -- maximum memory-workfactor (default: 1, no limitation)
    """

    WF_mem = c_float(0)
    WF_time = c_float(0)
    _ball_collision_workfactor_c_func(rate, omega, grid_percision, grid_iterations, WF_time, WF_mem, max_mem)
    return WF_time.value, WF_mem.value


def bjmm_workfactor(rate, omega, grid_percision=10, grid_iterations=250, max_mem=1):
    """
    Computes the workfactor (time and memory) the BJMM algorithm (depth 3) via gridsearch (4 parameters).

    INPUT:

    - ``rate`` -- rate of the code (k/n)
    - ``omega`` -- weight of the error
    - ``grid_percision`` -- amount of intervals initial parameter range is seperated in (default: 10)
    - ``grid_iterations`` -- number of times best parameter set in current range is searched and ranges updated (default: 250)
    - ``max_mem`` -- maximum memory-workfactor (default: 1, no limitation)
    """

    WF_mem = c_float(0)
    WF_time = c_float(0)
    _bjmm_wokfactor_c_func(rate, omega, grid_percision, grid_iterations, WF_time, WF_mem, max_mem)
    return WF_time.value, WF_mem.value


def may_ozerov_workfactor(rate, omega, grid_percision=5, grid_iterations=1000, max_mem=1, use_mo=True):
    """
    Computes the workfactor (time and memory) the May-Ozerov (depth 3) algorithm via gridsearch (4 parameters).

    INPUT:

    - ``rate`` -- rate of the code (k/n)
    - ``omega`` -- weight of the error
    - ``grid_percision`` -- amount of intervals initial parameter range is seperated in (default: 15)
    - ``grid_iterations`` -- number of times best parameter set in current range is searched and ranges updated (default: 150)
    - ``max_mem`` -- maximum memory-workfactor (default: 1, no limitation)
    - ``use_mo`` -- include may ozerov nearest neighbor search algorithm for computing the workfactors (default: true)
    """

    WF_mem = c_float(0)
    WF_time = c_float(0)
    _may_ozerov_workfactor_c_func(rate, omega, grid_percision, grid_iterations, WF_time, WF_mem, max_mem, use_mo)
    return WF_time.value, WF_mem.value


def both_may_workfactor(rate, omega, grid_percision=5, grid_iterations=1000, max_mem=1, use_mo=True):
    """
    Computes the workfactor (time and memory) the Both-May algorithm (depth 2) via gridsearch (5 parameters).

    INPUT:

    - ``rate`` -- rate of the code (k/n)
    - ``omega`` -- weight of the error
    - ``grid_percision`` -- amount of intervals initial parameter range is seperated in (default: 15)
    - ``grid_iterations`` -- number of times best parameter set in current range is searched and ranges updated (default: 150)
    - ``max_mem`` -- maximum memory-workfactor (default: 1, no limitation)
    - ``use_mo`` -- include may ozerov nearest neighbor search algorithm for computing the workfactors (default: true)
    """

    WF_mem = c_float(0)
    WF_time = c_float(0)
    _both_may_workfactor_c_func(rate, omega, grid_percision, grid_iterations, WF_time, WF_mem, max_mem, use_mo)
    return WF_time.value, WF_mem.value
