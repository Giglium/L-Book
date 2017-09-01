#include "loans.h"

loans::loans()
      :loanCollection() {}

void loans::addLoan( const loans &lends ) {
    for( int i = 0; i < lends.showLoanNumber() ; ++i ){
        addLoan( lends.showLoan( i ) );
    }
}

void loans::addLoan( const QSharedPointer < loan > lend ) {
    if( !lend.isNull() )
        loanCollection << lend;
}

void loans::addLoan( const QSharedPointer < account > user, const QSharedPointer < publication > publi, const QDate &date) {
    addLoan( QSharedPointer < loan > ( new loan( user, publi, date ) ) );
}

void loans::addLoan( const QSharedPointer < account > user, QSharedPointer < publication > publi, const int &date ) {
   addLoan( QSharedPointer < loan > ( new loan( user, publi, date ) )  );
}

int loans::showLoanNumber() const {
    return loanCollection.size();
}

QSharedPointer < loan > loans::showLoan( const int &position ) const {
    if( position <= loanCollection.size() )
        return loanCollection.at( position );
    return QSharedPointer < loan > ();
}

loans loans::showFinishLoan( ) const {
    loans lends;

    QListIterator < QSharedPointer < loan > > list( loanCollection );

    while( list.hasNext() ){
        QSharedPointer < loan > lend = list.next();
        if( lend->isfinish() )
            lends<<lend;
    }

    return lends;
}

loans loans::showLoans( ) const {
    loans lends;

    QListIterator < QSharedPointer < loan > > list( loanCollection );

    while( list.hasNext() ){
            lends<<list.next();
    }

    return lends;
}

loans loans::showUnfinishLoan() const {
    loans lends;

    QListIterator < QSharedPointer < loan > > list( loanCollection );

    while( list.hasNext() ){
        QSharedPointer < loan > lend = list.next();
        if( !lend->isfinish() )
            lends<<lend;
    }

    return lends;
}

loans loans::showDeadlineLoan( const int &deadline ) const {
    loans lends;

    QListIterator < QSharedPointer < loan > > list( loanCollection );

    while( list.hasNext() ){
        QSharedPointer < loan > lend = list.next();
        if( lend->showDaytoEnd() < deadline && !lend->isfinish() )
            lends<<lend;
    }

    return lends;
}

loans loans::showExpiredLoan() const {
    loans lends;

    QListIterator < QSharedPointer < loan > > list( loanCollection );

    while( list.hasNext() ){
        QSharedPointer < loan > lend = list.next();
        if( lend->showDaytoEnd() < 0 )
            lends<<lend;
    }

    return lends;
}

loans loans::userLoans( const QString &user ) const {
    loans lends;

    QListIterator < QSharedPointer < loan > > list( loanCollection );

    while( list.hasNext() ){
        QSharedPointer < loan > lend = list.next();
        if( lend->p_user()->p_info()->showRegistrationNumber() == user )
            lends<<lend;
    }

    return lends;
}

loans loans::userLoans( const QSharedPointer< account > user ) const {
   return userLoans( user->p_info()->showRegistrationNumber() );
}

loans loans::publicationLoans( const QString &ID ){
    loans lends;

    QListIterator < QSharedPointer < loan > > list( loanCollection );

    while( list.hasNext() ){
        QSharedPointer < loan > lend = list.next();
        if( lend->p_title()->showIdentification() == ID )
            lends<<lend;
    }

    return lends;
}

loans loans::publicationLoans( const QSharedPointer<publication> publi ){
    return publicationLoans( publi->showIdentification() );
}

loans loans::unorderClassroomLoans( const QString &clas ) const {
    loans lends;

    QListIterator < QSharedPointer < loan > > list( loanCollection );

    while( list.hasNext() ){
        QSharedPointer < loan > lend = list.next();
        if( utility::checkString( lend->p_user()->p_info()->showClass(), clas ) )
            lends<<lend;
    }

    return lends;
}


loans loans::usernameLoans( const QString & user ) const {
    loans lends;

    QListIterator < QSharedPointer < loan > > list( loanCollection );

    while( list.hasNext() ){
        QSharedPointer < loan > lend = list.next();
        if( lend->p_user()->p_user()->showUser() == user )
            lends<<lend;
    }

    return lends;
}

loans loans::surnameLoans( const QString & user ) const {
    loans lends;

    QListIterator < QSharedPointer < loan > > list( loanCollection );

    while( list.hasNext() ){
        QSharedPointer < loan > lend = list.next();
        if( lend->p_user()->p_info()->showSurname() == user )
            lends<<lend;
    }

    return lends;
}


loans loans::orderClassroomLoans( const QString &clas ) const {
    QStringList classList = utility::toQStringList( clas );
    QStringListIterator list ( classList );
    loans lends;

    while ( list.hasNext() ) {
        QString nextclass = list.next();
        lends<<unorderClassroomLoans( nextclass );
    }

    return lends;
}

loans loans::professorLoans() const {
    loans pLoans;

    QListIterator < QSharedPointer < loan > > list( loanCollection );

    while( list.hasNext() ){
        QSharedPointer < loan > lend = list.next();
        if( lend->p_user()->p_permission()->showType()  == 2 )
            pLoans<<lend;
    }

    return pLoans;
}

loans loans::studentLoans() const {
    loans sLoans;

    QListIterator < QSharedPointer < loan > > list( loanCollection );

    while( list.hasNext() ){
        QSharedPointer < loan > lend = list.next();
        if( lend->p_user()->p_permission()->showType()  == 1 )
            sLoans<<lend;
    }

    return sLoans;
}

loans loans::publicationLoans( const QString &isbn ) const {
    loans lends;

    QListIterator < QSharedPointer < loan > > list( loanCollection );

    while( list.hasNext() ){
        QSharedPointer < loan > lend = list.next();
        if( lend->p_title()->showISBN_13()  == isbn )
            lends<<lend;
    }

    return lends;
}

loans loans::publicationLoans( const QSharedPointer < publication > publi ) const {
    return publicationLoans( publi->showISBN_13() );
}

bool loans::makeLoan( const QSharedPointer < account > user, const QSharedPointer < publication > publi, const int &duration ) {
    QSharedPointer < account_permission > userPermission = user->p_permission();
    QSharedPointer < publication_permission > publiPermission = publi->p_permission();

    if( userPermission && publiPermission )
        if( userPermission->showFreedomLoan() && publiPermission->showFreedomCopy() )
            if( userPermission->makeLoan() ) {
                if( publiPermission->makeLoan() ) {
                    addLoan( user, publi, duration );
                    return true;
                }
                else
                    userPermission->returnLoan();
            }

    return false;
}

void loans::removeLoan( const QSharedPointer < loan > lend ) {
    QList < QSharedPointer < loan > >::Iterator list = loanCollection.begin();

    while( list != loanCollection.end() ){
        if( list->data()->showID() == lend->showID()  )
        {
           list = loanCollection.erase( list );
        }
        else
            ++list;
    }
}

void loans::removeAllUserLoan( const QSharedPointer < account > user ) {
    QListIterator < QSharedPointer < loan > > list( loanCollection );

    while( list.hasNext() ){
        QSharedPointer < loan > lend = list.next();
        if( lend->p_user()->p_info()->showRegistrationNumber() == user->p_info()->showRegistrationNumber() )
            removeLoan( lend );
    }
}

void loans::removeAllPublicationLoan( const QSharedPointer<publication> publi ){
    QListIterator < QSharedPointer < loan > > list( loanCollection );

    while( list.hasNext() ){
        QSharedPointer < loan > lend = list.next();
        if( lend->p_title()->showIdentification() == publi->showIdentification() )
            removeLoan( lend );
    }
}

void loans::removeLoanFromDate(  const QDate &date ) {
    QListIterator < QSharedPointer < loan > > list( loanCollection );

    while( list.hasNext() ){
        QSharedPointer < loan > lend = list.next();
        if( lend->showEndDate().toJulianDay() < date.toJulianDay() ){
            removeLoan( lend );
            list.previous();
        }

    }
}

void loans::operator <<( const QSharedPointer < loan > lend ) {
    addLoan( lend );
}

void loans::operator <<( const loans &lend ) {
    addLoan( lend );
}
