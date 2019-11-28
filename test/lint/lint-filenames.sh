#!/bin/bash
#
# Copyright (c) 2019 The Bitcoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.
#
# Make sure only lowercase alphanumerics (a-z0-9), underscores (_),
# hyphens (-) and dots (.) are used in source code filenames.

export LC_ALL=C

EXIT_CODE=0
OUTPUT=$(git ls-files -- "*.cpp" "*.h" "*.py" "*.sh" | grep -vE '^[a-z0-9_./-]+$' | grep -vE 'src/(secp256k1|univalue|crypto)/')
if [[ ${OUTPUT} != "" ]]; then
    echo "Use only lowercase alphanumerics (a-z0-9), underscores (_), hyphens (-) and dots (.)"
    echo "in source code filenames:"
    echo
    echo "${OUTPUT}"
    EXIT_CODE=1
fi
exit ${EXIT_CODE}
