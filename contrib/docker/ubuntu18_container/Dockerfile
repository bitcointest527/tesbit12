FROM ubuntu:18.04

RUN apt-get update

RUN apt-get install -y build-essential
RUN apt-get install -y git
RUN apt-get install -y software-properties-common python-software-properties

RUN add-apt-repository ppa:bitcoin/bitcoin
RUN apt-get update

RUN apt-get install -y libdb4.8-dev libdb4.8++-dev libtool autotools-dev automake pkg-config libssl-dev libevent-dev \
    bsdmainutils git libboost-all-dev libminiupnpc-dev libqt5gui5 libqt5core5a libqt5webkit5-dev libqt5dbus5 qttools5-dev qttools5-dev-tools \
    libprotobuf-dev protobuf-compiler libqrencode-dev zlib1g-dev libseccomp-dev libcap-dev libncap-dev

#bitcoinphantom
RUN mkdir /root/bitcoinphantom
RUN git clone https://github.com/bitcoinphantom/bitcoinphantom /root/bitcoinphantom
RUN cd /root/bitcoinphantom/ ; /root/bitcoinphantom/autogen.sh
RUN cd /root/bitcoinphantom/ ; /root/bitcoinphantom/configure
RUN cd /root/bitcoinphantom/ ; make

RUN chmod 0777 /root/bitcoinphantom/src/*

ADD ./conf/bitcoinphantom.conf /root/.bitcoinphantom/bitcoinphantom.conf

WORKDIR /root/bitcoinphantom

EXPOSE 11211 11207

#CMD printenv | grep -v "yyyyyxxxx" >> /etc/environment && tail -f /dev/null

CMD /root/bitcoinphantom/src/bitcoinphantomd -printtoconsole
