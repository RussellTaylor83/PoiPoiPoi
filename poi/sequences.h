//#include "justeat.h"
//#include "infernopattern.h"
//#include "lightning3blue.h"
#include "lightning3white.h"
#include "holdinghands.h"
#include "celticknot.h"
#include "skullxbones.h"
#include "arrows.h"
#include "flower.h"

int duration;
int numberOfSlices;
unsigned long rotationSpeed;

ImageStruct Sequences[3][2] = {
  {celticknot, skullxbones},
  {arrows, flower},
  {holdinghands, lightning3white},
};
