#include "makeloan.h"

#include "ui_makeloan.h"

makeLoan::makeLoan(const dataCollector &coll, const QSharedPointer<account> log,
                   QWidget *parent)
    : QDialog(parent), ui(new Ui::makeLoan) {
  ui->setupUi(this);

  QWidget::setWindowTitle(QCoreApplication::applicationName());
  this->setFixedSize(this->size());

  ui->logoLabel->setFont(QFont("A Charming Font", 40, 15));
  ui->makeButton->setEnabled(false);
  ui->userTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
  ui->publicationTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

  collector = coll;
  logUser = log;

  QStringList title;
  title << tr("Name") << tr("Surname") << tr("Class");
  ui->userTable->setColumnCount(3);
  ui->userTable->setHorizontalHeaderLabels(title);
  title.clear();
  title << tr("Title") << tr("ISBN13");
  ui->publicationTable->setColumnCount(2);
  ui->publicationTable->setHorizontalHeaderLabels(title);
  ui->durationLine->setValidator(new QRegExpValidator(QRegExp("\\d*"), this));

  on_userResetButton_clicked();
  on_publiResetButton_clicked();
}

makeLoan::~makeLoan() { delete ui; }

void makeLoan::on_exitButton_clicked() { QDialog::reject(); }

void makeLoan::setUserTable(const users &listUser) {
  ui->userTable->setRowCount(0);

  for (int i = 0; i < listUser.showUserNumber(); ++i) {
    addRow(listUser.showUser(i));
  }
}

void makeLoan::setPubliTable(const library &listPubli) {
  ui->publicationTable->setRowCount(0);

  for (int i = 0; i < listPubli.showPublicationNumber(); ++i) {
    addRow(listPubli.showPublication(i));
  }
}

void makeLoan::addRow(const QSharedPointer<account> user) {
  ui->userTable->insertRow(ui->userTable->rowCount());
  int row = ui->userTable->rowCount() - 1;

  ui->userTable->setItem(row, 0,
                         new QTableWidgetItem(user->p_info()->showName()));
  ui->userTable->setItem(row, 1,
                         new QTableWidgetItem(user->p_info()->showSurname()));
  ui->userTable->setItem(row, 2,
                         new QTableWidgetItem(user->p_info()->showClass()));
}

void makeLoan::addRow(const QSharedPointer<publication> publi) {
  ui->publicationTable->insertRow(ui->publicationTable->rowCount());
  int row = ui->publicationTable->rowCount() - 1;

  ui->publicationTable->setItem(row, 0,
                                new QTableWidgetItem(publi->showTitle()));
  ui->publicationTable->setItem(row, 1,
                                new QTableWidgetItem(publi->showISBN_13()));
}

void makeLoan::on_userResetButton_clicked() {
  currentUsers = collector.p_accounts()->showUsers();
  setUserTable(currentUsers);
}

void makeLoan::on_publiResetButton_clicked() {
  currenPublications = collector.p_publications()->showPublications();
  setPubliTable(currenPublications);
}

void makeLoan::on_userTable_cellDoubleClicked(int row, int) {
  showUser userData(currentUsers.showUser(row), collector.p_loans());
  userData.exec();
}

void makeLoan::on_publicationTable_cellDoubleClicked(int row, int) {
  showPublication bookView(currenPublications.showPublication(row),
                           collector.p_loans());
  bookView.exec();
}

void makeLoan::on_userSearchButton_clicked() {
  QString searchText = ui->userSearchLine->text();

  currentUsers = users();

  currentUsers << collector.p_accounts()->showUserFromNameSurname(searchText);
  currentUsers << collector.p_accounts()->showUserFromUsername(searchText);
  currentUsers << collector.p_accounts()->orderClassroomUsers(searchText);

  setUserTable(currentUsers);
}

void makeLoan::on_publiSearchButton_clicked() {
  QString searchText = ui->publiSearchLine->text();

  currenPublications = library();

  if (utility::checkISSN(searchText))
    currenPublications << collector.p_publications()->showPublicationsFromISSN(
        searchText);

  if (utility::checkISBN13(searchText))
    currenPublications
        << collector.p_publications()->showPublicationsFromISBN13(searchText);

  if ((searchText.size() == 18 || searchText.size() == 19) &&
      utility::checkAllInteger(searchText))
    currenPublications << collector.p_publications()->showPublication(
        searchText.remove(" "));

  currenPublications << collector.p_publications()->showPublicationsFromTitle(
      searchText);

  currenPublications << collector.p_publications()->thisAuthorPublications(
      searchText);

  setPubliTable(currenPublications);
}

void makeLoan::on_userTable_cellClicked(int row, int) {
  ui->userTable->selectRow(row);
}

void makeLoan::on_publicationTable_cellClicked(int row, int) {
  ui->publicationTable->selectRow(row);
}

void makeLoan::on_makeButton_clicked() {
  if (collector.p_loans()->makeLoan(
          collector.p_accounts()->showUser(ui->userTable->currentRow()),
          collector.p_publications()->showPublication(
              ui->publicationTable->currentRow()),
          ui->durationLine->text().toInt()))
    QDialog::accept();
  else
    QMessageBox::critical(this, tr("Error"),
                          tr("Please check the permission of the user or the "
                             "publication. It wasn't possible to make loan."));
}

void makeLoan::on_durationLine_textChanged(const QString &arg) {
  if (!arg.isEmpty())
    ui->makeButton->setEnabled(true);
  else
    ui->makeButton->setEnabled(false);
}
