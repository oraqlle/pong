#ifndef PONG_STATES_SAMPLE
#   define PONG_STATES_SAMPLE

#include <crank/crank.hxx>
#include <SFML/Graphics.hpp>

#include <memory>

namespace pong::states
{

    class game
        : public crank::states::state_interface
    {
    public:

        explicit game(
            std::shared_ptr<sf::RenderWindow> window,
            float radius,
            sf::Color colour
        ) noexcept;

        void init(crank::engine& engine) noexcept;

        void cleanup() noexcept;

        void pause() noexcept;

        void resume() noexcept;

        void handle_events(crank::engine& eng) noexcept;

        void update(crank::engine& eng) noexcept;

        void render(crank::engine& eng) noexcept;

    protected:

        game() = default;

    protected:

        std::shared_ptr<sf::RenderWindow> m_window;
        sf::CircleShape m_circle;

    };  /// class sample

}  /// namespace pong::states

#endif  /// PONG_STATES_SAMPLE
