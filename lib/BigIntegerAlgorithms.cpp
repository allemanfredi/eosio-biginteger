/** 
 * This source adapted from https://mattmccutchen.net/bigint/ by allemanfredi for EOS.IO smart contract v1.6
 */
#include "BigIntegerAlgorithms.hpp"
#include <eosio/system.hpp>

BigUnsigned gcd(BigUnsigned a, BigUnsigned b) {
	BigUnsigned trash;
	// Neat in-place alternating technique.
	for (;;) {
		if (b.isZero())
			return a;
		a.divideWithRemainder(b, trash);
		if (a.isZero())
			return b;
		b.divideWithRemainder(a, trash);
	}
}

void extendedEuclidean(BigInteger m, BigInteger n,
		BigInteger &g, BigInteger &r, BigInteger &s) {
	//gongsang
	eosio::check( &g != &r && &g != &s && &r != &s
		, "BigInteger extendedEuclidean: Outputs are aliased" );
	// if (&g == &r || &g == &s || &r == &s)
	// 	throw "BigInteger extendedEuclidean: Outputs are aliased";
	BigInteger r1(1), s1(0), r2(0), s2(1), q;
	/* Invariants:
	 * r1*m(orig) + s1*n(orig) == m(current)
	 * r2*m(orig) + s2*n(orig) == n(current) */
	for (;;) {
		if (n.isZero()) {
			r = r1; s = s1; g = m;
			return;
		}
		// Subtract q times the second invariant from the first invariant.
		m.divideWithRemainder(n, q);
		r1 -= q*r2; s1 -= q*s2;

		if (m.isZero()) {
			r = r2; s = s2; g = n;
			return;
		}
		// Subtract q times the first invariant from the second invariant.
		n.divideWithRemainder(m, q);
		r2 -= q*r1; s2 -= q*s1;
	}
}
   
BigUnsigned modinv(const BigInteger &x, const BigUnsigned &n) {
	BigInteger g, r, s;
	extendedEuclidean(x, n, g, r, s);
	if (g == 1)
		// r*x + s*n == 1, so r*x === 1 (mod n), so r is the answer.
		return (r % n).getMagnitude(); // (r % n) will be nonnegative
	else {
		//gongsang throw "BigInteger modinv: x and n have a common factor";
		eosio::check( 0, "BigInteger modinv: x and n have a common factor");
		return 0; // here will never be reached!
	}
} 

BigUnsigned modexp(const BigInteger &base, const BigUnsigned &exponent,
		const BigUnsigned &modulus) {
	BigUnsigned ans = 1, base2 = (base % modulus).getMagnitude();
	BigUnsigned::Index i = exponent.bitLength();
	// For each bit of the exponent, most to least significant...
	while (i > 0) {
		i--;
		// Square.
		ans *= ans;
		ans %= modulus;
		// And multiply if the bit is a 1.
		if (exponent.getBit(i)) {
			ans *= base2;
			ans %= modulus;
		}
	}
	return ans;
}

BigUnsigned addmod(const BigUnsigned &a, const BigUnsigned &b, 
		const BigUnsigned &modulus){
	return (a + b) % modulus;
}

BigUnsigned submod(const BigUnsigned &a, const BigUnsigned &b, 
		const BigUnsigned &modulus){
	//(a - b) % c = (c + a - b) % c => no overflow
	return (modulus + (a % modulus) - (b % modulus)) % modulus;
}

BigUnsigned mulmod(const BigUnsigned &a, const BigUnsigned &b,
		const BigUnsigned &modulus){
	
	BigUnsigned n1 = a;
	BigUnsigned n2 = b;
    BigUnsigned res = 0; 
	BigUnsigned one = 1;
	BigUnsigned two = 2;
  
    // Update n1 if it is more than 
    // or equal to mod 
    n1 %= modulus; 
  
    while (n2 > 0) 
    { 
        // If n2 is odd, add a with result 
        if (( n2 & one ) > 0) 
            res = (res + n1) % modulus; 
  
        // Here we assume that doing 2*n1
        // doesn't cause overflow 
        n1 = (two * n1) % modulus; 
  
        n2 >>= 1; // n2 = n2 / 2 
    } 
  
    return res; 
} 

/*
find a number c such that (b * c) % modulus = a % modulus.
The task is to compute a/b under modulo m.
Check if inverse of b under modulo exists or not. 
	if inverse doesn't exists (GCD of b and m is not 1), 
    else return  "(inv * a) % modulus" 
*/
BigUnsigned divmod(const BigUnsigned &a, const BigUnsigned &b,
		const BigUnsigned &modulus){	
	BigUnsigned n = a;
	n %= modulus; 
    BigUnsigned inv = modinv(b, modulus); 
	if (inv == 0) return 0;
	return (n * inv) % modulus;
}
