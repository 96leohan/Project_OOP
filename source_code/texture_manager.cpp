#include "texture_manager.h"
#include <iostream>

TextureManager *TextureManager::instance = nullptr;

TextureManager *TextureManager::getInstance()
{
    if (instance == nullptr)
    {
        instance = new TextureManager();
    }
    return instance;
}

void TextureManager::setResourcePath(const std::string &path)
{
    resourcePath = path;
    if (resourcePath.back() != '/')
    {
        resourcePath += '/';
    }
}

std::shared_ptr<sf::Texture> TextureManager::getTexture(const std::string &name)
{
    auto it = textures.find(name);
    if (it != textures.end())
    {
        return it->second;
    }

    // Nếu không tìm thấy, thử tải texture
    if (loadTexture(name, name))
    {
        return textures[name];
    }

    return nullptr;
}

bool TextureManager::loadTexture(const std::string &name, const std::string &filename)
{
    auto texture = std::make_shared<sf::Texture>();
    std::string fullPath = resourcePath + filename;

    if (!texture->loadFromFile(fullPath))
    {
        std::cerr << "Không thể tải texture từ: " << fullPath << std::endl;
        return false;
    }

    textures[name] = texture;
    return true;
}