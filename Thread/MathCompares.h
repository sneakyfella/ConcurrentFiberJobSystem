/* This source file is part of the concurrent Fiber based Framework.
*
* Copyright (c) 2015-2016 Joshua Chew
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*    http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
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