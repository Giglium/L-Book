#ifndef PERIODIC_H
#define PERIODIC_H

#include <QString>
#include <QDate>
#include <QMap>

#include "publication.h"

class periodic :public publication
{
private:
    QString ID_number;
    unsigned int birthyear;
    unsigned int number;

    static QString fromISSNtoISBN13( const QString & );
    static QString fromISBN13toISSN( QString );

    static QString toRoman( const unsigned int & );  /* max int number to roman: 3999 */
    static unsigned int fromRoman( const QString & ); /* max roman number to int: MMMCMXCIX */

public:
    periodic( const QString &, const unsigned int &, const unsigned int &, const QString &, const QString &, const QString &, const QDate &, const QString ="" , const QString ="" );
    periodic( const QString &, const QString &, const unsigned int &, const QString &, const QString &, const QString &, const QDate &, const QString ="", const QString ="" );
    virtual ~periodic() {}

    void setBirthYear( const unsigned int & );
    void setActivityYears( const unsigned int & );
    void setActivityYears( const QString & );
    void setNumber( const unsigned int & );
    bool setISBN_13( const QString & );
    void setIDnumber( const QString & );

    virtual QString showIdentification() const;
    int showBirthYear() const;
    int showActivityYears() const;
    QString showRomanActivityYears() const;
    int showNumber() const;
    int showMonth() const;
    QString showCharMonth() const;
    QString showISSN() const;
    QString showID_number() const;
};

#endif // PERIODIC_H
