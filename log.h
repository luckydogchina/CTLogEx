#ifndef __OPERATION_H__
#define __OPERATION_H__

#include "CTLogEx.h"

#ifndef _DEBUG //用户日志预编译宏
#define TRACE
#define ERROR
#define WARN_1
#define WARN_2
#define WARN_3
#define WARN_4
#define WARN_5
#define WARN_6
#else

#define TRACE ctrace(("(%s %s, %s, %d) :"), __DATE__,__TIME__ ,__FUNCTION__, __LINE__);\
											ctrace		

#ifdef WIN32
#define ERROR(x, ...)	cwarn(0, ("(%s %s, %s, %d) :"), __DATE__, __TIME__ ,__FUNCTION__, __LINE__);\
											cwarn(0, x , ##__VA_ARGS__) 	
#define WARN_1(x, ...)	cwarn(1, ("(%s %s, %s, %d) :"), __DATE__, __TIME__ ,__FUNCTION__, __LINE__);\
											cwarn(1, x , ##__VA_ARGS__) 	
#define WARN_2(x, ...)	cwarn(2, ("(%s %s, %s, %d) :"), __DATE__, __TIME__ ,__FUNCTION__, __LINE__);\
											cwarn(2, x , ##__VA_ARGS__) 	
#define WARN_3(x, ...)	cwarn(3, ("(%s %s, %s, %d) :"), __DATE__, __TIME__ ,__FUNCTION__, __LINE__);\
											cwarn(3, x , ##__VA_ARGS__) 	
#define WARN_4(x, ...)	cwarn(4, ("(%s %s, %s, %d) :"),__DATE__,  __TIME__ ,__FUNCTION__, __LINE__);\
											cwarn(4, x , ##__VA_ARGS__) 	
#define WARN_5(x, ...)	cwarn(5, ("(%s %s, %s, %d) :"), __DATE__,__TIME__ ,__FUNCTION__, __LINE__);\
											cwarn(5, x , ##__VA_ARGS__) 	
#define WARN_6(x, ...)	cwarn(6, ("(%s %s, %s, %d) :"),__DATE__ ,__TIME__ ,__FUNCTION__, __LINE__);\
											cwarn(6, x , ##__VA_ARGS__)

#else ifdef UNIX

#define ERROR(x, args...)	cwarn(0, ("(%s %s, %s, %d) :"), __DATE__, __TIME__ ,__FUNCTION__, __LINE__);\
											cwarn(0, x , ##args)	
#define WARN_1(x, args...)	cwarn(0, ("(%s %s, %s, %d) :"), __DATE__, __TIME__ ,__FUNCTION__, __LINE__);\
											cwarn(1, x , ##args) 	
#define WARN_2(x, args...)	cwarn(0, ("(%s %s, %s, %d) :"), __DATE__, __TIME__ ,__FUNCTION__, __LINE__);\
											cwarn(2, x , ##args) 	
#define WARN_3(x, args...)	cwarn(0, ("(%s %s, %s, %d) :"), __DATE__, __TIME__ ,__FUNCTION__, __LINE__);\
											cwarn(3, x , ##args) 	
#define WARN_4(x, args...)	cwarn(0, ("(%s %s, %s, %d) :"), __DATE__, __TIME__ ,__FUNCTION__, __LINE__);\
											cwarn(4, x , ##args) 	
#define WARN_5(x, args...)	cwarn(0, ("(%s %s, %s, %d) :"), __DATE__, __TIME__ ,__FUNCTION__, __LINE__);\
											cwarn(5, x , ##args) 	
#define WARN_6(x, args...)	cwarn(0, ("(%s %s, %s, %d) :"), __DATE__, __TIME__ ,__FUNCTION__, __LINE__);\
											cwarn(6, x , ##args)

#endif

#endif

#endif

//#endif // !__OPERATION_H__