#include "BishopPiece.hh"
#include <cmath>
#include "ChessBoard.hh"

using Student::BishopPiece;

// constructor
BishopPiece::BishopPiece(ChessBoard &board, Color col, int row, int column)
    :ChessPiece(board, col, row, column) {

}

// pure virtuals from base ChessPiece
Type BishopPiece::getType() {
    return Bishop;
}
bool BishopPiece::canMoveToLocation(int toRow, int toColumn) {
    int fromRow = getRow();
    int fromColumn = getColumn();
    Color currColor = getColor();
    auto &board2D = board.getBoard();

    if (fromRow == toRow && fromColumn == toColumn) {
        return false;
    }

    // Option 1: move diagonal
    int deltaRow = std::abs(fromRow-toRow);
    int deltaColumn = std::abs(fromColumn-toColumn);
    if (deltaRow == deltaColumn) {
        // check obstruction
        int rowStep = (toRow > fromRow) ? 1 : -1;
        int colStep = (toColumn > fromColumn) ? 1 : -1;
        int row_idx = fromRow + rowStep;
        int col_idx = fromColumn + colStep;
        while (row_idx != toRow && col_idx != toColumn) {
            if (board2D[row_idx][col_idx] != nullptr) {
                return false;
            }
            row_idx += rowStep;
            col_idx += colStep;
        }
        // Obstruction check
        ChessPiece* targetPiece = board2D[toRow][toColumn];
        if (targetPiece == nullptr) {
            return true;
        }
        if (targetPiece->getColor() != currColor) {
            return true;
        }
    }

    // Otherwise
    return false;
}
const char *BishopPiece::toString() {
    if (getColor() == White) {
        return "♗";
    }
    return "♝";
}
