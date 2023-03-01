#include "Game.hpp"
#include <array>
#include <iostream>
#include <stdexcept>
#include <tuple>

bool Game::canMakeMove(GamePosition position) noexcept {
  if (gamePositions[position].getPlayer() == Player::NONE) {
    return true;
  }
  return false;
}

void Game::gameUpdate() noexcept {
  static unsigned int gamePlays{0U};
  std::array<std::array<GamePosition, 3>, 8> threeInALinePossibilities{
      {{GamePosition::TOP_LEFT, GamePosition::TOP_CENTER,
        GamePosition::TOP_RIGHT},
       {GamePosition::CENTER_LEFT, GamePosition::CENTER_CENTER,
        GamePosition::CENTER_RIGHT},
       {GamePosition::BOTTOM_LEFT, GamePosition::BOTTOM_CENTER,
        GamePosition::BOTTOM_RIGHT},
       {GamePosition::TOP_LEFT, GamePosition::CENTER_LEFT,
        GamePosition::BOTTOM_LEFT},
       {GamePosition::TOP_CENTER, GamePosition::CENTER_CENTER,
        GamePosition::BOTTOM_CENTER},
       {GamePosition::TOP_RIGHT, GamePosition::CENTER_RIGHT,
        GamePosition::BOTTOM_RIGHT},
       {GamePosition::TOP_LEFT, GamePosition::CENTER_CENTER,
        GamePosition::BOTTOM_RIGHT},
       {GamePosition::BOTTOM_LEFT, GamePosition::CENTER_CENTER,
        GamePosition::TOP_RIGHT}}};

  std::array<Player, numberOfPlayers> players{Player::PLAYER_1,
                                              Player::PLAYER_2};

  gamePlays++;
  if ((gamePlays >= maxNumberOfPlays) || std::get<0>(isGameOver())) {
    setGameOver();
    return;
  }

  for (const auto &threeInALine : threeInALinePossibilities) {
    for (const auto &player : players) {
      if (playerHasBlocks(player, threeInALine)) {
        playerWins(player);
      }
    }
  }
}

bool Game::playerHasBlocks(
    Player player, std::array<GamePosition, 3> threeInALine) const noexcept {
  auto playerBlocks = getPlayerMoves(player);

  bool hasAllBlock{true};
  for (const auto &position : threeInALine) {
    bool hasBlock{false};
    for (const auto &block : playerBlocks) {
      if (block.getPosition() == position) {
        hasBlock = true;
      }
    }
    hasAllBlock &= hasBlock;
  }

  return hasAllBlock;
}

GameReturn Game::makeMove(const Player player,
                          const GamePosition gamePosition) noexcept {
  auto [gameOver, _] = isGameOver();
  if (gameOver) {
    return GameReturn::GAME_OVER;
  }

  if (canMakeMove(gamePosition)) {
    auto &block = getBlock(gamePosition);
    block.setOwnership(player);

    gameUpdate();

    auto [gameOver, winningPlayer] = isGameOver();
  } else {
    return GameReturn::MOVE_NOT_POSSIBLE;
  }

  return GameReturn::OK;
}

const Game::GameMap Game::getGame() const noexcept { return gamePositions; }

Block &Game::getBlock(const GamePosition position) noexcept {
  return gamePositions.at(position);
}

std::vector<Block> Game::getPlayerMoves(const Player player) const noexcept {
  std::vector<Block> playerBlocks{};
  for (auto &[_, block] : gamePositions) {
    if (block.getPlayer() == player) {
      playerBlocks.push_back(block);
    }
  }
  return playerBlocks;
}

std::vector<Block> Game::getPossibleMoves() const noexcept {
  return getPlayerMoves(Player::NONE);
}

std::tuple<bool, Player> Game::isGameOver() const noexcept {
  return std::make_tuple(gameOver, winner);
}

void Game::printGame() { throw std::logic_error("printGame not implemented."); }