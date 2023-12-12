#include "chessBoardSpot.h"

class ChessBoardSpot;
using namespace std;

ChessBoardSpot::ChessBoardSpot(pieceTypeEnum piece_, colorEnum color_, char boardChar_, validMove* move_)
    :piece{piece_}, color{color_}, boardChar{boardChar_}, move{move_}
{
}

ChessBoardSpot::ChessBoardSpot()
{
  move = nullptr;
  piece = EMPTY;
  color = NONE;
  boardChar = '*';
}

void ChessBoardSpot::setColor(colorEnum color_)
{
  this->color = color_;
}
colorEnum ChessBoardSpot::getColor() const
{
  return this->color;
}

pieceTypeEnum ChessBoardSpot::getPiece() const
{
  return this->piece;
}
void ChessBoardSpot::setPiece(pieceTypeEnum piece_)
{
  this->piece = piece_;
}

char ChessBoardSpot::getChar() const
{
  return this->boardChar;
}
void ChessBoardSpot::setChar(char char_)
{
  this->boardChar = char_;
}

void ChessBoardSpot::setMove(validMove* move_)
{
  this->move = move_;
}
validMove* ChessBoardSpot::getMove() const
{
  return this->move;
}

ChessBoardSpot::~ChessBoardSpot()
{
  delete move;
}

void ChessBoardSpot::clear()
{
  this->piece = EMPTY;
  this->color = NONE;
  this->boardChar = '*';
  delete this->move;
  this->move = nullptr;
}

string ChessBoardSpot::getPieceStr()
{
  switch(this->piece)
  {
    case GENERAL:
    {
      return "general";
      break;
    }
    case ADVISOR:
    {
      return "advisor";
      break;
    }
    case ELEPHANT:
    {
      return "elephant";
      break;
    }
    case HORSE:
    {
      return "horse";
      break;
    }
    case CHARIOT:
    {
      return "chariot";
      break;
    }
    case CANNON:
    {
      return "cannon";
      break;
    }
    case SOLDIER:
    {
      return "soldier";
      break;
    }
  }
  return "empty";
}

ChessBoardSpot::ChessBoardSpot(const ChessBoardSpot &cpyObj)
{
  piece = cpyObj.getPiece();
  color = cpyObj.getColor();
  boardChar = cpyObj.getChar();
  delete this->move;

  if(cpyObj.getMove() == nullptr)
  {
    this->move = nullptr;
  }
  else{
    switch(cpyObj.getPiece())
    {
      case GENERAL:
      {
        this->move = new generalMove();
        this->move->cpy(*cpyObj.getMove());
        break;
      }
      case ADVISOR:
      {
        this->move = new advisorMove();
        this->move->cpy(*cpyObj.getMove());
        break;
      }
      case ELEPHANT:
      {
        this->move = new elephantMove();
        this->move->cpy(*cpyObj.getMove());
        break;
      }
      case HORSE:
      {
        this->move = new horseMove();
        this->move->cpy(*cpyObj.getMove());
        break;
      }
      case CHARIOT:
      {
        this->move = new chariotMove();
        this->move->cpy(*cpyObj.getMove());
        break;
      }
      case CANNON:
      {
        this->move = new powMove();
        this->move->cpy(*cpyObj.getMove());
        break;
      }
      case SOLDIER:
      {
        this->move = new soldierMove();
        this->move->cpy(*cpyObj.getMove());
        break;
      }
      default:
      {
        this->move = nullptr;
      }
    }
  }
}
void ChessBoardSpot::cpy(ChessBoardSpot cpyObj)
{
  delete this->move;

  this->piece = cpyObj.piece;
  this->color = cpyObj.color;
  this->boardChar = cpyObj.boardChar;
  if(cpyObj.getMove() == nullptr)
  {
    this->move = nullptr;
  }
  else
  {
    switch(cpyObj.getPiece())
    {
      case GENERAL:
      {
        this->move = new generalMove();
        this->move->cpy(*cpyObj.getMove());
        break;
      }
      case ADVISOR:
      {
        this->move = new advisorMove();
        this->move->cpy(*cpyObj.getMove());
        break;
      }
      case ELEPHANT:
      {
        this->move = new elephantMove();
        this->move->cpy(*cpyObj.getMove());
        break;
      }
      case HORSE:
      {
        this->move = new horseMove();
        this->move->cpy(*cpyObj.getMove());
        break;
      }
      case CHARIOT:
      {
        this->move = new chariotMove();
        this->move->cpy(*cpyObj.getMove());
        break;
      }
      case CANNON:
      {
        this->move = new powMove();
        this->move->cpy(*cpyObj.getMove());
        break;
      }
      case SOLDIER:
      {
        this->move = new soldierMove();
        this->move->cpy(*cpyObj.getMove());
        break;
      }
      default:
      {
        this->move = nullptr;
      }
    }
  }
}

void ChessBoardSpot::setData(pieceTypeEnum piece_, colorEnum color_,
char boardChar_, validMove* move_)
{
  piece = piece_;
  color = color_;
  boardChar = boardChar_;
  move = move_;
}
