//Jacob Boney
//COP 3503
//Project 03

#include "TextureManager.h"

std::unordered_map<std::string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(std::string fileName) {
    std::string path = "images/";
    path += fileName + ".png";

    textures[fileName].loadFromFile(path);
}

sf::Texture& TextureManager::GetTexture(std::string textureName){

    if(textures.find(textureName) == textures.end()){
        TextureManager::LoadTexture(textureName);
    }
    return textures[textureName];
}

void TextureManager::Clear(){
    textures.clear();
}
