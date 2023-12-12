#ifndef SHOWLOAN_H
#define SHOWLOAN_H

#include <QDate>
#include <QDialog>
#include <QFont>
#include <QFontMetrics>
#include <QLabel>
#include <QMessageBox>
#include <QRegExp>
#include <QRegExpValidator>
#include <QSharedPointer>

#include "../Lib/account.h"
#include "../Lib/book.h"
#include "../Lib/loan.h"
#include "../Lib/periodic.h"
#include "../Lib/publication.h"
#include "../Lib/userinfo.h"
#include "../Lib/username.h"

namespace Ui {
class showLoan;
}

class showLoan : public QDialog {
  Q_OBJECT

 public:
  explicit showLoan(const QSharedPointer<loan>,
                    const QSharedPointer<account> = QSharedPointer<account>(),
                    QWidget *parent = 0);
  ~showLoan();

 signals:
  void removeLoan(const QSharedPointer<loan>);

 private slots:
  void on_extendButton_clicked();

  void on_finishedButton_clicked();

  void on_exitButton_clicked();

  void on_deleteButton_clicked();

 private:
  Ui::showLoan *ui;
  QSharedPointer<loan> currentLoan;

  static void textForLabel(QLabel *, const QString &);
  void setInformation();
};

#endif  // SHOWLOAN_H
