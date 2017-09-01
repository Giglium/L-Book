#include "userinfo.h"

void userinfo::getRegistrationNumber () {
    registration_number.append( name[ utility::randomNumber( name.length()-1 ) ] );
    registration_number.append( QString::number( birthdate.QDate::dayOfWeek(), 10 ) );
    registration_number.append( surname[ utility::randomNumber( surname.length()-1 ) ] );
    registration_number.append( QString::number( utility::randomNumber( 10 ) ) );
    registration_number.append( QString::number( birthdate.QDate::year() - 1900 ) );
    registration_number.append( utility::randomString( 1 ) );
    registration_number = registration_number.QString::toLower();
}

userinfo::userinfo( const QString &nam, const QString &sur, const QDate &date, const QString cla, const QString cNumber, const QString mail )
         :name( nam ), surname( sur ), cellnumber( cNumber ), email( mail ) {
     birthdate.setDate( date.year(), date.month(), date.day() );
     setClass( cla );
     getRegistrationNumber();
}

userinfo::userinfo( const QString &number, const QString &nam, const QString &sur, const QDate &date, const QString cla, const QString cNumber, const QString mail )
         :registration_number( number ), name( nam ), surname( sur ), cellnumber( cNumber ), email( mail ) {
     birthdate.setDate( date.year(), date.month(), date.day() );
     setClass( cla );
}

void userinfo::setName( const QString &nam ) {
    name = nam;
}

void userinfo::setSurname( const QString &sur ) {
    surname = sur;
}

void userinfo::setDate( const QDate &date ) {
    birthdate.setDate( date.year(), date.month(), date.day() );
}

void userinfo::setCellNumber( const QString &cell ) {
    cellnumber = cell;
}

void userinfo::setEmail( const QString &mail ) {
    email = mail;
}

void userinfo::setClass( const QString &cla ) {
    if( cla.isEmpty())
        clas = QStringList();
    else
        clas = utility::toQStringList( cla );
}

QString userinfo::showRegistrationNumber() const {
    return registration_number;
}

QString userinfo::showName() const {
    if( !name.isEmpty() )
        return name;
    return QString( "" );
}

QString userinfo::showSurname() const {
    if( !surname.isEmpty() )
        return surname;
    return QString( "" );
}

QDate userinfo::showBirthdate() const {
    if( birthdate.isValid() )
        return birthdate;
    return QDate();
}

QString userinfo::showCharBirthdate() const {
    if( birthdate.isValid() )
        return birthdate.toString("dd-MMM-yyyy");
    return QString( "" );
}

QString userinfo::showCellNumber() const {
    if( !cellnumber.isEmpty() ) return cellnumber;
    return QString( "" );
}

QString userinfo::showEmail() const {
    if( !email.isEmpty() ) return email;
    return QString( "" );
}

QString userinfo::showClass()const {
    if( clas.isEmpty() )
        return QString( "" );
    return clas.join( " " );
}

QStringList userinfo::showClassList() const{
    return clas;
}

void userinfo::addClass( const QString &cla ) {
    if( !cla.isEmpty())
        clas << utility::toQStringList( cla );
}

void userinfo::removeClass( const QString &cla ) {
    QStringList classList = utility::toQStringList( cla );
    QStringListIterator list ( classList );

    while ( list.hasNext() ) {
        clas.removeAll( list.next() );
    }
}

void userinfo::removeallClass() {
    clas.clear();
}
