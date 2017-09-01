#ifndef PUBLICATION_H
#define PUBLICATION_H

#include <QDate>
#include <QString>
#include <QStringList>
#include <QSharedPointer>

#include "publication_permission.h"
#include "Utility/utility.h"

class publication
{
private:
    QString title;
    QString publishing;
    QStringList genre;
    QString subtitle;
    QSharedPointer < publication_permission > permission;

protected:
    QDate release_date;
    QString ISBN_13;
    publication( const QString &, const QString &, const QString ="" , const QString ="", const QDate =QDate() );

public:
    virtual ~publication() {}

    void setTitle( const QString & );
    void setSubtitle( const QString & );
    void setPublishing( const QString & );
    virtual bool setISBN_13( const QString & ) = 0;
    void setGenre( const QString & );
    void setReleaseDate ( const QDate & );
    void setPermission( const unsigned int &, const unsigned int &, const unsigned int =0 );
    void setPermission( const QSharedPointer < publication_permission > );

    virtual QString showIdentification() const =0;
    QString showTitle() const;
    QString showSubtitle() const;
    QString showPublishing() const;
    QString showISBN_13() const;
    QString showGenre() const;
    QStringList showGenreList() const;
    QDate showReleaseDate() const;
    QString showCharReleaseDate () const;

    QSharedPointer < publication_permission > p_permission() const;

    void addGenre( const QString & );
    void removeGenre( const QString & );
    void removeallGenre();

};

#endif // PUBLICATION_H
