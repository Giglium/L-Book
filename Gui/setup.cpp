#include "setup.h"
#include "ui_setup.h"

setup::setup(QWidget *parent)
      :QDialog(parent), ui(new Ui::setup) {
    ui->setupUi(this);
    QWidget::setWindowTitle( QCoreApplication::applicationName() );
    this->setFixedSize( this->size() );

    ui->logoLabel->setFont( QFont("A Charming Font", 40, 15) );
}

setup::~setup() {
    delete ui;
}

void setup::on_selectFolder_clicked() {
    ui->sharedButton->setChecked(1);

    QFileDialog dialog( this );
    dialog.setFileMode( QFileDialog::Directory );
    QStringList dir;
    if( dialog.exec() )
        dir = dialog.selectedFiles();

    if( !dir.isEmpty() )
        emit sendPath( dir.join("") );
}

void setup::on_exitButton_clicked() {
    QDialog::reject();
}

void setup::on_nextButton_clicked() {
    if( ui->LocalButton->isChecked() )
        emit sendPath("");
    QDialog::accept();
}
