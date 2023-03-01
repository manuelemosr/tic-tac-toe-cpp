#pragma once

#include <map>
#include <tuple>
#include <vector>

#include "Block.hpp"
#include "GameClasses.hpp"

class Game {
public:
  using GameMap = std::map<GamePosition, Block>;

protected:
  static constexpr unsigned int maxNumberOfPlays{9U};
  GameMap gamePositions{
      {GamePosition::TOP_LEFT, Block(GamePosition::TOP_LEFT)},
      {GamePosition::TOP_CENTER, Block(GamePosition::TOP_CENTER)},
      {GamePosition::TOP_RIGHT, Block(GamePosition::TOP_RIGHT)},
      {GamePosition::CENTER_LEFT, Block(GamePosition::CENTER_LEFT)},
      {GamePosition::CENTER_CENTER, Block(GamePosition::CENTER_CENTER)},
      {GamePosition::CENTER_RIGHT, Block(GamePosition::CENTER_RIGHT)},
      {GamePosition::BOTTOM_LEFT, Block(GamePosition::BOTTOM_LEFT)},
      {GamePosition::BOTTOM_CENTER, Block(GamePosition::BOTTOM_CENTER)},
      {GamePosition::BOTTOM_RIGHT, Block(GamePosition::BOTTOM_RIGHT)}};

private:
  /* data */
  bool gameOver{false};
  Player winner{Player::NONE};
  bool canMakeMove(GamePosition position) noexcept;
  void gameUpdate() noexcept;
  void setGameOver() noexcept { gameOver = true; }
  void playerWins(Player player) noexcept {
    gameOver = true;
    winner = player;
  }
  bool playerHasBlocks(Player player,
                       std::array<GamePosition, 3> threeInALine) const noexcept;

public:
  Game(/* args */) = default;
  ~Game() = default;
  GameReturn makeMove(const Player player,
                      const GamePosition gamePosition) noexcept;
  const GameMap getGame() const noexcept;
  Block &getBlock(const GamePosition position) noexcept;
  std::vector<Block> getPlayerMoves(const Player player) const noexcept;
  std::vector<Block> getPossibleMoves() const noexcept;
  std::tuple<bool, Player> isGameOver() const noexcept;
  virtual void printGame();
};