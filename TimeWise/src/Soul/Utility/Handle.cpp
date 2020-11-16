#include "Handle.h"

namespace Soul
{
	unsigned long long GetUniqueHandle()
	{
		static unsigned long long id = 0;
		return id++;
	}
}