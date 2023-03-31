#ifndef PONG_ENTITIES_PADDLE
#   define PONG_ENTITIES_PADDLE

#include <SFML/Graphics.hpp>

#include <utility>

namespace pong::entities
{

    class paddle
        : public sf::Sprite
    {
    public:

        using float_type    = float;
        using colour_type   = sf::Color;
        using shape_type    = sf::RectangleShape;
        using texture_type  = sf::RenderTexture;

        paddle() noexcept = default;

        paddle(const paddle& other) noexcept
            : sf::Sprite()
            , m_width{ other.m_width }
            , m_height{ other.m_height }
            , m_xpos{ other.m_xpos }
            , m_ypos{ other.m_ypos }
            , m_colour{ other.m_colour }
            , m_rectangle{ other.m_rectangle }
            , m_texture{ texture_type{} }
        {
            m_texture.create(static_cast<unsigned int>(m_width), static_cast<unsigned int>(m_height));
            this->setTexture(other.m_texture.getTexture());
        }

        paddle(paddle&& other) noexcept
            : m_width{ other.m_width }
            , m_height{ other.m_height }
            , m_xpos{ other.m_xpos }
            , m_ypos{ other.m_ypos }
            , m_colour{ std::move(other.m_colour) }
            , m_rectangle{ std::move(other.m_rectangle) }
            , m_texture{ texture_type{} }
        {
            other.m_width   = float_type{};
            other.m_height  = float_type{};

            m_texture.create(static_cast<unsigned int>(m_width), static_cast<unsigned int>(m_height));
            this->setTexture(other.m_texture.getTexture());
            other.m_texture.clear();
        }

        explicit paddle(
            float_type width,
            float_type height,
            float_type xpos,
            float_type ypos,
            colour_type colour
        ) noexcept
            : m_width{ width }
            , m_height{ height }
            , m_xpos{ width }
            , m_ypos{ height }
            , m_colour{ colour }
            , m_rectangle{ shape_type{ sf::Vector2f(width, height) } }
            , m_texture{ texture_type{} }
        {
            m_rectangle.setRotation(180);
            m_rectangle.setPosition(sf::Vector2f(xpos, ypos));
            m_rectangle.setFillColor(m_colour);
            m_texture.create(static_cast<unsigned int>(m_width), static_cast<unsigned int>(m_height));
            this->setTexture(m_texture.getTexture());
        }

        auto operator= 
        (const paddle& other) noexcept 
            -> paddle&
        {
            if (*this != other)
            {
                m_width     = other.m_width;
                m_height    = other.m_height;
                m_xpos      = other.m_xpos;
                m_ypos      = other.m_ypos;
                m_colour    = other.m_colour;
                m_rectangle = other.m_rectangle;

                m_texture.clear();

                m_texture.create(static_cast<unsigned int>(m_width), static_cast<unsigned int>(m_height));
                this->setTexture(other.m_texture.getTexture());
            }

            return *this;
        }

        auto operator=
        (paddle&& other) noexcept 
            -> paddle&
        {
            if (*this != other)
            {
                m_width     = other.m_width;
                m_height    = other.m_height;
                m_xpos      = other.m_xpos;
                m_ypos      = other.m_ypos;
                m_colour    = std::move(other.m_colour);
                m_rectangle = std::move(other.m_rectangle);

                m_texture.clear();

                m_texture.create(static_cast<unsigned int>(m_width), static_cast<unsigned int>(m_height));
                this->setTexture(other.m_texture.getTexture());

                other.m_width   = float_type{};
                other.m_height  = float_type{};
                other.m_xpos    = float_type{};
                other.m_ypos    = float_type{};
                other.m_texture.clear();
            }

            return *this;
        }

        auto render() noexcept -> void
        {
            m_texture.clear();
            m_texture.draw(m_rectangle);
            m_texture.display();
        }

        friend auto
        operator== (const paddle& first, const paddle& second)
            noexcept -> bool
        {
            return ((first.m_width == second.m_width) 
                 && (first.m_height == second.m_height)
                 && (first.m_xpos == second.m_xpos) 
                 && (first.m_ypos == second.m_ypos)
                 && (first.m_colour == second.m_colour)
                 && (first.m_rectangle.getPosition() == second.m_rectangle.getPosition())
                 && (first.m_texture.getSize() == second.m_texture.getSize()));
        }

    private:

        float_type m_width;
        float_type m_height;
        float_type m_xpos;
        float_type m_ypos;
        colour_type m_colour;
        shape_type m_rectangle;
        texture_type m_texture;
    };

}  /// namespace pong::entities

#endif  /// PONG_ENTITIES_PADDLE
