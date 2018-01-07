#ifndef MODIFYPUBLICATION_H
#define MODIFYPUBLICATION_H

#include <QDialog>
#include <QDate>
#include <QString>
#include <QFileDialog>
#include <QSharedPointer>
#include <QMessageBox>
#include <QRegExp>
#include <QRegExpValidator>
#include <QFont>

#include "../Lib/account_permission.h"
#include "../Lib/book.h"
#include "../Lib/periodic.h"
#include "../Lib/publication.h"
#include "../Lib/publication_permission.h"
#include "../Utility/utility.h"

namespace Ui {
class modifyPublication;
}

class modifyPublication : public QDialog
{
    Q_OBJECT

public:
    explicit modifyPublication( const QSharedPointer < publication > =QSharedPointer < publication >() , QWidget *parent = 0);
    ~modifyPublication();

signals:
    void savePublication( const QSharedPointer < publication > );

private slots:
    void on_exitButton_clicked();
    void on_publiBox_currentIndexChanged( int );
    void checkLineEdits( const QString & );
    void checkLineEdits( const QDate & );
    void on_saveButton_clicked();
    void addResult( const bool & );

private:
    Ui::modifyPublication *ui;
    QSharedPointer < publication > currentPublication;

    void isbnError( const bool & = true );
};

#endif // MODIFYPUBLICATION_H
