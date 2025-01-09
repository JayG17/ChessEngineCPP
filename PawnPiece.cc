#include "PawnPiece.hh"
#include <cmath>
#include "ChessBoard.hh"

using Student::PawnPiece;

// constructor
PawnPiece::PawnPiece(ChessBoard &board, Color col, int row, int column)
    :ChessPiece(board, col, row, column) {

}

// pure virtuals from base ChessPiece
Type PawnPiece::getType() {
    return Pawn;
}
bool PawnPiece::canMoveToLocation(int toRow, int toColumn) {
    int fromRow = getRow();
    int fromColumn = getColumn();
    Color currColor = getColor();
    auto &board2D = board.getBoard();
    int num_rows_total = board.getNumRows();
    auto enPassantTarget = board.getEnPassantTarget();
    
    if (fromColumn == toColumn) {
        // Option 1: forward one
        if ((currColor == White && toRow == fromRow-1) || (currColor == Black && toRow == fromRow+1)) {
            // Obstruction check
            if (board2D[toRow][toColumn] == nullptr) {
                return true;
            }
        }

        // Option 2: forward two
        int whiteStartRow = num_rows_total - 2;
        int blackStartRow = 1;
        if (currColor == White && fromRow == whiteStartRow && toRow == fromRow-2) {
            // Obstruction check
            if (board2D[fromRow-1][toColumn] == nullptr && board2D[toRow][toColumn] == nullptr) {
                return true;
            }
        }
        if (currColor == Black && fromRow == blackStartRow && toRow == fromRow+2) {
            // Obstruction check
            if (board2D[fromRow+1][toColumn] == nullptr && board2D[toRow][toColumn] == nullptr) {
                return true;
            }
        }
    }

    // Option 3: diagonal
    // column must change by max 1
    // row must inc/dec respectively by 1
    int deltaColumn = std::abs(fromColumn-toColumn);
    if (deltaColumn == 1) {
        // Obstruction check
        if (currColor == White && toRow == fromRow-1 && board2D[toRow][toColumn] != nullptr) {
            if (board2D[toRow][toColumn]->getColor() == Black) {
                return true;
            }
        }
        // Obstruction check
        if (currColor == Black && toRow == fromRow+1 && board2D[toRow][toColumn] != nullptr) {
            if (board2D[toRow][toColumn]->getColor() == White) {
                return true;
            }
        }
        // En passant 
        if(toRow == enPassantTarget.first && toColumn == enPassantTarget.second)
        {
            return true;
        }
    }
    // Otherwise
    return false;
}

bool PawnPiece::promoteIfPossible() {
    int promotionRow = (getColor() == White) ? 0 : board.getNumRows() - 1;
    if(getRow() == promotionRow)
    {
        board.promotePawn(getRow(), getColumn());
        return true;
    }
    return false;
}

const char *PawnPiece::toString() {
    if (getColor() == White) {
        return "♙";
    }
    return "♟";
}
