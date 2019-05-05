#include "Thread.h"
#include <QThread>

Thread::Thread() {}

void Thread::run()
{
  while (true) {
    emit refresh();
    msleep(35);
  }
}
