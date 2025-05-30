#include "RendererFactory.h"
#include "ConsoleRenderer.h"
#include "HighlightedRenderer.h"

std::unique_ptr<ui::Renderer> ui::RendererFactory::createRenderer(const std::string& type) {
    if (type == "console") {
        return std::make_unique<ui::ConsoleRenderer>();
    } else if (type == "highlighted") {
        auto console_renderer = std::make_unique<ui::ConsoleRenderer>();
        return std::make_unique<ui::HighlightedRenderer>(std::move(console_renderer));
    }
    return nullptr;
}
