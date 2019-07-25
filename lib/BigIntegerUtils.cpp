/** 
 * This source adapted from https://mattmccutchen.net/bigint/ by allemanfredi for EOS.IO smart contract v1.6
 */
#include "BigIntegerUtils.hpp"
#include "BigUnsignedInABase.hpp"

std::string bigUnsignedToString( const BigUnsigned &x) {
	return std::string(BigUnsignedInABase(x, BigUnsignedInABase::Base(10) ) );
}

std::string bigIntegerToString( const  BigInteger &x) {
	return (x.getSign() == BigInteger::negative)
		? (std::string("-") + bigUnsignedToString(x.getMagnitude()))
		: (bigUnsignedToString(x.getMagnitude()));
}

BigUnsigned stringToBigUnsigned(const std::string &s) {
	return BigUnsigned(BigUnsignedInABase(s, BigUnsignedInABase::Base(10) ) );
}


class ext_string : public std::string {
public:
	ext_string( const std::string &cstr): std::string(cstr){}

	const std::string substr(size_t offset, size_t substr_size) {
		return (const std::string) ( std::string::substr( offset, substr_size ) ) ;
    }
};

BigInteger stringToBigInteger( const std::string &s) {
	// Recognize a sign followed by a BigUnsigned.
	const char signChar = s[0];
	ext_string childStr( s );
	
	return (signChar == '-') ? BigInteger(stringToBigUnsigned(childStr.substr(1, s.length() - 2)), BigInteger::negative)
		: (signChar == '+') ? BigInteger(stringToBigUnsigned(childStr.substr(1, s.length() - 2)))
		: BigInteger(stringToBigUnsigned(s));
}

