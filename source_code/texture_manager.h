// file này quản lý hình ảnh

#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <memory>

class TextureManager
{
private:
    std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textures;
    std::string resourcePath;

    static TextureManager *instance;

    // Singleton
    TextureManager() : resourcePath("resources/") {}

public:
    static TextureManager *getInstance();

    // Không cho phép sao chép
    TextureManager(const TextureManager &) = delete;
    TextureManager &operator=(const TextureManager &) = delete;

    void setResourcePath(const std::string &path);

    std::shared_ptr<sf::Texture> getTexture(const std::string &name);

    bool loadTexture(const std::string &name, const std::string &filename);
};

#endif // TEXTURE_MANAGER_H