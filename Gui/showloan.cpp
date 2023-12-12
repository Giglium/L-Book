#include "showloan.h"

#include "ui_showloan.h"

showLoan::showLoan(const QSharedPointer<loan> lend,
                   const QSharedPointer<account> logUser, QWidget *parent)
    : QDialog(parent), ui(new Ui::showLoan) {
  ui->setupUi(this);
  QWidget::setWindowTitle(QCoreApplication::applicationName());
  this->setFixedSize(this->size());

  ui->logoLabel->setFont(QFont("A Charming Font", 40, 15));

  currentLoan = lend;

  ui->startDate->setEnabled(false);
  ui->endDate->setEnabled(false);
  ui->startDate->setDate(lend->showStartDate());
  ui->extendLine->setValidator(new QRegExpValidator(QRegExp("\\d*"), this));
  setInformation();

  ui->usernameLabel->setText(lend->p_user()->p_user()->showUser());
  ui->nameLabel->setText(lend->p_user()->p_info()->showName());
  ui->surnameLabel->setText(lend->p_user()->p_info()->showSurname());
  textForLabel(ui->classLabel, lend->p_user()->p_info()->showClass());

  textForLabel(ui->titleLabel, lend->p_title()->showTitle());
  ui->isbnLabel->setText(lend->p_title()->showISBN_13());

  if (logUser.isNull() || logUser->p_permission()->showType() != 3) {
    ui->extendLabel->hide();
    ui->extendLine->hide();
    ui->extendButton->hide();
    ui->deleteButton->hide();
    ui->finishedButton->hide();
  }

  QSharedPointer<book> manual =
      qSharedPointerDynamicCast<book>(lend->p_title());
  if (!manual.isNull()) {
    ui->publicationBox->setTitle(tr("Book:"));
    ui->poliLabel_0->setText(tr("Author:"));
    ui->poliLabel_2->setText(tr("Edition:"));
    textForLabel(ui->poliLabel_1, manual->showAuthor());
    if (manual->showEdition())
      ui->poliLabel_3->setText(QString::number(manual->showEdition()));
  }

  QSharedPointer<periodic> magazine =
      qSharedPointerDynamicCast<periodic>(lend->p_title());
  if (!magazine.isNull()) {
    ui->publicationBox->setTitle(tr("Periodic:"));
    ui->poliLabel_0->setText(tr("ISSN:"));
    ui->poliLabel_2->setText(tr("Number:"));
    ui->poliLabel_1->setText(magazine->showISSN());
    if (magazine->showNumber())
      ui->poliLabel_3->setText(QString::number(magazine->showNumber()));
  }
}

showLoan::~showLoan() { delete ui; }

void showLoan::textForLabel(QLabel *label, const QString &text) {
  QFontMetrics metrix(label->font());
  int width = label->width() - 1;
  QString clippedText = metrix.elidedText(text, Qt::ElideRight, width);
  label->setText(clippedText);
}

void showLoan::setInformation() {
  ui->endDate->setDate(currentLoan->showEndDate());
  if (currentLoan->isFinish()) {
    ui->endLabel->setText(tr("Redelivered:"));
    ui->endDayLabel->hide();
    ui->extendLabel->hide();
    ui->extendLine->hide();
    ui->extendButton->hide();
    ui->dayEndLabel->hide();
    ui->finishedButton->setEnabled(false);
  } else {
    ui->endDayLabel->setText(currentLoan->showDayToEnd() > 0
                                 ? QString::number(currentLoan->showDayToEnd())
                                 : tr("Expired"));
    ui->extendLine->setText(QString::number(0));
  }
}

void showLoan::on_extendButton_clicked() {
  currentLoan->extendLoan(ui->extendLine->text().toInt());
  setInformation();
}

void showLoan::on_finishedButton_clicked() {
  QMessageBox messageBox(
      QMessageBox::Information, tr("Attention"),
      tr(" You really want to confirm the redelivery of this loan: "),
      QMessageBox::Yes | QMessageBox::No);
  messageBox.setButtonText(QMessageBox::Yes, tr("Yes"));
  messageBox.setButtonText(QMessageBox::No, tr("No"));
  if (QMessageBox::Yes == messageBox.exec()) {
    currentLoan->finishLoan();

    setInformation();
  }
}

void showLoan::on_exitButton_clicked() { QDialog::reject(); }

void showLoan::on_deleteButton_clicked() {
  QMessageBox messageBox(QMessageBox::Information, tr("Attention"),
                         tr(" You really want to delete this loan: "),
                         QMessageBox::Yes | QMessageBox::No);
  messageBox.setButtonText(QMessageBox::Yes, tr("Yes"));
  messageBox.setButtonText(QMessageBox::No, tr("No"));
  if (QMessageBox::Yes == messageBox.exec()) {
    emit removeLoan(currentLoan);
    QDialog::reject();
  }
}
