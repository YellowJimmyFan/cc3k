#include "DECORATOR.h"

Decorator::Decorator(PC *effected): original{effected} {}

Decorator::~Decorator() { delete original; }
