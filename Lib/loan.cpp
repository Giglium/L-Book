#include "loan.h"

loan::loan(const QSharedPointer<account> accoun,
           const QSharedPointer<publication> publi, const QDate &startDate,
           const QDate &endDate, const bool &fin)
    : user(accoun), title(publi), startloan(startDate), finish(fin) {
  extendLoan(endDate);
}

loan::loan(const QSharedPointer<account> accoun,
           const QSharedPointer<publication> publi, const QDate &date)
    : user(accoun),
      title(publi),
      startloan(QDate::currentDate()),
      finish(false) {
  extendLoan(date);
}

loan::loan(const QSharedPointer<account> accoun,
           const QSharedPointer<publication> publi, const int &duration)
    : user(accoun),
      title(publi),
      startloan(QDate::currentDate()),
      finish(false) {
  extendLoan(duration);
}

bool loan::setEndDate(const QDate &date) {
  if (date >= startloan) {
    endloan = date;
    finish = true;
    return true;
  }
  return false;
}

void loan::finishLoan() {
  user->p_permission()->returnLoan();
  title->p_permission()->returnLoan();
  setEndDate(QDate::currentDate());
}

bool loan::extendLoan(const QDate &date) {
  if (date >= startloan) {
    endloan = date;
    return true;
  }
  return false;
}

void loan::extendLoan(const int &days) {
  if (!endloan.isValid())
    endloan = QDate::currentDate().addDays(days);
  else
    endloan = endloan.addDays(days);
}

QDate loan::showStartDate() const { return startloan; }

QString loan::showCharStartDate() const {
  return startloan.toString("dd-MMM-yyyy");
}

QDate loan::showEndDate() const {
  if (endloan.isValid()) return endloan;
  return QDate();
}

QString loan::showCharEndDate() const {
  return endloan.toString("dd-MMM-yyyy");
}

int loan::showDayToEnd() const {
  return endloan.toJulianDay() - QDate::currentDate().toJulianDay();
}

QString loan::showID() const {
  QString ID;

  ID.append(user->p_info()->showRegistrationNumber());
  ID.append(startloan.toString("dd-MMM-yyyy"));
  ID.append(title->showIdentification());

  return ID;
}

QSharedPointer<account> loan::p_user() const { return user; }

QSharedPointer<publication> loan::p_title() const { return title; }

bool loan::isFinish() const { return finish; }
