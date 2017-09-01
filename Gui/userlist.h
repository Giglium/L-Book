#ifndef USERLIST_H
#define USERLIST_H

#include <QDialog>
#include <QStringList>
#include <QSharedPointer>
#include <QFont>

#include "../Gui/modifyuser.h"
#include "../Gui/showuser.h"
#include "../Lib/account.h"
#include "../Lib/loans.h"
#include "../Lib/userinfo.h"
#include "../Lib/users.h"

namespace Ui {
class userList;
}

class userList : public QDialog
{
    Q_OBJECT

public:
    explicit userList( const QSharedPointer < users >, const QSharedPointer < loans > =QSharedPointer < loans >(), const QSharedPointer < account > =QSharedPointer < account >() , QWidget *parent = 0);
    ~userList();

signals:
    void sendPath( const loans &, const QString& );
    void userResult( const bool & );

private slots:
    void on_exitButton_clicked();
    void on_tableWidget_cellDoubleClicked( int, int );
    void on_resetButton_clicked();
    void recivePath( const loans &, const QString& );
    void eraseUser( const QSharedPointer < account > );
    void addUser( const QSharedPointer < account > );
    void on_addButton_clicked();
    void addUSername( const QSharedPointer < account >, const QString &, const QString & );

    void on_searchButton_clicked();

private:
    Ui::userList *ui;
    QSharedPointer < loans > allLoans;
    QSharedPointer < users > allUser;
    QSharedPointer < account > logUser;
    users currentUsers;

    void setTable( const users );
    void addRow( const QSharedPointer < account > );
};

#endif // USERLIST_H
