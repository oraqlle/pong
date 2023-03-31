#include <states/game.hxx>
#include <states/sample.hxx>

// #include <SFML/Graphics.hpp>

#include <memory>
#include <utility>

enum id { GAME };

auto main() -> int
{
    auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode::getDesktopMode(), "Pong", sf::Style::Fullscreen);
    auto engine = crank::engine{};
    engine.make_factory_for<pong::states::game>(
        id::GAME,
        window,
        12.5f,
        sf::Color::Blue
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