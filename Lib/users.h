#ifndef USERS_H
#define USERS_H

#include <QList>
#include <QString>
#include <QSharedPointer>

#include "account.h"
#include "userinfo.h"
#include "username.h"
#include "account_permission.h"

class users
{
private:
    QList < QSharedPointer < account > > userCollection;

public:
    users();

    void addUser(const users & );
    void addUser( const QSharedPointer < account > );
    bool addUsername( const QSharedPointer < account >, const QString & );

    void removeUser( const QString & );
    void removeUser( const QSharedPointer < account > );

    int showUserNumber() const;
    QSharedPointer < account > showUser( const int & ) const;
    QSharedPointer < account > showUser( const QString & ) const; /*work only with registration  number */
    QSharedPointer < account > showUser( const QSharedPointer < account > ) const;
    QSharedPointer < account > showUserfromUsername( const QString & ) const;

    bool checkAdmin() const;
    bool checkIfUsernameExist( const QString & ) const;

    users showUsers() const;
    users unorderClassroomUsers( const QString & ) const;
    users orderClassroomUsers( const QString & ) const;
    users showUserFromNameSurname( const QString & ) const;

    QSharedPointer < account > login( const QString &, const QString & ) const;

    void operator<<( const users & );
    void operator<<( const QSharedPointer < account > );
};

#endif // USERS_H
