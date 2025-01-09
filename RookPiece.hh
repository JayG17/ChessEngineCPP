#ifndef _ROOKPIECE_H__
#define _ROOKPIECE_H__

#include "ChessPiece.hh"

/**
 * Student implementation of a Rook chess piece.
 * The class is defined within the Student namespace.
 */
namespace Student
{
    class RookPiece : public ChessPiece
    {
        public:
            // constructor
            RookPiece(ChessBoard &board, Color col, int row, int column);

            // pure virtuals from base ChessPiece
            Type getType() override;
            bool canMoveToLocation(int toRow, int toColumn) override;
            const char *toString() override;
    };
}

#endif
