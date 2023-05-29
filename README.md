# Syndrome Decoding Estimator

This project provides an estimator for the hardness of the syndrome decoding problem written in python. Some functionalities (precisely, the computation of theoretical workfactors) are outsourced to a C-library.

More details on the theoretical foundations of the estimator can be found in the corresponding paper

> [EssBel22] Esser, A., Bellini, E.: Syndrome decoding estimator. In: PKC 2022, Part I. pp. 112–141. LNCS, Springer, Heidelberg (May 2022). https://doi.org/10.1007/978-3-030-97121-2_5

## Using and Contributing
We launched another more comprehensive estimator project that incorporates the source code of this repository with some improvements.
We therefore highly recommend to use that new project available at https://github.com/Crypto-TII/CryptographicEstimators to produce new estimates. The current repository is not actively maintained (apart from bug fixes) 
and serves mainly for reference purposes. The most up-to-date estimates are therefore obtained via the new project ``CrypographicEstimators``.

## Setting up the estimator

The installation requires an up to date C-Compiler and python version (we used Clang 12.0.0 together with python 3.9.5). To install the dependencies and to build the C-library run inside the SyndromeDecodingEstimator directory 

    $ make

The C-library is installed into the directory ``/usr/local/lib``, while the python part is installed as a python module named ``sd_estimator`` into your standard python package directory.
To build the documentation run

    $make doc
    
The documentation can then be found in docs/build/index.html.

## Using the estimator

### Recomputing the results in the paper

To recalculate the tables presented in Section 5 of [EssBel22] use the script ``estimate_code_based_nist_schemes.py``:

    $ python estimate_code_based_nist_schemes.py -h
    usage: estimate_code_based_nist_schemes.py [-h] [--McEliece | --BIKEmsg | --BIKEkey | --HQC]

    Estimate Security of Code-Based NIST PQC Schemes

    optional arguments:
      -h, --help  show this help message and exit
      --McEliece  estimate security of McEliece parameter sets.
      --BIKEmsg   estimate security of BIKE parameter sets (message security).
      --BIKEkey   estimate security of BIKE parameter sets (key security).
      --HQC       estimate security of HQC parameter sets.

### Computing independent estimates

The ``estimator``  includes a function ``sd_estimate_display``, which can be used to obtain a summary of the estimated hardness of arbitrary syndrome decoding instances using different algorithms (see documentation for details and examples). Additionally the file includes for each algorithm a function following the naming convention ``<algorithm_name>_complexity`` allowing to obtain the estimate for an instance when only using this specific algorithm.

    $ python
    >>> from sd_estimator.estimator import sd_estimate_display
    >>> sd_estimate_display(n=100,k=50,w=10)

## Citing this work

When referring to the estimator, please cite our work [EssBel22], for example by using the following bibtex entry (source: dblp.org):

    @inproceedings{EssBel22,
      author       = {Andre Esser and
                      Emanuele Bellini},
      editor       = {Goichiro Hanaoka and
                      Junji Shikata and
                      Yohei Watanabe},
      title        = {Syndrome Decoding Estimator},
      booktitle    = {Public-Key Cryptography - {PKC} 2022 - 25th {IACR} International Conference
                      on Practice and Theory of Public-Key Cryptography, Virtual Event,
                      March 8-11, 2022, Proceedings, Part {I}},
      series       = {Lecture Notes in Computer Science},
      volume       = {13177},
      pages        = {112--141},
      publisher    = {Springer},
      year         = {2022},
      url          = {https://doi.org/10.1007/978-3-030-97121-2\_5},
      doi          = {10.1007/978-3-030-97121-2\_5},
      timestamp    = {Thu, 10 Mar 2022 11:26:10 +0100},
      biburl       = {https://dblp.org/rec/conf/pkc/Esser022.bib},
      bibsource    = {dblp computer science bibliography, https://dblp.org}
    }
