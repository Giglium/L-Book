#include "utility.h"

QString utility::encript(const QString &pass){
    QCryptographicHash password ( QCryptographicHash::Md5 );
    password.addData( pass.toUtf8() );
    return QString( password.result().toHex() );
}

QStringList utility::toQStringList( const QString &string ){
    QStringList stringList;
    if( string.contains( "," ) )
        return stringList << string.split( "," ,QString::SkipEmptyParts, Qt::CaseInsensitive );
    else
        if( string.contains( "-" ) )
            return stringList << string.split( "-" ,QString::SkipEmptyParts, Qt::CaseInsensitive );
        else
            if( string.contains( ";" ) )
                return stringList << string.split( ";" ,QString::SkipEmptyParts, Qt::CaseInsensitive );
            else
                if( string.contains( " " ) )
                    return stringList << string.split( " " ,QString::SkipEmptyParts, Qt::CaseInsensitive );
                else
                    return stringList << string;
}

QString utility::fusePath( const QDir &firstPath, const QDir &secondPath ) {
    return fusePath( firstPath.absolutePath(), secondPath.absolutePath() );
}

QString utility::fusePath( const QDir &firstPath, const QString &secondPath ) {
      return fusePath( firstPath.absolutePath(), secondPath );
}

QString utility::fusePath( const QString &firstPath, const QDir &secondPath ) {
    return fusePath( firstPath, secondPath.absolutePath() );
}

QString utility::fusePath( const QString &firstPath, const QString &secondPath ){
    return QDir::cleanPath( firstPath + QDir::separator() + secondPath );
}


bool utility::checkAllInteger( const QString &string ) {

    for (int i = 0; i < string.size(); ++i )
    {
        if ( string[i].isLetter())
            return false;
    }

    return true;
}

bool utility::checkISBN13( const QString &isbn ) {
    if( isbn.size() == 13 && checkAllInteger( isbn ) ){
        QStringList stringList = isbn.split( "",QString::SkipEmptyParts, Qt::CaseInsensitive );
        QStringListIterator list ( stringList );

        int sum=0;

        for ( int i = 1 ; list.hasNext(); ( i == 1 ) ? i = 3 : i = 1 ) {
            QString string = list.next();

            sum += ( string.toInt() *i );
        }

        if ( !( sum % 10 ) )
            return true;
    }
    return false;
}

bool utility::checkISSN( QString issn ) {
    issn.remove( QChar('-') );
    if( issn.size() == 8 ){
        QStringList stringList = issn.split( "",QString::SkipEmptyParts, Qt::CaseInsensitive );
        QStringListIterator list ( stringList );

        int sum=0;

        for ( int i = 8 ; i >= 2 && list.hasNext(); --i ) {
            QString string = list.next();
            sum += ( string.toInt() *i );
        }

        sum = 11 - ( sum % 11) ;

        if( sum == 10 && issn.at(7).toUpper() == 'X' )
            return true;

        if ( sum  == issn.at( 7 ).digitValue() )
            return true;

    }
    return false;
}

bool utility::checkString ( const QString firstString, const QString secondString, const bool caseSensitive ){
    QStringList firstStringList = utility::toQStringList( firstString );
    QStringList secondoStringList = utility::toQStringList( secondString );
    return utility::checkString( firstStringList, secondoStringList, caseSensitive );
}

bool utility::checkString ( const QStringList firstStringList, const QString string, const bool caseSensitive ){
    QStringList secondStringList = utility::toQStringList( string );
    return utility::checkString( firstStringList, secondStringList, caseSensitive );
}

bool utility::checkString ( const QString string, const QStringList secondStringList, const bool caseSensitive ){
    QStringList firstStringList = utility::toQStringList( string );
    return utility::checkString( firstStringList, secondStringList, caseSensitive );
}

bool utility::checkString( const QStringList firstStringList, const QStringList secondStringList, const bool caseSensitive ) {
    QStringListIterator list ( secondStringList );
    while ( list.hasNext() ) {
        QString string = list.next();
        QStringList secondList = firstStringList.filter( string, Qt::CaseInsensitive );
        QStringListIterator list1( secondList );
        while ( list1.hasNext() ) {
            if( caseSensitive ) {
                if( list1.next() == string ) return true;
            }
            else
                if( list1.next().toUpper() == string.toUpper() ) return true;
        }
    }
    return false;
}

int utility::randomNumber( const int &high, const int low ) {
    return qrand() % ( ( high + 1 ) - low ) + low;
}

QString utility::randomString( const int &charactersNumber ) {
    const QString characters("abcdefghijklmnopqrstuvwxyz");
    QString random;

    for(int i = 0; i < charactersNumber; ++i ) {
           QChar character = characters.at( utility::randomNumber( 26 ) );
           random.append( character );
       }

    return random;
}
