#ifndef PONG_STATES_GAME
#   define PONG_STATES_GAME

#include <entities/ball.hxx>
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
        
        using ball_type         = pong::entities::ball;
        using boundary_type     = sf::Rect<float>;
        using direction_type    = pong::entities::ball::direction;
        using paddle_type       = pong::entities::paddle;
    
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

    private:

        void start_game() noexcept;

    protected:

        std::shared_ptr<sf::RenderWindow> m_window;
        ball_type m_ball;
        paddle_type m_left_paddle;
        paddle_type m_right_paddle;
        boundary_type m_top_boundary;
        boundary_type m_bottom_boundary;
        boundary_type m_left_boundary;
        boundary_type m_right_boundary;
        boundary_type m_left_paddle_boundary;
        boundary_type m_right_paddle_boundary;
        bool m_running;

    };  //< class game

}  //< namespace pong::states

#endif  //< PONG_STATES_GAME
