#ifndef PONG_ENTITIES_BALL
#   define PONG_ENTITIES_BALL

#include <SFML/Graphics.hpp>

#include <memory>
#include <utility>

namespace pong::entities
{
    class ball
        : public sf::CircleShape
    {
    public:

        enum class direction
            : unsigned short
        { 
            UPLEFT = 1, UP = 7, UPRIGHT = 2,
            LEFT = 3, STOP = 0, RIGHT = 4,
            DOWNLEFT = 5, DOWN = 8, DOWNRIGHT = 6
        };

        using float_type    = float;
        using colour_type   = sf::Color;
        // using direction_t   = direction;

    public:

        ball() noexcept
            : sf::CircleShape()
            , m_direction{ direction::STOP }
        { }

        explicit ball(
            float_type radius,
            float_type xpos,
            float_type ypos,
            colour_type colour
        ) noexcept
            : sf::CircleShape(radius)
            , m_direction{ direction::STOP }
        {
            setOrigin(radius / 2.0f, radius / 2.0f);
            setPosition(sf::Vector2f(xpos, ypos));
            setFillColor(colour);
        }

        auto get_direction() noexcept
            -> direction&
        { return m_direction; }

        auto get_direction() const noexcept
            -> const direction&
        { return m_direction; }

        auto move() noexcept
            -> void
        {
            auto [xpos, ypos] = getPosition();


            switch (m_direction)
            {
                case direction::UPLEFT:
                    xpos -= m_xspeed;
                    ypos -= m_yspeed;
                    break;

                case direction::UP:
                    ypos -= m_yspeed;
                    break;

                case direction::UPRIGHT:
                    xpos += m_xspeed;
                    ypos -= m_yspeed;
                    break;

                case direction::LEFT:
                    xpos -= m_xspeed;
                    break;

                case direction::STOP:
                    break;

                case direction::RIGHT:
                    xpos += m_xspeed;
                    break;

                case direction::DOWNLEFT:
                    xpos -= m_xspeed;
                    ypos += m_yspeed;
                    break;

                case direction::DOWN:
                    ypos += m_yspeed;
                    break;

                case direction::DOWNRIGHT:
                    xpos += m_xspeed;
                    ypos += m_yspeed;
                    break;
                
                default:
                    break;
            }

            setPosition(sf::Vector2f(xpos, ypos));
        }

    private:

        static constexpr float_type m_xspeed = 2.5f;
        static constexpr float_type m_yspeed = 2.250f;
        direction m_direction;

    };  //< class ball

}  //< namespace pong::entities

#endif  //< PONG_ENTITIES_BALL
