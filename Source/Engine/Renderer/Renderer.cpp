#include "Renderer.h"
#include "Core/Logger.h"

#include<string>

namespace Rex {
    bool Renderer::Initialize() {

        if (!SDL_Init(SDL_INIT_VIDEO)) {

            Rex::Logger::Error("SDL_Init Error: " , std::string(SDL_GetError()));
            return false;
        }

        if (!TTF_Init())
        {
            Rex::Logger::Error("TTF_Init Error: " , std::string(SDL_GetError()));
            return false;
        }

        return true;
    }

    void Renderer::Shutdown(){

        TTF_Quit();
        SDL_DestroyRenderer(s_renderer);
        SDL_DestroyWindow(s_window);
        SDL_Quit();
    }

    bool Renderer::CreateWindow(const std::string& name, int width, int height) {

        s_width = width;
        s_height = height;

        s_window = SDL_CreateWindow(name.c_str(), width, height, 0);
        if (s_window == nullptr) {

            Rex::Logger::Error("SDL_CreateWindow Error: " , std::string(SDL_GetError()));
            SDL_Quit();
            return false;
        }

        s_renderer = SDL_CreateRenderer(s_window, NULL);
        if (s_renderer == nullptr) {

            Rex::Logger::Error("SDL_CreateRenderer Error: " , std::string(SDL_GetError()));
            SDL_DestroyWindow(s_window);
            SDL_Quit();
            return false;
        }

        return true;
    }

    void Renderer::SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {

        SDL_SetRenderDrawColor(s_renderer, r, g, b, a);
    }

    void Renderer::SetColor(float r, float g, float b, float a) {

        SDL_SetRenderDrawColorFloat(s_renderer, r, g, b, a);
    }

    void Renderer::DrawLine(float x1, float y1, float x2, float y2) {

        SDL_RenderLine(s_renderer, x1, y1, x2, y2);
    }

    void Renderer::DrawPoint(float x, float y) {

        SDL_RenderPoint(s_renderer, x, y);
    }

    void Renderer::DrawTexture(Texture* texture, float x, float y, float angle ) {

        vec2 size = texture->GetSize();

        SDL_FRect destRect;
        destRect.x = x;
        destRect.y = y;
        destRect.w = size.x;
        destRect.h = size.y;

        SDL_RenderTexture(s_renderer, texture->s_texture, NULL, &destRect);
    }

    void Renderer::Clear()  {

        SDL_RenderClear(s_renderer);
    }

    void Renderer::Present() {

        SDL_RenderPresent(s_renderer);
    }
}
