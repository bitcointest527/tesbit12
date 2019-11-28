// Copyright (c) 2017 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef bitcoinphantom_RPC_MINING_H
#define bitcoinphantom_RPC_MINING_H

#include <script/script.h>
#include <rpc/server.h>

#include <univalue.h>

/** Check bounds on a command line confirm target */
unsigned int ParseConfirmTarget(const UniValue& value);

#endif // bitcoinphantom_RPC_MINING_H
