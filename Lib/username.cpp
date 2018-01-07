#include "username.h"

username::username( const QString &name, const QString &pass )
         : user( name ), password( pass ) {}

QString username::showUser() const {
    return user;
}

QString username::showPass() const {
    return password;
}

void username::setUsername( const QString &name ) {
    user = name;
}

void username::setPassword( const QString &pass ) {
    password = pass;
}
