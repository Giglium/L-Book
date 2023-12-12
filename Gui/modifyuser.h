#ifndef MODIFYUSER_H
#define MODIFYUSER_H

#include <QDate>
#include <QDialog>
#include <QFont>
#include <QMessageBox>
#include <QRegExpValidator>
#include <QSharedPointer>
#include <QString>
#include <QWidget>

#include "../Lib/account.h"
#include "../Lib/account_permission.h"
#include "../Lib/userinfo.h"
#include "../Lib/username.h"
#include "../Utility/utility.h"

namespace Ui {
class modifyUser;
}

class modifyUser : public QDialog {
  Q_OBJECT

 public:
  explicit modifyUser(const QSharedPointer<account> = QSharedPointer<account>(),
                      const bool = false, QWidget *parent = 0);
  ~modifyUser();

 signals:
  void sendUser(const QSharedPointer<account>);
  void sendUsername(const QSharedPointer<account>, const QString &,
                    const QString &);

 private slots:
  void userResult(const bool &);
  void checkLineEdits(const QString &);
  void on_ExitButton_clicked();
  void on_nextButton_clicked();

 private:
  Ui::modifyUser *ui;
  QSharedPointer<account> user;
  bool mode;
};

#endif  // MODIFYUSER_H
