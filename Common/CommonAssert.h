#include <assert.h>
#include <iostream>

#ifdef  _DEBUG
#endif
#ifdef _DEBUG
#define Assert(_Expression){ if(!(_Expression)){ std::cout << "!Assert!" << __FILE__ << "," << __LINE__ << ":" << #_Expression; assert(_Expression); return ;} }
#define Assert_Re0(_Expression){ if(!(_Expression)){ std::cout << "!Assert!" << __FILE__ << "," << __LINE__ << ":" << #_Expression; assert(_Expression); return 0;} } 
#define Assert_Re(_Expression , _ReturnValue){ if(!(_Expression)){ std::cout << "!Assert!" << __FILE__ << "," << __LINE__ << ":" << #_Expression; assert(_Expression); return _ReturnValue;} }
 
#else
#define Assert(_Expression){ if(!(_Expression)){ std::cout << "!Assert!" << __FILE__ << "," << __LINE__ << ":" << #_Expression; return ;} }
#define Assert_Re0(_Expression){ if(!(_Expression)){ std::cout << "!Assert!" << __FILE__ << "," << __LINE__ << ":" << #_Expression ; return 0;} } 
#define Assert_Re(_Expression , _ReturnValue){ if(!(_Expression)){ std::cout << "!Assert!" << __FILE__ << "," << __LINE__ << ":" << #_Expression; return _ReturnValue;} }
#endif