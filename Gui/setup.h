#ifndef SETUP_H
#define SETUP_H

#include <QDialog>
#include <QFileDialog>
#include <QFont>
#include <QString>
#include <QStringList>
#include <QWidget>

namespace Ui {
class setup;
}

class setup : public QDialog {
  Q_OBJECT

 public:
  explicit setup(QWidget *parent = 0);
  ~setup();

 signals:
  void sendPath(const QString &);

 private slots:
  void on_selectFolder_clicked();
  void on_exitButton_clicked();
  void on_nextButton_clicked();

 private:
  Ui::setup *ui;
};

#endif  // SETUP_H
