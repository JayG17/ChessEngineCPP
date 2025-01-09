#include "RookPiece.hh"
#include "ChessBoard.hh"
#include <iostream>
using Student::RookPiece;

// constructor
RookPiece::RookPiece(ChessBoard &board, Color col, int row, int column)
    :ChessPiece(board, col, row, column) {

}

// pure virtuals from base ChessPiece
Type RookPiece::getType() {
    return Rook;
}
bool RookPiece::canMoveToLocation(int toRow, int toColumn) {
    int fromRow = getRow();
    int fromColumn = getColumn();
    Color currColor = getColor();
    auto &board2D = board.getBoard();

    // Option 1: move up/down via rows (constant column)
    if (fromColumn == toColumn && fromRow != toRow) {
        // check obstruction
        int rowStep = (toRow > fromRow) ? 1 : -1;
        for (int row = fromRow + rowStep; row != toRow; row += rowStep) {
            if (board2D[row][fromColumn] != nullptr) {
                return false;
            }
        }
        if (board2D[toRow][toColumn] == nullptr || board2D[toRow][toColumn]->getColor() != currColor) {
            return true;
        }
    }

    // Option 2: move left/right via columns (constant row)
    if (fromRow == toRow && fromColumn != toColumn) {
        // check obstruction
        int colStep = (toColumn > fromColumn) ? 1 : -1;
        for (int col = fromColumn + colStep; col != toColumn; col += colStep) {
            if (board2D[fromRow][col] != nullptr) {
                return false;
            }
        }
        if (board2D[toRow][toColumn] == nullptr || board2D[toRow][toColumn]->getColor() != currColor) {
            return true;
        }
    }

    // Otherwise
    return false;
}
const char *RookPiece::toString() {
    if (getColor() == White) {
        return "♖";
    }
    return "♜";
}
