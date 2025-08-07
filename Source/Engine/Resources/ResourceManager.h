#pragma once
#include "Core/StringHelper.h"
#include "Core/Singleton.h"
#include "Resource.h"

#include <string>
#include <map>
#include <iostream>

namespace Rex {
	class ResourceManager : Singleton<ResourceManager> {
	public:

		template<typename T, typename ... Args>

		res_t<T> Get(const std::string& name, Args&& ... args);

		template<typename T, typename ... Args>

		res_t<T> GetWithId(const std::string& id, const std::string& name, Args&& ... args);

		static ResourceManager& Instance() {

			static ResourceManager instance;
			return instance;
		}
	private:

		friend class Singleton;

		ResourceManager() = default;

		std::map<std::string, res_t<Resource>> s_resource;
	};

	template<typename T, typename ... Args>

	inline res_t<T> ResourceManager::Get(const std::string& name, Args&& ... args) {

		return GetWithId(name, name, std::forward<Args>(args)...);
	}

	template<typename T, typename ... Args>

	inline res_t<T> ResourceManager::GetWithId(const std::string& id, const std::string& name, Args&& ... args) {

		std::string key = tolower(key);

		auto iter = s_resource.find(key);
		if (iter != s_resource.end()) {

			auto base = iter->second;

			auto resource = std::dynamic_pointer_cast<T>(base);
			if (resource == nullptr) {

				std::cerr << "Resorce type mismatch: " << key << std::endl;
				return res_t<T>();
			}

			return resource;
		}

		res_t<T> resource = std::make_shared<T>();
		if (resource->Load(name, std::forward<Args>(args)...) == false) {

			std::cerr << "Could not load resource: " << key << std::endl;
			return res_t<T>();
		}

		s_resource[key] = resource;

		return resource;
	}

	inline ResourceManager& Resources() { return ResourceManager::Instance(); }
}