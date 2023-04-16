#include <states/id.hxx>
#include <states/start_screen.hxx>

#include <crank/crank.hxx>
#include <SFML/Graphics.hpp>

#include <filesystem>
#include <iostream>
#include <memory>
#include <numeric>
#include <ranges>
#include <source_location>
#include <string>

using namespace std::literals;
namespace fs = std::filesystem;

namespace pong::states
{

    start_screen::start_screen(
        std::shared_ptr<sf::RenderWindow> window
    ) noexcept
        : m_window{ window }
        , m_cursor_pos { cursor_position::PLAY }
        , m_font{ }
        , m_title_text{ }
        , m_play_text{ }
        , m_controls_text{ }
        , m_quit_text{ }
    {
        auto srcloc         = std::source_location::current();
        auto src_path       = fs::path(srcloc.file_name());
        auto asset_path     = src_path.remove_filename() / "../../fonts"s;

        if (!m_font.loadFromFile(asset_path / "JetBrainsMonoNF.ttf"s))
            std::clog << "Error loading font!" << std::endl;

        auto [w, h] = static_cast<sf::Vector2f>(m_window->getSize());

        m_title_text.setFont(m_font);
        m_title_text.setString("Pong"s);
        m_title_text.setStyle(text_type::Style::Bold | text_type::Style::Underlined);
        m_title_text.setCharacterSize(static_cast<unsigned>(0.1f * h));
        auto title_w = m_title_text.getGlobalBounds().width;
        auto title_h = m_title_text.getGlobalBounds().height;
        m_title_text.setOrigin(title_w / 2.0f, title_h / 2.0f);
        m_title_text.setPosition(w / 2.0f, 0.3f * h);

        m_play_text.setFont(m_font);
        m_play_text.setString("> Play <"s);
        m_play_text.setStyle(text_type::Style::Bold);
        m_play_text.setCharacterSize(static_cast<unsigned>(0.04f * h));
        auto play_w = m_play_text.getGlobalBounds().width;
        auto play_h = m_play_text.getGlobalBounds().height;
        m_play_text.setOrigin(play_w / 2.0f, play_h / 2.0f);
        m_play_text.setPosition(w / 2.0f, h / 2.0f);

        m_controls_text.setFont(m_font);
        m_controls_text.setString("  Controls  "s);
        m_controls_text.setStyle(text_type::Style::Bold);
        m_controls_text.setCharacterSize(static_cast<unsigned>(0.04f * h));
        auto ctrl_w = m_controls_text.getGlobalBounds().width;
        auto ctrl_h = m_controls_text.getGlobalBounds().height;
        m_controls_text.setOrigin(ctrl_w / 2.0f, ctrl_h / 2.0f);
        m_controls_text.setPosition(w / 2.0f, h * 0.6f);

        m_quit_text.setFont(m_font);
        m_quit_text.setString("  Quit  "s);
        m_quit_text.setStyle(text_type::Style::Bold);
        m_quit_text.setCharacterSize(static_cast<unsigned>(0.04f * h));
        auto quit_w = m_quit_text.getGlobalBounds().width;
        auto quit_h = m_quit_text.getGlobalBounds().height;
        m_quit_text.setOrigin(quit_w / 2.0f, quit_h / 2.0f);
        m_quit_text.setPosition(w / 2.0f, h * 0.7f);
    }

    void start_screen::init([[maybe_unused]] crank::engine& eng) noexcept
    { }

    void start_screen::cleanup() noexcept
    { }

    void start_screen::pause() noexcept
    { }

    void start_screen::resume() noexcept
    { }

    void start_screen::handle_events(crank::engine& eng) noexcept
    { 
        auto event = sf::Event{};
        while (m_window->pollEvent(event))
            if (event.type == sf::Event::Closed)
                m_window->close();
            else if (event.type == sf::Event::KeyPressed)
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    m_cursor_pos = static_cast<cursor_position>(std::ranges::clamp(
                        static_cast<int>(m_cursor_pos) - 1,
                        static_cast<int>(cursor_position::PLAY),
                        static_cast<int>(cursor_position::QUIT)
                    ));
                    break;

                case sf::Keyboard::Down:
                    m_cursor_pos = static_cast<cursor_position>(std::ranges::clamp(
                        static_cast<int>(m_cursor_pos) + 1,
                        static_cast<int>(cursor_position::PLAY),
                        static_cast<int>(cursor_position::QUIT)
                    ));
                    break;

                case sf::Keyboard::Enter:
                    option_select(eng);
                    break;
                
                default:
                    break;
                }
    }

    void start_screen::update([[maybe_unused]] crank::engine& eng) noexcept
    {
        switch (m_cursor_pos)
        {
        case cursor_position::PLAY:
            m_play_text.setString("> Play <"s);
            m_controls_text.setString("  Controls  "s);
            m_quit_text.setString("  Quit  "s);
            break;

        case cursor_position::CONTROLS:
            m_play_text.setString("  Play  "s);
            m_controls_text.setString("> Controls <"s);
            m_quit_text.setString("  Quit  "s);
            break;

        case cursor_position::QUIT:
            m_play_text.setString("  Play  "s);
            m_controls_text.setString("  Controls  "s);
            m_quit_text.setString("> Quit <"s);
            break;
        
        default:
            break;
        }
    }

    void start_screen::render([[maybe_unused]] crank::engine& eng) noexcept
    { 
        m_window->clear();
        m_window->draw(m_title_text);
        m_window->draw(m_play_text);
        m_window->draw(m_controls_text);
        m_window->draw(m_quit_text);
        m_window->display();
    }

    void start_screen::option_select(crank::engine& eng) noexcept
    {
        switch (m_cursor_pos)
        {
        case cursor_position::PLAY:
            eng.change_state(states::id::GAME);
            break;

        case cursor_position::CONTROLS:
            break;

        case cursor_position::QUIT:
            m_window->close();
        
        default:
            break;
        }
    }

}  /// namespace pong::states
