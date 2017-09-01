#include "periodic.h"

QString periodic::fromISSNtoISBN13( const QString &ISSN ){
    QString ISBN;

    ISBN.append( "977" );
    ISBN.append( ISSN );
    ISBN.remove( 10, 1 );
    ISBN.append( "00" );

    QStringList tmp = ISBN.split( "",QString::SkipEmptyParts, Qt::CaseInsensitive );
    QStringListIterator list ( tmp );

    int sum = 0;

    for ( int i = 1; list.hasNext(); ( i == 1 ) ? i = 3 : i = 1 ) {
        QString integer = list.next();

        sum += ( integer.toInt() *i );
    }

    sum = 10 - ( sum % 10 );

    ISBN.append( QString::number( sum ) );

    return ISBN;
 }

QString periodic::fromISBN13toISSN( QString ISBN ) {
    ISBN.remove( 0,3 );
    ISBN.remove( 7, 3 );

    QStringList tmp = ISBN.split( "",QString::SkipEmptyParts, Qt::CaseInsensitive );
    QStringListIterator list ( tmp );

    int sum = 0;

    for ( int i = 8 ; i >= 2 && list.hasNext(); --i ) {
        QString integer = list.next();

        sum += ( integer.toInt() *i );
    }

    sum = 11 - ( sum % 11) ;

    if( sum != 10 )
        ISBN.append( QString::number( sum ) );
    else
        ISBN.append("X");

    ISBN.insert( 4, "-" );

    return ISBN;
}


QString periodic::toRoman( const unsigned int &number ){
    QString Roman;
    QStringList M,C,X,I;

    M<<""<<"M"<<"MM"<<"MMM";
    C<<""<<"C"<<"CC"<<"CCC"<<"CD"<<"D"<<"DC"<<"DCC"<<"DCCC"<<"CM";
    X<<""<<"X"<<"XX"<<"XXX"<<"XL"<<"L"<<"LX"<<"LXX"<<"LXXX"<<"XC";
    I<<""<<"I"<<"II"<<"III"<<"IV"<<"V"<<"VI"<<"VII"<<"VIII"<<"IX";

    Roman.append( M.at( number/1000 ) );
    Roman.append( C.at( (number%1000)/100 ) );
    Roman.append( X.at( (number%100)/10 ) );
    Roman.append( I.at( number%10 ) );

    return Roman;
}

unsigned int periodic::fromRoman( const QString &roman_number ) {
    QStringList app = roman_number.toUpper().split( "",QString::SkipEmptyParts, Qt::CaseInsensitive );
    QMap< QString, int > roman;
    QStringListIterator lista ( app );

    roman["M"] = 1000;
    roman["D"] = 500;
    roman["C"] = 100;
    roman["L"] = 50;
    roman["X"] = 10;
    roman["V"] = 5;
    roman["I"] = 1;
    roman[""] = 0;

    int sum=0;

    while ( lista.hasNext() ) {
        QString a = lista.next(), b;
        if ( lista.hasNext() )
            b = lista.peekNext();
        else
            b="";
        if( roman.value( a ) < roman.value( b ) )
            sum -= roman.value( a );
        else
            sum += roman.value( a );
    }

    return sum;
}

periodic::periodic( const QString &ID, const unsigned int &year, const unsigned int &num, const QString &title, const QString &publishing, const QString &isbn, const QDate &date, const QString subtitle, const QString genre )
         :publication( title, publishing, subtitle, genre, date ), number( num ) {
    if( year > 1000 )
        birthyear = year;
    else
        setActivityYears( year );
    setIDnumber( ID );
    setISBN_13( isbn );
}

periodic::periodic( const QString &ID, const QString &year, const unsigned int &num, const QString &title, const QString &publishing, const QString &isbn, const QDate &date, const QString subtitle, const QString genre )
         :publication( title, publishing, subtitle, genre, date ), number( num ) {
        setActivityYears( year );
        setIDnumber( ID );
        setISBN_13( isbn );
}

void periodic::setBirthYear( const unsigned int &year ) {
    birthyear = year;
}

void periodic::setActivityYears( const unsigned int &year ) {
    birthyear = release_date.year() - year;
}

void periodic::setActivityYears( const QString &roman ) {
    birthyear = release_date.year() - fromRoman( roman );
}

void periodic::setNumber( const unsigned int &num ) {
    number = num;
}

bool periodic::setISBN_13( const QString &ISBN ){
    if( ISBN.size() == 13 && utility::checkISBN13( ISBN ) ){
        ISBN_13 = ISBN;
        return true;
    }

    QString ISSN = ISBN;
    ISSN.remove("-");

    if( ISSN.size() == 8 && utility::checkISSN( ISSN ) ){
        ISBN_13 = fromISSNtoISBN13( ISSN );
        return true;
    }
    return false;
}

void periodic::setIDnumber( const QString &ID ) {
    if( ID.size() == 5 && QString::number(release_date.year()).at( 3 ) == ID.at(0) )
        ID_number = ID;
}

QString periodic::showIdentification() const {
        return ISBN_13 + ID_number;
}

int periodic::showBirthYear() const {
    return birthyear;
}

int periodic::showActivityYears() const {
   return release_date.year() - birthyear;
}

QString periodic::showRomanActivityYears( ) const {
    return toRoman( showActivityYears() );
}

int periodic::showNumber() const {
    return number;
}

int periodic::showMonth() const {
    return release_date.month();
}

QString periodic::showCharMonth() const {
    return QDate::longMonthName( release_date.month() );
}

QString periodic::showISSN() const {
    return fromISBN13toISSN( ISBN_13 );
}

QString periodic::showID_number() const{
    return ID_number;
}
