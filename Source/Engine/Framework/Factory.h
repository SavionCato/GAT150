#pragma once
#include "Framework/Object.h"

#include <map>
#include <memory>
#include <string>

namespace Rex {
	class CreatorBase {
	public:

		virtual ~CreatorBase() = default;
		virtual Object* Create() = 0;
	};

	template<typename T>
	requires std::derived_from<T, Object>
	class Creator : public CreatorBase {

	};
}