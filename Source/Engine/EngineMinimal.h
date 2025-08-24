#pragma once

//Core
#include "Core/File.h"
#include "Core/Logger.h"
#include "Core/Random.h"
#include "Core/Singleton.h"
#include "Core/StringHelper.h"
#include "Core/Time.h"

//Components
#include "Components/SpriteRenderer.h"
#include "Components/RendererComponent.h"
#include "Components/RigidBody.h"
#include "Components/ColliderComponent.h"
#include "Components/CircleCollider.h"

//Framework
#include "Framework/Actor.h"
#include "Framework/Component.h"
#include "Framework/Game.h"
#include "Framework/Object.h"
#include "Framework/Scene.h"

//Input
#include "Input/InputSystem.h"

//Math
#include "Math/Math.h"
#include "Math/Transform.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"

//Renderer
#include "Renderer/Font.h"
#include "Renderer/Model.h"
#include "Renderer/ParticleSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Text.h"
#include "Renderer/Texture.h"

//Resources
#include "Resources/Resource.h"
#include "Resources/ResourceManager.h"

//STD Lib
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <map>
#include <random>

//ThirdParty Lib
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <fmod.hpp>
#include <fmod_errors.h>