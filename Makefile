CLIB_DIR=C

all: install

install_clib:
	mkdir -p $(CLIB_DIR)/build && cmake -DCMAKE_INSTALL_PREFIX=local/ -B $(CLIB_DIR)/build -S $(CLIB_DIR)
	cd $(CLIB_DIR)/build && make && make install

doc:
	sphinx-build -b html Docs/source Docs/build  

install: install_clib
	python3 -m pip install --upgrade setuptools
	python3 -m pip install .

clean:
	python3 -m pip uninstall -y sd_estimator    
	rm -rf build
	rm -rf C/build
	rm -rf SyndromeDecodingEstimator.egg-info
	rm -rf __pycache__
	rm -rf docs/build
	find ~/lib -maxdepth 1 -name 'lib_SyndromeDecodingEstimator*' -delete 


