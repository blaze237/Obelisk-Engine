#pragma once

const float PI =  3.14159265359;

namespace MathHelp
{
	template <class T>
	T Clamp(T val, T lb, T ub)
	{
		if (val < lb)
			return lb;
		if (val > ub)
			return ub;

		return val;
	}
}