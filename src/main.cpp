#include <functional>
#include <iostream>
#include <optional>

#include <CLI/CLI.hpp>
#include <spdlog/spdlog.h>

#include "model.h"

// This file will be generated automatically when you run the CMake configuration step.
// It creates a namespace called `tic_tac_toe`.
// You can modify the source template at `configured_files/config.hpp.in`.
#include <internal_use_only/config.hpp>


// NOLINTNEXTLINE(bugprone-exception-escape)
int main(int argc, const char **argv)
{
  try {
    CLI::App app{ fmt::format("{} version {}", tic_tac_toe::cmake::project_name, tic_tac_toe::cmake::project_version) };

    std::optional<std::string> message;
    app.add_option("-m,--message", message, "A message to print back out");
    bool show_version = false;
    app.add_flag("--version", show_version, "Show version information");

    CLI11_PARSE(app, argc, argv);

    if (show_version) {
      fmt::print("{}\n", tic_tac_toe::cmake::project_version);
      return EXIT_SUCCESS;
    }

    // Use the default logger (stdout, multi-threaded, colored)
    spdlog::info("Hello, {}!", "World");

    if (message) {
      fmt::print("Message: '{}'\n", *message);
    } else {
      fmt::print("No Message Provided :(\n");
    }

    auto g = Game{};
    g.print_board();

    auto p1 = Player{};
    p1.figure = Figure::CROSS;
    auto p2 = Player{};
    p2.figure = Figure::CIRCLE;

    g.play(p1, {0, 0});
    g.play(p2, {1, 1});
    g.play(p1, {0, 1});
    g.play(p2, {0, 2});
    g.play(p1, {2, 0});
    g.play(p2, {1, 0});
    g.play(p1, {1, 2});
    g.play(p2, {2, 1});
    g.play(p1, {2, 2});

    g.play(p2, {2, 2});

    g.play(p2, {2, 3});
    g.play(p2, {3, 2});
    g.play(p2, {3, 3});

    g.print_board();

  } catch (const std::exception &e) {
    spdlog::error("Unhandled exception in main: {}", e.what());
  }
}
