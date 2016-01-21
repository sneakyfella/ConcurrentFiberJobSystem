#pragma once
#include "ForwardDeclarations.h"

namespace ComparisonFunctors
{
	template <typename T>
	struct LessThan {
		bool operator ()(const T& lhs, const T& rhs) {
			return lhs < rhs;
		}
	};
	template <typename T>
	struct MoreThan {
		bool operator ()(const T& lhs, const T& rhs) {
			return lhs > rhs;
		}
	};
	template <typename T>
	struct EqualsTo {
		bool operator ()(const T& lhs, const T& rhs) {
			return lhs == rhs;
		}
	};
	template <typename T>
	struct LessThanOrEqualsTo {
		bool operator ()(const T& lhs, const T& rhs) {
			return lhs <= rhs;
		}
	};
	template <typename T>
	struct MoreThanOrEqualsTo {
		bool operator ()(const T& lhs, const T& rhs) {
			return lhs >= rhs;
		}
	};
}