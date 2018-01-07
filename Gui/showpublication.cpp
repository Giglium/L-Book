#include "showpublication.h"
#include "ui_showpublication.h"

showPublication::showPublication( const QSharedPointer < publication > publi, const QSharedPointer < loans > lends, const QSharedPointer <account > user, QWidget *parent)
                :QDialog(parent), ui(new Ui::showPublication)
{
    ui->setupUi(this);
    QWidget::setWindowTitle( QCoreApplication::applicationName() );
    this->setFixedSize(this->size());

    ui->logoLabel->setFont( QFont("A Charming Font", 40, 15) );
    ui->tableWidget->setEditTriggers( QAbstractItemView::NoEditTriggers );

    currentPublication = publi;
    allLoans = lends;
    logUser = user;

    if( logUser.isNull() || logUser->p_permission()->showType() != 3 ){
        ui->actionBox->hide();
    }

    on_allButton_clicked();
    setPubli();
}

showPublication::~showPublication(){
    delete ui;
}

void showPublication::setPubli(){
    ui->titleLabel->setText( currentPublication->showTitle() );
    ui->genreLabel->setText( currentPublication->showGenre() );
    ui->subtitlesLabel->setText( currentPublication->showSubtitle() );
    ui->publishingLabel->setText( currentPublication->showPublishing() );


    QSharedPointer < book > manual = qSharedPointerDynamicCast < book > ( currentPublication);
    if( !manual.isNull() ){
        ui->poliLabel_1->setText( tr( "Author:" ) );
        ui->poliLabel_2->setText( manual->showAuthor() );
        ui->isbnLabel->setText( manual->showISBN_13() );
        ui->poliLabel_3->setText( tr( "Place:" ) );
        ui->poliLabel_4->setText( manual->showPlace() );
        ui->poliLabel_5->setText( tr("Collection:") );
        ui->poliLabel_6->setText( manual->showCollection() );
        ui->poliLabel_7->setText( tr("Print Date:") );
        ui->poliLabel_8->setText( manual->showCharReleaseDate() );
        ui->poliLabel_9->setText( tr( "First Edition Year:" ) );
        ui->poliLabel_10->setText( manual->showCharYear() );
        ui->poliLabel_11->setText( tr("Number of Pages:") );
        ui->poliLabel_12->setText( QString::number( manual->showPages() ) );
        ui->poliLabel_13->setText( tr("Edition:") );
        ui->poliLabel_14->setText( QString::number( manual->showEdition() ) );
        ui->plotLabel->setText( manual->showPlot() );
    }

    QSharedPointer < periodic > magazine = qSharedPointerDynamicCast < periodic > ( currentPublication );
    if( !magazine.isNull() ){
        ui->poliLabel_1->setText( tr( "ISSN:" ) );
        ui->poliLabel_2->setText( magazine->showISSN() );
        ui->isbnLabel->setText( magazine->showISBN_13() + " " + magazine->showID_number() );
        ui->poliLabel_3->setText( tr( "Number:" ) );
        ui->poliLabel_4->setText( QString::number( magazine->showNumber() ) );
        ui->poliLabel_5->setText( tr("Release Date:") );
        ui->poliLabel_6->setText( magazine->showCharReleaseDate() );
        ui->poliLabel_11->setText( tr("Year:") );
        ui->poliLabel_12->setText( magazine->showRomanActivityYears() + "  (" + QString::number( magazine->showActivityYears() ) +")" );
        ui->plotBox->hide();
    }

    QSharedPointer < publication_permission > per = currentPublication->p_permission();

    if( !per.isNull() ){
        switch( per->showType() ){
            case 0:
                ui->typeLabel->setText( tr("Read only in the library") );
                break;
            case 1:
                ui->typeLabel->setText( tr("Not Avalidable") );
                break;
            case 2:
                ui->typeLabel->setText( tr("Avalidable") );
                break;
        }

        ui->freeCopyLabel->setText( QString::number( per->showFreedomCopy() ) );
        ui->lockedCopyLabel->setText( QString::number( per->showLockedCopy() ) );
        ui->numberCopyLabel->setText( QString::number( per->showCopyNumber() ) );
    }
}

void showPublication::setTable( const loans & lends ){
    ui->tableWidget->setRowCount(0);
    if( !logUser.isNull() && logUser->p_permission()->showType() == 3 ){
        ui->tableWidget->setColumnCount(6);
        QStringList title;
        title<<tr( "Name" )<<tr( "Surname" )<<tr( "Class" )<<tr( "Start Date" )<<tr( "DeadLine" )<<tr( "Redelivered");
        ui->tableWidget->setHorizontalHeaderLabels( title );
    }
    else{
        ui->tableWidget->setColumnCount(3);
        QStringList title;
        title<<tr( "Start Date" )<<tr( "DeadLine" )<<tr( "Redelivered" );
        ui->tableWidget->setHorizontalHeaderLabels( title );
    }


    for( int i = 0; i < lends.showLoanNumber(); ++i  ){
        addRow( lends.showLoan( i ) );
    }
}

void showPublication::addRow( const QSharedPointer < loan > lend ){
    ui->tableWidget->insertRow( ui->tableWidget->rowCount() );
    int row = ui->tableWidget->rowCount() - 1, colum = 0;
    if( ui->tableWidget->columnCount() == 6 ){
    ui->tableWidget->setItem( row, colum, new QTableWidgetItem( lend->p_user()->p_info()->showName() )  );
    ++colum;
    ui->tableWidget->setItem( row, colum, new QTableWidgetItem( lend->p_user()->p_info()->showSurname() )  );
    ++colum;
    ui->tableWidget->setItem( row, colum, new QTableWidgetItem( lend->p_user()->p_info()->showClass() )  );
    ++colum;
    }

    ui->tableWidget->setItem( row, colum, new QTableWidgetItem( lend->showCharStartDate() )  );
    ++colum;

    if( !lend->isfinish() )
            ui->tableWidget->setItem( row, colum, new QTableWidgetItem( lend->showCharEndDate() ) );
    else{
            ++colum;
            ui->tableWidget->setItem( row, colum, new QTableWidgetItem( lend->showCharEndDate() ) );
    }
}

void showPublication::on_exitButton_clicked() {
    QDialog::reject();
}

void showPublication::on_allButton_clicked() {
    currentLoans = allLoans->publicationLoans( currentPublication );
    setTable( currentLoans );

    ui->allButton->setEnabled(false);
    ui->activeButton->setEnabled(true);
    ui->finishButton->setEnabled(true);
}

void showPublication::on_activeButton_clicked() {
    currentLoans = currentLoans.showUnfinishLoan();
    setTable( currentLoans );

    ui->allButton->setEnabled(true);
    ui->activeButton->setEnabled(false);
    ui->finishButton->setEnabled(true);
}

void showPublication::on_finishButton_clicked() {
    currentLoans = currentLoans.showFinishLoan();
    setTable( currentLoans );

    ui->allButton->setEnabled(true);
    ui->activeButton->setEnabled(true);
    ui->finishButton->setEnabled(false);
}


void showPublication::on_exportButton_clicked() {
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
        emit sendPath( currentLoans.showFinishLoan(), path );

    if( !ui->activeButton->isEnabled() )
        emit sendPath( currentLoans.showUnfinishLoan(), path );

    if( !ui->allButton->isEnabled() )
         emit sendPath( currentLoans, path );
    }

}

void showPublication::on_tableWidget_cellDoubleClicked(int row, int){
    if( !logUser.isNull() && logUser->p_permission()->showType() == 3 ){
        QSharedPointer < loan > lend;

        if( !ui->finishButton->isEnabled() )
            lend = currentLoans.showFinishLoan().showLoan( row );

        if( !ui->activeButton->isEnabled() )
            lend = currentLoans.showUnfinishLoan().showLoan( row );

        if( !ui->allButton->isEnabled() )
            lend = currentLoans.showLoan( row );

        showLoan thisLoan( lend, logUser );
        QObject::connect( &thisLoan, SIGNAL( removeLoan( QSharedPointer < loan > ) ), this, SLOT( removeLoan( QSharedPointer < loan > ) ) );
        thisLoan.exec();
        if( !ui->finishButton->isEnabled() )
            setTable( currentLoans.showFinishLoan() );

        if( !ui->activeButton->isEnabled() )
            setTable( currentLoans.showUnfinishLoan() );

        if( !ui->allButton->isEnabled() )
            setTable( currentLoans );
    }
}

void showPublication::on_deleteButton_clicked() {
    QMessageBox messageBox( QMessageBox::Information, tr( "Attention" ), tr( " Attention please, this action is permanent and can't be changed once you have saved. Are you sure to delete this book and all his loan? " ), QMessageBox::Yes|QMessageBox::No );
    messageBox.setButtonText( QMessageBox::Yes, tr( "Yes" ) );
    messageBox.setButtonText( QMessageBox::No, tr( "No" ) );
    if( QMessageBox::Yes == messageBox.exec() ) {
        emit erasePublication( currentPublication );
        QDialog::reject();
    }
}

void showPublication::on_modifyButton_clicked(){
    modifyPublication edit( currentPublication );
    edit.exec();
    setPubli();
}
