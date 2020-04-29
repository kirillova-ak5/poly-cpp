#include "anim.h"
#include "unit_segment.h"

#include <list>

struct UNIT_TEST : public UNIT, public UNIT_SEGMENT {
   ANIM *ani;
   //UNIT_SEGMENT seg;
   VEC speed;
   std::list<UNIT_SEGMENT> sled;
   
   UNIT_TEST(ANIM * anim) : 
      UNIT_SEGMENT(anim, VEC(0.0, 0.0), VEC(0.1, 0.1), 0.1),
      ani(anim), 
      speed(0, 0)
   {
      
   }

   virtual VOID Draw(VOID)
   {
      UNIT_SEGMENT::Draw();
      for (auto s : sled)
         s.Draw();
   }
   virtual VOID Response(VOID)
   {
      speed -= speed * 0.007;

      if (ani->GetKeyboardData().keysClick[VK_SPACE])
         exit(0);

      if (ani->GetKeyboardData().keys['R']) {
         speed = VEC(0, 0);
         pos = (0.0, 0.0);
         norm = !VEC(0.1, 0.1);
         sled.clear();
      }

      if (ani->GetKeyboardData().keys['W']) {
         speed += speed * 0.01;
         if (fabs(speed.x) < 1e-7 && fabs(speed.y) < 1e-7)
            speed = norm * 0.0001;
      }
      if (ani->GetKeyboardData().keys['A']) {
         VEC3 rotatedS = VEC3(speed.x, speed.y, 0) * MATR::MatrRotationZ(0.2);
         VEC3 rotatedN = VEC3(norm.x, norm.y, 0) * MATR::MatrRotationZ(0.2);
         
         speed = VEC(rotatedS.x, rotatedS.y);
         norm = !VEC(rotatedN.x, rotatedN.y);
      }
      if (ani->GetKeyboardData().keys['D']) {
         VEC3 rotatedS = VEC3(speed.x, speed.y, 0) * MATR::MatrRotationZ(-0.2);
         VEC3 rotatedN = VEC3(norm.x, norm.y, 0) * MATR::MatrRotationZ(-0.2);
         
         speed = VEC(rotatedS.x, rotatedS.y);
         norm = !VEC(rotatedN.x, rotatedN.y);
      }

      if (sled.size() >= 64)
         sled.pop_front();
         
      sled.push_back(UNIT_SEGMENT(ani, pos, norm, rad, COLOR(32, 255, 32, 0)));

      for (auto &s : sled) {
         s.IncreaseAlpha(3);
         s.Scale(1.01);
      }


      pos += speed;
   }
};

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInctance, CHAR *cmdLine, INT showCmd)
{
   ANIM anim;

   anim.AddUnit(new UNIT_TEST(&anim));
   anim.Run();

   return 0x1e;
}
