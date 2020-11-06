#pragma once

namespace Soul
{
	class IHashable
	{
	public:
		virtual unsigned long long Hash() = 0;
	};
}