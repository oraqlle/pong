#ifndef PONG_ENTITIES_BALL
#define PONG_ENTITIES_BALL

#include <SFML/Graphics.hpp>

#include <memory>
#include <utility>

namespace pong::entities {
class ball
    : public sf::CircleShape {
public:
    // clang-format off
        enum class direction_t
            : unsigned short
        { 
            UPLEFT = 1, UP = 7, UPRIGHT = 2,
            LEFT = 3, STOP = 0, RIGHT = 4,
            DOWNLEFT = 5, DOWN = 8, DOWNRIGHT = 6
        };
    // clang-format on

    using colour_type = sf::Color;
    using float_type = float;

public:
    ball() noexcept
        : sf::CircleShape()
        , m_direction { direction_t::STOP }
    {
    }

    explicit ball(
        float_type radius,
        float_type xpos,
        float_type ypos,
        colour_type colour) noexcept
        : sf::CircleShape(radius)
        , m_direction { direction_t::STOP }
    {
        setOrigin(radius, radius);
        setPosition(sf::Vector2f(xpos, ypos));
        setFillColor(colour);
    }

    auto direction() noexcept
        -> direction_t&
    {
        return m_direction;
    }

    auto get_direction() const noexcept
        -> const direction_t&
    {
        return m_direction;
    }

    auto reset_position(const float& w, const float& h) noexcept
        -> void
    {
        setPosition(sf::Vector2f(w / 2.0f, h / 2.0f));
    }

    auto move() noexcept
        -> void
    {
        auto [xpos, ypos] = getPosition();

        switch (m_direction) {
        case direction_t::UPLEFT:
            xpos -= m_xspeed;
            ypos -= m_yspeed;
            break;

        case direction_t::UP:
            ypos -= m_yspeed;
            break;

        case direction_t::UPRIGHT:
            xpos += m_xspeed;
            ypos -= m_yspeed;
            break;

        case direction_t::LEFT:
            xpos -= m_xspeed;
            break;

        case direction_t::STOP:
            break;

        case direction_t::RIGHT:
            xpos += m_xspeed;
            break;

        case direction_t::DOWNLEFT:
            xpos -= m_xspeed;
            ypos += m_yspeed;
            break;

        case direction_t::DOWN:
            ypos += m_yspeed;
            break;

        case direction_t::DOWNRIGHT:
            xpos += m_xspeed;
            ypos += m_yspeed;
            break;

        default:
            break;
        }

        setPosition(sf::Vector2f(xpos, ypos));
    }

private:
    static constexpr float_type m_xspeed = 2.25f;
    static constexpr float_type m_yspeed = 2.125f;
    direction_t m_direction;

}; //< class ball

} //< namespace pong::entities

#endif //< PONG_ENTITIES_BALL
