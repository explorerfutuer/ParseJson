#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "Json.hpp"


TEST_CASE("json syntax-good check" , "[syntax-good]")
{
  SECTION("best brief example , str(ok)")
    {
      ParseNode pn("{\"str(ok)\":\"ok\"}") ;
      std::string strActual = pn.get_str_by_path("/str(ok)") ;
      std::string strExpect = "ok";
      REQUIRE(strActual == strExpect) ;
    }
  SECTION("best brief example , int(100)")
    {
      ParseNode pn("{\"int(100)\":100}") ;
      long long  intActual = pn.get_llong_by_path("/int(100)") ;
      long long  intExpect = 100 ;
      REQUIRE(intActual == intExpect) ;
    }
  // SECTION("best brief example , double(3.14)")
  //   {
  //     ParseNode pn("{\"double(3.14)\":3.14}") ;
  //   }
  // SECTION("best brief example , bool(true)")
  //   {
  //     ParseNode pn("{\"bool(true)\":true}") ;
  //   }
  // SECTION("best brief example , bool(false)")
  //   {
  //     ParseNode pn("{\"key\":\"value\"}") ;
  //   }
  // SECTION("best brief example , null")
  //   {
  //     ParseNode pn("{\"null\":null}") ;
  //   }
  // SECTION("best brief  , list(int)")
  //   {
  //     ParseNode pn("{\"list(1,2,3,4)\":[1,2,3,4]}") ;
  //   }
  // SECTION("best brief  , list(double)")
  //   {
  //     ParseNode pn("{\"list(1.0,2.0,3.0,4.0)\":[1.0,2.0,3.0,4.0]}") ;
  //   }
  // SECTION("best brief  , list(str)")
  //   {
  //     ParseNode pn("{\"list(l1,l2,l3,l4)\":[\"l1\",\"l2\",\"l3\",\"l4\"]}") ;
  //   }
  // SECTION("best brief  , list(int,double,str)")
  //   {
  //     ParseNode pn("{\"list(100,3.14,ok)\":[100,3.14,\"ok\"]}") ;
  //   }  
}


TEST_CASE("json syntax-bad check" , "[syntax-bad]")
{
}

TEST_CASE("json memory new-delete check" , "[syntax-memory]")
{
}
