#pragma once

enum class GamePosition {
    TOP_LEFT,
    TOP_CENTER,
    TOP_RIGHT,
    CENTER_LEFT,
    CENTER_CENTER,
    CENTER_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_CENTER,
    BOTTOM_RIGHT,
    Count
};

enum class GameReturn {
    OK,
    GAME_OVER,
    MOVE_NOT_POSSIBLE,
};

enum class Player { NONE, PLAYER_1, PLAYER_2 };

constexpr auto numberOfPlayers{static_cast<unsigned int>(Player::PLAYER_2)};