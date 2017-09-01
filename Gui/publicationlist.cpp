#include "publicationlist.h"
#include "ui_publicationlist.h"

publicationList::publicationList( const QSharedPointer < library > list, const QSharedPointer < loans > loansList , const bool mode, const QSharedPointer < account > user, QWidget *parent )
                :QDialog(parent), ui(new Ui::publicationList) {
    ui->setupUi(this);

    QWidget::setWindowTitle( QCoreApplication::applicationName() );
    this->setFixedSize( this->size() );

    ui->logoLabel->setFont( QFont("A Charming Font", 40, 15) );
    ui->bookTable->setEditTriggers( QAbstractItemView::NoEditTriggers );
    ui->periodicTable->setEditTriggers( QAbstractItemView::NoEditTriggers );

    ui->bookTable->setColumnCount(6);
    ui->periodicTable->setColumnCount(6);

    QStringList title;
    title<<tr( "Title" )<<tr( "Subtittle" )<<tr( "Author" )<<tr( "Edition" )<<tr( "Genre" )<<tr( "ISBN 13" );
    ui->bookTable->setHorizontalHeaderLabels( title );
    title.clear();
    title<<tr( "Title" )<<tr( "Subtittle" )<<tr( "Number" )<<tr( "Genre" )<<tr( "ISSN" )<<tr( "ISBN 13" );
    ui->periodicTable->setHorizontalHeaderLabels( title );

    allPublications = list;

    on_resetButton_clicked();

    if(mode)
        on_bookButton_clicked();
    else
        on_periodicButton_clicked();

    allLoans = loansList;
    logUser = user;

    if( logUser.isNull() || logUser->p_permission()->showType() != 3 ){
        ui->addButton->hide();
    }
}

publicationList::~publicationList(){
    delete ui;
}

void publicationList::on_bookButton_clicked() {
    ui->bookButton->setEnabled(false);
    ui->periodicButton->setEnabled(true);
    ui->bookTable->show();
    ui->periodicTable->hide();
}

void publicationList::on_periodicButton_clicked() {
    ui->bookButton->setEnabled(true);
    ui->periodicButton->setEnabled(false);
    ui->bookTable->hide();
    ui->periodicTable->show();
}

void publicationList::setTables(){
    ui->bookTable->setRowCount(0);
    ui->periodicTable->setRowCount(0);
    ui->resultLabel->setText( QString::number( currentPublications.showPublicationNumber() ) );

    for( int i = 0; i < currentPublications.showPublicationNumber(); ++i ){
        addRow( currentPublications.showPublication( i ) );
    }

    if( ui->bookTable->rowCount() )
        on_bookButton_clicked();
    else
        on_periodicButton_clicked();
}

void publicationList::addRow( const QSharedPointer < publication > publicatio ){
    QSharedPointer < book > manual = qSharedPointerDynamicCast < book > ( publicatio );
    if( !manual.isNull() ){
        ui->bookTable->insertRow( ui->bookTable->rowCount() );
        int rowB = ui->bookTable->rowCount() - 1;

        ui->bookTable->setItem( rowB, 0, new QTableWidgetItem( manual->showTitle() ) );
        ui->bookTable->setItem( rowB, 1, new QTableWidgetItem( manual->showSubtitle() ) );
        ui->bookTable->setItem( rowB, 2, new QTableWidgetItem( manual->showAuthor() ) );
        ui->bookTable->setItem( rowB, 3, new QTableWidgetItem( QString::number( manual->showEdition() ) ) );
        ui->bookTable->setItem( rowB, 4, new QTableWidgetItem( manual->showGenre() ) );
        ui->bookTable->setItem( rowB, 5, new QTableWidgetItem( manual->showISBN_13() ) );
    }

    QSharedPointer < periodic > magazine = qSharedPointerDynamicCast < periodic > ( publicatio );
    if( !magazine.isNull() ){
        ui->periodicTable->insertRow( ui->periodicTable->rowCount() );
        int rowP = ui->periodicTable->rowCount() - 1;

        ui->periodicTable->setItem( rowP, 0, new QTableWidgetItem( magazine->showTitle() ) );
        ui->periodicTable->setItem( rowP, 1, new QTableWidgetItem( magazine->showSubtitle() ) );
        ui->periodicTable->setItem( rowP, 2, new QTableWidgetItem( QString::number( magazine->showNumber() ) ) );
        ui->periodicTable->setItem( rowP, 3, new QTableWidgetItem( magazine->showGenre() ) );
        ui->periodicTable->setItem( rowP, 4, new QTableWidgetItem( magazine->showISSN() ) );
        ui->periodicTable->setItem( rowP, 5, new QTableWidgetItem( magazine->showISBN_13() ) );
    }
}

void publicationList::on_exportButton_clicked() {
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

    if( !ui->bookButton->isEnabled() )
        emit sendPath( currentPublications.allBook(), path );

    if( !ui->periodicButton->isEnabled() )
        emit sendPath( currentPublications.allPeriodic(), path );
    }
}

void publicationList::on_resetButton_clicked() {
    currentPublications = allPublications->showPublications();
    setTables();
}

void publicationList::on_exitButton_clicked() {
    QDialog::reject();
}

void publicationList::on_searchButton_clicked() {
    QString searchText = ui->searchLine->text();

    currentPublications = library();

    if( utility::checkISSN( searchText ) )
        currentPublications<<allPublications->showPublicationsFromISSN( searchText );

    if( utility::checkISBN13( searchText ) )
        currentPublications<<allPublications->showPublicationsFromISBN13( searchText );

    if( ( searchText.size() == 18 || searchText.size() == 19 ) && utility::checkAllInteger( searchText ) )
        currentPublications<<allPublications->showPublication( searchText.remove(" ") );

    currentPublications<<allPublications->showPublicationsFromTitle( searchText );

    currentPublications<<allPublications->thisGenrePublications( searchText );

    currentPublications<<allPublications->thisAuthorPublications( searchText );

    setTables();
}

void publicationList::on_bookTable_cellDoubleClicked(int row, int) {
  showPublication bookView( currentPublications.allBook().showPublication( row ), allLoans, logUser );

  QObject::connect( &bookView, SIGNAL( sendPath( loans, QString ) ), this, SLOT( recivePath( loans, QString ) ) );
  QObject::connect( &bookView, SIGNAL( erasePublication( QSharedPointer < publication > ) ), this, SLOT( removePublication( QSharedPointer < publication > ) ) );

  bookView.exec();
  on_resetButton_clicked();
}

void publicationList::on_periodicTable_cellDoubleClicked(int row, int) {
    showPublication bookView( currentPublications.allPeriodic().showPublication( row ), allLoans, logUser );

    QObject::connect( &bookView, SIGNAL( sendPath( loans, QString ) ), this, SLOT( recivePath( loans, QString ) ) );
    QObject::connect( &bookView, SIGNAL( erasePublication( QSharedPointer < publication > ) ), this, SLOT( removePublication( QSharedPointer < publication > ) ) );

    bookView.exec();
    on_resetButton_clicked();
}

void publicationList::recivePath( const loans &lends, const QString &path ){
    emit sendPath( lends, path );
}

void publicationList::removePublication( const QSharedPointer<publication> publi ){
    allLoans->removeAllPublicationLoan( publi );
    allPublications->removePublication( publi );
    on_resetButton_clicked();
}

void publicationList::on_addButton_clicked() {
    modifyPublication newPublication;

    QObject::connect( &newPublication, SIGNAL( savePublication( QSharedPointer < publication > ) ), this, SLOT( addPublication( QSharedPointer < publication > ) ) );
    QObject::connect( this, SIGNAL( addPublicationResult(bool) ), &newPublication, SLOT( addResult(bool) ) );

    newPublication.exec();
    on_resetButton_clicked();
}

void publicationList::addPublication( const QSharedPointer < publication > publi ){
    if( allPublications->showPublication( publi ).isNull() ){
            allPublications->addPublication( publi );
            emit addPublicationResult(true);
    }
    else
        emit addPublicationResult(false);
}
