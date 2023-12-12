#include <QApplication>
#include <QFontDatabase>
#include <QIcon>
#include <QLocale>

#include "App/applicationmanager.h"
#include "Utility/utility.h"

void setupTheApplication(const QApplication &);

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  setupTheApplication(a);
  applicationManager app;
  app.start();
  return a.exec();
}

void setupTheApplication(const QApplication &app) {
  QCoreApplication::setApplicationName(QString("L-Book"));
  app.setWindowIcon(QIcon(":/images/logo.png"));
  QLocale::setDefault(QLocale(QLocale::English));
  QFontDatabase::addApplicationFont(":/fonts/Achafont.ttf");
}
