#pragma once

#include "Game.hpp"
#include <iostream>

class LaptopGame : public Game {
private:
  /* data */
public:
  void getMoveInput(Player player) {
    int num = 0;
    std::cin >> num;
    switch (num) {
    case 1:
      makeMove(player, GamePosition::TOP_LEFT);
      break;
    case 2:
      makeMove(player, GamePosition::TOP_CENTER);
      break;
    case 3:
      makeMove(player, GamePosition::TOP_RIGHT);
      break;
    case 4:
      makeMove(player, GamePosition::CENTER_LEFT);
      break;
    case 5:
      makeMove(player, GamePosition::CENTER_CENTER);
      break;
    case 6:
      makeMove(player, GamePosition::CENTER_RIGHT);
      break;
    case 7:
      makeMove(player, GamePosition::BOTTOM_LEFT);
      break;
    case 8:
      makeMove(player, GamePosition::BOTTOM_CENTER);
      break;
    case 9:
      makeMove(player, GamePosition::BOTTOM_RIGHT);
      break;
    }
  }
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
      if (static_cast<int>(winner)) {
        std::cout << "Game Over! Player " +
                         std::to_string(static_cast<int>(winner)) + " wins!"
                  << std::endl;
      } else {
        std::cout << "Game Over! Draw. " << std::endl;
      }
    }
  }
};