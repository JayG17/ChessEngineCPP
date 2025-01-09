#ifndef __CHESSPIECE_H__
#define __CHESSPIECE_H__

#include "Chess.h"
#include "ChessBoard.hh"

using Student::ChessPiece;


// constructor 
ChessPiece::ChessPiece(ChessBoard &board, Color color, int row, int column)
    :row(row), column(column), color(color), board(board) {

}

// destructor
// ChessPiece::~ChessPiece() {
    
// }
// nvm don't need to define this

// get color
Color ChessPiece::getColor() {
    return color;
}

// get row
int ChessPiece::getRow() {
    return row;
}

// get column
int ChessPiece::getColumn() {
    return column;
}

void ChessPiece::setPosition(int newRow, int newColumn) {
    row = newRow;
    column = newColumn;
}

// NOTE: This abstract class has 3 pure virtual functions
// 1. getType
// 2. canMoveToLocation
// 3. toString

#endif