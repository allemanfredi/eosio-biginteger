#include "lib/BigIntegerLibrary.hpp"  
#include <eosio/contract.hpp>
#include <eosio/eosio.hpp>

using namespace eosio;
using namespace std;

class [[eosio::contract("test")]] test : public contract {
  public:
      using contract::contract;

      BigInteger n = 65536;  
      BigUnsigned a = 34324;
      BigUnsigned b = 4321;
      BigUnsigned m = 7;

      [[eosio::action]]
      void execute(){
         print("n * n * n * n * n * n * n * n: ", ( n * n * n * n * n * n * n * n )); 
         print("(a + b) % c: " , addmod(a,b,m));
         print("(b - a) % c: " , submod(b,a,m));
         print("(a * b) % c: " , mulmod(a,b,m));
         print("(a / b) % c: " , divmod(a,b,m));
      }
};

