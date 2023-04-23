#pragma once
#include "../src/network/src/model.h"
#include "LaptopGame.hpp"
#include <algorithm>
#include <limits>
#include <random>

class LaptopAIGame : public LaptopGame {
private:
  /* data */
  Player player;
  keras2cpp::Model model;

  double getMoveScore(Game::GameMap game) const noexcept {
    keras2cpp::Tensor in{9};

    Game::GameMap::iterator it;
    int i = 0;
    for (it = game.begin(); it != game.end(); it++) {
      auto player = it->second.getPlayer();
      switch (player) {
      case Player::PLAYER_1:
        in.data_[i] = 1;
        break;
      case Player::PLAYER_2:
        in.data_[i] = 2;
        break;
      case Player::NONE:
        in.data_[i] = 0;
        break;
      }
      i++;
    }
    keras2cpp::Tensor out = model(in);

    std::array<double, 3> outArray{};
    i = 0;
    for (auto it = out.begin(); it != out.end(); it++) {
      outArray[i] = *it;
      i++;
    }

    const auto drawChance = outArray[0];
    const auto winChance =
        (player == Player::PLAYER_1) ? outArray[1] : outArray[2];
    const auto loseChance =
        (player == Player::PLAYER_1) ? outArray[2] : outArray[1];

    if (1.5 * winChance > loseChance) {
      return 1.5 * winChance - loseChance;
    }
    return 0.8 * (drawChance - loseChance);
    // return std::max(winChance - loseChance, drawChance - loseChance);
  }

  GamePosition inferBestMove(const std::vector<Block> &moves) const noexcept {
    double highestScore = {-std::numeric_limits<double>::max()};
    GamePosition bestPosition{};
    const auto originalGame = getGame();
    for (auto &move : moves) {
      const auto position = move.getPosition();
      auto gameWithPossibleMove = originalGame;
      gameWithPossibleMove[position] = Block{position};
      gameWithPossibleMove[position].setOwnership(player);

      auto score = getMoveScore(gameWithPossibleMove);
      highestScore = std::max(score, highestScore);
      if (highestScore == score) {
        bestPosition = position;
      }
    }
    return bestPosition;
  }

public:
  LaptopAIGame() = default;
  LaptopAIGame(Player player, std::string modelPath) : player(player) {
    model = keras2cpp::Model::load(modelPath);
  }
  void play() noexcept {
    auto possibleMoves = getPossibleMoves();
    auto bestMove = inferBestMove(possibleMoves);
    makeMove(player, bestMove);
  }
  void playFirst() noexcept {
    const std::array<GamePosition, 5> possibleFirstPlays{
        GamePosition::TOP_LEFT, GamePosition::TOP_RIGHT,
        GamePosition::CENTER_CENTER, GamePosition::BOTTOM_LEFT,
        GamePosition::BOTTOM_RIGHT};
    std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<std::size_t> distribution(
        0, possibleFirstPlays.size() - 1);
    std::size_t number = distribution(generator);
    auto firstPlayMove = possibleFirstPlays[number];
    makeMove(player, firstPlayMove);
  }
};