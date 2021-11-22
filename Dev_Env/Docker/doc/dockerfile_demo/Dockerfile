FROM nvcr.io/nvidia/pytorch:19.06-py3
RUN apt-get update && \
    cd /opt/ && wget -c https://cmake.org/files/v3.13/cmake-3.13.2.tar.gz && \
    tar xvf cmake-3.13.2.tar.gz && cd cmake-3.13.2 && \ 
    ./configure && \
    make && make install && \
    echo 'export PATH=$PATH:/opt/cmake-3.13.2/bin' >> ~/.bashrc && source ~/.bashrc && \
    cd /workspace/ &&  apt -y install libboost-all-dev && \
    git clone https://github.com/traveller59/spconv.git --recursive && \
    cd spconv && git checkout 7342772 && \
    python setup.py bdist_wheel && \
    cd ./dist && pip install * && \
    cd ../.. && \
    git clone https://github.com/poodarchu/nuscenes.git && \
    cd nuscenes && \
    python setup.py install && \
    