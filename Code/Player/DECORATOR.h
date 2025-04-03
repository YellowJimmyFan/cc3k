#ifndef DECORATOR_H
#define DECORATOR_H

#include "PC.h"

class Decorator : public PC {
 protected:
  PC *original;
 public:
  Decorator(PC *effected);
  virtual ~Decorator();
};

#endif
