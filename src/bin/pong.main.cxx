#include <states/sample.hxx>

// #include <SFML/Graphics.hpp>

#include <memory>
#include <utility>

enum id { SAMPLE };

auto main() -> int
{
    auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(200, 200), "SFML works!");
    auto engine = crank::engine{};
    engine.make_factory_for<pong::states::sample>(
        id::SAMPLE,
        window,
        100.0f,
        sf::Color::Green
    );
    engine.change_state(id::SAMPLE);

    while (window->isOpen())
    {
        engine.handle_events();
        engine.update();
        engine.render();
    }

    return 0;
}