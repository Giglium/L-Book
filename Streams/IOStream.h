#ifndef IOSTREAM_H
#define IOSTREAM_H

#include <QString>
#include <QDir>
#include <QStandardPaths>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTranslator>
#include <QApplication>
#include <QLocale>
#include <QTextStream>

#include "../Lib/dataCollector.h"
#include "../Lib/users.h"
#include "../Lib/account.h"
#include "../Lib/userinfo.h"
#include "../Lib/username.h"
#include "../Lib/library.h"
#include "../Lib/publication.h"
#include "../Lib/periodic.h"
#include "../Lib/book.h"
#include "../Lib/loans.h"
#include "../Lib/loan.h"
#include "../Utility/utility.h"


class IOStream
{
private:
    QDir localPath;
    QDir sharedPath;

    QSharedPointer < users > loadUsers( const QString & );
    QSharedPointer < library > loadLibrary( const QString & );
    QSharedPointer < loans > loadLoans( const QSharedPointer < library >, const QSharedPointer < users >, const QString & );

    QJsonObject readJsonFile( const QString & ) const;
    void writeJsonFile( const QJsonDocument &, const QString & ) const;

    QSharedPointer < account > fromJsontoUser( const QJsonObject & );
    QSharedPointer < publication > fromJsontoPubblication( const QJsonObject & );
    QSharedPointer < loan > fromJsontoLoan( const QJsonObject &, const QSharedPointer < library >, const QSharedPointer < users > ) const;

    void writeJsonfromUser( const QSharedPointer < users >, const QString & ) const;
    void writeJsonfromLibrary( const QSharedPointer < library >, const QString & ) const;
    void writeJsonfromLoans( const QSharedPointer < loans >, const QString & ) const;

    QJsonObject toJson( const QSharedPointer < account > ) const;
    QJsonObject toJson( const QSharedPointer < publication > ) const;
    QJsonObject toJson( const QSharedPointer < loan > ) const;

    static void toCsv( const QSharedPointer < loan >, QTextStream & );
    static void toCsv( const QSharedPointer< publication >, QTextStream & );

public:
    IOStream();

    bool firstStart() const;

    bool setSharedDir();
    bool setSharedDir( const QString & );

    void loadsettings();
    dataCollector loadData();
    dataCollector loadData( const QString & );

    void saveSettings();
    void saveData( const dataCollector & ) const;
    void saveData( const dataCollector &, const QString & ) const;

    bool switchTranslator( QTranslator & ) const;

    static void writeCsvFile( const loans &, const QString & );
    static void writeCsvFile( const library &, const QString & );

    void removeLocal();
};

#endif // IOSTREAM_H
