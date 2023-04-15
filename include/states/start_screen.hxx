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

    protected:

        std::shared_ptr<sf::RenderWindow> m_window;

    };  /// class start_screen

}  /// namespace pong::states

#endif  /// PONG_STATES_SAMPLE
