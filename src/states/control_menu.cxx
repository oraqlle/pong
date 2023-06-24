#include <states/control_menu.hxx>
#include <states/id.hxx>
#include <utils/src.hxx>

#include <SFML/Graphics.hpp>

#include <engine.hxx>
#include <state_interface.hxx>

#include <filesystem>
#include <iostream>
#include <memory>
#include <numeric>
#include <ranges>
#include <source_location>
#include <string>

using namespace std::literals;
namespace fs = std::filesystem;

namespace pong::states {

control_menu::control_menu(std::shared_ptr<sf::RenderWindow> window) noexcept
    : m_window { window }
{
    auto asset_path = fs::weakly_canonical(
        pong::utils::src_absolute_path().parent_path()
        / ".."sv
        / ".."sv
        / "pong"sv
        / "fonts"sv);

    if (!m_font.loadFromFile(asset_path / "JetBrainsMonoNF.ttf"sv))
        std::clog << "Error loading font!" << std::endl;

    auto [w, h] = static_cast<sf::Vector2f>(m_window->getSize());

    m_title_text.setFont(m_font);
    m_title_text.setString("Controls Menu"s);
    m_title_text.setStyle(
        text_type::Style::Bold | text_type::Style::Underlined);
    m_title_text.setCharacterSize(static_cast<unsigned>(0.1f * h));
    auto title_w = m_title_text.getGlobalBounds().width;
    auto title_h = m_title_text.getGlobalBounds().height;
    m_title_text.setOrigin(title_w / 2.0f, title_h / 2.0f);
    m_title_text.setPosition(w / 2.0f, 0.3f * h);

    m_select_text.setFont(m_font);
    m_select_text.setString("Select - <Enter>"s);
    m_select_text.setStyle(text_type::Style::Bold);
    m_select_text.setCharacterSize(static_cast<unsigned>(0.04f * h));
    auto main_w = m_select_text.getGlobalBounds().width;
    auto main_h = m_select_text.getGlobalBounds().height;
    m_select_text.setOrigin(main_w / 2.0f, main_h / 2.0f);
    m_select_text.setPosition(w / 2.0f, h / 2.0f);

    m_left_player_controls_text.setFont(m_font);
    m_left_player_controls_text.setString("Left Player Controls - Up: <W>, Down: <S>"s);
    m_left_player_controls_text.setStyle(text_type::Style::Bold);
    m_left_player_controls_text.setCharacterSize(static_cast<unsigned>(0.04f * h));
    auto left_player_controls_w = m_left_player_controls_text.getGlobalBounds().width;
    auto left_player_controls_h = m_left_player_controls_text.getGlobalBounds().height;
    m_left_player_controls_text.setOrigin(left_player_controls_w / 2.0f, left_player_controls_h / 2.0f);
    m_left_player_controls_text.setPosition(w / 2.0f, h * 0.6f);

    m_right_player_controls_text.setFont(m_font);
    m_right_player_controls_text.setString("Right Player Controls - Up: <I>, Down: <K>"s);
    m_right_player_controls_text.setStyle(text_type::Style::Bold);
    m_right_player_controls_text.setCharacterSize(static_cast<unsigned>(0.04f * h));
    auto right_player_controls_w = m_right_player_controls_text.getGlobalBounds().width;
    auto right_player_controls_h = m_right_player_controls_text.getGlobalBounds().height;
    m_right_player_controls_text.setOrigin(right_player_controls_w / 2.0f, right_player_controls_h / 2.0f);
    m_right_player_controls_text.setPosition(w / 2.0f, h * 0.7f);

    m_back_text.setFont(m_font);
    m_back_text.setString("Back to Main Page - <Esc>"s);
    m_back_text.setStyle(text_type::Style::Bold);
    m_back_text.setCharacterSize(static_cast<unsigned>(0.04f * h));
    auto back_w = m_back_text.getGlobalBounds().width;
    auto back_h = m_back_text.getGlobalBounds().height;
    m_back_text.setOrigin(back_w / 2.0f, back_h / 2.0f);
    m_back_text.setPosition(w / 2.0f, h * 0.9f);
}

void control_menu::init([[maybe_unused]] crank::engine& eng) noexcept
{
}

void control_menu::cleanup() noexcept
{
}

void control_menu::pause() noexcept
{
}

void control_menu::resume() noexcept
{
}

void control_menu::handle_events(crank::engine& eng) noexcept
{
    auto event = sf::Event {};
    while (m_window->pollEvent(event))
        if (event.type == sf::Event::Closed)
            m_window->close();
        else if (event.type == sf::Event::KeyPressed)
            switch (event.key.code) {
            case sf::Keyboard::Escape: {
                auto rid = eng.pop_state<pong::states::id>();
                break;
            }
            default:
                break;
            }
}

void control_menu::update([[maybe_unused]] crank::engine& eng) noexcept
{
}

void control_menu::render([[maybe_unused]] crank::engine& eng) noexcept
{
    m_window->clear();
    m_window->draw(m_title_text);
    m_window->draw(m_select_text);
    m_window->draw(m_left_player_controls_text);
    m_window->draw(m_right_player_controls_text);
    m_window->draw(m_back_text);
    m_window->display();
}

} // namespace pong::states
