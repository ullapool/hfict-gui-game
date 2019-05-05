#ifndef THREAD_H
#define THREAD_H

#include <QThread>

class Thread : public QThread
{
  Q_OBJECT

public:
  Thread();
  virtual void run();

signals:
  void refresh();
};

#endif // THREAD_H
