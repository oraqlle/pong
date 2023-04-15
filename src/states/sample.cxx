#include <states/sample.hxx>

#include <crank/crank.hxx>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <memory>

namespace pong::states
{

    sample::sample(
        std::shared_ptr<sf::RenderWindow> window,
        float radius,
        sf::Color colour
    ) noexcept
        : m_window{ window }
        , m_circle{ sf::CircleShape(radius) }
    { m_circle.setFillColor(colour); }

    void sample::init([[maybe_unused]] crank::engine& eng) noexcept
    { }

    void sample::cleanup() noexcept
    { }

    void sample::pause() noexcept
    { }

    void sample::resume() noexcept
    { }

    void sample::handle_events([[maybe_unused]] crank::engine& eng) noexcept
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

    void sample::update([[maybe_unused]] crank::engine& eng) noexcept
    { }

    void sample::render([[maybe_unused]] crank::engine& eng) noexcept
    { 
        m_window->clear();
        m_window->draw(m_circle);
        m_window->display();
    }

}  /// namespace pong::states
