#include <list>
#include <exception>
#include <iostream>

class JsonNode ;

typedef std::list<char>  Type_List_Char ;
typedef std::list<JsonNode*> ListJsonNode ;

enum JsonNodeType
  {
    JSON_ERR ,
    JSON_BOOL ,
    JSON_NULL ,
    JSON_INT ,
    JSON_LONGLONG ,
    JSON_DOUBLE ,
    JSON_STR ,
    JSON_OBJ ,
    JSON_LIST
  };

class JsonNode
{
public:
  JsonNode(const char* _szKey)
  {
    this->m_strKeyName = _szKey ;
    this->m_pDataNode = NULL ;
    this->m_NodeType = JSON_ERR ;
  }
  JsonNode(const std::string& _strKey)
  {
    this->m_strKeyName = _strKey ;
    this->m_pDataNode = NULL ;
    this->m_NodeType = JSON_ERR ;
  }
  void init_node(JsonNodeType _type , void* _pVal)
  {
    this->m_NodeType = _type ;
    switch(this->m_NodeType)
      {
      case JSON_ERR:
	{
	  break ;
	}
      case JSON_BOOL:
      case JSON_NULL:
      case JSON_INT:
	{
	  this->m_pDataNode = new int (*(int*)_pVal) ;
	  break ;
	}
      case JSON_LONGLONG:
	{
	  this->m_pDataNode = new long long (*(long long*)_pVal);
	  break ;
	}
      case JSON_DOUBLE:
	{
	  this->m_pDataNode = new double(*(double*)_pVal) ;
	  break ;
	}
      case JSON_STR:
	{
	  this->m_pDataNode = (new std::string(*(std::string*)_pVal))  ;
	  break ;
	}
      case JSON_OBJ:
      case JSON_LIST:
	{
	  this->m_pDataNode = new std::list<JsonNode*>() ;
	  break ;
	}
      }
  }
  ~JsonNode()
  {
    if(this->m_pDataNode == NULL)
	  return ;
    std::cout << "destory JsonNode " << this->m_strKeyName << std::endl ;
    switch(this->m_NodeType)
      {
      case JSON_ERR:
	{
	  break ;
	}
      case JSON_BOOL:
      case JSON_NULL:
      case JSON_INT:
	{
	  delete ((int*)this->m_pDataNode) ;
	  break ;
	}
      case JSON_LONGLONG:
	{
	  delete ((long long *)this->m_pDataNode) ;
	  break ;
	}
      case JSON_DOUBLE:
	{
	  delete ((double *)this->m_pDataNode) ;
	  break ;
	}
      case JSON_STR:
	{
	  delete ((std::string*)this->m_pDataNode) ;
	  break ;
	}
      case JSON_OBJ:
	{
	  ListJsonNode* pListNode = (ListJsonNode*)this->m_pDataNode ;
	  ListJsonNode::iterator begIt , endIt ;
	  for( begIt = pListNode->begin() , endIt = pListNode->end() ; begIt != endIt ; ++begIt)
	    {
	      JsonNode* pJN = *(begIt) ;
	      delete pJN ;
	    }
	  delete pListNode ;
	  break ;
	}
      case JSON_LIST:
	{
	  ListJsonNode* pListNode = (ListJsonNode*)this->m_pDataNode ;
	  ListJsonNode::iterator begIt , endIt ;
	  for( begIt = pListNode->begin() , endIt = pListNode->end() ; begIt != endIt ; ++begIt)
	    {
	      JsonNode* pJN = *(begIt) ;
	      delete pJN ;
	    }
	  break ;
	}
      }
    this->m_pDataNode = NULL ;
  }
  void set_node_value(void* _pVal)
  {
    switch(this->m_NodeType)
      {
	case JSON_ERR:
	  {
	    break ;
	  }
	case JSON_BOOL:
	case JSON_NULL:
	case JSON_INT:
	  {
	    (*(int *)this->m_pDataNode) = *((int*) _pVal) ;
	    break ;
	  }
	case JSON_LONGLONG:
	  {
	    (*(long long*)this->m_pDataNode) = (*(long long*)_pVal)  ;
	    break ;
	  }
	case JSON_DOUBLE:
	  {
	    (*(double*)this->m_pDataNode) = (*(double*)_pVal) ;
	    break ;
	  }
	case JSON_STR:
	  {
	    (*(std::string*)this->m_pDataNode) = (*(std::string*)_pVal) ;
	    break ;
	  }
	case JSON_OBJ:
	case JSON_LIST:
	  {
	    std::list<JsonNode*>* pListData = (std::list<JsonNode*>*)this->m_pDataNode ;
	    pListData->push_back((JsonNode*)_pVal) ;
	    break ;
	  }
	}
    }
  void print_tree()
  {
    switch(this->m_NodeType)
      {
      case JSON_ERR:
	{
	  break ;
	}
      case JSON_BOOL:
      case JSON_NULL:
      case JSON_INT:
	{
	  std::cout << this->m_strKeyName << "\t(int)=>" << (*(int*)this->m_pDataNode) << std::endl ;
	  break ;
	}
      case JSON_LONGLONG:
	{
	  std::cout << this->m_strKeyName << "\t(long long)=>" << (*(long long*)this->m_pDataNode) << std::endl ;
	  break ;
	}
      case JSON_DOUBLE:
	{
	  std::cout << this->m_strKeyName << "\t(double)=>" << (*(double*)this->m_pDataNode) << std::endl ;
	  break ;
	}
      case JSON_STR:
	{
	  std::cout << this->m_strKeyName << "\tstring=>" << (*(std::string*)this->m_pDataNode) << std::endl ;
	  break ;
	}
      case JSON_OBJ:
      case JSON_LIST:
	{
	  ListJsonNode* pListNode = (ListJsonNode*)this->m_pDataNode ;
	  ListJsonNode::iterator begIt , endIt ;
	  for( begIt = pListNode->begin() , endIt = pListNode->end() ; begIt != endIt ; ++begIt)
	    {
	      JsonNode* pJN = *(begIt) ;
	      std::cout << this->m_strKeyName << "\t" ;
	      pJN->print_tree() ;
	    }
	  break ;
	}
      }
  }
public:
  JsonNodeType    m_NodeType ;
  JsonNode*       m_pParentNode ;
  void*           m_pDataNode ;
  std::string     m_strKeyName ;
};


class ModeStack
{
public:
  ModeStack()
  {
    this->m_iSizeQueue = 0 ;
    this->m_ModeQueue.clear() ;
  }
  void  push_mode(char _ch , JsonNode* _pjn)
  {
    this->m_ModeQueue.push_back(_ch) ;
    ++(this->m_iSizeQueue) ;
    this->m_NodeQueue.push_back(_pjn) ;
  }
  char  top_mode()
  {
    return this->m_ModeQueue.back() ;
  }
  JsonNode* top_node()
  {
    return this->m_NodeQueue.back() ;
  }
  char pop_mode()
  {
    if(this->m_iSizeQueue <= 0)
      throw "does't match {} or []" ;
    char ch = this->m_ModeQueue.back() ;
    this->m_ModeQueue.pop_back() ;
    this->m_NodeQueue.pop_back() ;
    --(this->m_iSizeQueue) ;
    return ch ;
  }
private:
  int m_iSizeQueue ;
  std::list<char> m_ModeQueue ;
  std::list<JsonNode*> m_NodeQueue ;
};

class ParseNode
{
public:
  ParseNode(const std::string& _strJson){}
  ~ParseNode()
  {
    this->destroy_jsonnode() ;
  }
  void destroy_jsonnode()
  {
    std::cout << "destory ParseNode" << std::endl ;
    if(this->m_pRootJsonNode != NULL)
      {
	delete this->m_pRootJsonNode ;
      }
    this->m_pRootJsonNode = NULL ;
  }
  void parse_json(const std::string& _strJson)
  {
    this->m_pFocus = _strJson.c_str() ;
    this->m_pTerminal = _strJson.c_str() + _strJson.size() ;
    try
      {
	this->m_bStatus = false ;
	this->skip_black_char() ;
	if(*(this->m_pFocus++) != '{')
	  {
	    this->m_strErr = "json must start with '{'" ;
	    this->m_strTip = std::string(this->m_pFocus , this->m_pTerminal) ;
	    return ;
	  }
	this->m_pRootJsonNode = new JsonNode("/") ;
	this->m_pRootJsonNode->init_node(JSON_OBJ , NULL) ;
	this->m_ModeStack.push_mode('{' , this->m_pRootJsonNode) ;
	this->parse_obj() ;
	this->m_bStatus = true ;
	this->m_pRootJsonNode->print_tree() ;
      }
    catch (std::string strErr)
      {
	std::cout << strErr << std::endl ;
      }
    catch(const char* szErr)
      {
	std::cout << szErr << std::endl ;
      }
    if(!this->m_bStatus)
      {
	this->destroy_jsonnode() ;
      }
    std::cout << "Err:" << this->m_strErr << std::endl ;
    std::cout << "Tip:" << this->m_strTip << std::endl ;
  }

  void parse_list()
  {
    int iIndexCnt = 0 ;
    char bufIndexCnt[32] ;
    for( ; this->m_pFocus < this->m_pTerminal ; ++(this->m_pFocus))
      {
	this->skip_black_char() ;
	switch(*(this->m_pFocus))
	  {
	  case '}':
	    {
	      if(this->m_ModeStack.pop_mode() != '{')
		{
		  this->m_strErr = "does't match {}" ;
		  this->m_strTip = std::string(this->m_pFocus , this->m_pTerminal) ;
		  throw this->m_strErr ;
		}
	      return ;
	    }
	  case ']':
	    {
	      if(this->m_ModeStack.pop_mode() != '[')
		{
		  this->m_strErr = "does't match []" ;
		  this->m_strTip = std::string(this->m_pFocus , this->m_pTerminal) ;
		  throw this->m_strErr ;
		}
	      return ;
	    }
	  case ',':
	    continue ;
	  default: ;
	  }
	snprintf(bufIndexCnt , 32 , "%d" , iIndexCnt++) ;
	this->m_strKey = bufIndexCnt ;
	switch(*(this->m_pFocus))
	  {
	  case '{':
	    {
	      ++(this->m_pFocus) ;
	      JsonNode* pTmpNode = new JsonNode(this->m_strKey) ;
	      pTmpNode->init_node(JSON_OBJ , NULL) ;
	      this->m_ModeStack.top_node()->set_node_value(pTmpNode) ;
	      this->m_ModeStack.push_mode('{' , pTmpNode) ;
	      this->parse_obj() ;
	      break ;
	    }
	  case '[':
	    {
	      ++(this->m_pFocus) ;
	      JsonNode* pTmpNode = new JsonNode(this->m_strKey) ;
	      pTmpNode->init_node(JSON_LIST , NULL) ;
	      this->m_ModeStack.top_node()->set_node_value(pTmpNode) ;
	      this->m_ModeStack.push_mode('[' , pTmpNode) ;
	      this->parse_list() ;
	      break ;
	    }
	  case '"':
	    {
	      this->m_strVal = this->json_str() ;
	      JsonNode* pTmpNode = new JsonNode(this->m_strKey) ;
	      pTmpNode->init_node(JSON_STR , &this->m_strVal) ;
	      this->m_ModeStack.top_node()->set_node_value(pTmpNode) ; 
	      break ;
	    }
	  default:
	    {
	      this->m_strVal = this->json_int() ;
	      this->confirm_json_value() ;
	      break ;
	    }
	  }
	std::cout << "list Val=" << this->m_strVal << std::endl ;
      }
  }
  void parse_obj()
  {
    for( ; this->m_pFocus < this->m_pTerminal ; ++(this->m_pFocus))
      {
	  this->skip_black_char() ;
	  switch(*(this->m_pFocus))
	    {
	    case '}':
	      {
		if(this->m_ModeStack.pop_mode() != '{')
		  {
		    this->m_strErr = "does't match {}" ;
		    this->m_strTip = std::string(this->m_pFocus , this->m_pTerminal) ;
		    throw this->m_strErr ;
		  }
		return ;
	      }
	    case ']':
	      {
		if(this->m_ModeStack.pop_mode() != '[')
		  {
		    this->m_strErr = "does't match []" ;
		    this->m_strTip = std::string(this->m_pFocus , this->m_pTerminal) ;
		    throw this->m_strErr ;
		  }
		return ;
	      }
	    case ',':
	      continue ;
	    default: ;
	    }
	  this->m_strKey = this->json_str() ;
	  std::cout << "Key=" << this->m_strKey << std::endl ;
	  ++(this->m_pFocus) ; // 跳转字符串最后一个"
	  this->skip_black_char() ;
	  if(*(this->m_pFocus++) != ':')
	    {
	      this->m_strErr = "json obj type \"key\": , ':' lose" ;
	      this->m_strTip = std::string(this->m_pFocus , this->m_pTerminal) ;
	      throw this->m_strErr ;
	    }
	  this->skip_black_char() ;
	  switch(*(this->m_pFocus))
	    {
	    case '{':
	      {
		++(this->m_pFocus) ;
		JsonNode* pTmpNode = new JsonNode(this->m_strKey) ;
		pTmpNode->init_node(JSON_OBJ , NULL) ;
		this->m_ModeStack.top_node()->set_node_value(pTmpNode) ;
		this->m_ModeStack.push_mode('{' , pTmpNode) ;
		this->parse_obj() ;
		break ;
	      }
	    case '[':
	      {
		++(this->m_pFocus) ;
		JsonNode* pTmpNode = new JsonNode(this->m_strKey) ;
		pTmpNode->init_node(JSON_LIST , NULL) ;
		this->m_ModeStack.top_node()->set_node_value(pTmpNode) ;
		this->m_ModeStack.push_mode('[' , pTmpNode) ;
		this->parse_list() ;
		break ;
	      }
	    case '"':
	      {
		this->m_strVal = this->json_str() ;
		JsonNode* pTmpNode = new JsonNode(this->m_strKey) ;
		pTmpNode->init_node(JSON_STR , &this->m_strVal) ;
		this->m_ModeStack.top_node()->set_node_value(pTmpNode) ;
		std::cout << "obj Val=" << this->m_strVal << std::endl ;
		break ;
	      }
	    default:
	      {
		this->m_strVal = this->json_int() ;
		this->confirm_json_value() ;
		std::cout << "obj Val=" << this->m_strVal << std::endl ;
		break ;
	      }
	    }
	}
    }
  public:
    bool m_bStatus ;
    const char* m_pFocus ;
    const char* m_pTerminal ;
    std::string  m_strErr ;
    std::string  m_strTip ;
    std::string  m_strKey ;
    std::string  m_strVal ;
    ModeStack    m_ModeStack ;
    JsonNode* m_pRootJsonNode ;
  public:
    void skip_black_char(bool _bThrow = true)
    {
      for( ; this->m_pFocus < this->m_pTerminal ; ++(this->m_pFocus))
	{
	  if(*(this->m_pFocus) == ' ' || *(this->m_pFocus) == '\t' || *(this->m_pFocus) == '\n')
	    continue ;
	  return ;
	}
      if(_bThrow)
	{
	  this->m_strErr = "does't except finished without \"" ;
	  this->m_strTip = std::string(this->m_pFocus , this->m_pTerminal) ;
	  throw this->m_strErr ;

	}
    }

    std::string json_str()
    {
      const char* pStrBeg = this->m_pFocus ;
      for( ; this->m_pFocus < this->m_pTerminal ; ++(this->m_pFocus))
	{
	  if(*(this->m_pFocus) == ' ' || *(this->m_pFocus) == '\t' || *(this->m_pFocus) == '\n')
	    continue ;
	  break ;
	}
      if (*(this->m_pFocus) != '"')
	{
	  this->m_strErr = "invalid string" ;
	  this->m_strTip = std::string(pStrBeg , this->m_pTerminal) ;
	  throw this->m_strErr ;
	}
      pStrBeg = ++(this->m_pFocus) ;
      for( ; this->m_pFocus < this->m_pTerminal ; ++(this->m_pFocus))
	{
	  if(*(this->m_pFocus) == '"' && *(this->m_pFocus - 1) != '\\')
	    {
	      return std::string(pStrBeg , this->m_pFocus ) ;
	    }
	}
      this->m_strErr = "invalid string , json finish must with '}'" ;
      this->m_strTip = std::string(pStrBeg , this->m_pTerminal) ;
      throw this->m_strErr ;
    }
    std::string json_int()
    {
      const char* pNumber = this->m_pFocus ;
      for( ; this->m_pFocus < this->m_pTerminal ; ++(this->m_pFocus))
	{
	  if(*(this->m_pFocus) == ',' || *(this->m_pFocus) == '}' || *(this->m_pFocus) == ']')
	    break ;
	}
      if (this->m_pFocus == this->m_pTerminal)
	{
	  this->m_strErr = "invalid number" ;
	  this->m_strTip = std::string(pNumber , this->m_pTerminal) ;
	  throw this->m_strErr ;
	}
      return std::string(pNumber , this->m_pFocus--) ; // 指针指向数值型的最后一个字符有效字符
    }
    void confirm_json_value()
    {
      size_t posExcept , posDot ;
      posExcept = this->m_strVal.find_last_not_of(" \t \n") ;
      if(posExcept != std::string::npos)
	{
	  this->m_strVal = this->m_strVal.substr(0 , posExcept + 1) ;
	}
      else
	{
	  this->m_strVal = "" ;
	}
      JsonNode* pTmpNode ;
      JsonNode* pRootNode = this->m_ModeStack.top_node() ;
      if(this->m_strVal.empty())
	{
	  goto parse_except ;
	}
      if(this->m_strVal == "true")
	{
	  int iVal = 0 ;
	  pTmpNode = new JsonNode(this->m_strKey) ;
	  pTmpNode->init_node(JSON_INT , &iVal) ;
	  pRootNode->set_node_value((void*)pTmpNode ) ;
	  return ;
	}
      else if(this->m_strVal == "false")
	{
	  int iVal = 0 ;
	  pTmpNode = new JsonNode(this->m_strKey) ;
	  pTmpNode->init_node(JSON_INT , &iVal) ;
	  pRootNode->set_node_value((void*)pTmpNode ) ;
	  return ;
	}
      else if(this->m_strVal == "null")
	{
	  int iVal = 0 ;
	  pTmpNode = new JsonNode(this->m_strKey) ;
	  pTmpNode->init_node(JSON_INT , &iVal) ;
	  pRootNode->set_node_value((void*)pTmpNode ) ;
	  return ;
	}
      if(!(this->m_strVal[0] == '+' || this->m_strVal[0] == '-' || (this->m_strVal[0] <= '9' && this->m_strVal[0] >= '0')))
	{
	  goto parse_except ;
	}
      posDot = this->m_strVal.find('.') ;
      if(posDot == std::string::npos) // 整型
	{
	  posExcept = this->m_strVal.find_first_not_of("01234567890" , 1) ;
	  if(posExcept != std::string::npos)
	    {
	      goto parse_except ;
	    }
	  long long llVal = atoll(this->m_strVal.c_str()) ;
	  pTmpNode = new JsonNode(this->m_strKey) ;
	  pTmpNode->init_node(JSON_LONGLONG , &llVal) ;
	  pRootNode->set_node_value((void*)pTmpNode ) ;
	}
      else  // 浮点型
	{
	  posExcept = this->m_strVal.rfind('.') ;
	  if(posExcept != posDot)
	    {
	      goto parse_except ;
	    }
	  posExcept = this->m_strVal.find_first_not_of("01234567890." , 1) ;
	  if(posExcept != std::string::npos)
	    {
	      goto parse_except ;
	    }
	  double dVal = atof(this->m_strVal.c_str()) ;
	  pTmpNode = new JsonNode(this->m_strKey) ;
	  pTmpNode->init_node(JSON_DOUBLE , &dVal) ;
	  pRootNode->set_node_value((void*)pTmpNode ) ;
	}
      return ;
    parse_except:
      this->m_strErr = "invalid type" ;
      this->m_strTip = this->m_strVal ;
      this->m_bStatus = false ;
      throw this->m_strErr ;
    }
  
  };






