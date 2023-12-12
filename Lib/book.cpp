#include "book.h"

book::book(const QString &auth, const QString &plo, const QString &title,
           const QString &publishing, const QString &isbn,
           const QString subtile, const QString genre, const QDate date,
           const QString plac, const QString coll, const unsigned int nEdition,
           const unsigned int nPages, const unsigned int year)
    : publication(title, publishing, subtile, genre, date),
      author(auth),
      plot(plo),
      place(plac),
      collection(coll),
      numberEdition(nEdition),
      numberPages(nPages) {
  setYear(year);
  setISBN_13(isbn);
}

void book::setAuthor(const QString &auth) {
  if (auth.isEmpty())
    author = QStringList();
  else
    author = utility::toQStringList(auth);
}

void book::setPlot(const QString &plo) { plot = plo; }

void book::setPlace(const QString &plac) { place = plac; }

void book::setCollection(const QString &coll) { collection = coll; }

void book::setEdition(const unsigned int &edition) { numberEdition = edition; }

void book::setPages(const unsigned int &number) { numberPages = number; }

void book::setYear(const unsigned int &year) {
  if (numberEdition == 1 && release_date.isValid())
    firstEditionYear = release_date.year();
  else
    firstEditionYear = year;
}

bool book::setISBN_13(const QString &ISBN) {
  if (utility::checkISBN13(ISBN)) {
    ISBN_13 = ISBN;
    return true;
  }
  return false;
}

QString book::showIdentification() const { return ISBN_13; }

QString book::showAuthor() const {
  if (author.isEmpty()) return QString("");
  return author.join(" ");
}

QStringList book::showAuthorList() const { return author; }

QString book::showPlot() const { return plot; }

QString book::showPlace() const {
  if (place.isEmpty()) return QString("");
  return place;
}

QString book::showCollection() const { return collection; }

int book::showEdition() const { return numberEdition; }

int book::showPages() const { return numberPages; }

int book::showYear() const { return firstEditionYear; }

QString book::showCharYear() const {
  if (firstEditionYear) return QString::number(firstEditionYear);
  return QString("");
}

void book::addAuthor(const QString &auth) {
  if (!auth.isEmpty()) author << utility::toQStringList(auth);
}

void book::removeAuthor(const QString &auth) {
  QStringList authList = utility::toQStringList(auth);
  QStringListIterator list(authList);

  while (list.hasNext()) {
    author.removeAll(list.next());
  }
}

void book::removeAllAuthor() { author.clear(); }
