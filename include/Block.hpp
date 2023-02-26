#pragma once

#include "GameClasses.hpp"

class Block {
  private:
    /* data */
    GamePosition position;
    Player ownership{Player::NONE};

  public:
    Block(/* args */){};
    Block(GamePosition position) : position(position){};
    void setOwnership(Player player) noexcept { ownership = player; };
    GamePosition getPosition() const noexcept { return position; }
    Player getPlayer() const noexcept { return ownership; }
};
