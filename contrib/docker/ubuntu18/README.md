Copied from here: 
   https://github.com/bitcoinphantom/Docker-bitcoinphantom-Daemon

To build:
---
    docker build --rm -t bitcoinphantom/bitcoinphantom:5.0.0-ubuntu18 .


Before running:
---
Place bitcoinphantom.conf in /tmp/bitcoinphantom/.bitcoinphantom/bitcoinphantom.conf on the HOST system. You probably want something a directory other than /tmp, I am just using it to test that everything works. It will need to have at least these two values (like this):

    rpcuser=bitcoinrpc
    rpcpassword=Bnec4eGig52MTEAkzk4uMjsJechM7rA9EQ4NzkDHLwpG


Test that the docker runs:
---
    mkdir -p tmpbitcoinphantom/.bitcoinphantom
    echo "rpcuser=bitcoinrpc" > tmpbitcoinphantom/.bitcoinphantom/bitcoinphantom.conf
    echo "rpcpassword=Bnec4eGig52MTEAkzk4uMjsJechM7rA9EQ4NzkDHLwpG" >> tmpbitcoinphantom/.bitcoinphantom/bitcoinphantom.conf


To run:
---
    docker run -d --name bitcoinphantom:ubuntu18 -v `pwd`/tmpbitcoinphantom:/coin/home -p 11207:11207 -p 11211:11211 bitcoinphantom

This command should return a container id. You can use this id (or the first few characters of it to refer to later. We added a name option above so we can just refer to it as 'bitcoinphantom'.)

To watch the debug log:
---
    tail -f tmpbitcoinphantom/.bitcoinphantom/debug.log

To connect to the running container
---
    docker exec -it bitcoinphantom:ubuntu14 bash

To kill the running container:
---
    docker kill bitcoinphantom:ubuntu14

To remove the stopped container:
---
    docker rm bitcoinphantom:ubuntu14


To run bitcoinphantom wallet on a Synology using this docker image:
---
* Create a folder that will have the bitcoinphantom wallet configuration. Open up 'Filestation', select 'home', then 'create folder'. I'll use 'bitcoinphantom' as the name for the folder. (full path of "home/mkinney/bitcoinphantom")

* This folder should be visible to your computer, because you will need to create a configuration file in this folder. Follow the instructions at: [the bitcoinphantom github page](https://github.com/bitcoinphantom/bitcoinphantom) for more info. 

    Be sure to create the bitcoinphantom.conf in a folder called ".bitcoinphantom". I have "home" mounted to my mac, so I see it as '/Volumes/home/bitcoinphantom/.bitcoinphantom/bitcoinphantom.conf'. 
    
    Be sure to *NOT* set ```daemon=1```, if so, then the container will stop, then re-start, and repeat.
    
* Start docker. Click 'main menu', then 'Docker'. (If you do not see that option, you will have install the Docker package on the Synology.)

* Click on 'Image', then 'Add', 'from URL', and enter ```https://hub.docker.com/r/bitcoinphantom/bitcoinphantom/```

* Wait for it to download.

* Click on the image in the list, then click 'Launch', feel free to change the 'Container Name' or ports (but the defaults should be fine).

* Accept (or change if you want) the Step 2 options (resource limitation, shortcut on desktop, enable auto-restart). I think it makes sense to check "shortcut" and "auto restart".

* Summary (click the 'Advanced settings' button - this is easy to miss!)

* Under 'Volume', click 'add folder' and select a folder (I'm using '/homes/mkinney/bitcoinphantom'). For the 'Mount path', enter '/coin/home'

* Start up the container. You should see files in the .bitcoinphantom directory.
