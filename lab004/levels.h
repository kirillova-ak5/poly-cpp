#ifndef __LEVELS_H_
#define __LEVELS_H_

#include "def.h"
#include "texture.h"
#include <ctime>

class ANIM;
class LEVEL;

class PAWN {
public:
  LEVEL* lev = NULL;
  BOOL IsExist = TRUE;
  virtual VOID Draw(VOID) = 0;
  virtual VOID Response(VOID) = 0;
};

struct TILE
{
  enum TYPE
  {
    FREE = 0,
    WALLS = 1,
    FOODS = 2
  } type;
  PAWN *pawn;
};

class LEVEL {
public:
   ANIM *ani = NULL;
   std::vector<PAWN *> pawns;
   std::vector<std::vector<TILE>> map;
   VEC2i Size;
   texture Background;
   LEVEL(std::string Filename);
   VOID Draw(VOID)
   {
      Background.Apply();

      glBegin(GL_QUADS);

      glTexCoord2f(0, 0);
      glVertex2f(-1, 1);
      glTexCoord2f(1, 0);
      glVertex2f(1, 1);
      glTexCoord2f(1, 1);
      glVertex2f(1, -1);
      glTexCoord2f(0, 1);
      glVertex2f(-1, -1);
      glEnd();

      for (auto &a : pawns)
         if (a->IsExist)
            a->Draw();
   }
   VOID Response(VOID)
   {
      for (auto &a : pawns)
         a->Response();
   }
   ~LEVEL();
};

class SNAKE : public PAWN
{
public:
  static texture Tex;
  std::vector<VEC2i> Arr;
  VEC2i CurVel = VEC2i(0);
  SNAKE() {};
  ~SNAKE() {};
  virtual VOID Draw(VOID);
  virtual VOID Response(VOID);
};

class WALL : public PAWN
{
public:
  static texture Tex;
  VEC2i Pos;
  WALL() {};
  ~WALL() {};
  virtual VOID Draw(VOID);
  virtual VOID Response(VOID) {};
};

class FOOD : public PAWN
{
public:
  static texture Tex;
  UINT Type = 0;
  VEC2i Pos;
  FOOD()
  {
    Type = rand() % 3;
  }
  ~FOOD() {}
  virtual VOID Draw(VOID);
  virtual VOID Response(VOID);
};

#endif // __LEVELS_H_
