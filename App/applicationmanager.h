#ifndef APPLICATIONMANAGER_H
#define APPLICATIONMANAGER_H

#include <QObject>
#include <QTime>
#include <QString>
#include <QLocale>
#include <QProcess>
#include <QTranslator>
#include <QApplication>
#include <QMessageBox>

#include "../Gui/adminmainwindow.h"
#include "../Gui/loanlist.h"
#include "../Gui/mainwindow.h"
#include "../Gui/modifyuser.h"
#include "../Gui/setup.h"
#include "../Gui/publicationlist.h"
#include "../Gui/showuser.h"
#include "../Gui/userlist.h"
#include "../Lib/dataCollector.h"
#include "../Lib/account.h"
#include "../Lib/publication.h"
#include "../Streams/IOStream.h"
#include "../Utility/utility.h"

class applicationManager : public QObject {
    Q_OBJECT
private:
    IOStream io;
    dataCollector collector;
    mainWindow *gui;
    QTranslator linguist;

    bool loadData();

private slots:
    void setDataPath( const QString & );
    void addUser( QSharedPointer < account > );
    void changeLanguage( const int & );
    void updateRequest();
    void loginRequest( const QString &, const QString & );
    void writeCsv( const loans &, const QString & );
    void writeCsv( const library&, const QString & );
    void eraseUser( const QSharedPointer < account > );
    void openPublicationList( bool );
    void closeAdmin( adminMainWindow* );
    void openPublication( const QSharedPointer < account > );
    void openLoan( const QSharedPointer < account > );
    void openUser( const QSharedPointer < account > );
    void saveData();
    void removeLocalData();

public:
    applicationManager();
    ~applicationManager();
    void start();
    void loadLanguage( const QString & );

signals:
    void userResult( const bool & );
    void languageResult( const bool & );
    void updateComplete();
    void badLogin();
    void saveComplete( const bool &);
};

#endif // APPLICATIONMANAGER_H
