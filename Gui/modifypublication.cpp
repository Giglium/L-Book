#include "modifypublication.h"
#include "ui_modifypublication.h"

modifyPublication::modifyPublication( const QSharedPointer < publication > publi, QWidget *parent)
                  :QDialog(parent), ui(new Ui::modifyPublication) {
    ui->setupUi(this);
    QWidget::setWindowTitle( QCoreApplication::applicationName() );
    this->setFixedSize( this->size() );

    ui->logoLabel->setFont( QFont("A Charming Font", 40, 15) );

    currentPublication = publi;

    QObject::connect( ui->titleLine, SIGNAL( textChanged( const QString & ) ), this, SLOT( checkLineEdits( const QString & ) ) );
    QObject::connect( ui->isbnLine, SIGNAL( textChanged( const QString & ) ), this, SLOT( checkLineEdits( const QString & ) ) );
    QObject::connect( ui->poliLine_2, SIGNAL( textChanged( const QString & ) ), this, SLOT( checkLineEdits( const QString & ) ) );
    QObject::connect( ui->poliLine_10, SIGNAL( textChanged( const QString & ) ), this, SLOT( checkLineEdits( const QString & ) ) );
    QObject::connect( ui->poliLine_12, SIGNAL( textChanged( const QString & ) ), this, SLOT( checkLineEdits( const QString & ) ) );
    QObject::connect( ui->dateEdit, SIGNAL( dateChanged( QDate ) ), this, SLOT( checkLineEdits( QDate ) ) );

    if( currentPublication.isNull() ){
        ui->dateEdit->setDate( QDate::currentDate() );
        on_publiBox_currentIndexChanged( 0 );
    }
    else{
           ui->titleLine->setText( publi->showTitle() );
           ui->subtitleLine->setText( publi->showSubtitle() );
           ui->isbnLine->setText( publi->showISBN_13() );
           ui->isbnLine->setEnabled( false );
           ui->genreLine->setText( publi->showGenre() );
           ui->publishingLine->setText( publi->showPublishing() );
           ui->dateEdit->setDate( publi->showReleaseDate() );
           if( !publi->p_permission().isNull() ){
               ui->typeCombo->setCurrentIndex( publi->p_permission()->showType() ? 2 : 1 );
               ui->nCopyLine->setText( QString::number( publi->p_permission()->showCopyNumber() ) );
           }
           ui->nCopyLine->setValidator( new QRegExpValidator( QRegExp( "\\d*" ), this) );

           QSharedPointer < book > manual = qSharedPointerDynamicCast < book > ( publi );
           if( !manual.isNull() ){
               ui->publiBox->setCurrentIndex(1);
               ui->publiBox->setEnabled(false);
               ui->poliLine_2->setText( manual->showAuthor() );
               ui->plotLine->setText( manual->showPlot() );
               ui->poliLine_4->setText( QString::number( manual->showYear() ) );
               ui->poliLine_6->setText( QString::number( manual->showPages() ) );
               ui->poliLine_8->setText( manual->showCollection() );
               ui->poliLine_10->setText( QString::number( manual->showEdition() ) );
               ui->poliLine_12->setText( manual->showPlace() );
           }

           QSharedPointer < periodic > magazine = qSharedPointerDynamicCast < periodic > ( publi );
           if( !magazine.isNull() ){
               ui->publiBox->setCurrentIndex(2);
               ui->publiBox->setEnabled(false);
               ui->poliLine_2->setText( magazine->showISSN() );
               ui->poliLine_2->setEnabled(false);
               ui->poliLine_8->setText( magazine->showID_number() );
               ui->poliLine_8->setEnabled(false);
               ui->poliLine_10->setText( QString::number( magazine->showNumber() ) );
               ui->poliLine_12->setText( magazine->showRomanActivityYears() );
           }
   }
}

modifyPublication::~modifyPublication()
{
    delete ui;
}

void modifyPublication::on_exitButton_clicked()
{
    QDialog::reject();
}

void modifyPublication::on_publiBox_currentIndexChanged(int index)
{
    if( index == 0 ){
        ui->plotBox->hide();
        ui->poliLine_2->hide();
        ui->poliLine_4->hide();
        ui->poliLine_6->hide();
        ui->poliLine_8->hide();
        ui->poliLine_10->hide();
        ui->poliLine_12->hide();
        ui->poliLabel_1->hide();
        ui->poliLabel_3->hide();
        ui->poliLabel_5->hide();
        ui->poliLabel_7->hide();
        ui->poliLabel_9->hide();
        ui->poliLabel_11->hide();
        ui->poliLine_4->setValidator( new QRegExpValidator( QRegExp( ".*" ), this) );
        ui->poliLine_6->setValidator( new QRegExpValidator( QRegExp( ".*" ), this) );
        ui->poliLine_10->setValidator( new QRegExpValidator( QRegExp( ".*" ), this) );
    }

    if( index == 1 ){
        ui->noteLabel->setText( tr("Title, Author and ISBN13 are always required.") );
        ui->poliLabel_1->setText( tr( "Author:" ) );
        ui->poliLabel_3->setText( tr( "First Edition Year:" ) );
        ui->poliLabel_5->setText( tr( "Number of Pages:" ) );
        ui->poliLabel_7->setText( tr( "Collection:" ) );
        ui->poliLabel_9->setText( tr( "Edition:" ) );
        ui->poliLabel_11->setText( tr( "Place:" ) );
        ui->poliLine_4->setValidator( new QRegExpValidator( QRegExp( "\\d*" ), this) );
        ui->poliLine_6->setValidator( new QRegExpValidator( QRegExp( "\\d*" ), this) );
        ui->poliLine_10->setValidator( new QRegExpValidator( QRegExp( "\\d*" ), this) );
        ui->plotBox->show();
        ui->poliLine_2->show();
        ui->poliLine_4->show();
        ui->poliLine_6->show();
        ui->poliLine_8->show();
        ui->poliLine_10->show();
        ui->poliLine_12->show();
        ui->poliLabel_1->show();
        ui->poliLabel_3->show();
        ui->poliLabel_5->show();
        ui->poliLabel_7->show();
        ui->poliLabel_9->show();
        ui->poliLabel_11->show();
    }

    if( index == 2 ){
       ui->noteLabel->setText( tr("Title, Release Date, Years, ISBN13 or ISSN and Number are always required.") );
       ui->poliLabel_1->setText( tr( "ISSN:" ) );
       ui->poliLabel_7->setText( tr( "ID:" ) );
       ui->poliLabel_9->setText( tr( "Number:" ) );
       ui->poliLabel_11->setText( tr( "Year:" ) );
       ui->poliLine_4->setValidator( new QRegExpValidator( QRegExp( ".*" ), this) );
       ui->poliLine_6->setValidator( new QRegExpValidator( QRegExp( ".*" ), this) );
       ui->poliLine_10->setValidator( new QRegExpValidator( QRegExp( "\\d*" ), this) );
       ui->plotBox->hide();
       ui->poliLine_2->show();
       ui->poliLine_4->hide();
       ui->poliLine_6->hide();
       ui->poliLine_8->show();
       ui->poliLine_10->show();
       ui->poliLine_12->show();
       ui->poliLabel_1->show();
       ui->poliLabel_3->hide();
       ui->poliLabel_5->hide();
       ui->poliLabel_7->show();
       ui->poliLabel_9->show();
       ui->poliLabel_11->show();
    }
}

void modifyPublication::checkLineEdits( const QString & ) {
    bool ok( true );
    ok &= !ui->titleLine->text().isEmpty();

    if( ui->publiBox->currentIndex() == 0 ){
        ok &= false;
    }

    if( ui->publiBox->currentIndex() == 1 ){
        ok &= !ui->poliLine_2->text().isEmpty();
        ok &= !ui->isbnLine->text().isEmpty();
    }

    if( ui->publiBox->currentIndex() == 2 ){
        ok &= !ui->dateEdit->date().isNull();
        ok &= !ui->poliLine_12->text().isEmpty();
        ok &= !ui->poliLine_10->text().isEmpty();
    }

    ui->saveButton->setEnabled( ok );
}

void modifyPublication::checkLineEdits( const QDate & ) {
    checkLineEdits( "" );
}

void modifyPublication::on_saveButton_clicked()
{
    if( currentPublication.isNull() ){
        if( ui->publiBox->currentIndex() == 1 ){
            if( utility::checkISBN13( ui->isbnLine->text() ) ){
                currentPublication = QSharedPointer < publication >( new book( ui->poliLine_2->text(), ui->plotLine->toPlainText(), ui->titleLine->text(), ui->publishingLine->text(), ui->isbnLine->text(), ui->subtitleLine->text(), ui->genreLine->text(), ui->dateEdit->date(), ui->poliLine_12->text(), ui->poliLine_8->text(), ui->poliLine_10->text().toInt(), ui->poliLine_6->text().toInt() ,ui->poliLine_4->text().toInt() ) );
            }
            else
                isbnError();
        }
        if( ui->publiBox->currentIndex() == 2 ){
            if( !ui->isbnLine->text().isEmpty() ){
                if( utility::checkISBN13( ui->isbnLine->text() ) ){
                    if( utility::checkAllInteger( ui->poliLine_12->text() ) )
                        currentPublication = QSharedPointer < publication >( new periodic( ui->poliLine_2->text(), ui->poliLine_12->text().toInt(), ui->poliLine_10->text().toInt(), ui->titleLine->text(), ui->publishingLine->text(), ui->isbnLine->text(), ui->dateEdit->date(), ui->subtitleLine->text(), ui->genreLine->text() ) );
                    else
                       currentPublication = QSharedPointer < publication >( new periodic( ui->poliLine_2->text(), ui->poliLine_12->text(), ui->poliLine_10->text().toInt(), ui->titleLine->text(), ui->publishingLine->text(), ui->isbnLine->text(), ui->dateEdit->date(), ui->subtitleLine->text(), ui->genreLine->text() ) );
                }
                    else{
                        isbnError();
                    }
                }
            }
            else{
                if( !ui->poliLine_2->text().isEmpty() && utility::checkISSN( ui->poliLine_2->text() ) ){
                    if( utility::checkAllInteger( ui->poliLine_12->text() ) )
                        currentPublication = QSharedPointer < publication >( new periodic( ui->poliLine_2->text(), ui->poliLine_12->text().toInt(), ui->poliLine_10->text().toInt(), ui->titleLine->text(), ui->publishingLine->text(), ui->poliLine_2->text(), ui->dateEdit->date(), ui->subtitleLine->text(), ui->genreLine->text() ) );
                    else
                       currentPublication = QSharedPointer < publication >( new periodic( ui->poliLine_2->text(), ui->poliLine_12->text(), ui->poliLine_10->text().toInt(), ui->titleLine->text(), ui->publishingLine->text(), ui->poliLine_2->text(), ui->dateEdit->date(), ui->subtitleLine->text(), ui->genreLine->text() ) );
                }
                else{
                isbnError(false);
                }
        }

        if( ui->typeCombo->currentIndex() )
            currentPublication->setPermission( ui->typeCombo->currentIndex()-1, ui->nCopyLine->text().toInt() );

        if( !currentPublication.isNull() )
            emit savePublication( currentPublication );
    }
    else{
        currentPublication->setTitle( ui->titleLine->text() );
        currentPublication->setSubtitle( ui->subtitleLine->text() );
        currentPublication->setPublishing( ui->publishingLine->text() );
        currentPublication->setGenre( ui->genreLine->text() );
        currentPublication->setReleaseDate( ui->dateEdit->date() );

        QSharedPointer < book > manual = qSharedPointerDynamicCast < book > ( currentPublication );
        if( !manual.isNull() ){
            manual->setPlot( ui->plotLine->toPlainText() );
            manual->setAuthor( ui->poliLine_2->text() );
            manual->setYear( ui->poliLine_4->text().toInt() );
            manual->setPages( ui->poliLine_6->text().toInt() );
            manual->setCollection( ui->poliLine_8->text() );
            manual->setEdition( ui->poliLine_10->text().toInt() );
            manual->setPlace( ui->poliLine_12->text() );
        }

        QSharedPointer < periodic > magazine = qSharedPointerDynamicCast < periodic > ( currentPublication );
        if( !magazine.isNull() ){
            magazine->setNumber( ui->poliLine_10->text().toInt() );
            magazine->setActivityYears( ui->poliLine_12->text() );
        }

        if( ui->typeCombo->currentIndex() ){
            if( currentPublication->p_permission().isNull() )
                currentPublication->setPermission( ui->typeCombo->currentIndex()-1, ui->nCopyLine->text().toInt() );
            else{
                currentPublication->p_permission()->setType( ui->typeCombo->currentIndex() );
                currentPublication->p_permission()->setCopyNumber( ui->nCopyLine->text().toInt() );
            }
        }

        QDialog::reject();
    }

}

void modifyPublication::isbnError( const bool &mode ){
    if( mode ){
        ui->isbnLine->setStyleSheet( "background: rgb(255, 0, 0);" );
        ui->noteLabel->setText( tr( "Sorry but the ISBN 13 that you have insert isn't valid." ) );
        QMessageBox::critical( this, tr( "Error" ), tr( "Sorry but the ISBN 13 that you have insert isn't valid." ) );
    }
    else{
        ui->poliLine_2->setStyleSheet( "background: rgb(255, 0, 0);" );
        ui->noteLabel->setText( tr( "Sorry but the ISSN that you have insert isn't valid." ) );
        QMessageBox::critical( this, tr( "Error" ), tr( "Sorry but the ISSN that you have insert isn't valid." ) );
    }
}

void modifyPublication::addResult( const bool &result ){
    if( result )
        QDialog::accept();
    else{
        ui->isbnLine->setStyleSheet( "background: rgb(255, 0, 0);" );
        ui->noteLabel->setText( tr( "There is already a publication with the ISBN 13 that you have insert. If you want to add a periodic you have to remember to insert also the ID." ) );
        QMessageBox::critical( this, tr( "Error" ), tr( "There is already a publication with the ISBN 13 that you have insert.There is already a publication with the ISBN 13 that you have insert. If you want to add a periodic you have to remember to insert also the ID." ) );
    }
}
