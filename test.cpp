#include "lib/BigIntegerLibrary.hpp"  
#include <eosio/contract.hpp>
#include <eosio/eosio.hpp>

using namespace eosio;
using namespace std;

class [[eosio::contract("test")]] test : public contract {
  public:
      using contract::contract;

      BigInteger a = 65536;  

      [[eosio::action]]
      void execute(){
         print("a * a * a * a * a * a * a * a: ", ( a * a * a * a * a * a * a * a ) ); 
      }
};

