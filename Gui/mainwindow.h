#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSignalBlocker>
#include <QStyle>
#include <QDesktopWidget>
#include <QFont>

#include "../Utility/utility.h"

namespace Ui {
class mainWindow;
}

class mainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainWindow( QWidget *parent = 0 );
    ~mainWindow();

signals:
    void changeLanguage( const int & );
    void updateRequest();
    void loginRequest( const QString &, const QString & );
    void publicationListRequest( const bool );

private slots:
    void on_comboBox_currentIndexChanged( int );
    void languageResult( const bool & );
    void checkLineEdits( const QString & );
    void updateComplete();
    void badLogin();
    void on_ExitButton_clicked();
    void on_updateButton_clicked();
    void on_nextButton_clicked();
    void on_booksButton_clicked();
    void on_periodicalsButton_clicked();
    void on_allButton_clicked();

private:
    Ui::mainWindow *ui;
};

#endif // MAINWINDOW_H
