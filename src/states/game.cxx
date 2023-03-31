#include <states/game.hxx>

#include <crank/crank.hxx>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <memory>

namespace pong::states
{

    game::game(
        std::shared_ptr<sf::RenderWindow> window,
        float radius,
        sf::Color colour
    ) noexcept
        : m_window{ window }
        , m_circle{ sf::CircleShape(radius) }
    {
        m_circle.setFillColor(colour);
        m_circle.setOrigin(radius, radius);

        auto [w, h] = static_cast<sf::Vector2f>(m_window->getSize());
        m_circle.setPosition(w / 2.0f, h / 2.0f);
    }

    void game::init([[maybe_unused]] crank::engine& eng) noexcept
    { }

    void game::cleanup() noexcept
    { }

    void game::pause() noexcept
    { }

    void game::resume() noexcept
    { }

    void game::handle_events([[maybe_unused]] crank::engine& eng) noexcept
    { 
        auto event = sf::Event{};
        while (m_window->pollEvent(event))
            if (event.type == sf::Event::Closed)
                m_window->close();
            else if (event.type == sf::Event::KeyPressed)
                switch (event.key.code)
                {
                    case sf::Keyboard::Escape:
                        m_window->close();
                        break;
                    default:
                        break;
                }
    }

    void game::update([[maybe_unused]] crank::engine& eng) noexcept
    { }

    void game::render([[maybe_unused]] crank::engine& eng) noexcept
    { 
        m_window->clear();
        m_window->draw(m_circle);
        m_window->display();
    }

}  /// namespace pong::states
