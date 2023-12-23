FROM ubuntu:18.04
LABEL Description="Build environment"

ENV HOME /root

COPY . ${HOME}/my_proj

SHELL ["/bin/bash", "-c"]

RUN apt-get update && apt-get -y --no-install-recommends install \
    apt-utils \
    build-essential \
    clang \
    cmake \
    gdb \
    wget \
    vim

RUN apt update && apt install -y debconf debconf-utils

# Let us add some heavy dependency
RUN cd ${HOME} && \
    wget --no-check-certificate --quiet \
        https://boostorg.jfrog.io/artifactory/main/release/1.77.0/source/boost_1_77_0.tar.gz && \
        tar xzf ./boost_1_77_0.tar.gz && \
        cd ./boost_1_77_0 && \
        ./bootstrap.sh && \
        ./b2 install && \
        cd .. && \
        rm -rf ./boost_1_77_0

