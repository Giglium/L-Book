#ifndef LOANS_H
#define LOANS_H

#include <QList>
#include <QSharedPointer>
#include <QDate>

#include "loan.h"
#include "Utility/utility.h"

class loans
{
private:
    QList < QSharedPointer < loan > > loanCollection;

public:
    loans();

    void addLoan( const loans & );
    void addLoan( const QSharedPointer < loan > );
    void addLoan( const QSharedPointer < account >, const QSharedPointer < publication >, const QDate & );
    void addLoan( const QSharedPointer < account >, const QSharedPointer < publication >, const int & );

    int showLoanNumber() const;
    QSharedPointer < loan > showLoan( const int & ) const;
    loans showLoans() const;
    loans showFinishLoan() const;
    loans showUnfinishLoan() const;
    loans showDeadlineLoan( const int & ) const;
    loans showExpiredLoan() const;

    loans userLoans( const QString & ) const; /* Work only with registration number */
    loans userLoans( const QSharedPointer < account > ) const;
    loans publicationLoans( const QString & ); /* Work only with Identification code */
    loans publicationLoans( const QSharedPointer < publication > );
    loans usernameLoans( const QString & ) const;
    loans surnameLoans( const QString & ) const;
    loans unorderClassroomLoans( const QString & ) const;
    loans orderClassroomLoans( const QString & ) const;
    loans professorLoans() const;
    loans studentLoans() const;

    loans publicationLoans( const QString & ) const; /* Work only with ISBN 13 */
    loans publicationLoans( const QSharedPointer < publication > ) const;

    void removeLoan( const QSharedPointer < loan > );
    void removeAllUserLoan( const QSharedPointer < account > );
    void removeAllPublicationLoan( const QSharedPointer < publication > );
    void removeLoanFromDate( const QDate & );

    bool makeLoan( const QSharedPointer < account >, const QSharedPointer < publication >, const int & );

    void operator <<( QSharedPointer < loan > );
    void operator <<( const loans & );
};

#endif // LOANS_H
