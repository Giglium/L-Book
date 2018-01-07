#ifndef SHOWPUBLICATION_H
#define SHOWPUBLICATION_H

#include <QDialog>
#include <QString>
#include <QFileDialog>
#include <QSharedPointer>
#include <QMessageBox>
#include <QFont>

#include "../Gui/modifypublication.h"
#include "../Gui/showloan.h"
#include "../Lib/account.h"
#include "../Lib/account_permission.h"
#include "../Lib/book.h"
#include "../Lib/loans.h"
#include "../Lib/loan.h"
#include "../Lib/periodic.h"
#include "../Lib/publication.h"
#include "../Lib/publication_permission.h"
#include "../Lib/userinfo.h"
#include "../Lib/username.h"

namespace Ui {
class showPublication;
}

class showPublication : public QDialog
{
    Q_OBJECT

public:
    explicit showPublication( const QSharedPointer < publication >, const QSharedPointer < loans >, const QSharedPointer < account > =QSharedPointer < account >(), QWidget *parent = 0);
    ~showPublication();

signals:
    void sendPath( const loans &, const QString & );
    void erasePublication( const QSharedPointer < publication > );

private slots:
    void on_exitButton_clicked();
    void on_allButton_clicked();
    void on_activeButton_clicked();
    void on_finishButton_clicked();
    void on_exportButton_clicked();
    void on_tableWidget_cellDoubleClicked( int, int );
    void on_deleteButton_clicked();
    void on_modifyButton_clicked();

private:
    Ui::showPublication *ui;
    QSharedPointer < account > logUser;
    QSharedPointer < publication > currentPublication;
    QSharedPointer < loans > allLoans;
    loans currentLoans;

    void setPubli();
    void setTable( const loans & );
    void addRow( const QSharedPointer < loan > );
};

#endif // SHOWPUBLICATION_H
