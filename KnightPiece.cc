#include "KnightPiece.hh"
#include <cmath>
#include "ChessBoard.hh"

using Student::KnightPiece;

// Constructor
KnightPiece::KnightPiece(ChessBoard &board, Color col, int row, int column)
    : ChessPiece(board, col, row, column) {}

// Get piece type
Type KnightPiece::getType() {
    return Knight;
}

// Can move to location
bool KnightPiece::canMoveToLocation(int toRow, int toColumn) {
    int fromRow = getRow();
    int fromColumn = getColumn();
    Color currColor = getColor();
    auto &board2D = board.getBoard();

    int rowDiff = std::abs(toRow - fromRow);
    int colDiff = std::abs(toColumn - fromColumn);

    // Ensure the move follows the "L-shape" (2x1 or 1x2)
    if ((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2)) {
        if (board2D[toRow][toColumn] == nullptr || board2D[toRow][toColumn]->getColor() != currColor) {
            return true;
        }
    }

    return false;
}

const char *KnightPiece::toString() {
    return (getColor() == White) ? "♘" : "♞";
}
