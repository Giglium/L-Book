#ifndef LIBRARY_H
#define LIBRARY_H

#include <QList>
#include <QSharedPointer>

#include "publication.h"
#include "book.h"
#include "periodic.h"

class library
{
private:
    QList < QSharedPointer < publication > > publicationCollection;

public:
    library();

    void addPublication( const library & );
    void addPublication( const QSharedPointer < publication > );

    void removePublication( const QString & );
    void removePublication( const QSharedPointer < publication > );

    int showPublicationNumber() const;
    library showPublications() const;
    QSharedPointer < publication > showPublication( const int & ) const;
    QSharedPointer < publication > showPublication( const QString & ) const;  /* Work only with Identification */
    QSharedPointer < publication > showPublication( const QSharedPointer < publication > ) const;
    library showPublicationsFromISSN( const QString & ) const;
    library showPublicationsFromISBN13( const QString & ) const;
    library showPublicationsFromTitle( const QString & );
    library allBook() const;
    library allPeriodic() const;

    library thisGenrePublications( const QString & ) const;
    library thisAuthorPublications( const QString & ) const;

    void operator<<( const QSharedPointer< publication > );
    void operator<<( const library & );
};

#endif // LIBRARY_H
