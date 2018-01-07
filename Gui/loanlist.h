#ifndef LOANLIST_H
#define LOANLIST_H

#include <QDialog>
#include <QString>
#include <QStringList>
#include <QFileDialog>
#include <QFont>

#include "../Gui/makeloan.h"
#include "../Gui/showloan.h"
#include "../Lib/account.h"
#include "../Lib/dataCollector.h"
#include "../Lib/loan.h"
#include "../Lib/loans.h"
#include "../Lib/publication.h"
#include "../Lib/username.h"

namespace Ui {
class loanList;
}

class loanList : public QDialog
{
    Q_OBJECT

public:
    explicit loanList( const dataCollector &, const QSharedPointer < account > =QSharedPointer < account >() , QWidget *parent = 0);
    ~loanList();

signals:
    void sendPath( const loans &, const QString & );

private slots:
    void on_exitButton_clicked();
    void on_tableWidget_cellDoubleClicked(int, int);
    void on_allButton_clicked();
    void on_finishButton_clicked();
    void on_activeButton_clicked();
    void removeLoan( const QSharedPointer < loan > );
    void on_exportButton_clicked();
    void on_searchButton_clicked();
    void on_makebutton_clicked();

private:
    Ui::loanList *ui;
    dataCollector collector;
    loans currentLoans;
    QSharedPointer < account > logUser;

    void setTable( const loans & );
    void addRow( const QSharedPointer < loan > );
};

#endif // LOANLIST_H
