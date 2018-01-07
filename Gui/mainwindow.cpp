#include "mainwindow.h"
#include "ui_mainwindow.h"

mainWindow::mainWindow( QWidget *parent )
            :QMainWindow( parent ), ui(new Ui::mainWindow) {
    ui->setupUi( this );

    QWidget::setWindowTitle( QCoreApplication::applicationName() );
    this->statusBar()->setSizeGripEnabled(false);
    this->setFixedSize( this->size() );

    setGeometry( QStyle::alignedRect( Qt::LeftToRight, Qt::AlignCenter, this->size(), qApp->desktop()->availableGeometry() ) );

    ui->logoLabel->setFont( QFont("A Charming Font", 40, 15) );
    ui->usernameLine->setValidator( new QRegExpValidator( QRegExp("[A-Za-z0-9_]*"), this ) );
    ui->nextButton->setEnabled( false );
    connect( ui->usernameLine, SIGNAL( textChanged( const QString & ) ), this, SLOT( checkLineEdits( const QString & ) ) );
    connect( ui->passwordLine, SIGNAL( textChanged( const QString & ) ), this, SLOT( checkLineEdits( const QString & ) ) );
}

mainWindow::~mainWindow() {
    delete ui;
}

void mainWindow::on_comboBox_currentIndexChanged(int index) {
    if( index )
        emit changeLanguage( index );
}


void mainWindow::languageResult( const bool & result ){
    if( result ){
        QSignalBlocker blocker(ui->comboBox);
        ui->retranslateUi( this );
        blocker.unblock();
    }
    else
        QMessageBox::critical( this, tr( "Error" ), tr( "Language files don't found. This program is available in english only." ) );
}

void mainWindow::checkLineEdits( const QString & ) {
    bool ok( true );

    ok &= !ui->usernameLine->text().isEmpty();
    ok &= !ui->passwordLine->text().isEmpty();

    ui->nextButton->setEnabled( ok );
}

void mainWindow::on_ExitButton_clicked() {
    exit( 0 );
}

void mainWindow::on_updateButton_clicked() {
    ui->usernameLine->setEnabled(false);
    ui->passwordLine->setEnabled(false);
    ui->nextButton->setEnabled(false);
    ui->ExitButton->setEnabled(false);
    ui->updateButton->setEnabled(false);
    ui->comboBox->setEnabled(false);
    ui->booksButton->setEnabled(false);
    ui->periodicalsButton->setEnabled(false);
    ui->allButton->setEnabled(false);
    emit updateRequest();
}

void mainWindow::updateComplete() {
    ui->usernameLine->setEnabled(true);
    ui->passwordLine->setEnabled(true);
    ui->ExitButton->setEnabled(true);
    ui->updateButton->setEnabled(true);
    ui->comboBox->setEnabled(true);
    ui->booksButton->setEnabled(true);
    ui->periodicalsButton->setEnabled(true);
    ui->allButton->setEnabled(true);

    QMessageBox::information( this, tr( "Update" ), tr( "All data updated!" ) );
}

void mainWindow::badLogin(){
    QMessageBox::critical( this, tr( "Bad login" ), tr( "Wrong username or password" ) );
}

void mainWindow::on_nextButton_clicked() {
    emit loginRequest( ui->usernameLine->text(), utility::encript( ui->passwordLine->text() ) );
    ui->passwordLine->setText("");
}

void mainWindow::on_booksButton_clicked() {
    emit publicationListRequest(true);
}

void mainWindow::on_periodicalsButton_clicked() {
    emit publicationListRequest(false);
}

void mainWindow::on_allButton_clicked() {
    emit publicationListRequest(true);
}
