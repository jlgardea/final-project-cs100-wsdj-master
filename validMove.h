#ifndef VALIDMOVE_H
#define VALIDMOVE_H

#include "chessBoardSpot.h"
#include <cmath>
using namespace std;

class ChessBoardSpot;

// strategy class, other classes just need to inherit from this
class validMove{
  public:
    validMove() {}
    validMove(int x, int y) {}
    virtual void setCoors(int currX_, int currY_, int newX_, int newY_)
    {
      newX = newX_;
      newY = newY_;
      currX = currX_;
      currY = currY_;
    }
    void cpy(const validMove& other) {
      this->newX = other.newX;
      this->newY = other.newY;
      this->currX = other.currX;
      this->currY = other.currY;
    };
    validMove(const validMove& other)
    {
      this->newX = other.newX;
      this->newY = other.newY;
      this->currX = other.currX;
      this->currY = other.currY;
    }
    ~validMove() {}
    virtual bool move(bool occupied[][9], colorEnum color, vector<int> king) { return false; };
  protected:
    int newX;
    int newY;
    int currX;
    int currY;
};

// other pieces inherit from validMove
class generalMove: public validMove {
public:
  generalMove() {}
  generalMove(int x, int y) {}
  ~generalMove() {}
  virtual bool move(bool occupied[][9], colorEnum color, vector<int> king) {
    //General cannot leave palace [3-5][0-2]
	 if ( (color == BLACK && (newY < 0 || newY > 2)) ||
            (color == RED && (newY > 9 || newY < 7)) ||
            (newX < 3 || newX > 5))
   {
     return false;
   }
    //can only move one spot up/down or one spot left/right
    if (abs(currY - newY) == 1 && abs(currX - newX) == 0 ||
      abs(currY - newY) == 0 && abs(currX - newX) == 1) {
	    /*cannot be in the same column as the other general unless there
 	     is another piece between them*/
      if (color == BLACK) {
          for (int i = newY + 1; i < 10; i++)
          {
              if (occupied[i][newX] == true)
              {
                  if (newX == king[2] && i == king[3])
                  {
                      return false;
                  }
                  else {
                      return true;
                  }
              }
           }
	         return true;
       }
      if (color == RED)
      {
          for (int i = newY - 1; i >= 0; i--)
          {
              if (occupied[i][newX] == true)
              {
                  if (newX == king[0] && i == king[1])
                  {
                      return false;
                  }
                  else
                  {
                      return true;
                  }
              }
          }
          return true;
      }
    }
    return false;
  }
};

class advisorMove: public validMove {
public:
  advisorMove() {}
  advisorMove(int x, int y) {}
  ~advisorMove() {}
  virtual bool move(bool occupied[][9], colorEnum color, vector<int> king) {
    //Advisor cannot leave Palace (RED[7-9]/BLACK[0-2])[3 -5]
        if ( (color == BLACK && (newY < 0 || newY > 2)) ||
            (color == RED && (newY > 9 || newY < 7)) ||
            (newX < 3 || newX > 5) ) {
            return false;
        }
        //can only move diagonally one space
        if ((abs(currY - newY) == 1 && abs(currX - newX) == 1)) {
            return true;
        }
      	else{
      	    return false;
      	}
    }
};

class elephantMove: public validMove {
public:
  elephantMove() {}
  elephantMove(int x, int y) {}
  ~elephantMove() {}
  virtual bool move(bool occupied[][9], colorEnum color, vector<int> king) {
    //elephant cannot cross river Red[0-4]/Black[5-9]
        if ((color == BLACK && newY > 4) ||
            (color == RED && newY < 5)) {
            return false;
        }
        //can only move two spaces diagonally with an empty space in the middle
        int  midx = (newX - currX) / 2;
        int midy = (newY - currY) / 2;
        if ((abs(currY - newY) != 2 || abs(currX - newX) != 2) ||
            (occupied[currY + midy][currX + midx] != false)) {
            return false;
        }
        return true;
  }
};

class horseMove: public validMove {
public:
  horseMove() {}
  horseMove(int x, int y) {}
  ~horseMove() {}
  virtual bool move(bool occupied[][9], colorEnum color, vector<int> king) {
      vector<vector<int> > possible;

      // Make sure the user picked a valid location
      vector<int> ValidMove1 { currX-2, currY-1}; // Left Up
      possible.push_back(ValidMove1);

      vector<int> ValidMove2 { currX-2, currY+1}; // Left Down
      possible.push_back(ValidMove2);

      vector<int> ValidMove3 { currX+2, currY-1}; // Right Up
      possible.push_back(ValidMove3);

      vector<int> ValidMove4 { currX+2, currY+1}; // Right Down
      possible.push_back(ValidMove4);

      vector<int> ValidMove5 { currX-1, currY-2}; //  Up Left
      possible.push_back(ValidMove5);

      vector<int> ValidMove6 { currX+1, currY-2}; // Up Right
      possible.push_back(ValidMove6);

      vector<int> ValidMove7 { currX-1, currY+2}; // Down Left
      possible.push_back(ValidMove7);

      vector<int> ValidMove8 { currX+1, currY+2}; // Down Right
      possible.push_back(ValidMove8);

      vector<int> newLocation {newX, newY};

      // if we enter the if statemnet that means that we have found possibel location horse can move
      if(find(possible.begin(), possible.end(), newLocation) != possible.end())
      {
          // lets check if the Vertical and Horizontal move prior to the diagonal is empty
          if((currX-1 == newX && currY-2 == newY) || (currX+1 == newX && currY-2 == newY)) // Check if up move
          {
              if(occupied[currY-1][currX] == false) // Check if Left Location is Empty
              {
                return true;
              }
          }
          else if((currX-1 == newX && currY+2 == newY) || (currX+1 == newX && currY+2 == newY))// Check if down Move
          {
              if(occupied[currY+1][currX] == false) // Check if Right Location is Empty
              {
                  return true;
              }
          }
          else if((currX-2 == newX && currY-1 == newY) || (currX-2 == newX && currY+1 == newY)) // Chcek if left Move
          {
              if(occupied[currY][currX-1] == false) // Check if Up Location is Empty
              {
                  return true;
              }
          }

          else if((currX+2 == newX && currY-1 == newY) || (currX+2 == newX && currY+1 == newY)) // Check if right Move
          {
              if(occupied[currY][currX+1] == false) // Check if Down Location is Empty
              {
                  return true;
              }
          }
          return false;

      }
      else
        return false;
    }
};

class chariotMove : public validMove {
public:
    chariotMove() {}
    chariotMove(int x, int y) {}
    ~chariotMove() {}
    virtual bool move(bool occupied[][9], colorEnum color, vector<int> king) {
    	if (currX > newX) { // moving left
        if(currY != newY)
        {
          return false;
        }
    		for (int i = currX - 1; i > newX; i--) {
    			if (occupied[currY][i] == true) { return false;}
    		}
        return true;
    	}
    	else if (currX < newX) { //moving right
        if(currY != newY)
        {
          return false;
        }
    		for (int i = currX + 1; i < newX; i++) {
    			if (occupied[i][currY] == true) { return false;}
    		}
        return true;
    	}
    	else if (currY > newY) { // moving up board(from black's POV)
        if(currX != newX)
        {
          return false;
        }
    		for (int i = currY - 1; i > newY; i--) {
    			if (occupied[i][currX] == true) { return false;}
    		}
        return true;
    	}
    	else if (currY < newY ) { //moving down board(from black's POV)
        if(currX != newX)
        {
          return false;
        }
    		for (int i = currY + 1; i < newY; i++) {
    			if (occupied[i][currX] == true) { return false;}
    		}
        return true;
    	}
      return false;
   }
};

class powMove: public validMove {
public:
  powMove() {}
  powMove(int x, int y) {}
  virtual bool move(bool occupied[][9], colorEnum color, vector<int> king) {
      int pc = 0;

      if (currX > newX && currY == newY) {
            for (int i = currX - 1; i > newX; i--) {
                if (occupied[currY][i] == true) { pc++; }
            }
       }
       else if (currX < newX && currY == newY) {
            for (int i = currX + 1; i < newX; i++) {
                if (occupied[currY][i] == true) { pc++; }
            }
       }
       else if (currY > newY && currX == newX) {
            for (int i = currY - 1; i > newY; i--) {
                if (occupied[i][currX] == true) { pc++; }
            }
       }
       else if (currY < newY && currX == newX) {
            for (int i = currY + 1; i < newY; i++) {
                if (occupied[i][currX] == true) { pc++; }
            }
       }
       else {
            return false;
       }

       if (occupied[newY][newX] == true) {
            return pc == 1 ? true : false;
       }
       else{
            return pc == 0 ? true : false;
       }
  }  
};

class soldierMove: public validMove{
public:
  soldierMove() {}
  soldierMove(int x, int y) {}
  ~soldierMove() {}
  virtual bool move(bool occupied[][9], colorEnum color, vector<int> king) {
    vector<vector<int>> possible;

    if( (color == RED && currY < 5) || (color == BLACK && currY > 4))
    {
      vector<int> temp1;
      if(color == RED)
      {
        temp1 = {currX, currY - 1};
      }
      else if(color == BLACK)
      {
        temp1  = {currX, currY + 1};
      }
      vector<int> temp2 = {currX - 1, currY};
      vector<int> temp3 = {currX + 1, currY};
      vector<int> temp4 = {newX, newY};

      possible.push_back(temp1);
      possible.push_back(temp2);
      possible.push_back(temp3);

      if(find(possible.begin(), possible.end(), temp4) != possible.end())
      {
        return true;
      }
      return false;
    }
    else {
      if(newX != currX)
      {
        return false;
      }
      if(color == RED && newY != currY - 1)
      {
        return false;
      }
      if(color == BLACK && newY != currY + 1)
      {
        return false;
      }
      return true;
    }
  }
};


#endif
