#ifndef CQUtil_H
#define CQUtil_H

#include <Qt>
#include <CKeyType.h>

namespace CQUtil {
  CKeyType convertKey(int key, Qt::KeyboardModifiers modifiers);
}

#endif
