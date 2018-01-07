#ifndef USERNAME_H
#define USERNAME_H

#include <QString>

class username
{
private:
    QString user;
    QString password;

public:
    username( const QString &, const QString & );

    QString showUser() const;
    QString showPass() const;

    void setUsername( const QString & );
    void setPassword( const QString & );
};
#endif // USERNAME_H
