Note: This is for cross compiling windows binaries using ubuntu

# To build:

At first we should build docker images for building the application for Windows x64 and Windows x32:

```
$ sudo docker build --file ./Dockerfile-bitcoinphantom-win64 --tag bitcoinphantom-win64/ubuntu:18.04 .
$ sudo docker build --file ./Dockerfile-bitcoinphantom-win32 --tag bitcoinphantom-win32/ubuntu:18.04 .
```

After the images will be built successfully we can run them and build the application itself.
Please note that it is recommended to clone git repository from the host machine and share the directory with the images.

For Windows x64:

```
$ sudo docker run -ti -v <path-to-bitcoinphantom-source-codes>:/bitcoinphantom bitcoinphantom-win64/ubuntu:18.04 bash
$ /tmp/build.sh
```

For Windows x32:

```
$ sudo docker run -ti -v <path-to-bitcoinphantom-source-codes>:/bitcoinphantom bitcoinphantom-win32/ubuntu:18.04 bash
$ /tmp/build.sh
```



