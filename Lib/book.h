#ifndef BOOK_H
#define BOOK_H

#include <QString>
#include <QStringList>

#include "Utility/utility.h"
#include "publication.h"

class book : public publication {
 private:
  QStringList author;
  QString plot;
  QString place;
  QString collection;
  unsigned int numberEdition;
  unsigned int numberPages;
  unsigned int firstEditionYear;

 public:
  book(const QString &, const QString &, const QString &, const QString &,
       const QString &, const QString = "", const QString = "",
       const QDate = QDate(), const QString = "", const QString = "",
       const unsigned int = 0, const unsigned int = 0, const unsigned int = 0);
  virtual ~book() {}

  void setAuthor(const QString &);
  void setPlot(const QString &);
  void setPlace(const QString &);
  void setCollection(const QString &);
  void setEdition(const unsigned int &);
  void setPages(const unsigned int &);
  void setYear(const unsigned int &);
  bool setISBN_13(const QString &);

  virtual QString showIdentification() const;
  QString showAuthor() const;
  QStringList showAuthorList() const;
  QString showPlot() const;
  QString showPlace() const;
  QString showCollection() const;
  int showEdition() const;
  int showPages() const;
  int showYear() const;
  QString showCharYear() const;

  void addAuthor(const QString &);
  void removeAuthor(const QString &);
  void removeAllAuthor();
};

#endif  // BOOK_H
