#ifndef UTILITY_H
#define UTILITY_H

#include <QtGlobal>
#include <QString>
#include <QStringList>
#include <QDir>
#include <QCryptographicHash>


namespace utility {
    QString encript( const QString & );

    QStringList toQStringList( const QString & );

    QString fusePath( const QDir &, const QDir & );
    QString fusePath( const QDir &, const QString & );
    QString fusePath( const QString &, const QDir & );
    QString fusePath( const QString &, const QString & );

    bool checkAllInteger( const QString & );
    bool checkISBN13( const QString & );
    bool checkISSN( QString );
    bool checkString( const QString, const QString, const bool =true );
    bool checkString( const QStringList, const QString, const bool =true );
    bool checkString( const QString, const QStringList, const bool =true );
    bool checkString( const QStringList, const QStringList, const bool =true );

    int randomNumber( const int &, const int =0 ); /* generate random number between 0 to X-1 */
    QString randomString( const int & ); /* generate a random string lenght x */
}

#endif // UTILITY_H
