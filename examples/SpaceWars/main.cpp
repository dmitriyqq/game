#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "SpaceWarsGame.hpp"

int main(int argc, char **argv)
{
    SpaceWarsGame game;
    auto console = spdlog::stdout_color_mt("log");
    console->info("Welcome to spdlog!");
    console->error("Some error message with arg: {}", 1);

    game.start();
    return 0;
}
