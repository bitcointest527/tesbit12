// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainparams.h>
#include <consensus/merkle.h>

#include <tinyformat.h>
#include <util/system.h>
#include <util/strencodings.h>

#include <assert.h>

#include <chainparamsseeds.h>
#include <arith_uint256.h>

static CBlock CreateGenesisBlock(const char* pszTimestamp, Crypto the voice for the voiceless)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.nTime = nTime;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].SetEmpty();

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, bool isTestnet = false)
{
    const char* pszTimestamp = isTestnet ? "bitcoinphantom TESTNET" : "Name: Dogecoin Dark";
    return CreateGenesisBlock(pszTimestamp, nTime, nNonce, nBits, nVersion);
}

void CChainParams::UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    consensus.vDeployments[d].nStartTime = nStartTime;
    consensus.vDeployments[d].nTimeout = nTimeout;
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.ForkHeight = 2800000;
        consensus.MULTI_ALGO_SWITCH_BLOCK = 340000;
        consensus.STEALTH_TX_SWITCH_BLOCK = 1824150;
        consensus.FlexibleMiningAlgorithms = 2042000;
        consensus.CLOCK_DRIFT_FORK = 2218500;
        consensus.nSubsidyHalvingInterval = 500000;

        consensus.BIP34Height = consensus.ForkHeight;
        consensus.BIP65Height = consensus.ForkHeight;
        consensus.BIP66Height = consensus.ForkHeight;


        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000"); //ArithToUint256(~arith_uint256(0) >> 20);
        consensus.nPowTargetTimespan = 30; // diff readjusting time
        consensus.nPowTargetSpacing = 30; //
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 100; // 100 out of 200 blocks
        consensus.nMinerConfirmationWindow = 200;

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1529247969; // May 1st, 2016
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1559347200; // May 1st, 2017

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        // It is all safe :thumbsup:
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1529247969; // November 15th, 2016.
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1559347200; // November 15th, 2017.

        // The best chain should have at least this much work.
        // KeyNote: (Kind of like a checkpoint)
        consensus.nMinimumChainWork = uint256S("0x000000000000000000000000000000000000000000000000000000222e000001");

        // By default assume that the signatures in ancestors of this block are valid.
        // KeyNote: Seems like speedup, similar to a checkpoint
        consensus.defaultAssumeValid = uint256S("0xc766387a2e0cd6af995ea432518614824fe313e988598ea8b26f58efb99ebcdc"); // block 1,100,000

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xf9;
        pchMessageStart[1] = 0xa6;
        pchMessageStart[2] = 0x7d;
        pchMessageStart[3] = 0xfa;
        nDefaultPort = 11211;
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1574851424, 1562391, 0xde00000, 1);
        consensus.hashGenesisBlock = genesis.GetHash();

        assert(genesis.hashMerkleRoot == uint256S("0x1c83275d9151711eec3aec37d829837cc3c2730b2bdfd00ec5e8e5dce675fd00"));
        assert(consensus.hashGenesisBlock == uint256S("0x00000fc63692467faeb20cdb3b53200dc601d75bdfa1001463304cc790d77278"));

        // Note that of those which support the service bits prefix, most only support a subset of
        // possible options.
        // This is fine at runtime as we'll fall back to using them as a oneshot if they don't support the
        // service bits we want, but we should get them updated to support all service bits wanted by any
        // release ASAP to avoid it where possible.

        // Adding some nodes in case it works
        if(!gArgs.IsArgSet("-without-tor")){
            vSeeds.emplace_back("lhvnwvqdlxxyotdmfej45jgphupxob5fci4hjxvw2ui75e24tjssl2id.onion");
            vSeeds.emplace_back("n7rk4xqurrvedhhghkkvz2pmxalgmoviokgjiwjgcvpcxa6piym5m2ad.onion");
            vSeeds.emplace_back("amafdqgkmtbkld45kaal5cwwfbrsgnimw77gawwltsaklgxxlubjvhid.onion");
            vSeeds.emplace_back("gasppfoxxedddnme.onion");
            vSeeds.emplace_back("oxcfjsfmkrqjehjy.onion");
            vSeeds.emplace_back("bnm5ujfsvexzba4w.onion");
            vSeeds.emplace_back("sarpou7gsi7nan5m.onion");
            vSeeds.emplace_back("4j3cz66g4z5o4aso.onion");
            vSeeds.emplace_back("fqsvfu5gcmjox26m.onion");
            vSeeds.emplace_back("kte6vpxfpim5lwqv.onion");
            vSeeds.emplace_back("3z4vuj5k5xymy5su.onion");
            vSeeds.emplace_back("ruxut6k4a6d4qe53.onion");
            vSeeds.emplace_back("wfyfkm6j3vcuw2qz.onion");
            vSeeds.emplace_back("cit2rtwxzwxrmory.onion");
            vSeeds.emplace_back("vwym36tts7zhm24k.onion");
            vSeeds.emplace_back("jzo6govpwfeauspf.onion");
            vSeeds.emplace_back("ngfxjjrrtxteffvt.onion");
            vSeeds.emplace_back("y2czcambifo2ybdm.onion");
            vSeeds.emplace_back("6telhbsuva4qkff2.onion");
        } else {
            vSeeds.emplace_back("seed.marpmedev.xyz"); // marples DNS seed (v4, v5)
            vSeeds.emplace_back("seed.bitcoinphantom.dev"); // additional DNS seed
            vSeeds.emplace_back("185.162.9.97");
            vSeeds.emplace_back("159.89.46.252"); // v5-new-york
            vSeeds.emplace_back("139.59.34.170"); // v5-india
            vSeeds.emplace_back("134.209.197.243"); // v5-NL
            vSeeds.emplace_back("104.131.144.82");
            vSeeds.emplace_back("192.241.187.222");
            vSeeds.emplace_back("105.228.198.44");
            vSeeds.emplace_back("46.127.57.167");
            vSeeds.emplace_back("98.5.123.15");
            vSeeds.emplace_back("81.147.68.236");
            vSeeds.emplace_back("77.67.46.100");
            vSeeds.emplace_back("95.46.99.96");
            vSeeds.emplace_back("138.201.91.159");
            vSeeds.emplace_back("159.89.202.56");
            vSeeds.emplace_back("163.158.20.118");
            vSeeds.emplace_back("99.45.88.147");
            vSeeds.emplace_back("114.145.237.35");
            vSeeds.emplace_back("73.247.117.99");
            vSeeds.emplace_back("145.239.0.122");
        }



        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,80);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,80);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,138); //128 + PUBKEY_ADDRESS
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x2C, 0x28, 0x39};

        bech32_hrp = "vg";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;

        checkpointData = {
            {
				0x0
            }
        };

        checkpointIndexData = {
            {
                0x0
            }
        };

        // FIXME: need to know the amount of transactions
        chainTxData = ChainTxData{
            // Data as of block 0000000000000000002d6cca6761c99b3c2e936f9a0e304b7c7651a993f461de (height 506081).
            1574851566, // * UNIX timestamp of last known number of transactions
            30000,  // * total number of transactions between genesis and that timestamp
                        //   (the tx=... number in the SetBestChain debug.log lines)
            30000         // * estimated number of transactions per second after that timestamp
        };

        /* disable fallback fee on mainnet */
        m_fallback_fee_enabled = false;
    }
};

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        // KeyNote: we'll leave testnet as is for now
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 210000;
        consensus.MULTI_ALGO_SWITCH_BLOCK = 340000;
        consensus.STEALTH_TX_SWITCH_BLOCK = 1824150;
        consensus.FlexibleMiningAlgorithms = 2042000;
        consensus.CLOCK_DRIFT_FORK = 2218500;

        consensus.BIP34Height = 0;
        consensus.BIP65Height = 0; // 00000000007f6655f22f98e72ed80d8b06dc761d5da09df0fa1dc4be4f861eb6
        consensus.BIP66Height = 0; // 000000002104c8c45e99a8853285a3b592602a3ccde2b832481da85e9e4ba182
        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000"); // FIXME: change to actual genesis limit
        consensus.nPowTargetTimespan = 12 * 30 * 30; // 0.5 day
        consensus.nPowTargetSpacing = 45;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1512; // 75% for testchains
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1574852125; // December 21st, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1574852192; // June 21st, 2019

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1574852488; // December 21st, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1574852545; // June 21st, 2019

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x000000000000000000000000000000000000000000000000000000000000000000f");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x65b4e101cacf3e1e4f3a9237e3a74ffd1186e595d8b78fa8ea22c21ef5bf9347"); //also genesis

        pchMessageStart[0] = 0xcb;
        pchMessageStart[1] = 0xf4;
        pchMessageStart[2] = 0xc2;
        pchMessageStart[3] = 0xed;
        nDefaultPort = 11213;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1574852609, 2, 0xdec000cd, 1, true);
        consensus.hashGenesisBlock = genesis.GetHash();

        assert(consensus.hashGenesisBlock == uint256S("0x65b4e101cacf3e1e4f3a9237e3a74ffd1186e595d8b78fa8ea22c21ef5bf9347"));
        assert(genesis.hashMerkleRoot == uint256S("0x768cc22f70bbcc4de26f83aca1b4ea2a7e25f0d100497ba47c7ff2d9b696414c"));

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.emplace_back("2l7hxpeyhmy4c2tnlmgf7rgcn6epsaaspv7473f3r5uncqzs6pnltqqd.onion");
        vSeeds.emplace_back("qwwqi7h6bkkcw6clp34ttg5mxmcwerkot2hepfhi6g4yclvlhsv2kxid.onion");
        vSeeds.emplace_back("2l7hxpeyhmy4c2tnlmgf7rgcn6epsaaspv7473f3r5uncqzs6pnltqqd.onion");

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,80);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,80);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,126); // 128 + PUBKEY_ADDRESS_TEST
        base58Prefixes[EXT_PUBLIC_KEY] = {0x06, 0x80, 0x97, 0xDD};
        base58Prefixes[EXT_SECRET_KEY] = {0x08, 0x88, 0x89, 0x74};

        bech32_hrp = "vt";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;


        checkpointData = {
            {
                0x0
            }
        };

        chainTxData = ChainTxData{
            // Data as of block e3fe6040c157d64e636fecb6cb766e6221d8d4f102b3e4da457d0ca4741884d5 (height 1042701)
            1574853689,
            1,
            0.1
        };

        /* enable fallback fee on testnet */
        m_fallback_fee_enabled = true;
    }
};

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        consensus.BIP34Height = 100000000; // BIP34 has not activated on regtest (far in the future so block v1 are not rejected in tests)
        consensus.BIP65Height = 1351; // BIP65 activated on regtest (Used in rpc activation tests)
        consensus.BIP66Height = 1251; // BIP66 activated on regtest (Used in rpc activation tests)
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 3.5 * 12 * 30 * 30; // half week
        consensus.nPowTargetSpacing = 30;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0xfb;
        pchMessageStart[1] = 0xbc;
        pchMessageStart[2] = 0xb8;
        pchMessageStart[3] = 0xdc;
        nDefaultPort = 8333;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1574852918, 2, 0xdec000cd, 1);
        consensus.hashGenesisBlock = genesis.GetHash();
        //assert(consensus.hashGenesisBlock == uint256S("0x65b4e101cacf3e1e4f3a9237e3a74ffd1186e595d8b78fa8ea22c21ef5bf9347"));
        //assert(genesis.hashMerkleRoot == uint256S("0x768cc22f70bbcc4de26f83aca1b4ea2a7e25f0d100497ba47c7ff2d9b696414c"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;

        checkpointData = {
            {
                0x0
            }
        };

        chainTxData = ChainTxData{
            0x0,


        };

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,80);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,80);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "vgrt";

        /* enable fallback fee on regtest */
        m_fallback_fee_enabled = true;
    }
};

static std::unique_ptr<CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams());
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}

void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    globalChainParams->UpdateVersionBitsParameters(d, nStartTime, nTimeout);
}
