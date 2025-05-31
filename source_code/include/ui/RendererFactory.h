#pragma once
#include "Renderer.h"
#include <memory>

namespace ui {
    class RendererFactory {
    public:
        static std::unique_ptr<Renderer> createRenderer(const std::string& type);
    };
}
