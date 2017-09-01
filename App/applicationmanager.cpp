#include "applicationmanager.h"

bool applicationManager::loadData(){

    if( io.firstStart() ){
        setup setUp;
        QObject::connect( &setUp, SIGNAL( sendPath( const QString & ) ), this, SLOT( setDataPath( const QString & ) ) );
        if( !setUp.exec() )
            return false;
    }

    collector = io.loadData();

    if( !collector.p_accounts()->checkAdmin() ) {
        modifyUser needAdmin( QSharedPointer < account >(), true );

        QObject::connect( &needAdmin, SIGNAL( sendUser( QSharedPointer < account > ) ), this, SLOT( addUser( QSharedPointer < account > ) ) );
        QObject::connect( this, SIGNAL( userResult( bool ) ), &needAdmin, SLOT( userResult( bool ) ) );

        if( !needAdmin.exec() )
            return false;
       io.saveData( collector );
    }

    return true;
}

void applicationManager::setDataPath( const QString &path ) {
    if( path == "" )
        io.setSharedDir();
    else
        io.setSharedDir( path );
}

void applicationManager::addUser( QSharedPointer < account > user ) {
    if( !user->p_user().isNull() ){
        if( collector.p_accounts()->showUserfromUsername( user->p_user()->showUser() ).isNull() ){
            collector.p_accounts()->addUser( user );
            emit userResult(true);
        }
        else
            emit userResult(false);
    }
    else{
       collector.p_accounts()->addUser( user );
       emit userResult(true);
    }
}

void applicationManager::changeLanguage( const int &index ){
    QString language;

    if( index == 1 )
        language = "en";
    if( index == 2 )
        language = "it";

    loadLanguage( language );
}

applicationManager::applicationManager()
{
    qsrand( QTime::currentTime().QTime::msec() );

    QString defaultLanguage = QLocale::system().name();
    defaultLanguage.truncate( defaultLanguage.lastIndexOf('_') );
    loadLanguage( defaultLanguage );

    if( !loadData() ){
        exit( 0 );
    }
}

applicationManager::~applicationManager(){
    delete gui;
}

void applicationManager::start(){
    gui = new mainWindow();

    QObject::connect( gui, SIGNAL( changeLanguage( int ) ), this, SLOT( changeLanguage( int ) ) );
    QObject::connect( this, SIGNAL( languageResult( bool ) ), gui, SLOT( languageResult( bool ) ) );
    QObject::connect( gui, SIGNAL( updateRequest() ), this, SLOT( updateRequest() ) );
    QObject::connect( this, SIGNAL( updateComplete() ), gui, SLOT( updateComplete() ) );
    QObject::connect( gui, SIGNAL( loginRequest( QString, QString ) ), this, SLOT( loginRequest( QString, QString ) ) );
    QObject::connect( this, SIGNAL( badLogin() ), gui, SLOT( badLogin() ) );
    QObject::connect( gui, SIGNAL( publicationListRequest( bool ) ), this, SLOT( openPublicationList( bool ) ) );
    gui->show();
}

void applicationManager::loadLanguage( const QString &newLanguage ) {

    QString currentLanguage = QLocale().name();
    currentLanguage.truncate( currentLanguage.lastIndexOf('_') );

    if( newLanguage != currentLanguage ){

        if( newLanguage == "it" )
            QLocale::setDefault( QLocale( QLocale::Italian ) );
        if( newLanguage == "en" )
            QLocale::setDefault( QLocale( QLocale::English ) );

        emit languageResult( io.switchTranslator( linguist ) );
    }
}

void applicationManager::updateRequest() {
    loadData();
    emit updateComplete();
}

void applicationManager::loginRequest( const QString &name, const QString &password ){
    QSharedPointer< account > logUser = collector.p_accounts()->login( name, password );
    if( !logUser.isNull() ){
        if( logUser->p_permission()->showType() == 3 ){
            gui->hide();
            adminMainWindow* adminPanel = new adminMainWindow( logUser );

            QObject::connect( adminPanel, SIGNAL( closeAdmin(adminMainWindow*) ), this, SLOT( closeAdmin(adminMainWindow*) ) );
            QObject::connect( adminPanel, SIGNAL( openPublication(QSharedPointer<account>) ), this, SLOT( openPublication(QSharedPointer<account>) ) );
            QObject::connect( adminPanel, SIGNAL( openLoan( QSharedPointer < account > ) ), this, SLOT( openLoan( QSharedPointer < account > ) ) );
            QObject::connect( adminPanel, SIGNAL( saveData() ), this, SLOT( saveData() ) );
            QObject::connect( this, SIGNAL( saveComplete( bool ) ), adminPanel, SLOT( saveResult( bool ) ) );
            QObject::connect( adminPanel, SIGNAL( unistall() ), this, SLOT( removeLocalData() ) );
            QObject::connect( adminPanel, SIGNAL( openUser( QSharedPointer < account > ) ), this, SLOT( openUser( QSharedPointer < account > ) ) );

            adminPanel->show();
        }
        else{
            gui->hide();
            showUser userData ( logUser, collector.p_loans(), logUser );
            QObject::connect( &userData, SIGNAL( sendPath( loans, QString ) ), this, SLOT( writeCsv( loans, QString ) ) );
            QObject::connect(  &userData, SIGNAL( eraseUser( QSharedPointer < account > ) ), this, SLOT( eraseUser( QSharedPointer < account > ) ) );
            userData.exec();
            gui->show();
        }
    }
    else
        emit badLogin();
}

void applicationManager::writeCsv( const loans &lends, const QString &path ){
    IOStream::writeCsvFile( lends, path );
}

void applicationManager::writeCsv( const library &books, const QString &path ){
    IOStream::writeCsvFile( books, path );
}

void applicationManager::eraseUser( const QSharedPointer< account > user ){   
    collector.p_loans()->removeAllUserLoan( user );
    collector.p_accounts()->removeUser( user );
}

void applicationManager::openPublicationList( bool mode ){
   gui->hide();
   publicationList books( collector.p_publications(), collector.p_loans() , mode );

   QObject::connect( &books, SIGNAL( sendPath( library, QString ) ), this, SLOT( writeCsv( library, QString ) ) );
   QObject::connect( &books, SIGNAL( sendPath( loans, QString ) ), this, SLOT( writeCsv( loans, QString ) ) );

   books.exec();
   gui->show();
}

void applicationManager::closeAdmin( adminMainWindow * adminPanel ){
    adminPanel->hide();
    gui->show();
    delete adminPanel;
}

void applicationManager::openPublication( const QSharedPointer < account > logUser ){
    publicationList BookList( collector.p_publications(), collector.p_loans(), true, logUser );
    BookList.exec();
}

void applicationManager::openLoan( const QSharedPointer<account> logUser ){
    loanList lendList( collector, logUser );

    QObject::connect( &lendList, SIGNAL( sendPath( loans, QString ) ), this, SLOT( writeCsv( loans, QString ) ) );

    lendList.exec();
}

void applicationManager::saveData(){
    io.saveData( collector );
    emit saveComplete(true);
}

void applicationManager::removeLocalData(){
    io.removeLocal();
    exit(0);
}

void applicationManager::openUser( const QSharedPointer<account> logUser ){
    userList listUsers( collector.p_accounts(), collector.p_loans(), logUser );

    QObject::connect( &listUsers, SIGNAL( sendPath( loans, QString ) ), this, SLOT( writeCsv( loans, QString ) ) );

    listUsers.exec();
}
