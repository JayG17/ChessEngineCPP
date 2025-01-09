#ifndef __KNIGHTPIECE_H__
#define __KNIGHTPIECE_H__

#include "ChessPiece.hh"

/**
 * Student implementation of a Knight chess piece.
 * The class is defined within the Student namespace.
 */
namespace Student
{
    class KnightPiece : public ChessPiece
    {
        public:
            // Constructor
            KnightPiece(ChessBoard &board, Color col, int row, int column);

            // Override pure virtual functions
            Type getType() override;
            bool canMoveToLocation(int toRow, int toColumn) override;
            const char *toString() override;
    };
}

#endif
