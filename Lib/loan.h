#ifndef LOAN_H
#define LOAN_H

#include <QString>
#include <QDate>
#include <QSharedPointer>

#include "account.h"
#include "publication.h"

class loan
{
private:
    QSharedPointer < account > user;
    QSharedPointer < publication > title;
    QDate startloan;
    QDate endloan;
    bool finish;

public:
    loan( const QSharedPointer < account >, const QSharedPointer < publication >, const QDate &, const QDate &, const bool & );
    loan( const QSharedPointer < account >, const QSharedPointer < publication >, const QDate & );
    loan( const QSharedPointer < account >, const QSharedPointer < publication >, const int & );

    bool setEndDate( const QDate & );
    void finishLoan();

    bool isfinish() const;

    bool extendLoan( const QDate & );
    void extendLoan( const int & );

    QDate showStartDate() const;
    QString showCharStartDate()const;
    QDate showEndDate() const;
    QString showCharEndDate() const;
    int showDaytoEnd() const;
    QString showID() const;

    QSharedPointer < account > p_user() const;
    QSharedPointer < publication > p_title() const;
};

#endif // LOAN_H
