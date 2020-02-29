#pragma once

#ifdef MOLERS_PLATFORM_WINDOWS
	#ifdef MOLERS_BUILD_DLL
		#define MOLERS_API __declspec(dllexport)
	#else
		#define MOLERS_API __declspec(dllimport)
	#endif
#else 
	#error Molers only support Windows!
#endif


#ifdef MOLERS_ENABLE_ASSERTS
#define MOLERS_ASSERT(x, ...)												\
	{																		\
		if(!(x))															\
		{																	\
			Molers::Log::Error("Assertion Failed : {0}", __VA_ARGS__);		\
			__debugbreak();													\
		}																	\
	}												

#define MOLERS_CORE_ASSERT(x, ...)											\
	{																		\
		if(!(x))															\
		{																	\
			Molers::Log::Error("Assertion Failed : {0}", __VA_ARGS__);		\
			__debugbreak();													\
		}																	\
	}																

#else
	#define MOLERS_CLIENT_ASSERT(x,...)
	#define MOLERS_CORE_ASSERT(x,...)
#endif




#define BIT(x) (1 << x) //1×óÒÆxÎ»

#define BIND_EVENT_FN(fn) std::bind(&fn,this,std::placeholders::_1)
