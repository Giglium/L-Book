#ifndef PUBLICATIONLIST_H
#define PUBLICATIONLIST_H

#include <QDialog>
#include <QString>
#include <QStringList>
#include <QSharedPointer>
#include <QFileDialog>
#include <QFont>

#include "../Gui/showpublication.h"
#include "../Lib/account.h"
#include "../Lib/account_permission.h"
#include "../Lib/book.h"
#include "../Lib/library.h"
#include "../Lib/loans.h"
#include "../Lib/loan.h"
#include "../Lib/periodic.h"
#include "../Lib/publication.h"
#include "../Lib/publication_permission.h"
#include "../Utility/utility.h"


namespace Ui {
class publicationList;
}

class publicationList : public QDialog
{
    Q_OBJECT

public:
    explicit publicationList( const QSharedPointer < library >, const QSharedPointer < loans >, const bool =false, const QSharedPointer < account > =QSharedPointer < account >(), QWidget *parent = 0);
    ~publicationList();

signals:
    void sendPath( const library &, const QString & );
    void sendPath( const loans &, const QString & );
    void addPublicationResult( const bool & );

private slots:
    void on_bookButton_clicked();
    void on_periodicButton_clicked();
    void on_exportButton_clicked();
    void on_resetButton_clicked();
    void on_exitButton_clicked();
    void on_searchButton_clicked();
    void on_bookTable_cellDoubleClicked( int, int );
    void on_periodicTable_cellDoubleClicked( int, int );
    void recivePath( const loans &, const QString & );
    void removePublication( const QSharedPointer < publication > );
    void on_addButton_clicked();
    void addPublication( const QSharedPointer < publication > );

private:
    Ui::publicationList *ui;
    QSharedPointer < account > logUser;
    QSharedPointer < loans > allLoans;
    QSharedPointer < library > allPublications ;
    library currentPublications;

    void setTables();
    void addRow( const QSharedPointer < publication > );
};

#endif // SHOWPUBLICATION_H
