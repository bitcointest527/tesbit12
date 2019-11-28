# Dockerfile for bitcoinphantom
# http://bitcoinphantom.com/
# https://bitcointalk.org/index.php?topic=1365894
# https://github.com/bitcoinphantom/bitcoinphantom

# https://github.com/bitcoinphantom/Docker-bitcoinphantom-Daemon.git
#  Jeremiah Buddenhagen <bitspill@bitspill.net>

FROM ubuntu:18.04

MAINTAINER Mike Kinney <mike.kinney@gmail.com> / Sunerok

ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update --yes > /dev/null && \
    apt-get upgrade --yes > /dev/null && \
    apt-get install --yes -qq software-properties-common > /dev/null && \
    add-apt-repository --yes ppa:bitcoin/bitcoin && \
    apt-get update --yes > /dev/null && \
    apt-get upgrade --yes > /dev/null && \
    apt-get install --yes -qq \
       autoconf \
       automake \
       autotools-dev \
       bsdmainutils \
       build-essential \
       git \
       libboost-all-dev \
       libboost-filesystem-dev \
       libboost-program-options-dev \
       libboost-system-dev \
       libboost-test-dev \
       libboost-thread-dev \
       libcap-dev \
       libncap-dev \
       libdb4.8++-dev \
       libdb4.8-dev \
       libevent-dev \
       libminiupnpc-dev \
       libprotobuf-dev \
       libqrencode-dev \
       libqt5core5a \
       libqt5dbus5 \
       libqt5gui5 \
       libseccomp-dev \
       libsqlite3-dev \
       libssl-dev \
       libtool \
       pkg-config \
       protobuf-compiler \
       qt5-default \
       qtbase5-dev \
       qtdeclarative5-dev \
       qttools5-dev \
       qttools5-dev-tools \
       zlib1g-dev \
      > /dev/null

RUN git clone https://github.com/bitcoinphantom/bitcoinphantom.git /coin/git

WORKDIR /coin/git

RUN ./autogen.sh && ./configure --with-gui=qt5 && make && mv src/bitcoinphantomd /coin/bitcoinphantomd

WORKDIR /coin
VOLUME ["/coin/home"]

ENV HOME /coin/home

CMD ["/coin/bitcoinphantomd"]

# P2P, RPC
EXPOSE 11211 11207
