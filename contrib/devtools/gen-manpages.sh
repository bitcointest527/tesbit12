#!/bin/bash

export LC_ALL=C
TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
BUILDDIR=${BUILDDIR:-$TOPDIR}

BINDIR=${BINDIR:-$BUILDDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

bitcoinphantomD=${bitcoinphantomD:-$BINDIR/bitcoinphantomd}
bitcoinphantomCLI=${bitcoinphantomCLI:-$BINDIR/bitcoinphantom-cli}
bitcoinphantomTX=${bitcoinphantomTX:-$BINDIR/bitcoinphantom-tx}
bitcoinphantomQT=${bitcoinphantomQT:-$BINDIR/qt/bitcoinphantom-qt}

[ ! -x $bitcoinphantomD ] && echo "$bitcoinphantomD not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
XSHVER=($($bitcoinphantomCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for bitcoinphantomd if --version-string is not set,
# but has different outcomes for bitcoinphantom-qt and bitcoinphantom-cli.
echo "[COPYRIGHT]" > footer.h2m
$bitcoinphantomd --version | sed -n '1!p' >> footer.h2m

for cmd in $bitcoinphantomd $bitcoinphantomCLI $bitcoinphantomTX $bitcoinphantomQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${XSHVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${XSHVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
