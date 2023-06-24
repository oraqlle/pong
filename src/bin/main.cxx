#include <states/control_menu.hxx>
#include <states/game.hxx>
#include <states/id.hxx>
#include <states/pause_menu.hxx>
#include <states/sample.hxx>
#include <states/start_screen.hxx>
#include <utils/match.hxx>

#include <SFML/Graphics.hpp>

#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <variant>

auto main() -> int
{
    auto window = std::make_shared<sf::RenderWindow>(
        sf::VideoMode::getDesktopMode(),
        "Pong",
        sf::Style::Fullscreen);

    auto engine = crank::engine {};

    engine.make_factory_for<pong::states::sample>(
        pong::states::id::SAMPLE,
        window,
        12.5f,
        sf::Color::Green);

    engine.make_factory_for<pong::states::start_screen>(
        pong::states::id::START,
        window);

    engine.make_factory_for<pong::states::control_menu>(
        pong::states::id::CONTROLS,
        window);

    engine.make_factory_for<pong::states::pause_menu>(
        pong::states::id::PAUSED,
        window);

    engine.make_factory_for<pong::states::main_game>(
        pong::states::id::GAME,
        window,
        12.5f,
        sf::Color::White);

    auto result = engine.change_state(pong::states::id::START);

    std::visit(
        pong::utils::match {
            [](const std::monostate&) {},
            [](const std::string& msg) {
                std::clog << msg << std::endl;
                std::exit(1);
            } },
        result);

    while (window->isOpen()) {
        engine.handle_events();
        engine.update();
        engine.render();
    }

    return 0;
}