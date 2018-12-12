
#include <glad/glad.h>

#include <vector>
#include "./Mesh.hpp"
#include <spdlog/spdlog.h>
#include "./Game.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main(int argc, char **argv)
{
    TestGame game;
    auto console = spdlog::stdout_color_mt("log");
    console->info("Welcome to spdlog!");
    console->error("Some error message with arg: {}", 1);

    game.start();
    return 0;
}