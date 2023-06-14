#include <states/id.hxx>
#include <states/menu.hxx>
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

menu::menu(std::shared_ptr<sf::RenderWindow> window) noexcept
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

    m_back_text.setFont(m_font);
    m_back_text.setString("Back - <Esc>"s);
    m_back_text.setStyle(text_type::Style::Bold);
    m_back_text.setCharacterSize(static_cast<unsigned>(0.04f * h));
    auto back_w = m_back_text.getGlobalBounds().width;
    auto back_h = m_back_text.getGlobalBounds().height;
    m_back_text.setOrigin(back_w / 2.0f, back_h / 2.0f);
    m_back_text.setPosition(w / 2.0f, h / 2.0f);

    m_main_text.setFont(m_font);
    m_main_text.setString("Text here"s);
    m_main_text.setStyle(text_type::Style::Bold);
    m_main_text.setCharacterSize(static_cast<unsigned>(0.04f * h));
    auto main_w = m_main_text.getGlobalBounds().width;
    auto main_h = m_main_text.getGlobalBounds().height;
    m_main_text.setOrigin(main_w / 2.0f, main_h / 2.0f);
    m_main_text.setPosition(w / 2.0f, h / 2.0f);
}

void menu::init([[maybe_unused]] crank::engine& eng) noexcept
{
}

void menu::cleanup() noexcept
{
}

void menu::pause() noexcept
{
}

void menu::resume() noexcept
{
}

void menu::handle_events(crank::engine& eng) noexcept
{
    auto event = sf::Event {};
    while (m_window->pollEvent(event))
        if (event.type == sf::Event::Closed)
            m_window->close();
        else if (event.type == sf::Event::KeyPressed)
            switch (event.key.code) {
            case sf::Keyboard::Escape: {
                auto rid = eng.pop_state<std::size_t>();
                break;
            }
            default:
                break;
            }
}

void menu::update([[maybe_unused]] crank::engine& eng) noexcept
{
}

void menu::render([[maybe_unused]] crank::engine& eng) noexcept
{
    m_window->clear();
    m_window->draw(m_title_text);
    m_window->draw(m_main_text);
    m_window->draw(m_back_text);
    m_window->display();
}

} // namespace pong::states
