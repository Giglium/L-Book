#include "loanlist.h"

#include "ui_loanlist.h"

loanList::loanList(const dataCollector &coll,
                   const QSharedPointer<account> user, QWidget *parent)
    : QDialog(parent), ui(new Ui::loanList) {
  ui->setupUi(this);

  QWidget::setWindowTitle(QCoreApplication::applicationName());
  this->setFixedSize(this->size());

  ui->logoLabel->setFont(QFont("A Charming Font", 40, 15));
  ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

  logUser = user;
  collector = coll;
  currentLoans = collector.p_loans()->showLoans();

  QStringList title;
  title << tr("Start Date") << tr("DeadLine") << tr("Redelivered")
        << tr("Day to end") << tr("Title") << tr("ISBN 13") << tr("Name")
        << tr("Class");
  ui->tableWidget->setColumnCount(8);
  ui->tableWidget->setHorizontalHeaderLabels(title);

  on_allButton_clicked();
}

loanList::~loanList() { delete ui; }

void loanList::on_exitButton_clicked() { QDialog::reject(); }

void loanList::setTable(const loans &lend) {
  ui->resultLabel->setText(QString::number(lend.showLoanNumber()));
  ui->tableWidget->setRowCount(0);

  for (int i = 0; i < lend.showLoanNumber(); ++i) {
    addRow(lend.showLoan(i));
  }
}

void loanList::addRow(const QSharedPointer<loan> lend) {
  ui->tableWidget->insertRow(ui->tableWidget->rowCount());
  int row = ui->tableWidget->rowCount() - 1;

  ui->tableWidget->setItem(row, 0,
                           new QTableWidgetItem(lend->showCharStartDate()));
  if (!lend->isFinish()) {
    ui->tableWidget->setItem(row, 1,
                             new QTableWidgetItem(lend->showCharEndDate()));
    ui->tableWidget->setItem(
        row, 3,
        new QTableWidgetItem(lend->showDayToEnd() > 0
                                 ? QString::number(lend->showDayToEnd())
                                 : tr("Expired")));
  } else {
    ui->tableWidget->setItem(row, 2,
                             new QTableWidgetItem(lend->showCharEndDate()));
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(tr("Redelivered")));
  }
  ui->tableWidget->setItem(row, 4,
                           new QTableWidgetItem(lend->p_title()->showTitle()));
  ui->tableWidget->setItem(
      row, 5, new QTableWidgetItem(lend->p_title()->showISBN_13()));
  ui->tableWidget->setItem(
      row, 6,
      new QTableWidgetItem(lend->p_user()->p_info()->showName() + " " +
                           lend->p_user()->p_info()->showSurname()));
  ui->tableWidget->setItem(
      row, 7, new QTableWidgetItem(lend->p_user()->p_info()->showClass()));
}

void loanList::on_tableWidget_cellDoubleClicked(int row, int) {
  QSharedPointer<loan> lend;

  if (!ui->finishButton->isEnabled())
    lend = currentLoans.showFinishLoan().showLoan(row);

  if (!ui->activeButton->isEnabled())
    lend = currentLoans.showUnfinishLoan().showLoan(row);

  if (!ui->allButton->isEnabled()) lend = currentLoans.showLoan(row);

  showLoan thisLoan(lend, logUser);
  QObject::connect(&thisLoan, SIGNAL(removeLoan(QSharedPointer<loan>)), this,
                   SLOT(removeLoan(QSharedPointer<loan>)));
  thisLoan.exec();
  if (!ui->finishButton->isEnabled()) setTable(currentLoans.showFinishLoan());

  if (!ui->activeButton->isEnabled()) setTable(currentLoans.showUnfinishLoan());

  if (!ui->allButton->isEnabled()) setTable(currentLoans);
}

void loanList::on_allButton_clicked() {
  currentLoans = collector.p_loans()->showLoans();
  setTable(currentLoans);
  ui->allButton->setEnabled(false);
  ui->activeButton->setEnabled(true);
  ui->finishButton->setEnabled(true);
}

void loanList::on_finishButton_clicked() {
  setTable(currentLoans.showFinishLoan());
  ui->allButton->setEnabled(true);
  ui->activeButton->setEnabled(true);
  ui->finishButton->setEnabled(false);
}

void loanList::on_activeButton_clicked() {
  setTable(currentLoans.showUnfinishLoan());
  ui->allButton->setEnabled(true);
  ui->activeButton->setEnabled(false);
  ui->finishButton->setEnabled(true);
}

void loanList::removeLoan(const QSharedPointer<loan> lend) {
  collector.p_loans()->removeLoan(lend);

  currentLoans = collector.p_loans()->showLoans();

  if (!ui->finishButton->isEnabled()) setTable(currentLoans.showFinishLoan());

  if (!ui->activeButton->isEnabled()) setTable(currentLoans.showUnfinishLoan());

  if (!ui->allButton->isEnabled()) setTable(currentLoans);
}

void loanList::on_exportButton_clicked() {
  QFileDialog dialog(this);
  dialog.setFileMode(QFileDialog::AnyFile);
  QStringList dir;
  dialog.setNameFilter(tr("csv (*.csv)"));
  if (dialog.exec()) dir = dialog.selectedFiles();
  QString path = dir.join("");
  if (!path.isEmpty()) {
    if (!path.contains(".csv")) path.append(".csv");

    if (!ui->finishButton->isEnabled())
      emit sendPath(currentLoans.showFinishLoan(), path);

    if (!ui->activeButton->isEnabled())
      emit sendPath(currentLoans.showUnfinishLoan(), path);

    if (!ui->allButton->isEnabled()) emit sendPath(currentLoans, path);
  }
}

void loanList::on_searchButton_clicked() {
  QString searchText = ui->searchLine->text();

  currentLoans = loans();
  library publiSearch;
  users userSearch;

  if (utility::checkISSN(searchText)) {
    publiSearch =
        collector.p_publications()->showPublicationsFromISSN(searchText);
    for (int i = 0; i < publiSearch.showPublicationNumber(); ++i)
      currentLoans << collector.p_loans()->publicationLoans(
          publiSearch.showPublication(i));
  }

  if (utility::checkISBN13(searchText)) {
    publiSearch =
        collector.p_publications()->showPublicationsFromISBN13(searchText);
    for (int i = 0; i < publiSearch.showPublicationNumber(); ++i)
      currentLoans << collector.p_loans()->publicationLoans(
          publiSearch.showPublication(i));
  }

  publiSearch =
      collector.p_publications()->showPublicationsFromTitle(searchText);
  for (int i = 0; i < publiSearch.showPublicationNumber(); ++i)
    currentLoans << collector.p_loans()->publicationLoans(
        publiSearch.showPublication(i));

  currentLoans << collector.p_loans()->orderClassroomLoans(searchText);
  currentLoans << collector.p_loans()->usernameLoans(searchText);

  userSearch = collector.p_accounts()->showUserFromNameSurname(searchText);
  for (int i = 0; i < userSearch.showUserNumber(); ++i)
    currentLoans << collector.p_loans()->userLoans(userSearch.showUser(i));

  on_activeButton_clicked();
}

void loanList::on_makebutton_clicked() {
  makeLoan newLoan(collector, logUser);
  newLoan.exec();
  on_allButton_clicked();
}
