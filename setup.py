import setuptools

setuptools.setup(

    name="sd_estimator",

    version="1.0.0",

    author="Andre Esser and Emanuele Bellini",

    author_email="andre.esser@tii.ae",

    packages=setuptools.find_packages(),

    classifiers=[

        "Programming Language :: Python :: 3",

    ],

    python_requires='>=3.6',
    
    install_requires=['progress','prettytable','scipy']

)


