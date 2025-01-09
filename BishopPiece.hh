
#ifndef __BISHOPPIECE_H__
#define __BISHOPPIECE_H__

#include "ChessPiece.hh"

/**
 * Student implementation of a Bishop chess piece.
 * The class is defined within the Student namespace.
 */
namespace Student
{
    class BishopPiece : public ChessPiece
    {
        public:
            // constructor
            BishopPiece(ChessBoard &board, Color col, int row, int column);

            // pure virtuals from base ChessPiece
            Type getType() override;
            bool canMoveToLocation(int toRow, int toColumn) override;
            const char *toString() override;
    };
}

#endif
