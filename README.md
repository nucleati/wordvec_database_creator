# wordvec_database_creator

Read word2vec binary file and store them in levelDB.

## Docker boilerplate to run the code

```Dockerfile 
FROM ubuntu:18.04
RUN apt-get --fix-missing update
RUN apt-get --assume-yes install gcc
RUN apt-get --assume-yes install g++
RUN apt-get --assume-yes install make
RUN apt-get --assume-yes install build-essential
RUN apt-get --assume-yes install libboost-all-dev
RUN apt-get --assume-yes install openssl
RUN apt-get --assume-yes install cmake
RUN apt-get --assume-yes install git
RUN apt-get --fix-missing update
RUN apt-get --assume-yes install curl
RUN apt-get --assume-yes install vim
RUN apt-get --assume-yes install libicu-dev git libjemalloc-dev zlib1g-dev liblzma-dev libboost-tools-dev
RUN apt-get --fix-missing update
RUN apt-get --assume-yes install libopenblas-dev liblapack-dev libarpack2-dev libsuperlu-dev libxml2-dev
# Level DB
WORKDIR /
RUN git clone --recurse-submodules https://github.com/google/leveldb.git
WORKDIR /leveldb
RUN mkdir build
WORKDIR /leveldb/build
RUN cmake -DCMAKE_BUILD_TYPE=Release .. && cmake --build .
RUN make
RUN make install```
