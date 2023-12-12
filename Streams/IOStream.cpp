#include "IOStream.h"

QSharedPointer<users> IOStream::loadUsers(const QString &path) {
  QJsonArray dataObject = readJsonFile(path)["users"].toArray();

  QSharedPointer<users> list(new users());

  QJsonArray::const_iterator it;

  for (it = dataObject.begin(); it != dataObject.end(); ++it) {
    list->addUser(fromJsonToUser((*it).toObject()));
  }

  return list;
}

QSharedPointer<library> IOStream::loadLibrary(const QString &path) {
  QJsonArray dataObject = readJsonFile(path)["library"].toArray();

  QSharedPointer<library> list(new library());

  QJsonArray::const_iterator it;

  for (it = dataObject.begin(); it != dataObject.end(); it++) {
    list->addPublication(fromJsonToPubblication((*it).toObject()));
  }

  return list;
}

QSharedPointer<loans> IOStream::loadLoans(
    const QSharedPointer<library> libraryList,
    const QSharedPointer<users> userList, const QString &path) {
  QJsonArray dataObject = readJsonFile(path)["loans"].toArray();

  QSharedPointer<loans> supp(new loans());

  QJsonArray::const_iterator it;

  for (it = dataObject.begin(); it != dataObject.end(); it++) {
    supp->addLoan(fromJsonToLoan((*it).toObject(), libraryList, userList));
  }

  return supp;
}

QJsonObject IOStream::readJsonFile(const QString &path) const {
  QFile file;
  file.setFileName(path);

  if (file.open(QIODevice::ReadOnly)) {
    QString fileContent = file.readAll();

    file.close();

    return QJsonDocument::fromJson(fileContent.toUtf8()).object();
  }

  return QJsonDocument().object();
}

void IOStream::writeJsonFile(const QJsonDocument &dataObject,
                             const QString &path) const {
  QFile file;
  file.setFileName(path);
  if (file.open(QIODevice::WriteOnly)) {
    file.write(dataObject.toJson());
    file.close();
  }
}

void IOStream::writeCsvFile(const loans &lends, const QString &path) {
  QFile file;
  file.setFileName(path);
  if (file.open(QIODevice::WriteOnly)) {
    QTextStream out(&file);

    for (int i = 0; i < lends.showLoanNumber(); ++i) {
      toCsv(lends.showLoan(i), out);
    }
    file.close();
  }
}

void IOStream::writeCsvFile(const library &books, const QString &path) {
  QFile file;
  file.setFileName(path);
  if (file.open(QIODevice::WriteOnly)) {
    QTextStream out(&file);

    for (int i = 0; i < books.showPublicationNumber(); ++i) {
      toCsv(books.showPublication(i), out);
    }
    file.close();
  }
}

QSharedPointer<account> IOStream::fromJsonToUser(
    const QJsonObject &dataObject) {
  QSharedPointer<userinfo> info(new userinfo(
      dataObject["registration"].toString(), dataObject["name"].toString(),
      dataObject["surname"].toString(),
      QDate::fromString(dataObject["date"].toString(), "yyyy/MM/dd"),
      dataObject["class"].toString(), dataObject["cellnumber"].toString(),
      dataObject["email"].toString()));
  QSharedPointer<account> user(new account(info));

  if (!dataObject["username"].isNull() &&
      dataObject["username"].toString() != "") {
    user->setUser(dataObject["username"].toString(),
                  dataObject["password"].toString());
  }

  if (!dataObject["type"].isNull()) {
    user->setPermission(dataObject["type"].toInt(),
                        dataObject["maxloan"].toInt());
  }

  return user;
}

QSharedPointer<publication> IOStream::fromJsonToPubblication(
    const QJsonObject &dataObject) {
  QSharedPointer<publication_permission> permission =
      QSharedPointer<publication_permission>();

  if (!dataObject["permissionType"].isNull())
    permission = QSharedPointer<publication_permission>(
        new publication_permission(dataObject["permissionType"].toInt(),
                                   dataObject["copynumber"].toInt()));

  if (dataObject["type"].toString() == "book") {
    QSharedPointer<book> tome(new book(
        dataObject["author"].toString(), dataObject["plot"].toString(),
        dataObject["title"].toString(), dataObject["publishing"].toString(),
        dataObject["isbn"].toString(), dataObject["subtitle"].toString(),
        dataObject["genre"].toString(),
        QDate::fromString(dataObject["releaseDate"].toString(), "yyyy/MM/dd"),
        dataObject["place"].toString(), dataObject["collection"].toString(),
        dataObject["edition"].toInt(), dataObject["numberOfPage"].toInt(),
        dataObject["year"].toInt()));

    if (!dataObject["permissionType"].isNull()) tome->setPermission(permission);

    return tome;
  }
  if (dataObject["type"].toString() == "periodic") {
    QSharedPointer<periodic> magazine(new periodic(
        dataObject["ID"].toString(), dataObject["birthyear"].toInt(),
        dataObject["number"].toInt(), dataObject["title"].toString(),
        dataObject["publishing"].toString(), dataObject["isbn"].toString(),
        QDate::fromString(dataObject["releaseDate"].toString(), "yyyy/MM/dd"),
        dataObject["subtitle"].toString(), dataObject["genre"].toString()));
    if (!dataObject["permissionType"].isNull())
      magazine->setPermission(permission);

    return magazine;
  }

  return QSharedPointer<publication>();
}

QSharedPointer<loan> IOStream::fromJsonToLoan(
    const QJsonObject &dataObject, const QSharedPointer<library> libraryList,
    const QSharedPointer<users> userList) const {
  QSharedPointer<account> loanUser = QSharedPointer<account>();
  QSharedPointer<publication> loanPublication = QSharedPointer<publication>();

  if (!dataObject["usersID"].isNull())
    loanUser = userList->showUser(dataObject["usersID"].toString());

  if (!dataObject["publicationID"].isNull())
    loanPublication =
        libraryList->showPublication(dataObject["publicationID"].toString());

  if (!loanUser.isNull())
    if (!loanUser->p_permission()->makeLoan())
      loanUser = QSharedPointer<account>();

  if (!loanPublication.isNull())
    if (!loanPublication->p_permission()->makeLoan())
      loanPublication = QSharedPointer<publication>();

  return QSharedPointer<loan>(new loan(
      loanUser, loanPublication,
      QDate::fromString(dataObject["startDate"].toString(), "yyyy/MM/dd"),
      QDate::fromString(dataObject["endDate"].toString(), "yyyy/MM/dd"),
      dataObject["finish"].toBool()));
}

void IOStream::writeJsonFromUser(const QSharedPointer<users> userList,
                                 const QString &path) const {
  QJsonArray dataArray;

  for (int i = 0; i < userList->showUserNumber(); ++i) {
    dataArray.append(toJson(userList->showUser(i)));
  }

  QJsonObject dataObject;

  dataObject["users"] = dataArray;

  writeJsonFile(QJsonDocument(dataObject), path);
}

void IOStream::writeJsonFromLibrary(
    const QSharedPointer<library> publicationList, const QString &path) const {
  QJsonArray dataArray;

  for (int i = 0; i < publicationList->showPublicationNumber(); ++i) {
    dataArray.append(toJson(publicationList->showPublication(i)));
  }

  QJsonObject dataObject;

  dataObject["library"] = dataArray;

  writeJsonFile(QJsonDocument(dataObject), path);
}

void IOStream::writeJsonFromLoans(const QSharedPointer<loans> loanList,
                                  const QString &path) const {
  QJsonArray dataArray;

  for (int i = 0; i < loanList->showLoanNumber(); ++i) {
    dataArray.append(toJson(loanList->showLoan(i)));
  }

  QJsonObject dataObject;

  dataObject["loans"] = dataArray;

  writeJsonFile(QJsonDocument(dataObject), path);
}

QJsonObject IOStream::toJson(const QSharedPointer<account> user) const {
  QJsonObject dataObject;
  QSharedPointer<userinfo> info = user->p_info();

  dataObject["registration"] = info->showRegistrationNumber();
  dataObject["name"] = info->showName();
  dataObject["surname"] = info->showSurname();
  dataObject["date"] = info->showBirthdate().toString("yyyy/MM/dd");
  dataObject["class"] = info->showClass();
  dataObject["cellnumber"] = info->showCellNumber();
  dataObject["email"] = info->showEmail();

  QSharedPointer<username> name = user->p_user();

  if (!name.isNull()) {
    dataObject["username"] = name->showUser();
    dataObject["password"] = name->showPass();
  }

  QSharedPointer<account_permission> permission = user->p_permission();

  if (!permission.isNull()) {
    dataObject["type"] = permission->showType();
    dataObject["maxloan"] = permission->showMaxLoan();
  }

  return dataObject;
}

QJsonObject IOStream::toJson(
    const QSharedPointer<publication> publicationList) const {
  QJsonObject dataObject;
  QSharedPointer<publication_permission> permission =
      publicationList->p_permission();

  if (!permission.isNull()) {
    dataObject["permissionType"] = permission->showType();
    dataObject["copynumber"] = permission->showCopyNumber();
  }

  dataObject["title"] = publicationList->showTitle();
  dataObject["publishing"] = publicationList->showPublishing();
  dataObject["isbn"] = publicationList->showISBN_13();
  dataObject["subtitle"] = publicationList->showSubtitle();
  dataObject["genre"] = publicationList->showGenre();
  dataObject["releaseDate"] =
      publicationList->showReleaseDate().toString("yyyy/MM/dd");

  QSharedPointer<book> tome = qSharedPointerDynamicCast<book>(publicationList);

  if (!tome.isNull()) {
    dataObject["type"] = "book";
    dataObject["author"] = tome->showAuthor();
    dataObject["plot"] = tome->showPlot();
    dataObject["place"] = tome->showPlace();
    dataObject["collection"] = tome->showCollection();
    dataObject["edition"] = tome->showEdition();
    dataObject["numberOfPage"] = tome->showPages();
    dataObject["year"] = tome->showYear();
  }

  QSharedPointer<periodic> periodical =
      qSharedPointerDynamicCast<periodic>(publicationList);

  if (!periodical.isNull()) {
    dataObject["type"] = "periodic";
    dataObject["ID"] = periodical->showID_number();
    dataObject["birthyear"] = periodical->showBirthYear();
    dataObject["number"] = periodical->showNumber();
  }

  return dataObject;
}

QJsonObject IOStream::toJson(const QSharedPointer<loan> loanList) const {
  QJsonObject dataObject;

  if (!loanList->p_user().isNull())
    dataObject["usersID"] =
        loanList->p_user()->p_info()->showRegistrationNumber();
  if (!loanList->p_title().isNull())
    dataObject["publicationID"] = loanList->p_title()->showIdentification();
  dataObject["startDate"] = loanList->showStartDate().toString("yyyy/MM/dd");
  dataObject["endDate"] = loanList->showEndDate().toString("yyyy/MM/dd");
  dataObject["finish"] = loanList->isFinish();

  return dataObject;
}

IOStream::IOStream()
    : localPath(QStandardPaths::writableLocation(
          QStandardPaths::AppLocalDataLocation)) {
  localPath.setPath(QDir::currentPath());
  localPath = utility::fusePath(localPath, "LBook");

  if (localPath.exists())
    loadSettings();
  else
    QDir().mkpath(localPath.absolutePath());
}

bool IOStream::firstStart() const {
  if (sharedPath == QDir()) return true;
  return false;
}

bool IOStream::setSharedDir() { return setSharedDir(localPath.absolutePath()); }

bool IOStream::setSharedDir(const QString &path) {
  if (QDir(path).exists()) {
    sharedPath = path;
    saveSettings();
    return true;
  }

  return false;
}

void IOStream::loadSettings() {
  QJsonObject dataObject =
      readJsonFile(utility::fusePath(localPath, "settings.json"));
  if (!dataObject["sharedPath"].isNull())
    sharedPath = dataObject["sharedPath"].toString();
}

dataCollector IOStream::loadData() {
  return loadData(sharedPath.absolutePath());
}

dataCollector IOStream::loadData(const QString &path) {
  QSharedPointer<users> usersList =
      loadUsers(utility::fusePath(path, "users.json"));

  QSharedPointer<library> libraryList =
      loadLibrary(utility::fusePath(path, "library.json"));

  QSharedPointer<loans> loansList =
      loadLoans(libraryList, usersList, utility::fusePath(path, "loans.json"));

  return dataCollector(libraryList, usersList, loansList);
}

void IOStream::saveSettings() {
  QJsonObject dataObject;

  dataObject["sharedPath"] = sharedPath.absolutePath();

  writeJsonFile(QJsonDocument(dataObject),
                utility::fusePath(localPath, "settings.json"));
}

void IOStream::saveData(const dataCollector &data) const {
  saveData(data, sharedPath.absolutePath());
}

void IOStream::saveData(const dataCollector &data, const QString &path) const {
  writeJsonFromUser(data.p_accounts(), utility::fusePath(path, "users.json"));
  writeJsonFromLibrary(data.p_publications(),
                       utility::fusePath(path, "library.json"));
  writeJsonFromLoans(data.p_loans(), utility::fusePath(path, "loans.json"));
}

bool IOStream::switchTranslator(QTranslator &translator) const {
  qApp->removeTranslator(&translator);

  QString path = utility::fusePath(qApp->applicationDirPath(), "languages");

  QString newLanguage = QLocale().name();
  newLanguage.truncate(newLanguage.lastIndexOf('_'));

  if (translator.load(
          utility::fusePath(path, QString("%1.qm").arg(newLanguage)))) {
    qApp->installTranslator(&translator);
    return true;
  }

  path = utility::fusePath(sharedPath, "languages");

  if (translator.load(
          utility::fusePath(path, QString("%1.qm").arg(newLanguage)))) {
    qApp->installTranslator(&translator);
    return true;
  }

  return false;
}

void IOStream::toCsv(const QSharedPointer<loan> lend, QTextStream &out) {
  out << lend->p_user()->p_info()->showName() << ";"
      << lend->p_user()->p_info()->showSurname() << ";"
      << lend->p_user()->p_info()->showClass() << ";"
      << lend->p_title()->showTitle() << ";" << lend->showCharStartDate() << ";"
      << lend->showCharEndDate() << "\n";
}

void IOStream::toCsv(const QSharedPointer<publication> publicatio,
                     QTextStream &out) {
  out << publicatio->showTitle() << ";" << publicatio->showSubtitle() << ";";

  QSharedPointer<book> manual = qSharedPointerDynamicCast<book>(publicatio);
  if (!manual.isNull()) {
    out << manual->showAuthor() << manual->showEdition() << manual->showGenre()
        << ";";
  }

  QSharedPointer<periodic> magazine =
      qSharedPointerDynamicCast<periodic>(publicatio);
  if (!magazine.isNull()) {
    out << magazine->showNumber() << ";" << magazine->showGenre() << ";"
        << magazine->showISSN() << ";";
  }

  out << publicatio->showISBN_13() << "\n";
}

void IOStream::removeLocal() { localPath.removeRecursively(); }
