#ifndef PONG_STATES_MENU_SCREEN
#define PONG_STATES_MENU_SCREEN

#include <SFML/Graphics.hpp>
#include <crank/crank.hxx>
#include <memory>

namespace pong::states
{

class menu : public crank::states::state_interface
{
  public:
    using font_type = sf::Font;
    using text_type = sf::Text;

  public:
    explicit menu (std::shared_ptr<sf::RenderWindow> window) noexcept;

    void init (crank::engine &engine) noexcept;

    void cleanup () noexcept;

    void pause () noexcept;

    void resume () noexcept;

    void handle_events (crank::engine &eng) noexcept;

    void update (crank::engine &eng) noexcept;

    void render (crank::engine &eng) noexcept;

  protected:
    menu () = default;

    void option_select (crank::engine &eng) noexcept;

  protected:
    std::shared_ptr<sf::RenderWindow> m_window;
    font_type m_font;
    text_type m_title_text;
    text_type m_main_text;
    text_type m_back_text;

}; /// class menu

} // namespace pong::states

#endif /// PONG_MENU_SAMPLE
