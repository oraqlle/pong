#ifndef PONG_STATES_PAUSE_SCREEN
#define PONG_STATES_PAUSE_SCREEN

#include <SFML/Graphics.hpp>

#include <engine.hxx>
#include <state_interface.hxx>

#include <memory>

namespace pong::states {

class pause_menu : public crank::states::state_interface {
public:
    using font_type = sf::Font;
    using text_type = sf::Text;

public:
    explicit pause_menu(std::shared_ptr<sf::RenderWindow> window) noexcept;

    void init(crank::engine& engine) noexcept;

    void cleanup() noexcept;

    void pause() noexcept;

    void resume() noexcept;

    void handle_events(crank::engine& eng) noexcept;

    void update(crank::engine& eng) noexcept;

    void render(crank::engine& eng) noexcept;

protected:
    pause_menu() = default;

private:
    std::shared_ptr<sf::RenderWindow> m_window;
    font_type m_font;
    text_type m_title_text;
    text_type m_back_text;
    text_type m_quit_text;

}; /// class pause_menu

} // namespace pong::states

#endif /// PONG_PAUSE_SAMPLE
