#include "Json.hpp"
int main(int argc , char* argv[])
{
  {
    ParseNode pn("") ;
    //    std::string strJson = "{\"aaa\":\"111\" , \t  \"bbb\":{\"xxx\":100,\"yyy\":3.14},\"bbb\":\"222\"}" ;
    //  std::string strJson = "{\"aaa\":111 , \"bbb\":\"222\"}" ;
    //  std::string strJson = "{\"aaa\":\"111\" , \t  \"bbb\":[100,3.14]}" ;
    //    std::string strJson = "{\"bbb\":[100,{\"x\":0.99,\"y\":\"yyy\"}]}" ;
    std::string strJson = "{\"bbb\":[100,{\"x\":0.99,\"y\":\"yyy\"}],\"a\":{\"b\":{\"c\":\"perfect\",\"x\":100}}}" ;
    pn.parse_json(strJson) ;
    JsonNode* pRootNode = pn.m_pRootJsonNode ;
    JsonNode* pTmpNode = pRootNode->get_node_by_path("/a/b/c") ;
    if(pTmpNode != NULL)
      {
	std::cout << "/a/b/c =>" << ((std::string*)pTmpNode->m_pDataNode)->c_str() <<  std::endl ;
      }
  }
  std::cout << "-------------------------------------------" << std::endl ;
  return 0 ;
}
