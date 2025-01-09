
#ifndef __KINGPIECE_H__
#define __KINGPIECE_H__

#include "ChessPiece.hh"

/**
 * Student implementation of a King chess piece.
 * The class is defined within the Student namespace.
 */
namespace Student
{
    class KingPiece : public ChessPiece
    {
        public:
            // constructor
            KingPiece(ChessBoard &board, Color col, int row, int column);

            // pure virtuals from base ChessPiece
            Type getType() override;
            bool canMoveToLocation(int toRow, int toColumn) override;
            const char *toString() override;
    };
}

#endif
