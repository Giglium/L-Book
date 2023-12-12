#include "dataCollector.h"

dataCollector::dataCollector() : publications(), accounts(), lending() {}

dataCollector::dataCollector(const QSharedPointer<library> libraryList,
                             const QSharedPointer<users> usersList,
                             const QSharedPointer<loans> loansList)
    : publications(libraryList), accounts(usersList), lending(loansList) {}

QSharedPointer<library> dataCollector::p_publications() const {
  return publications;
}

QSharedPointer<users> dataCollector::p_accounts() const { return accounts; }

QSharedPointer<loans> dataCollector::p_loans() const { return lending; }

void dataCollector::operator=(const dataCollector &coll) {
  publications = coll.p_publications();
  accounts = coll.p_accounts();
  lending = coll.p_loans();
}
