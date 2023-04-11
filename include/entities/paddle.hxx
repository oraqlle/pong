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

        using boundary_type = sf::Rect<float>;
        using colour_type   = sf::Color;
        using float_type    = float;

    public:

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
            setOrigin(width / 2.0f, height / 2.0f);
            setRotation(180);
            setPosition(sf::Vector2f(xpos, ypos));
            setFillColor(colour);
        }

        auto move_up() noexcept
            -> void
        {
            auto [xpos, ypos] = getPosition();
            ypos -= m_speed;
            setPosition(sf::Vector2f(xpos, ypos));
        }

        auto move_down() noexcept
            -> void
        {
            auto [xpos, ypos] = getPosition();
            ypos += m_speed;
            setPosition(sf::Vector2f(xpos, ypos));
        }

        auto as_bounds() noexcept
            -> boundary_type
        {
            auto [w, h] = getSize();
            auto [xpos, ypos] = getPosition();
            
            return boundary_type{
                sf::Vector2f{ xpos - (w / 2.0f), ypos - (h / 2.0f) },
                sf::Vector2f{ w, h }
            };
        }

    private:

        static constexpr float_type m_speed = 15.0f;

    };  //< class paddle

}  //< namespace pong::entities

#endif  //< PONG_ENTITIES_PADDLE
