#ifndef ADMINMAINWINDOW_H
#define ADMINMAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QStyle>
#include <QDesktopWidget>
#include <QFont>

#include "../Lib/account.h"

namespace Ui {
class adminMainWindow;
}

class adminMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit adminMainWindow( const QSharedPointer < account >, QWidget *parent = 0);
    ~adminMainWindow();

signals:
    void closeAdmin( adminMainWindow* );
    void openPublication( const QSharedPointer < account > );
    void openLoan( const QSharedPointer < account > );
    void openUser( const QSharedPointer < account > );
    void saveData();
    void unistall();

private slots:
    void on_exitButton_clicked();
    void on_publicationButton_clicked();
    void on_loanButton_clicked();
    void on_saveButton_clicked();
    void saveResult( const bool & );
    void on_clearButton_clicked();
    void on_userButton_clicked();

private:
    Ui::adminMainWindow *ui;
    QSharedPointer < account > logUser;
};

#endif // ADMINMAINWINDOW_H
