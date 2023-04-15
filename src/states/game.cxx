#include <states/game.hxx>

#include <crank/crank.hxx>
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <range/v3/core.hpp>
#include <range/v3/view/repeat.hpp>
#include <range/v3/view/take.hpp>
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
        , m_left_score{ text_type{} }
        , m_right_score{ text_type{} }
        , m_divider{ }
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

        m_left_score.setFont(m_font);
        m_left_score.setString("00"s);
        m_left_score.setStyle(text_type::Bold);
        m_left_score.setCharacterSize(static_cast<unsigned>(0.05f * h));
        auto left_score_txt_w = m_left_score.getLocalBounds().width;
        auto left_score_txt_h = m_left_score.getLocalBounds().height;
        m_left_score.setOrigin(left_score_txt_w / 2.0f, left_score_txt_h / 2.0f);
        m_left_score.setPosition(w * 0.1f, left_score_txt_h);

        m_right_score.setFont(m_font);
        m_right_score.setString("00"s);
        m_right_score.setCharacterSize(static_cast<unsigned>(0.05f * h));
        auto right_score_txt_w = m_right_score.getLocalBounds().width;
        auto right_score_txt_h = m_right_score.getLocalBounds().height;
        m_right_score.setOrigin(right_score_txt_w / 2.0f, right_score_txt_h / 2.0f);
        m_right_score.setPosition(w - (w * 0.1f), left_score_txt_h);
        
        using sz_t = decltype(m_divider)::size_type;
        m_divider.resize(static_cast<sz_t>(h / 25.0f));
        std::ranges::generate(
            m_divider,
            [&w, &h, &colour, n=0]() mutable {
                auto r = sf::RectangleShape{ sf::Vector2f(6.0f, 20.0f) };
                r.setFillColor(colour);
                auto [rw, rh] = r.getSize();
                r.setOrigin(rw / 2.0f, rh / 2.0f);
                r.setPosition(sf::Vector2f(w / 2.0f, static_cast<float>(n) * 25.0f));
                n += 1;
                return r;
            }
        );
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
                    if (!m_left_paddle.getGlobalBounds().intersects(m_top_boundary))
                        m_left_paddle.move_up();
                    break;
                case sf::Keyboard::S:
                    if (!m_left_paddle.getGlobalBounds().intersects(m_bottom_boundary))
                        m_left_paddle.move_down();
                    break;
                case sf::Keyboard::I:
                    if (!m_right_paddle.getGlobalBounds().intersects(m_top_boundary))
                        m_right_paddle.move_up();
                    break;
                case sf::Keyboard::K:
                    if (!m_right_paddle.getGlobalBounds().intersects(m_bottom_boundary))
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
        else if (m_ball.getGlobalBounds().intersects(m_bottom_boundary))
            m_ball.get_direction() = static_cast<direction_type>(static_cast<unsigned short>(m_ball.get_direction()) - 4);
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
        {
            if (m_ball.get_direction() == direction_type::LEFT)
            {
                auto eng            = std::default_random_engine{ std::random_device{}() };
                auto rand           = std::uniform_int_distribution{ 1, 3 };
                
                switch (rand(eng))
                {
                case 1:
                    m_ball.get_direction() = direction_type::UPRIGHT;
                    break;

                case 2:
                    m_ball.get_direction() = direction_type::DOWNRIGHT;
                    break;
                
                case 3:
                    m_ball.get_direction() = direction_type::RIGHT;
                    break;
                }
            }
            else
                m_ball.get_direction() = static_cast<direction_type>(static_cast<unsigned short>(m_ball.get_direction()) + 1);
        }
        else if (m_ball.getGlobalBounds().intersects(m_right_paddle.as_bounds()))
        {
            if (m_ball.get_direction() == direction_type::RIGHT)
            {
                auto eng            = std::default_random_engine{ std::random_device{}() };
                auto rand           = std::uniform_int_distribution{ 1, 3 };
                
                switch (rand(eng))
                {
                case 1:
                    m_ball.get_direction() = direction_type::UPLEFT;
                    break;

                case 2:
                    m_ball.get_direction() = direction_type::DOWNLEFT;
                    break;
                
                case 3:
                    m_ball.get_direction() = direction_type::LEFT;
                    break;
                }
            }
            else
                m_ball.get_direction() = static_cast<direction_type>(static_cast<unsigned short>(m_ball.get_direction()) - 1);
        }
    }

    void main_game::render([[maybe_unused]] crank::engine& eng) noexcept
    { 
        auto [p1, p2] = m_scores;

        m_left_score.setString(fmt::format("{:02}", p1));
        m_right_score.setString(fmt::format("{:02}", p2));

        m_window->clear();
        m_window->draw(m_ball);
        m_window->draw(m_left_paddle);
        m_window->draw(m_right_paddle);
        m_window->draw(m_left_score);
        m_window->draw(m_right_score);
        std::ranges::for_each(m_divider, [this](auto& r){ this->m_window->draw(r); });
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
