#include "publication.h"

publication::publication(const QString &tit, const QString &pub,
                         const QString subtit, const QString gen,
                         const QDate date)
    : title(tit), publishing(pub), subtitle(subtit), ISBN_13("") {
  release_date.setDate(date.year(), date.month(), date.day());
  setGenre(gen);
}

void publication::setTitle(const QString &tit) { title = tit; }

void publication::setSubtitle(const QString &subtit) { subtitle = subtit; }

void publication::setPublishing(const QString &pub) { publishing = pub; }

void publication::setGenre(const QString &gen) {
  if (gen.isEmpty())
    genre = QStringList();
  else
    genre = utility::toQStringList(gen);
}

void publication::setReleaseDate(const QDate &date) {
  release_date.setDate(date.year(), date.month(), date.day());
}

void publication::setPermission(const unsigned int &type,
                                const unsigned int &max,
                                const unsigned int locked) {
  permission.QSharedPointer::reset(
      new publication_permission(type, max, locked));
}

void publication::setPermission(
    const QSharedPointer<publication_permission> per) {
  permission = per;
}

QString publication::showTitle() const { return title; }

QString publication::showSubtitle() const { return subtitle; }

QString publication::showPublishing() const { return publishing; }

QString publication::showISBN_13() const { return ISBN_13; }

QString publication::showGenre() const {
  if (!genre.isEmpty()) return genre.join(" ");
  return QString("");
}

QStringList publication::showGenreList() const { return genre; }

QDate publication::showReleaseDate() const {
  if (release_date.isValid()) return release_date;
  return QDate();
}

QString publication::showCharReleaseDate() const {
  if (release_date.isValid()) return release_date.toString("dd-MMM-yyyy");
  return QString("S.d.");
}

QSharedPointer<publication_permission> publication::p_permission() const {
  return permission;
}

void publication::addGenre(const QString &gen) {
  if (!gen.isEmpty()) genre << utility::toQStringList(gen);
}

void publication::removeGenre(const QString &gen) {
  QStringList genList = utility::toQStringList(gen);

  QStringListIterator list(genList);
  while (list.hasNext()) {
    genre.removeAll(list.next());
  }
}

void publication::removeAllGenre() { genre.clear(); }
