#include "ChessBoard.hh"
#include "PawnPiece.hh"
#include "RookPiece.hh"
#include "BishopPiece.hh"
#include "KingPiece.hh"
#include "QueenPiece.hh"
#include "KnightPiece.hh"
#include <iostream>

using Student::ChessBoard;

std::ostringstream ChessBoard::displayBoard()
{
    std::ostringstream outputString;
    // top scale
    outputString << "  ";
    for (int i = 0; i < numCols; i++)
    {
        outputString << i;
    }
    outputString << std::endl
                 << "  ";
    // top border
    for (int i = 0; i < numCols; i++)
    {
        outputString << "-";
    }
    outputString << std::endl;

    for (int row = 0; row < numRows; row++)
    {
        outputString << row << "|";
        for (int column = 0; column < numCols; column++)
        {
            ChessPiece *piece = board.at(row).at(column);
            outputString << (piece == nullptr ? " " : piece->toString());
        }
        outputString << "|" << std::endl;
    }

    // bottom border
    outputString << "  ";
    for (int i = 0; i < numCols; i++)
    {
        outputString << "-";
    }
    outputString << std::endl
                 << std::endl;

    return outputString;
}


// Constructor
ChessBoard::ChessBoard(int numRow, int numCol)
    :numRows(numRow), numCols(numCol) {
    board.resize(numRows, std::vector<ChessPiece *>(numCols, nullptr));
}


// Implementation for createChessPiece
/**
 * @brief
 * Allocates memory for a new chess piece and assigns its
 * address to the corresponding pointer in the 'board' variable.
 * Remove any existing piece first before adding the new piece.
 * @param col
 * Color of the piece to be created.
 * @param ty
 * Type of the piece to be created.
 * @param startRow
 * Starting row of the piece to be created.
 * @param startColumn
 * Starting column of the piece to be created.
 */
void ChessBoard::createChessPiece(Color col, Type ty, int startRow, int startColumn) {
    // Note:
    // board is type std::vector<std::vector<ChessPiece *>>
    // board.at(row) returns entire row
    // board.at(row).at(col) returns a pointer to a ChessPiece object.
    // *(board.at(row).at(col)) returns the ChessPiece object itself.


    // First, remove any existing piece
    ChessPiece *existingPiece = board.at(startRow).at(startColumn);
    if (existingPiece != nullptr) {
        delete board.at(startRow).at(startColumn);
        board.at(startRow).at(startColumn) = nullptr;
    }

    // Second, allocate new memory for chess piece and assign to board
    ChessPiece *newPiece = nullptr;
    if (ty == Pawn) {
        newPiece = new PawnPiece(*this, col, startRow, startColumn);
    }
    else if (ty == Rook) {
        newPiece = new RookPiece(*this, col, startRow, startColumn);
    }
    else if (ty == Bishop) {
        newPiece = new BishopPiece(*this, col, startRow, startColumn);
    }
    else if (ty == King) {
        newPiece = new KingPiece(*this, col, startRow, startColumn);
    }
    else if (ty == Knight) {
        newPiece = new KnightPiece(*this, col, startRow, startColumn);
    }
    else if (ty == Queen) {
        newPiece = new QueenPiece(*this, col, startRow, startColumn);
    }


    board.at(startRow).at(startColumn) = newPiece;

    return;
}

// Implementation for isValidMove
/**
 * @brief
 * Checks if a move is valid without accounting for turns.
 * @param fromRow
 * The row of the piece to be moved.
 * @param fromColumn
 * The column of the piece to be moved.
 * @param toRow
 * The row of the destination position.
 * @param toColumn
 * The column of the destination position.
 * @return
 * Returns true if move may be executed without accounting for turn.
 */
bool ChessBoard::isValidMove(int fromRow, int fromColumn, int toRow, int toColumn) {
    //std::cout << "Check move from: (" << fromRow << ", " << fromColumn << ") to (" << toRow << ", " << toColumn << ")" << std::endl;
    
    int MIN_ROW_POS = 0;
    int MAX_ROW_POS = numRows - 1;
    int MIN_COL_POS = 0;
    int MAX_COL_POS = numCols - 1;
    
    // First, validate 'from' position existence
    if (fromRow < MIN_ROW_POS || fromRow > MAX_ROW_POS ||
        fromColumn < MIN_COL_POS || fromColumn > MAX_COL_POS )
    {
        return false;
    }

    // Second, validate 'to' position existence
    if (toRow < MIN_ROW_POS || toRow > MAX_ROW_POS ||
        toColumn < MIN_COL_POS || toColumn > MAX_COL_POS )
    {
        return false;
    }

    // Third, get existing piece and check if valid move
    ChessPiece *existingPiece = board.at(fromRow).at(fromColumn);
    ChessPiece *targetPiece = board.at(toRow).at(toColumn);
    if (existingPiece == nullptr) {
        //std::cout << "Result: from pos DNE" << std::endl;
        return false; // piece doesn't exist
    }
    // check move is valid
    bool validMove = existingPiece->canMoveToLocation(toRow, toColumn);
    // check target piece is empty or opponent's color
    bool validColor = (targetPiece == nullptr || existingPiece->getColor() != targetPiece->getColor());
    //std::cout << "Result: returning " << temp << std::endl;
    //bool notToCheck = !isPieceUnderThreat(toRow, toColumn);
    bool kingInCheck = false;
    board.at(toRow).at(toColumn) = existingPiece;
    board.at(fromRow).at(fromColumn) = nullptr;
    existingPiece->setPosition(toRow, toColumn);
    for (int row_idx=0; row_idx<numRows; ++row_idx) {
        for (int col_idx=0; col_idx<numCols; ++col_idx) {
            ChessPiece *currPiece = board.at(row_idx).at(col_idx);
            // check if it is a king of the choice/turn color
            if (currPiece && currPiece->getType()==King && currPiece->getColor()==existingPiece->getColor()) {
                kingInCheck = isPieceUnderThreat(row_idx, col_idx);
                break;
            }
        }
    }
    board.at(fromRow).at(fromColumn) = existingPiece;
    board.at(toRow).at(toColumn) = targetPiece;
    existingPiece->setPosition(fromRow, fromColumn);
    // milestone 2 return
    return (validMove && validColor && !kingInCheck);
}

bool ChessBoard::movePiece(int fromRow, int fromColumn, int toRow, int toColumn) {
    
    // Step 1: identify start and target
    ChessPiece *startPiece = board.at(fromRow).at(fromColumn);
    ChessPiece *targetPiece = board.at(toRow).at(toColumn);
    if (startPiece == nullptr) {
        return false;
    }

    // Step 2: ensure movement desired is possible
    bool validMove = this->isValidMove(fromRow, fromColumn, toRow, toColumn);
    bool validTurn = (startPiece->getColor()==this->turn);
    //bool underThreat = this->isPieceUnderThreat(toRow, toColumn);

    // Step 3: when move is possible, set new position
    if (validMove && validTurn) {
        ChessPiece *targetPiece = board[toRow][toColumn];
        if(startPiece->getType() == Pawn)
        {
            int deltaRow = std::abs(toRow - fromRow);
            if(toRow == enPassantTarget.first && toColumn == enPassantTarget.second)
            {
                int capturedPawnRow = (turn == White) ? toRow + 1 : toRow - 1;
                delete board[capturedPawnRow][toColumn];
                board[capturedPawnRow][toColumn] = nullptr;
            }
            if(deltaRow == 2)
            {
                enPassantTarget = {(fromRow + toRow) / 2, toColumn};
            }
            else
            {
                enPassantTarget = {-1, -1};
            }
        } else {
            enPassantTarget = {-1, -1};
        }
        if (targetPiece != nullptr) {
            delete targetPiece;
        }
        startPiece->setPosition(toRow, toColumn); // set start piece to new position
        board.at(toRow).at(toColumn) = startPiece; // set board to have startPiece
        board.at(fromRow).at(fromColumn) = nullptr; // remove old position
        if(startPiece->getType() == Pawn)
        {
            bool promoted = static_cast<PawnPiece *>(startPiece)->promoteIfPossible();
            if(promoted)
            {
                startPiece = board[toRow][toColumn];
            }
            
        }
        if (this->turn == White) { // switch turn
            this->turn = Black;
        }
        else {
            this->turn = White;
        }
        return true;
    }
    return false;
}

bool ChessBoard::isPieceUnderThreat(int row, int column) {

    // Step 1: Check if piece exists at stated position
    ChessPiece *currentPositionPiece = board.at(row).at(column);
    if (currentPositionPiece == nullptr) {
        return false;
    }

    // Step 2: Check if opponent may move to that position
    Color currColor = currentPositionPiece->getColor();
    for (int row_idx = 0; row_idx < numRows; ++row_idx) {
        for (int col_idx = 0; col_idx < numCols; ++col_idx) {
            // self-check
            ChessPiece *currPiece = board.at(row_idx).at(col_idx);
            if (currPiece == nullptr || currPiece->getColor() == currColor) {
                continue;
            }
            // check threaten
            if (currPiece->canMoveToLocation(row, column)) {
                return true;
            }
        }
    }

    return false;
}

// old valgrind fix solution
// ChessBoard::~ChessBoard() {
//     for (int row = 0; row < numRows; ++row) {
//         for (int col = 0; col < numCols; ++col) {
//             if (board.at(row).at(col) != nullptr) {
//                 delete board.at(row).at(col);
//                 board.at(row).at(col) = nullptr;
//             }
//         }
//     }
// }

// new valgrind solution attempt post submission 5
// note recheck this
// ChessBoard::~ChessBoard() {
//     for (int row = 0; row < numRows; ++row) {
//         for (int col = 0; col < numCols; ++col) {
//             if (board[row][col] != nullptr) {
//                 delete board[row][col];
//             }
//         }
//     }
// }

void ChessBoard::promotePawn(int row, int column) {
    ChessPiece *pawn = board[row][column];
    if(pawn != nullptr && pawn->getType() == Pawn) 
    {
        Color color = pawn->getColor();
        delete pawn;
        board[row][column] = new QueenPiece(*this, color, row, column); // Assuming QueenPiece is implemented
        std::cout << "Promoted pawn to Queen at (" << row << ", " << column << ")\n"; // debug
    }
    else
    {
        std::cerr << "Error: Failed to promote pawn at (" << row << ", " << column << ").\n";
    }
}

// valgrind solution attempt
ChessBoard::~ChessBoard() {
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            if (board[row][col] != nullptr) {
                delete board[row][col];
                board[row][col] = nullptr;
            }
        }
    }
}
