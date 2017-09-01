#include "library.h"

library::library()
        :publicationCollection() {}


void library::addPublication( const library &publications ) {
    for( int i = 0; i < publications.showPublicationNumber() ; ++i ){
        addPublication( publications.showPublication( i ) );
    }
}

void library::addPublication( const QSharedPointer < publication > publi ) {

    if( !publi.isNull() && publi->showIdentification() != "" && showPublication( publi->showIdentification() ).isNull() )
     publicationCollection << publi;

}

void library::removePublication( const QString &ID ) {
    QList < QSharedPointer < publication > >::Iterator list = publicationCollection.begin();

    while( list != publicationCollection.end() ){
        if( list->data()->showIdentification() == ID )
           list = publicationCollection.erase( list );
        else
            ++list;
    }
}

void library::removePublication( const QSharedPointer < publication > publi ){
    removePublication( publi->showIdentification() );
}

int library::showPublicationNumber() const {
    return publicationCollection.size();
}

library library::showPublications() const{
    library books;

    QListIterator < QSharedPointer < publication > > list( publicationCollection );

    while( list.hasNext() ){
        books<<list.next();
    }

    return books;
}

QSharedPointer < publication > library::showPublication( const int &position ) const {
     if( position<= publicationCollection.size() )
         return publicationCollection.at( position );
     return QSharedPointer < publication > ();
 }

QSharedPointer < publication > library::showPublication( const QString &ID ) const {
     QListIterator < QSharedPointer < publication > > list( publicationCollection );

     while( list.hasNext() ){
         QSharedPointer < publication > supp = list.next();

         if( supp->showIdentification() == ID )
            return supp;
     }

     return QSharedPointer < publication > ();
 }

QSharedPointer < publication > library::showPublication( const QSharedPointer < publication > publi ) const{
    return showPublication( publi->showIdentification() );
}

library library::showPublicationsFromISSN( const QString &issn ) const{
    library books;

    QListIterator < QSharedPointer < publication > > list( publicationCollection );

    while( list.hasNext() ){
        QSharedPointer < periodic > magazine = qSharedPointerDynamicCast < periodic > ( list.next() );
        if( !magazine.isNull() && magazine->showISSN() == issn.toUpper() )
            books<<magazine;
    }

    return books;
}

library library::showPublicationsFromISBN13( const QString &isbn ) const{
    library books;

    QListIterator < QSharedPointer < publication > > list( publicationCollection );

    while( list.hasNext() ){
        QSharedPointer < publication > publi = list.next();
        if( publi->showISBN_13() == isbn )
            books<<publi;
    }

    return books;
}

library library::showPublicationsFromTitle( const QString &title ){
    library books;

    QListIterator < QSharedPointer < publication > > list( publicationCollection );

    while( list.hasNext() ){
        QSharedPointer < publication > publi = list.next();
        QStringList tit = utility::toQStringList( publi->showTitle().append(",") );
        if( tit.filter( title , Qt::CaseInsensitive ).size() ){
         books<<publi;
        }
    }

    return books;
}

library library::allBook() const {
    library books;

    QListIterator < QSharedPointer < publication > > list( publicationCollection );

    while( list.hasNext() ){
        QSharedPointer < book > boo = qSharedPointerDynamicCast < book > ( list.next() );
        if( !boo.isNull() )
            books<<boo;
    }

    return books;
}

library library::allPeriodic() const {
    library books;

    QListIterator < QSharedPointer < publication > > list( publicationCollection );

    while( list.hasNext() ){
        QSharedPointer < periodic > boo = qSharedPointerDynamicCast < periodic > ( list.next() );
        if( !boo.isNull() )
            books<<boo;
    }

    return books;
}

library library::thisGenrePublications( const QString &genre ) const {
     library books;

     QListIterator < QSharedPointer < publication > > list( publicationCollection );

     while( list.hasNext() ){
         QSharedPointer < publication > publi = list.next();
         if( utility::checkString( publi->showGenreList(), genre, false ) )
             books<<publi;
     }

     return books;
}

library library::thisAuthorPublications( const QString &author ) const{
    library books;

    QListIterator < QSharedPointer < publication > > list( publicationCollection );

    while( list.hasNext() ){
        QSharedPointer < book > publi = qSharedPointerDynamicCast < book > ( list.next() );
           if( !publi.isNull()){
               QStringList auth = publi->showAuthorList();
               if( auth.filter( author , Qt::CaseInsensitive ).size() ){
                    books<<publi;
               }
           }
    }

    return books;
}

void library::operator<<( const library &books ) {
      addPublication( books );
}

void library::operator<<( const QSharedPointer < publication > publi ) {
     addPublication( publi );
}
