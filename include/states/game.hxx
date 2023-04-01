#ifndef PONG_STATES_SAMPLE
#   define PONG_STATES_SAMPLE

#include <entities/paddle.hxx>

#include <crank/crank.hxx>
#include <SFML/Graphics.hpp>

#include <memory>

namespace pong::states
{

    class main_game
        : public crank::states::state_interface
    {
    public:
        
        // using paddle_type = sf::RectangleShape;
        using paddle_type = pong::entities::paddle;
    
    public:

        explicit main_game(
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

        main_game() = default;

    protected:

        std::shared_ptr<sf::RenderWindow> m_window;
        sf::CircleShape m_circle;
        paddle_type m_left_paddle;
        paddle_type m_right_paddle;

    };  /// class sample

}  /// namespace pong::states

#endif  /// PONG_STATES_SAMPLE
