#include <states/game.hxx>

#include <crank/crank.hxx>
#include <SFML/Graphics.hpp>

#include <filesystem>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <source_location>

namespace fs = std::filesystem;
using namespace std::literals;

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
        , m_top_boundary{ boundary_type{} }
        , m_bottom_boundary{ boundary_type{} }
        , m_left_boundary{ boundary_type{} }
        , m_right_boundary{ boundary_type{} }
        , m_scores{ 0u, 0u }
        , m_running{ false }
        , m_score_label{ text_type{} }
        , m_score_values{ text_type{} }
        , m_font{ font_type{} }
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

        m_top_boundary = boundary_type{
            sf::Vector2f{ 0.0f, 0.0f },
            sf::Vector2f{ w, 1.0f }
        };

        m_bottom_boundary = boundary_type{
            sf::Vector2f{ 0.0f, h - 1.0f },
            sf::Vector2f{ w, 1.0f }
        };

        m_left_boundary = boundary_type{
            sf::Vector2f{ 0.0f, 0.0f },
            sf::Vector2f{ 1.0f, h }
        };

        m_right_boundary = boundary_type{
            sf::Vector2f{ w, 0.0f },
            sf::Vector2f{ 1.0f, h }
        };
    
        auto srcloc         = std::source_location::current();
        auto src_path       = fs::path(srcloc.file_name());
        auto asset_path     = src_path.remove_filename() / "../../fonts"s;

        if (!m_font.loadFromFile(asset_path / "JetBrainsMonoNF.ttf"s))
            std::clog << "Error loading font!" << std::endl;

        m_score_label.setFont(m_font);
        m_score_label.setString("Score:"s);
        m_score_label.setStyle(text_type::Bold | text_type::Underlined);
        m_score_label.setCharacterSize(static_cast<unsigned>(0.03f * h));
        auto label_txt_w = m_score_label.getLocalBounds().width;
        auto label_txt_h = m_score_label.getLocalBounds().height;
        m_score_label.setOrigin(label_txt_w / 2.0f, label_txt_h / 2.0f);
        m_score_label.setPosition(w / 2.0f, label_txt_h);

        m_score_values.setFont(m_font);
        m_score_values.setString("Player 1: 0 | Player 2: 0"s);
        m_score_values.setCharacterSize(static_cast<unsigned>(0.025f * h));
        auto values_txt_w = m_score_values.getLocalBounds().width;
        auto values_txt_h = m_score_values.getLocalBounds().height;
        m_score_values.setOrigin(values_txt_w / 2.0f, values_txt_h / 2.0f);
        m_score_values.setPosition(w / 2.0f, (2.0f * label_txt_h) + values_txt_h);
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
        auto [w, h] = static_cast<sf::Vector2f>(m_window->getSize());
        m_ball.move();

        if (m_ball.getGlobalBounds().intersects(m_top_boundary))
            m_ball.get_direction() = static_cast<direction_type>(static_cast<unsigned short>(m_ball.get_direction()) + 4);
            // m_ball.get_direction() = m_ball.get_direction() == direction_type::UPLEFT ? direction_type::DOWNLEFT : direction_type::DOWNRIGHT;
        else if (m_ball.getGlobalBounds().intersects(m_bottom_boundary))
            m_ball.get_direction() = static_cast<direction_type>(static_cast<unsigned short>(m_ball.get_direction()) - 4);
            // m_ball.get_direction() = m_ball.get_direction() == direction_type::DOWNLEFT ? direction_type::UPLEFT : direction_type::UPRIGHT;
        else if (m_ball.getGlobalBounds().intersects(m_left_boundary))
        {
            m_ball.get_direction() = direction_type::STOP;
            m_ball.setPosition(w / 2.0f, h / 2.0f);
            m_scores.second += 1u;
            m_running = false;
        }
        else if (m_ball.getGlobalBounds().intersects(m_right_boundary))
        {
            m_ball.get_direction() = direction_type::STOP;
            m_ball.setPosition(w / 2.0f, h / 2.0f);
            m_scores.first += 1u;
            m_running = false;
        }
        else if (m_ball.getGlobalBounds().intersects(m_left_paddle.as_bounds()))
            m_ball.get_direction() = static_cast<direction_type>(static_cast<unsigned short>(m_ball.get_direction()) + 1);
        else if (m_ball.getGlobalBounds().intersects(m_right_paddle.as_bounds()))
            m_ball.get_direction() = static_cast<direction_type>(static_cast<unsigned short>(m_ball.get_direction()) - 1);
    }

    void main_game::render([[maybe_unused]] crank::engine& eng) noexcept
    { 
        auto [p1, p2] = m_scores;

        m_score_values.setString(
            "Player 1: "s 
          + std::to_string(p1) 
          + " | Player 2: "
          + std::to_string(p2)
        );

        m_window->clear();
        m_window->draw(m_ball);
        m_window->draw(m_left_paddle);
        m_window->draw(m_right_paddle);
        m_window->draw(m_score_label);
        m_window->draw(m_score_values);
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
