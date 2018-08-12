#pragma once

// Forward declaration of SFML classes
namespace sf
{
    class Texture;
    class Font;
}

enum class TextureID
{
    RedO, BlueX, Board
};

enum class FontID
{
  GameStatus
};

//Forward declaration of template class ResourceManager
template<class Resource, class Indentifier>
class ResourceManager;

using TextureManager = ResourceManager<sf::Texture, TextureID>;
using FontManager = ResourceManager<sf::Font, FontID>;
