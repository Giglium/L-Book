#ifndef MAKELOAN_H
#define MAKELOAN_H

#include <QDialog>
#include <QFont>
#include <QMessageBox>
#include <QRegExp>
#include <QRegExpValidator>
#include <QSharedPointer>
#include <QStringList>

#include "../Gui/showpublication.h"
#include "../Gui/showuser.h"
#include "../Lib/account.h"
#include "../Lib/dataCollector.h"
#include "../Lib/library.h"
#include "../Lib/loans.h"
#include "../Lib/publication.h"
#include "../Lib/userinfo.h"
#include "../Lib/users.h"

namespace Ui {
class makeLoan;
}

class makeLoan : public QDialog {
  Q_OBJECT

 public:
  explicit makeLoan(const dataCollector &,
                    const QSharedPointer<account> = QSharedPointer<account>(),
                    QWidget *parent = 0);
  ~makeLoan();

 private slots:
  void on_exitButton_clicked();
  void on_userResetButton_clicked();
  void on_publiResetButton_clicked();
  void on_userTable_cellDoubleClicked(int, int);
  void on_publicationTable_cellDoubleClicked(int, int);
  void on_userSearchButton_clicked();
  void on_publiSearchButton_clicked();
  void on_userTable_cellClicked(int, int);
  void on_publicationTable_cellClicked(int, int);
  void on_makeButton_clicked();
  void on_durationLine_textChanged(const QString &);

 private:
  Ui::makeLoan *ui;
  dataCollector collector;
  QSharedPointer<account> logUser;
  users currentUsers;
  library currenPublications;

  void setUserTable(const users &);
  void setPubliTable(const library &);

  void addRow(const QSharedPointer<account>);
  void addRow(const QSharedPointer<publication>);
};

#endif  // MAKELOAN_H
