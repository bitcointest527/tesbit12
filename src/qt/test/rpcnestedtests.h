// Copyright (c) 2009-2017 The Bitcoin Core developers
// Copyright (c) 2019-2019 The bitcoinphantom Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef bitcoinphantom_QT_TEST_RPCNESTEDTESTS_H
#define bitcoinphantom_QT_TEST_RPCNESTEDTESTS_H

#include <QObject>
#include <QTest>

#include <txdb.h>
#include <txmempool.h>

class RPCNestedTests : public QObject
{
    Q_OBJECT

    private Q_SLOTS:
    void rpcNestedTests();
};

#endif // bitcoinphantom_QT_TEST_RPCNESTEDTESTS_H
