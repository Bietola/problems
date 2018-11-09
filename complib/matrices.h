#pragma once

template <class Board>
bool iob(const Board& board, int x, int y) {
    return x >= 0 && y >= 0 && x < board.size() && y < board.size();
}
