#include <states/start_screen.hxx>

#include <crank/crank.hxx>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <memory>

namespace pong::states
{

    start_screen::start_screen(
        std::shared_ptr<sf::RenderWindow> window
    ) noexcept
        : m_window{ window }
    { }

    void start_screen::init([[maybe_unused]] crank::engine& eng) noexcept
    { }

    void start_screen::cleanup() noexcept
    { }

    void start_screen::pause() noexcept
    { }

    void start_screen::resume() noexcept
    { }

    void start_screen::handle_events([[maybe_unused]] crank::engine& eng) noexcept
    { 
        auto event = sf::Event{};
        while (m_window->pollEvent(event))
            if (event.type == sf::Event::Closed)
                m_window->close();
    }

    void start_screen::update([[maybe_unused]] crank::engine& eng) noexcept
    { }

    void start_screen::render([[maybe_unused]] crank::engine& eng) noexcept
    { 
        m_window->clear();
        m_window->display();
    }

}  /// namespace pong::states
