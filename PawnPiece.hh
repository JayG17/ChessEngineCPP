
#ifndef __PAWNPIECE_H__
#define __PAWNPIECE_H__

#include "ChessPiece.hh"

/**
 * Student implementation of a Pawn chess piece.
 * The class is defined within the Student namespace.
 */
namespace Student
{
    class PawnPiece : public ChessPiece
    {
        public:
            // constructor
            PawnPiece(ChessBoard &board, Color col, int row, int column);

            // pure virtuals from base ChessPiece
            Type getType() override;
            bool canMoveToLocation(int toRow, int toColumn) override;
            const char *toString() override;
            bool promoteIfPossible();
            // destructor
            
    };
}

#endif
