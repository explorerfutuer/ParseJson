#include "Json.hpp"
int main(int argc , char* argv[])
{
  {
    ParseNode pn("") ;
    //    std::string strJson = "{\"aaa\":\"111\" , \t  \"bbb\":{\"xxx\":100,\"yyy\":3.14},\"bbb\":\"222\"}" ;
    //  std::string strJson = "{\"aaa\":111 , \"bbb\":\"222\"}" ;
    //  std::string strJson = "{\"aaa\":\"111\" , \t  \"bbb\":[100,3.14]}" ;
    std::string strJson = "{\"bbb\":[100,{\"x\":0.99,\"y\":\"yyy\"}]}" ;
    pn.parse_json(strJson) ;
  }
  std::cout << "-------------------------------------------" << std::endl ;
  return 0 ;
}
