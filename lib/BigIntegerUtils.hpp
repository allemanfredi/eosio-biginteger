/** 
 * This source adapted from https://mattmccutchen.net/bigint/ by allemanfredi for EOS.IO smart contract v1.6
 */
#ifndef BIGINTEGERUTILS_H
#define BIGINTEGERUTILS_H

#include "BigInteger.hpp"
#include <string>

// std::string conversion routines.  Base 10 only.
std::string bigUnsignedToString( const BigUnsigned &x);
std::string bigIntegerToString( const BigInteger &x);
BigUnsigned stringToBigUnsigned( const std::string &s);
BigInteger stringToBigInteger( const std::string &s);

// Creates a BigInteger from data such as `char's; read below for details.
template <class T>
BigInteger dataTobint( T* data, BigInteger::Index length, BigInteger::Sign sign);

#endif
