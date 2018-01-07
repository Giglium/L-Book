#include "modifyuser.h"
#include "ui_modifyuser.h"

modifyUser::modifyUser( const QSharedPointer<account> thisUser, const bool type , QWidget *parent)
           :QDialog(parent), ui(new Ui::modifyUser), user( thisUser ) ,mode(type)
{
    ui->setupUi(this);

    QWidget::setWindowTitle( QCoreApplication::applicationName() );
    this->setFixedSize( this->size() );

    ui->logoLabel->setFont( QFont("A Charming Font", 40, 15) );
    ui->loanLine->setValidator( new QRegExpValidator( QRegExp( "\\d*" ), this) );
    ui->cellLine->setValidator( new QRegExpValidator( QRegExp( "\\d*" ), this) );
    ui->usernameLine->setValidator( new QRegExpValidator( QRegExp("[A-Za-z0-9_]*"), this ) );

    if( user.isNull() ){
        ui->dateEdit->setDate( QDate::currentDate() );
        ui->nextButton->setEnabled( false );
        QObject::connect( ui->nameLine, SIGNAL( textChanged( const QString & ) ), this, SLOT( checkLineEdits( const QString & ) ) );
        QObject::connect( ui->surnameLine, SIGNAL( textChanged( const QString & ) ), this, SLOT( checkLineEdits( const QString & ) ) );
        QObject::connect( ui->usernameLine, SIGNAL( textChanged( const QString & ) ), this, SLOT( checkLineEdits( const QString & ) ) );
        QObject::connect( ui->passwordLine, SIGNAL( textChanged( const QString & ) ), this, SLOT( checkLineEdits( const QString & ) ) );

        if( mode ){
            ui->comboBox->addItem( tr("Admin") );
            ui->comboBox->setCurrentIndex(2);
            ui->comboBox->setEnabled(false);
            ui->classLine->setEnabled( false );
            ui->infoLabel->setText( tr( "I have not found any admin. So please register your account:" ) );
            ui->noteLabel->setText( tr( "Account and Information field can't be left blank. Username cannot be changed after registration." ) );
        }
    }
    else{
        ui->infoLabel->setText( tr( "Here you can modify sono user data:" ) );
        ui->noteLabel->setText( tr( "If you insert a password it will subscribe the old one." ) );
        ui->nextButton->setText( tr( "Modify User" ) );

        if( !user->p_user().isNull() ){
            ui->usernameLine->setText( user->p_user()->showUser() );
            ui->usernameLine->setEnabled( false );
        }

        ui->nameLine->setText( user->p_info()->showName() );
        ui->surnameLine->setText( user->p_info()->showSurname() );
        ui->dateEdit->setDate( user->p_info()->showBirthdate() );
        ui->classLine->setText( user->p_info()->showClass() );
        ui->cellLine->setText( user->p_info()->showCellNumber() );
        ui->mailLine->setText( user->p_info()->showEmail() );

        if( !user->p_permission().isNull() ){
            ui->loanLine->setText( QString::number( user->p_permission()->showMaxLoan() ) );

            int permission = user->p_permission()->showType();

            if( permission == 3 ){
                ui->comboBox->addItem(tr( "Admin" ) );
                ui->comboBox->setCurrentIndex(2);
                ui->comboBox->setEnabled(false);
                ui->classLine->setEnabled(false);
            }
            if( permission == 0 ){
                ui->comboBox->addItem( tr( "Banned" ) );
                ui->comboBox->setCurrentIndex(2);
                ui->comboBox->setEnabled(false);
                ui->usernameLine->setEnabled(false);
                ui->passwordLine->setEnabled(false);
                ui->nameLine->setEnabled(false);
                ui->surnameLine->setEnabled(false);
                ui->dateEdit->setEnabled(false);
                ui->classLine->setEnabled(false);
                ui->cellLine->setEnabled(false);
                ui->mailLine->setEnabled(false);
                ui->loanLine->setEnabled(false);
                ui->noteLabel->setText( tr( "This account is banned!" ) );
                ui->nextButton->setEnabled(false);
            }
            if( permission == 1 || permission == 2 )
                ui->comboBox->setCurrentIndex( permission - 1 );
        }

    }
}

void modifyUser::userResult( const bool &result ){
    if( result ){
        QDialog::accept();
    }
    else{
        ui->usernameLine->setStyleSheet( "background: rgb(255, 0, 0);" );
        QMessageBox::critical( this, tr( "Error" ), tr( "This username alredy exist." ) );
    }
}

void modifyUser::checkLineEdits( const QString & ) {
    bool ok( true );
    ok &= !ui->nameLine->text().isEmpty();
    ok &= !ui->surnameLine->text().isEmpty();

    if( !ui->usernameLine->text().isEmpty() )
        ok &= !ui->passwordLine->text().isEmpty();

    if( mode ){
        ok &= !ui->usernameLine->text().isEmpty();
        ok &= !ui->passwordLine->text().isEmpty();
    }

    ui->nextButton->setEnabled( ok );
}

modifyUser::~modifyUser(){
    delete ui;
}

void modifyUser::on_ExitButton_clicked(){
    QDialog::reject();
}

void modifyUser::on_nextButton_clicked()
{
    if( user.isNull() ){
        QSharedPointer < userinfo > info ( new userinfo( ui->nameLine->text(), ui->surnameLine->text(), ui->dateEdit->date(), ui->classLine->text(), ui->cellLine->text(), ui->mailLine->text() ) );
        QSharedPointer < account_permission > permission ( new account_permission( ui->comboBox->currentIndex() + 1, ui->loanLine->text().toInt() ) );

        if( !ui->usernameLine->text().isEmpty() && !ui->passwordLine->text().isEmpty() ){
            QSharedPointer < username > name ( new username( ui->usernameLine->text(), utility::encript( ui->passwordLine->text() ) ) );
            user = QSharedPointer < account > ( new account( info, permission, name ) );
            emit sendUser( user );
            user = QSharedPointer < account > ();
        }
        else{
            user = QSharedPointer < account > ( new account( info, permission ) );
            emit sendUser( user );
            QDialog::accept();
        }
    }
    else{
        user->p_info()->setName( ui->nameLine->text() );
        user->p_info()->setSurname( ui->surnameLine->text() );
        user->p_info()->setClass( ui->classLine->text() );
        user->p_info()->setDate( ui->dateEdit->date() );
        user->p_info()->setCellNumber( ui->cellLine->text() );
        user->p_info()->setEmail( ui->mailLine->text() );

        if( user->p_permission().isNull() ){
            user->setPermission( ui->comboBox->currentIndex() + 1, ui->loanLine->text().toInt() );
        }
        else{
            user->p_permission()->setType( ui->comboBox->currentIndex() + 1 );
            user->p_permission()->setMaxLoan( ui->loanLine->text().toInt() );
        }

        bool ok(true);
        if( user->p_user().isNull() && !ui->usernameLine->text().isEmpty() ){
            if( !ui->passwordLine->text().isEmpty() ){
                emit sendUsername( user, ui->usernameLine->text(), utility::encript( ui->passwordLine->text() ) );
                ok &= false;
            }
            else{
                ui->passwordLine->setStyleSheet( "background: rgb(255, 0, 0);" );
                QMessageBox::critical( this, tr( "Error" ), tr( "you need also to setup a password." ) );
                ok &= false;
            }
        }
        else{
            if( !ui->passwordLine->text().isEmpty() )
                user->p_user()->setPassword( utility::encript( ui->passwordLine->text() ) );
        }
        if( ok )
            QDialog::accept();
    }
}


