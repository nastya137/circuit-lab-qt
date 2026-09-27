#include <QApplication>
#include"schemewindow.h"
#include"startmenu.h"
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  startMenu m;
  m.show();
  return a.exec();
}
