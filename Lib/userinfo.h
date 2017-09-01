#ifndef USERINFO_H
#define USERINFO_H


#include <QDate>
#include <QString>
#include <QStringList>

#include "../Utility/utility.h"

class userinfo
{
private:
    QString registration_number;
    QString name;
    QString surname;
    QDate birthdate;
    QStringList clas;
    QString cellnumber;
    QString email;

    void getRegistrationNumber();

public:
    userinfo( const QString &, const QString &, const QDate &, const QString ="", const QString ="", const QString ="" );
    userinfo( const QString &, const QString &, const QString &, const QDate &, const QString ="", const QString ="", const QString ="" );

    void setName( const QString & );
    void setSurname( const QString & );
    void setDate( const QDate & );
    void setCellNumber( const QString & );
    void setEmail( const QString & );
    void setClass( const QString & );

    QString showRegistrationNumber() const;
    QString showName() const;
    QString showSurname() const;
    QDate showBirthdate() const;
    QString showCharBirthdate() const;
    QString showCellNumber() const;
    QString showEmail() const;
    QString showClass() const;
    QStringList showClassList() const;

    void addClass( const QString & );
    void removeClass( const QString & );
    void removeallClass();

};
#endif // USERINFO_H
