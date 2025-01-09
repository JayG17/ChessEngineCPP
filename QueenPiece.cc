#include "QueenPiece.hh"
#include "ChessBoard.hh"
#include "RookPiece.hh"
#include "BishopPiece.hh"

using Student::QueenPiece;

QueenPiece::QueenPiece(ChessBoard &board, Color col, int row, int column)
    : ChessPiece(board, col, row, column) {}

Type QueenPiece::getType() {
    return Queen;
}

bool QueenPiece::canMoveToLocation(int toRow, int toColumn) {
    RookPiece tempRook(board, getColor(), getRow(), getColumn());
    BishopPiece tempBishop(board, getColor(), getRow(), getColumn());
    return tempRook.canMoveToLocation(toRow, toColumn) || tempBishop.canMoveToLocation(toRow, toColumn);
}

const char *QueenPiece::toString() {
    return (getColor() == White) ? "♕" : "♛";
}
