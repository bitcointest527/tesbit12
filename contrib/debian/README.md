
Debian
====================
This directory contains files used to package bitcoinphantomd/bitcoinphantom-qt
for Debian-based Linux systems. If you compile bitcoinphantomd/bitcoinphantom-qt yourself, there are some useful files here.

## bitcoinphantom: URI support ##


bitcoinphantom-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install bitcoinphantom-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your bitcoinphantom-qt binary to `/usr/bin`
and the `../../share/pixmaps/bitcoinphantom128.png` to `/usr/share/pixmaps`

bitcoinphantom-qt.protocol (KDE)

