// Copyright (c) 2009-2017 The Bitcoin Core developers
// Copyright (c) 2019-2019 The bitcoinphantom Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef bitcoinphantom_RPC_UTIL_H
#define bitcoinphantom_RPC_UTIL_H

#include <pubkey.h>
#include <script/standard.h>
#include <univalue.h>

#include <boost/variant/static_visitor.hpp>

#include <string>
#include <vector>

class CKeyStore;
class CPubKey;
class CScript;

CPubKey HexToPubKey(const std::string& hex_in);
CPubKey AddrToPubKey(CKeyStore* const keystore, const std::string& addr_in);
CScript CreateMultisigRedeemscript(const int required, const std::vector<CPubKey>& pubkeys);

UniValue DescribeAddress(const CTxDestination& dest);

#endif // bitcoinphantom_RPC_UTIL_H
