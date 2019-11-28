// Copyright (c) 2009-2017 The Bitcoin Core developers
// Copyright (c) 2019-2019 The bitcoinphantom Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef bitcoinphantom_QT_bitcoinphantomADDRESSVALIDATOR_H
#define bitcoinphantom_QT_bitcoinphantomADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class bitcoinphantomAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit bitcoinphantomAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** bitcoinphantom address widget validator, checks for a valid bitcoinphantom address.
 */
class bitcoinphantomAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit bitcoinphantomAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // bitcoinphantom_QT_bitcoinphantomADDRESSVALIDATOR_H
