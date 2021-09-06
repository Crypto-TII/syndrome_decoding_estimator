# Syndrome Decoding Estimator

This project provides an estimator for the hardness of the syndrome decoding problem written in python. Some functionalities (precisely, the computation of theoretical workfactors) are outsourced to a C-library.

More details on the theoretical foundations of the estimator can be found in the corresponding paper

[EssBel21] Syndrome Decoding Estimator

## Setting up the estimator

The installation requires an up to date C-Compiler and python version (we used Clang 12.0.0 together with python 3.9.5). To install the dependencies and to build the C-library run inside the SyndromeDecodingEstimator directory 

    $ make

The C-library is installed into the directory $HOME/lib, while the python part is installed as a python module named ``sd_estimator``.
To build the documentation run

    $make doc
    
The documentation can then be found in docs/build/index.html.

## Using the estimator

### Recomputing the results in the paper

To recalculate the tables presented in Section 5 of [EssBel21] use the script ``estimate_code_based_nist_schemes.py``:

    $ python estimate_code_based_nist_schemes.py -h
    usage: estimate_code_based_nist_schemes.py [-h] [--McEliece | --BIKEmsg | --BIKEkey | --HQC]

    Estimate Security of Code-Based NIST PQC Schemes

    optional arguments:
      -h, --help  show this help message and exit
      --McEliece  estimate security of McEliece parameter sets.
      --BIKEmsg   estimate security of BIKE parameter sets (message security).
      --BIKEkey   estimate security of BIKE parameter sets (key security).
      --HQC       estimate security of HQC parameter sets.

### Computing indepent estimates

The ``estimator``  includes a function ``sd_estimate_display``, which can be used to obtain a summary of the estimated hardness of arbitrary syndrome decoding instances using different algorithms (see documentation for details and examples). Additionally the file includes for each algorithm a function following the naming convention ``<algorithm_name>_complexity`` allowing to obtain the estimate for an instance when only using this specific algorithm.

    $ python
    >>> from sd_estimator.estimator import sd_estimate_display
    >>> sd_estimate_display(n=100,k=50,w=10)

## Citing this work

    @misc{SyndromeDecodingEstimator,
      title  = {Syndrome Decoding Estimator},
      author = {Bellini, Emanuele and Esser, Andre},
      url    = {https://github.com/Crypto-TII/syndrome_decoding_estimator},
      year   = {2021}
    }

