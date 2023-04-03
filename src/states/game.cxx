#include <states/game.hxx>

#include <crank/crank.hxx>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <memory>
#include <random>

namespace pong::states
{

    main_game::main_game(
        std::shared_ptr<sf::RenderWindow> window,
        float radius,
        sf::Color colour
    ) noexcept
        : m_window{ window }
        , m_ball{ ball_type{}  }
        , m_left_paddle{ paddle_type{} }
        , m_right_paddle{ paddle_type{} }
    {
        auto [w, h] = static_cast<sf::Vector2f>(m_window->getSize());
        m_ball.setFillColor(colour);
        m_ball.setOrigin(radius, radius);
        m_ball.setPosition(w / 2.0f, h / 2.0f);

        auto paddle_w = 0.008f * w;
        auto paddle_h = 0.30f * h;

        auto left_paddle_xpos = w * 0.05f;
        auto right_paddle_xpos = w - (0.05f * w);
        auto paddle_ypos = h / 2.0f;

        m_ball = ball_type{
            radius,
            w / 2.0f,
            h / 2.0f,
            colour
        };

        m_left_paddle = paddle_type{
            paddle_w,
            paddle_h,
            left_paddle_xpos,
            paddle_ypos,
            sf::Color::White
        };

        m_right_paddle = paddle_type{ 
            paddle_w,
            paddle_h,
            right_paddle_xpos,
            paddle_ypos,
            sf::Color::White
        };
    }

    void main_game::init([[maybe_unused]] crank::engine& eng) noexcept
    { }

    void main_game::cleanup() noexcept
    { }

    void main_game::pause() noexcept
    { }

    void main_game::resume() noexcept
    { }

    void main_game::handle_events([[maybe_unused]] crank::engine& eng) noexcept
    { 
        /// Instead of handling player input here directly
        /// I could create event queues for the paddles
        /// and just push events to it from here then have
        /// a `.handle_events()` method for the paddle which
        /// is launched at the start of the state and handles
        /// the events of the paddles as the come, and only
        /// destroys or quit the event when the main game
        /// state class is destroyed.

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
                    case sf::Keyboard::W:
                        m_left_paddle.move_up();
                        break;
                    case sf::Keyboard::S:
                        m_left_paddle.move_down();
                        break;
                    case sf::Keyboard::I:
                        m_right_paddle.move_up();
                        break;
                    case sf::Keyboard::K:
                        m_right_paddle.move_down();
                        break;
                    case sf::Keyboard::Space:
                        if (!m_running)
                            start_game();
                        break;
                    default:
                        break;
                }
    }

    void main_game::update([[maybe_unused]] crank::engine& eng) noexcept
    { 
        m_ball.move();
    }

    void main_game::render([[maybe_unused]] crank::engine& eng) noexcept
    { 
        m_window->clear();
        m_window->draw(m_ball);
        m_window->draw(m_left_paddle);
        m_window->draw(m_right_paddle);
        m_window->display();
    }

    void main_game::start_game() noexcept
    {
        auto eng            = std::default_random_engine{ std::random_device{}() };
        auto rand           = std::uniform_int_distribution{ 1, 6 };
        auto dir            = rand(eng);
        m_ball.get_direction()  = static_cast<direction_type>(dir);
        m_running = true;
    }

}  /// namespace pong::states
