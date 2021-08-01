//Jacob Boney
//COP 3503
//Project 03

#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <string>

class TextureManager {
    static std::unordered_map<std::string, sf::Texture> textures;
    static void LoadTexture(std::string fileName);
public:
    static sf::Texture& GetTexture(std::string textureName);
    static void Clear();
};

