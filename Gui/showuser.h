#ifndef SHOWUSER_H
#define SHOWUSER_H

#include <QDialog>
#include <QSharedPointer>
#include <QString>
#include <QStringList>
#include <QAbstractItemView>
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>
#include <QFont>

#include "../Gui/modifyuser.h"
#include "../Gui/showloan.h"
#include "../Lib/account.h"
#include "../Lib/account_permission.h"
#include "../Lib/book.h"
#include "../Lib/loan.h"
#include "../Lib/loans.h"
#include "../Lib/publication.h"
#include "../Lib/periodic.h"
#include "../Lib/userinfo.h"
#include "../Lib/username.h"

namespace Ui {
class showUser;
}

class showUser : public QDialog
{
    Q_OBJECT

public:
    explicit showUser( const QSharedPointer < account >, const QSharedPointer < loans >, const QSharedPointer < account > =QSharedPointer < account >(),QWidget *parent = 0);
    ~showUser();

signals:
    void sendPath( const loans &, const QString &  );
    void eraseUser( const QSharedPointer < account > );
    void sendUsername( const QSharedPointer < account >, const QString &, const QString & );
    void sendResult( const bool & );

private slots:
    void removeLoan( const QSharedPointer < loan > );
    void on_ExitButton_clicked();
    void on_AllButton_clicked();
    void on_activeButton_clicked();
    void on_finishButton_clicked();
    void on_exportButton_clicked();
    void on_comboBox_currentIndexChanged( int );
    void on_loanButton_clicked();
    void on_searchButton_clicked();
    void on_modifyButton_clicked();
    void on_banButton_clicked();
    void on_tableWidget_cellDoubleClicked( int, int );
    void reciveUsername( const QSharedPointer < account >, const QString &, const QString & );
    void reciveResult( const bool & );

private:
    Ui::showUser *ui;
    QSharedPointer < account > currentUser;
    QSharedPointer < account > logUser;
    QSharedPointer < loans > AllLoans;
    loans CurrentLoans;

    void setTable( const loans & );
    void setClassTable( const loans & );
    void addRow( const QSharedPointer < loan > );
    void setUserData( const QSharedPointer < account > );
    void setLogUser( const QSharedPointer < account > );
};

#endif // SHOWUSER_H
