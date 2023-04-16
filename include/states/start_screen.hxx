#ifndef PONG_STATES_START_SCREEN
#   define PONG_STATES_START_SCREEN

#include <crank/crank.hxx>
#include <SFML/Graphics.hpp>

#include <memory>

namespace pong::states
{

    class start_screen
        : public crank::states::state_interface
    {
    public:

        using font_type = sf::Font;
        using text_type = sf::Text;

    public:

        enum class cursor_position 
            : short 
        { PLAY, CONTROLS, QUIT };

    public:

        explicit start_screen(
            std::shared_ptr<sf::RenderWindow> window
        ) noexcept;

        void init(crank::engine& engine) noexcept;

        void cleanup() noexcept;

        void pause() noexcept;

        void resume() noexcept;

        void handle_events(crank::engine& eng) noexcept;

        void update(crank::engine& eng) noexcept;

        void render(crank::engine& eng) noexcept;

    protected:

        start_screen() = default;

        void option_select(crank::engine& eng) noexcept;

    protected:

        std::shared_ptr<sf::RenderWindow> m_window;
        cursor_position m_cursor_pos;
        font_type m_font;
        text_type m_title_text;
        text_type m_play_text;
        text_type m_controls_text;
        text_type m_quit_text;

    };  /// class start_screen

}  /// namespace pong::states

#endif  /// PONG_STATES_SAMPLE
