#ifndef PONG_ENTITIES_PADDLE
#   define PONG_ENTITIES_PADDLE

#include <SFML/Graphics.hpp>

#include <memory>
#include <utility>

namespace pong::entities
{
    class paddle
        : public sf::RectangleShape
    {
    public:

        using float_type    = float;
        using colour_type   = sf::Color;

        paddle() noexcept = default;

        explicit paddle(
            float_type width,
            float_type height,
            float_type xpos,
            float_type ypos,
            colour_type colour
        ) noexcept
            : sf::RectangleShape(sf::Vector2f(width, height))
        {
            this->setOrigin(width / 2.0f, height / 2.0f);
            this->setRotation(180);
            this->setPosition(sf::Vector2f(xpos, ypos));
            this->setFillColor(colour);
        }
    };

}  /// namespace pong::entities

#endif  /// PONG_ENTITIES_PADDLE
