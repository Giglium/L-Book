#include "userlist.h"

#include "ui_userlist.h"

userList::userList(const QSharedPointer<users> accounts,
                   const QSharedPointer<loans> lend,
                   const QSharedPointer<account> log, QWidget *parent)
    : QDialog(parent), ui(new Ui::userList) {
  ui->setupUi(this);

  QWidget::setWindowTitle(QCoreApplication::applicationName());
  this->setFixedSize(this->size());

  ui->logoLabel->setFont(QFont("A Charming Font", 40, 15));

  allUser = accounts;
  allLoans = lend;
  logUser = log;

  QStringList title;
  title << tr("Name") << tr("Surname") << tr("Class");
  ui->tableWidget->setColumnCount(3);
  ui->tableWidget->setHorizontalHeaderLabels(title);

  on_resetButton_clicked();
}

userList::~userList() { delete ui; }

void userList::on_exitButton_clicked() { QDialog::reject(); }

void userList::setTable(const users listUser) {
  ui->tableWidget->setRowCount(0);

  for (int i = 0; i < listUser.showUserNumber(); ++i) {
    addRow(listUser.showUser(i));
  }
}

void userList::addRow(const QSharedPointer<account> user) {
  ui->tableWidget->insertRow(ui->tableWidget->rowCount());
  int row = ui->tableWidget->rowCount() - 1;

  ui->tableWidget->setItem(row, 0,
                           new QTableWidgetItem(user->p_info()->showName()));
  ui->tableWidget->setItem(row, 1,
                           new QTableWidgetItem(user->p_info()->showSurname()));
  ui->tableWidget->setItem(row, 2,
                           new QTableWidgetItem(user->p_info()->showClass()));
}

void userList::on_tableWidget_cellDoubleClicked(int row, int) {
  showUser userData(currentUsers.showUser(row), allLoans, logUser);

  QObject::connect(&userData, SIGNAL(sendPath(loans, QString)), this,
                   SLOT(receivePath(loans, QString)));
  QObject::connect(&userData, SIGNAL(eraseUser(QSharedPointer<account>)), this,
                   SLOT(eraseUser(QSharedPointer<account>)));
  QObject::connect(
      &userData,
      SIGNAL(sendUsername(QSharedPointer<account>, QString, QString)), this,
      SLOT(addUsername(QSharedPointer<account>, QString, QString)));
  QObject::connect(this, SIGNAL(userResult(bool)), &userData,
                   SLOT(receiveResult(bool)));

  userData.exec();
  setTable(currentUsers);
}

void userList::on_resetButton_clicked() {
  currentUsers = allUser->showUsers();
  setTable(currentUsers);
}

void userList::receivePath(const loans &lends, const QString &path) {
  emit sendPath(lends, path);
}

void userList::eraseUser(const QSharedPointer<account> user) {
  allLoans->removeAllUserLoan(user);
  allUser->removeUser(user);
  on_resetButton_clicked();
}

void userList::addUser(const QSharedPointer<account> user) {
  if (!user->p_user().isNull()) {
    if (allUser->showUserFromUsername(user->p_user()->showUser()).isNull()) {
      allUser->addUser(user);
      emit userResult(true);
      on_resetButton_clicked();
    } else {
      emit userResult(false);
    }
  } else {
    allUser->addUser(user);
    emit userResult(true);
    on_resetButton_clicked();
  }
}

void userList::on_addButton_clicked() {
  modifyUser addAccount;

  QObject::connect(&addAccount, SIGNAL(sendUser(QSharedPointer<account>)), this,
                   SLOT(addUser(QSharedPointer<account>)));
  QObject::connect(this, SIGNAL(userResult(bool)), &addAccount,
                   SLOT(userResult(bool)));

  addAccount.exec();
}

void userList::addUsername(const QSharedPointer<account> user,
                           const QString &name, const QString &pass) {
  if (!allUser->checkIfUsernameExist(name)) {
    user->setUser(name, pass);
    emit userResult(true);
  } else {
    emit userResult(false);
  }
}

void userList::on_searchButton_clicked() {
  QString searchText = ui->searchLine->text();

  currentUsers = users();

  currentUsers << allUser->showUserFromNameSurname(searchText);
  currentUsers << allUser->showUserFromUsername(searchText);
  currentUsers << allUser->orderClassroomUsers(searchText);

  setTable(currentUsers);
}
