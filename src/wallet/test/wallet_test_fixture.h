// Copyright (c) 2009-2017 The Bitcoin Core developers
// Copyright (c) 2019-2019 The bitcoinphantom Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef bitcoinphantom_WALLET_TEST_WALLET_TEST_FIXTURE_H
#define bitcoinphantom_WALLET_TEST_WALLET_TEST_FIXTURE_H

#include <test/setup_common.h>

#include <wallet/wallet.h>

#include <memory>

/** Testing setup and teardown for wallet.
 */
struct WalletTestingSetup: public TestingSetup {
    explicit WalletTestingSetup(const std::string& chainName = CBaseChainParams::MAIN);
    ~WalletTestingSetup();

    CWallet m_wallet;
};

#endif // bitcoinphantom_WALLET_TEST_WALLET_TEST_FIXTURE_H
