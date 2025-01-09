#include "KingPiece.hh"
#include <cmath>
#include "ChessBoard.hh"

using Student::KingPiece;

// constructor
KingPiece::KingPiece(ChessBoard &board, Color col, int row, int column)
    :ChessPiece(board, col, row, column) {

}

// pure virtuals from base ChessPiece
Type KingPiece::getType() {
    return King;
}
bool KingPiece::canMoveToLocation(int toRow, int toColumn) {
    // Rules: king must be able to move to the toRow and toColumn location
    // in terms of space +1/-1 horizontal or vertical
    // and must not be putting in check
    int fromRow = getRow();
    int fromColumn = getColumn();
    Color currColor = getColor();
    auto &board2D = board.getBoard();
    int numRows = board.getNumRows();
    int numCols = board.getNumCols();
    // Step 1. Check validity of horizontal or vertical movement
    int deltaRow = std::abs(fromRow-toRow);
    int deltaColumn = std::abs(fromColumn-toColumn);
    if (deltaRow<=1 && deltaColumn<=1) {
        // Step 2. Check that space is empty or an opponent piece
        if (board2D[toRow][toColumn] == nullptr || board2D[toRow][toColumn]->getColor() != currColor) {
            // Step 3. Check that space is not in check
            // for (int row_idx=0; row_idx<numRows; ++row_idx) {
            //     for (int col_idx=0; col_idx<numCols; ++col_idx) {
            //         if (row_idx == toRow && col_idx == toColumn) {
            //             continue;
            //         }
            //         if (row_idx == fromRow && col_idx == fromColumn) {
            //             continue;
            //         }
            //         ChessPiece *piece_idx = board2D[row_idx][col_idx];
            //         if (piece_idx && piece_idx->getColor()!=currColor && piece_idx->canMoveToLocation(toRow, toColumn)) {
            //             // if gets here, we know this is an opponent piece that can potentially create a check
            //             // scenarion to the toRow and toColumn king piece position.
            //             return false;
            //         }
            //     }
            // }
            return true; // reaches here when all pieces have provent to not be able to move to king desired pos
        }
    }

    return false;
}
// bool KingPiece::canMoveToLocation(int toRow, int toColumn) {
//     // Rules: king must be able to move to the toRow and toColumn location
//     // in terms of space +1/-1 horizontal or vertical
//     // and must not be putting in check
//     int fromRow = getRow();
//     int fromColumn = getColumn();
//     Color currColor = getColor();
//     auto &board2D = board.getBoard();
//     int numRows = board.getNumRows();
//     int numCols = board.getNumCols();
//     // Step 1. Check validity of horizontal or vertical movement
//     int deltaRow = std::abs(fromRow-toRow);
//     int deltaColumn = std::abs(fromColumn-toColumn);
//     if (deltaRow<=1 && deltaColumn<=1) {
//         // Step 2. Check that space is empty or an opponent piece
//         ChessPiece *toLocation = board2D[toRow][toColumn];
//         if (toLocation == nullptr || toLocation->getColor() != currColor) {
//             // Step 3. Check that space is not in check
//             board2D[toRow][toColumn] = this;
//             board2D[fromRow][fromColumn] = nullptr;
//             setPosition(toRow, toColumn);
//             bool kingInCheck = board.isPieceUnderThreat(toRow, toColumn);
//             board2D[fromRow][fromColumn] = this;
//             board2D[toRow][toColumn] = toLocation;
//             setPosition(fromRow, fromColumn);
//             return !kingInCheck; // reaches here when all pieces have provent to not be able to move to king desired pos
//         }
//     }

//     return false;
// }
const char *KingPiece::toString() {
    if (getColor() == White) {
        return "♔";
    }
    return "♚";
}
