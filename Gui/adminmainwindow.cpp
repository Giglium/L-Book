#include "adminmainwindow.h"

#include "ui_adminmainwindow.h"

adminMainWindow::adminMainWindow(const QSharedPointer<account> user,
                                 QWidget *parent)
    : QMainWindow(parent), ui(new Ui::adminMainWindow) {
  ui->setupUi(this);

  QWidget::setWindowTitle(QCoreApplication::applicationName());
  this->statusBar()->setSizeGripEnabled(false);
  this->setFixedSize(this->size());
  setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter,
                                  this->size(),
                                  qApp->desktop()->availableGeometry()));

  ui->logoLabel->setFont(QFont("A Charming Font", 40, 15));

  logUser = user;
}

adminMainWindow::~adminMainWindow() { delete ui; }

void adminMainWindow::on_exitButton_clicked() { emit closeAdmin(this); }

void adminMainWindow::on_publicationButton_clicked() {
  emit openPublication(logUser);
}

void adminMainWindow::on_loanButton_clicked() { emit openLoan(logUser); }

void adminMainWindow::on_saveButton_clicked() { emit saveData(); }

void adminMainWindow::saveResult(const bool &result) {
  if (result)
    QMessageBox::information(this, tr("Saved"),
                             tr("All data have been saved!"));
}

void adminMainWindow::on_clearButton_clicked() {
  QMessageBox messageBox(QMessageBox::Information, tr("Uninstall"),
                         tr(" You really want to delete all the local data and "
                            "close the program ? "),
                         QMessageBox::Yes | QMessageBox::No);
  messageBox.setButtonText(QMessageBox::Yes, tr("Yes"));
  messageBox.setButtonText(QMessageBox::No, tr("No"));
  if (QMessageBox::Yes == messageBox.exec()) {
    emit uninstall();
  }
}

void adminMainWindow::on_userButton_clicked() { emit openUser(logUser); }
