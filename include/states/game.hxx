#ifndef PONG_STATES_GAME
#define PONG_STATES_GAME

#include <entities/ball.hxx>
#include <entities/paddle.hxx>

#include <SFML/Graphics.hpp>

#include <engine.hxx>
#include <state_interface.hxx>

#include <memory>
#include <utility>
#include <vector>

namespace pong::states {

class main_game
    : public crank::states::state_interface {
public:
    using ball_type = pong::entities::ball;
    using boundary_type = sf::Rect<float>;
    using direction_type = pong::entities::ball::direction;
    using font_type = sf::Font;
    using paddle_type = pong::entities::paddle;
    using text_type = sf::Text;

public:
    explicit main_game(
        std::shared_ptr<sf::RenderWindow> window,
        float radius,
        sf::Color colour) noexcept;

    void init(crank::engine& engine) noexcept;

    void cleanup() noexcept;

    void pause() noexcept;

    void resume() noexcept;

    void handle_events(crank::engine& eng) noexcept;

    void update(crank::engine& eng) noexcept;

    void render(crank::engine& eng) noexcept;

private:
    void start_game() noexcept;

private:
    std::shared_ptr<sf::RenderWindow> m_window;
    ball_type m_ball;
    paddle_type m_left_paddle;
    paddle_type m_right_paddle;
    boundary_type m_top_boundary;
    boundary_type m_bottom_boundary;
    boundary_type m_left_boundary;
    boundary_type m_right_boundary;
    std::pair<unsigned, unsigned> m_scores = std::pair{ 0u, 0u };
    bool m_running = false;
    font_type m_font;
    text_type m_left_score;
    text_type m_right_score;
    text_type m_start_text;
    sf::RectangleShape m_start_tile;
    std::vector<sf::RectangleShape> m_divider;

}; //< class game

} //< namespace pong::states

#endif //< PONG_STATES_GAME
