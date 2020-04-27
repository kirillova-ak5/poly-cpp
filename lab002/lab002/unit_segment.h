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

public:
   COLOR col;
   VEC pos, norm;
   DBL rad;

   UNIT_SEGMENT(ANIM *anim, VEC p, VEC n, DBL r, COLOR c = COLOR(32, 32, 255, 0)) :
      pos(p), rad(r), norm(n), col(c)
   {
      ani = anim;
   }

   VOID SetAlpha(BYTE a)
   {
      col.a = a;
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
