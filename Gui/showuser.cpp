#include "showuser.h"
#include "ui_showuser.h"

showUser::showUser( const QSharedPointer < account > user, const QSharedPointer < loans > lends, const QSharedPointer < account > log, QWidget *parent)
         :QDialog(parent), ui(new Ui::showUser)
{
    ui->setupUi(this);

    QWidget::setWindowTitle( QCoreApplication::applicationName() );
    this->setFixedSize(this->size());

    ui->logoLabel->setFont( QFont("A Charming Font", 40, 15) );

    ui->yourClassLabel->hide();
    ui->comboBox->hide();
    ui->modifyButton->hide();
    ui->banButton->hide();
    ui->searchLabel->hide();
    ui->surnameEdit->hide();
    ui->searchButton->hide();
    ui->actionsBox->hide();
    ui->exportButton->hide();
    ui->loanButton->hide();
    ui->tableWidget->setEditTriggers( QAbstractItemView::NoEditTriggers );

    currentUser = user;
    logUser = log;
    setUserData( currentUser );
    setLogUser( logUser );
    AllLoans = lends;
    CurrentLoans = AllLoans->userLoans( currentUser );
    on_AllButton_clicked();
}

showUser::~showUser()
{
    delete ui;
}

void showUser::setTable( const loans &lends ){
    ui->tableWidget->setRowCount(0);
    if( ui->tableWidget->columnCount() != 7 ){
        ui->tableWidget->setColumnCount(7);
        QStringList title;
        title<<tr( "Title" )<<tr( "Subtittle" )<<tr( "ISBN 13" )<<tr( "Start Date" )<<tr( "DeadLine" )<<tr( "Redelivered")<<tr( "Day to end" );
        ui->tableWidget->setHorizontalHeaderLabels( title );
    }

    for( int i = 0; i < lends.showLoanNumber(); ++i  ){
        addRow( lends.showLoan( i ) );
    }
}

void showUser::setClassTable( const loans &lends ){
    ui->tableWidget->setRowCount(0);
    if( ui->tableWidget->columnCount() != 8 ){
        ui->tableWidget->setColumnCount(8);
        QStringList title;
        title<<tr( "Name" )<<tr( "Surname" )<< tr( "Title" )<<tr( "Subtittle" )<<tr( "ISBN 13" )<<tr( "Start Date" )<<tr( "DeadLine" )<<tr( "Redelivered" );
        ui->tableWidget->setHorizontalHeaderLabels( title );
    }

    for( int i = 0; i < lends.showLoanNumber(); ++i  ){
        addRow( lends.showLoan( i ) );
    }
}

void showUser::addRow( const QSharedPointer < loan > lend ){
    ui->tableWidget->insertRow( ui->tableWidget->rowCount() );
    int row = ui->tableWidget->rowCount() - 1, colum = 0;

    if( ui->tableWidget->columnCount() == 8 ){
        ui->tableWidget->setItem( row, colum, new QTableWidgetItem( lend->p_user()->p_info()->showName() ) );
        ++colum;
        ui->tableWidget->setItem( row, colum, new QTableWidgetItem( lend->p_user()->p_info()->showSurname() ) );
        ++colum;
    }

    ui->tableWidget->setItem( row, colum, new QTableWidgetItem( lend->p_title()->showTitle() ) );
    ++colum;
    ui->tableWidget->setItem( row, colum, new QTableWidgetItem( lend->p_title()->showSubtitle() ) );
    ++colum;
    ui->tableWidget->setItem( row, colum, new QTableWidgetItem( lend->p_title()->showISBN_13() ) );
    ++colum;
    ui->tableWidget->setItem( row, colum, new QTableWidgetItem( lend->showCharStartDate() ) );
    ++colum;
    if( !lend->isfinish() )
            ui->tableWidget->setItem( row, colum, new QTableWidgetItem( lend->showCharEndDate() ) );
    else{
            ++colum;
            ui->tableWidget->setItem( row, colum, new QTableWidgetItem( lend->showCharEndDate() ) );
    }

    if( ui->tableWidget->columnCount() == 7 ){
        if( !lend->isfinish() )
            ui->tableWidget->setItem( row, 6, new QTableWidgetItem( lend->showDaytoEnd() > 0 ? QString::number( lend->showDaytoEnd() ) : tr("Expired") ) );
        else
            ui->tableWidget->setItem( row, 6, new QTableWidgetItem( tr("Redelivered") ) );
    }
}

void showUser::setUserData( const QSharedPointer < account > user ){
    if( !user->p_user().isNull() && logUser == user )
        ui->usernameLabel->setText( user->p_user()->showUser() );
    ui->nameLabel->setText( user->p_info()->showName() );
    ui->surnameLabel->setText( user->p_info()->showSurname() );
    ui->birthdayLabel->setText( user->p_info()->showCharBirthdate() );
    ui->classLabel->setText( user->p_info()->showClass() );
    ui->cellLabel->setText( user->p_info()->showCellNumber() );
    ui->mailLabel->setText( user->p_info()->showEmail() );
    if( !user->p_permission().isNull() ){
        int type;
        type = user->p_permission()->showType();

        if( type == 0 )
            ui->typeLabel->setText( tr("Banned") );

        if( type == 1 )
            ui->typeLabel->setText( tr("Student") );

        if( type == 2 )
            ui->typeLabel->setText( tr("Professor") );

        if( type == 3 )
            ui->typeLabel->setText( tr("Admin") );

        ui->loansLabel->setText( QString::number( user->p_permission()->showFreedomLoan() ) );
        ui->lockedLabel->setText( QString::number( user->p_permission()->showLockedLoan() ) );
    }
}

void showUser::setLogUser( const QSharedPointer < account > user ){
    if( !user.isNull() && !user->p_permission().isNull() ){
        int type;
        type = user->p_permission()->showType();

        if( type == 2 ){
            ui->actionsBox->show();
            ui->exportButton->show();
            ui->yourClassLabel->show();
            ui->loanButton->show();
            ui->comboBox->show();
            ui->comboBox->addItem( tr("Select a class") );

            QStringList clas = user->p_info()->showClassList();

            QStringListIterator list ( clas );

            while( list.hasNext() ) {
              ui->comboBox->addItem( list.next() );
            }

            ui->searchLabel->show();
            ui->surnameEdit->show();
            ui->searchButton->show();


        }

        if( type == 3 ){
            ui->actionsBox->show();
            ui->exportButton->show();
            ui->modifyButton->show();
            ui->banButton->show();
        }
    }
}

void showUser::removeLoan( const QSharedPointer < loan > lend ){
    AllLoans->removeLoan( lend );

    CurrentLoans = AllLoans->userLoans( currentUser );

    if( !ui->finishButton->isEnabled() )
        setTable( CurrentLoans.showFinishLoan() );

    if( !ui->activeButton->isEnabled() )
        setTable( CurrentLoans.showUnfinishLoan() );

    if( !ui->AllButton->isEnabled() )
        setTable( CurrentLoans );
}

void showUser::on_ExitButton_clicked(){
    QDialog::reject();
}

void showUser::on_AllButton_clicked(){
    setTable( CurrentLoans );
    ui->AllButton->setEnabled(false);
    ui->activeButton->setEnabled(true);
    ui->finishButton->setEnabled(true);
}

void showUser::on_activeButton_clicked()
{
    setTable( CurrentLoans.showUnfinishLoan() );
    ui->AllButton->setEnabled(true);
    ui->activeButton->setEnabled(false);
    ui->finishButton->setEnabled(true);
}

void showUser::on_finishButton_clicked()
{
    setTable( CurrentLoans.showFinishLoan() );
    ui->AllButton->setEnabled(true);
    ui->activeButton->setEnabled(true);
    ui->finishButton->setEnabled(false);
}

void showUser::on_exportButton_clicked() {
    QFileDialog dialog( this );
    dialog.setFileMode( QFileDialog::AnyFile );
    QStringList dir;
    dialog.setNameFilter(tr("csv (*.csv)"));
    if( dialog.exec() )
        dir = dialog.selectedFiles();
    QString path = dir.join("");
    if( !path.isEmpty() ){
        if( !path.contains( ".csv" ) )
            path.append( ".csv" );

    if( !ui->finishButton->isEnabled() )
        emit sendPath( CurrentLoans.showFinishLoan(), path );

    if( !ui->activeButton->isEnabled() )
        emit sendPath( CurrentLoans.showUnfinishLoan(), path );

    if( !ui->AllButton->isEnabled() )
        emit sendPath( CurrentLoans, path );
    }
}

void showUser::on_comboBox_currentIndexChanged( int index ) {
    if( index ) {
        CurrentLoans = AllLoans->unorderClassroomLoans( currentUser->p_info()->showClassList().at( index -1 ) ).studentLoans();
        setClassTable( CurrentLoans );
        ui->AllButton->setEnabled(false);
        ui->activeButton->setEnabled(true);
        ui->finishButton->setEnabled(true);
    }
}

void showUser::on_loanButton_clicked()
{
    CurrentLoans = AllLoans->userLoans( currentUser );
    setTable( CurrentLoans );
    ui->comboBox->setCurrentIndex(0);
}

void showUser::on_searchButton_clicked()
{
    if( !ui->surnameEdit->text().isEmpty() ){
        if( ui->comboBox->currentIndex() ) {
            CurrentLoans = AllLoans->unorderClassroomLoans( currentUser->p_info()->showClassList().at( ui->comboBox->currentIndex() - 1 ) ).studentLoans().surnameLoans( ui->surnameEdit->text() );

        setClassTable( CurrentLoans );
        }
        else
           QMessageBox::critical( this, tr( "Error" ), tr( "You have to select a class first" ) );
    }
}

void showUser::on_modifyButton_clicked()
{
    modifyUser modify( currentUser );

    QObject::connect( &modify, SIGNAL( sendUsername( QSharedPointer < account >, QString, QString ) ), this, SLOT( reciveUsername( QSharedPointer < account >, QString, QString ) ) );
    QObject::connect( this, SIGNAL( sendResult(bool) ), &modify, SLOT( userResult( bool ) ) );

    modify.exec();
    setUserData( currentUser );
}

void showUser::on_banButton_clicked()
{
    if( currentUser->p_permission()->showType() == 3 ){
        QMessageBox::information( this, tr("Error"), tr("The Admin can't be banned!"));
    }
    else{
        QMessageBox messageBox( QMessageBox::Information, tr( "Attention" ), tr( " Attention please, this action is permanent and can't be changed once you have saved. If the account don't have any pending loans it with be erased, if not it will be permanently banned. " ), QMessageBox::Yes|QMessageBox::No );
        messageBox.setButtonText( QMessageBox::Yes, tr( "Yes" ) );
        messageBox.setButtonText( QMessageBox::No, tr( "No" ) );
        if( QMessageBox::Yes == messageBox.exec() ) {
            if( AllLoans->userLoans( currentUser ).showUnfinishLoan().showLoanNumber() ){
                currentUser->p_permission()->setType(0);
                setUserData( currentUser );
            }
            else {
                emit eraseUser( currentUser );
                QDialog::reject();
            }
        }
    }
}

void showUser::on_tableWidget_cellDoubleClicked(int row, int )
{
    QSharedPointer < loan > lend;

    if( !ui->finishButton->isEnabled() )
        lend = CurrentLoans.showFinishLoan().showLoan( row );

    if( !ui->activeButton->isEnabled() )
        lend = CurrentLoans.showUnfinishLoan().showLoan( row );

    if( !ui->AllButton->isEnabled() )
        lend = CurrentLoans.showLoan( row );

    showLoan thisLoan( lend, logUser );
    QObject::connect( &thisLoan, SIGNAL( removeLoan( QSharedPointer < loan > ) ), this, SLOT( removeLoan( QSharedPointer < loan > ) ) );
    thisLoan.exec();
    if( !ui->finishButton->isEnabled() )
        setTable( CurrentLoans.showFinishLoan() );

    if( !ui->activeButton->isEnabled() )
        setTable( CurrentLoans.showUnfinishLoan() );

    if( !ui->AllButton->isEnabled() )
        setTable( CurrentLoans );
}

void showUser::reciveUsername( const QSharedPointer < account > user, const QString &name , const QString &pass ){
    emit sendUsername( user, name, pass );
}

void showUser::reciveResult( const bool &result ){
    emit sendResult( result );
}
