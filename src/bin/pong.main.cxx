#include <states/game.hxx>
#include <states/sample.hxx>
#include <states/start_screen.hxx>

#include <memory>
#include <utility>

enum id { SAMPLE, GAME, START };

auto main() -> int
{
    auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode::getDesktopMode(), "Pong", sf::Style::Fullscreen);
    auto engine = crank::engine{};
    
    engine.make_factory_for<pong::states::sample>(
        id::SAMPLE,
        window,
        12.5f,
        sf::Color::Green
    );

    engine.make_factory_for<pong::states::main_game>(
        id::GAME,
        window,
        12.5f,
        sf::Color::White
    );

    engine.make_factory_for<pong::states::start_screen>(
        id::START,
        window
    );

    engine.change_state(id::GAME);

    while (window->isOpen())
    {
        engine.handle_events();
        engine.update();
        engine.render();
    }

    return 0;
}