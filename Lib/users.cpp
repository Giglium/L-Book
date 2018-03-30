#include "users.h"

users::users()
      :userCollection() {}

void users::addUser( const users &use ) {
    for( int i = 0; i < use.showUserNumber() ; ++i ){
        addUser( use.showUser( i ) );
    }
}

void users::addUser( const QSharedPointer < account > use ) {
    if( !use.isNull() ){
        QSharedPointer < username > name = use->p_user();

        if( !name.isNull() && checkIfUsernameExist( name->showUser() ) || !showUser( use->p_info()->showRegistrationNumber() ).isNull() )
            userCollection << use;
    }
}

bool users::addUsername( const QSharedPointer < account > use, const QString &name ) {
    if( checkIfUsernameExist( name ) )
        use->p_user()->setUsername( name );
    return false;
}

void users::removeUser( const QString &ID ) {
    QList < QSharedPointer < account > >::Iterator list = userCollection.begin();

    while( list != userCollection.end() ){
        if( list->data()->p_info()->showRegistrationNumber() == ID )
           list = userCollection.erase( list );
        else
            ++list;
    }
}

void users::removeUser( const QSharedPointer < account > user ){
    removeUser( user->p_info()->showRegistrationNumber() );
}

int users::showUserNumber() const {
    return userCollection.size();
}

QSharedPointer < account > users::showUser( const int &position ) const {
    if( position<= userCollection.size() )
        return userCollection.at( position );
    return QSharedPointer < account > ();
}

QSharedPointer < account > users::showUser( const QString &rNumber ) const {
    QListIterator < QSharedPointer < account > > list( userCollection );

    while( list.hasNext() ){
        QSharedPointer < account >  supp = list.next();

        if( supp->p_info()->showRegistrationNumber() == rNumber )
            return supp;
    }

    return QSharedPointer < account > ();
}

QSharedPointer < account > users::showUser( const QSharedPointer < account > user ) const {
    return showUser( user->p_info()->showRegistrationNumber() );
}

QSharedPointer < account > users::showUserfromUsername( const QString &name ) const {
    QListIterator < QSharedPointer < account > > list( userCollection );

    while( list.hasNext() ){
        QSharedPointer < account >  user = list.next();
        QSharedPointer < username > nam = user->p_user();
        if( !nam.isNull() && nam->showUser().toUpper() == name.toUpper() )
            return user;
    }

    return QSharedPointer < account > ();
}

bool users::checkAdmin() const{
    QListIterator < QSharedPointer < account > > list( userCollection );

    while( list.hasNext() ){
        QSharedPointer < account >  user = list.next();

        if( user->p_permission()->showType() == 3 )
            return true;
    }

    return false;
}

bool users::checkIfUsernameExist( const QString &user ) const {
    bool ok = showUserfromUsername( user ).isNull();
    return !ok;
}

users users::unorderClassroomUsers( const QString &clas ) const {
    users userList;

    QListIterator < QSharedPointer < account > > list( userCollection );

    while( list.hasNext() ){
        QSharedPointer < account >  user = list.next();

        if( utility::checkString( user->p_info()->showClass(), clas, false ) )
            userList<<user;
    }

    return userList;
}

users users::showUsers() const{
    users userList;

    QListIterator < QSharedPointer < account > > list( userCollection );

    while( list.hasNext() ){
         userList<<list.next();
    }

    return userList;
}

users users::orderClassroomUsers( const QString &clas ) const {
    QStringList clasList = utility::toQStringList( clas );
    QStringListIterator list ( clasList );
    users supp;

    while ( list.hasNext() ) {
        QString string = list.next();
        supp.addUser( unorderClassroomUsers( string ) );
    }

    return supp;
}

users users::showUserFromNameSurname( const QString &nameSurname ) const{
    users userList;

    QListIterator < QSharedPointer < account > > list( userCollection );

    while( list.hasNext() ){
        QSharedPointer < account > user = list.next();
        QStringList name = utility::toQStringList( user->p_info()->showName() + " " + user->p_info()->showSurname() + "," );
        if( name.filter( nameSurname , Qt::CaseInsensitive ).size() ){
         userList<<user;
        }
    }

    return userList;
}

QSharedPointer < account > users::login( const QString &username, const QString &password ) const {
    QSharedPointer < account > user = showUserfromUsername( username );
    if( !user.isNull() && user->p_user()->showPass() == password )
        return user;
    return QSharedPointer < account > ();
}

void users::operator<<( const users &user ){
    addUser( user );
}

void users::operator<< ( const QSharedPointer < account > user ){
    addUser( user );
}
