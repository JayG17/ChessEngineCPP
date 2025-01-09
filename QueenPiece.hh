#ifndef __QUEENPIECE_H__
#define __QUEENPIECE_H__

#include "ChessPiece.hh"

namespace Student
{
    class QueenPiece : public ChessPiece
    {
        public:
            QueenPiece(ChessBoard &board, Color col, int row, int column);

            Type getType() override;
            bool canMoveToLocation(int toRow, int toColumn) override;
            const char *toString() override;
    };
}

#endif
