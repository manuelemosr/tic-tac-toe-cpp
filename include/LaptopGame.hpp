#pragma once

#include "Game.hpp"
#include <iostream>

class LaptopGame : public Game {
private:
  /* data */
public:
  void printGame() noexcept {
    std::cout
        << std::endl
        << static_cast<int>(gamePositions[GamePosition::TOP_LEFT].getPlayer())
        << " | "
        << static_cast<int>(gamePositions[GamePosition::TOP_CENTER].getPlayer())
        << " | "
        << static_cast<int>(gamePositions[GamePosition::TOP_RIGHT].getPlayer())
        << std::endl;
    std::cout << "-   -   -" << std::endl;
    std::cout << static_cast<int>(
                     gamePositions[GamePosition::CENTER_LEFT].getPlayer())
              << " | "
              << static_cast<int>(
                     gamePositions[GamePosition::CENTER_CENTER].getPlayer())
              << " | "
              << static_cast<int>(
                     gamePositions[GamePosition::CENTER_RIGHT].getPlayer())
              << std::endl;
    std::cout << "-   -   -" << std::endl;
    std::cout << static_cast<int>(
                     gamePositions[GamePosition::BOTTOM_LEFT].getPlayer())
              << " | "
              << static_cast<int>(
                     gamePositions[GamePosition::BOTTOM_CENTER].getPlayer())
              << " | "
              << static_cast<int>(
                     gamePositions[GamePosition::BOTTOM_RIGHT].getPlayer())
              << std::endl
              << std::endl;
    auto [gameOver, winner] = isGameOver();

    if (gameOver) {
      std::cout << "Game Over! Player " +
                       std::to_string(static_cast<int>(winner)) + " wins!"
                << std::endl;
    }
  }
};