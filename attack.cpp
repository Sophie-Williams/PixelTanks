#include "attack.h"

Attack::Attack(
        int d,
        int f,
        int dm,
        int l,
        int s,
        AttackType t)
    :
      maxDelay(d),

      curentDelay(0),
       freeze(f),
      damage(dm),
      length(l),
      speed(s),
      type(t)
        {}
