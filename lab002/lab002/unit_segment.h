#ifndef __UNIT_SEGMENT_H_
#define __UNIT_SEGMENT_H_

#include "units.h"
#include "anim.h"

class UNIT_SEGMENT : public UNIT {
   VEC PointLeft(VOID)
   {
      return pos + VEC(norm.y, -norm.x) * rad;
   }

   VEC PointRight(VOID)
   {
      return pos - VEC(norm.y, -norm.x) * rad;
   }

   COLOR col;

protected:
   VEC pos, norm;
   DBL rad;
public:

   UNIT_SEGMENT(ANIM *anim, VEC p, VEC n, DBL r, COLOR c = COLOR(32, 32, 255, 0)) :
      pos(p), rad(r), norm(n), col(c)
   {
      ani = anim;
   }

   VOID IncreaseAlpha(int a)
   {
      col.a += (255 - col.a >= a) ? a : 0;
   }

   VOID Scale(double a)
   {
      rad *= a;
   }

   VOID Draw(VOID)
   {
      ani->Bresenham(PointLeft(), PointRight(), col);
   }
   VOID Response(VOID)
   {
   }
};

#endif // __UNIT_SEGMENT_H_
