#ifndef DATACOLLECTOR_H
#define DATACOLLECTOR_H

#include "library.h"
#include "loans.h"
#include "publication.h"
#include "users.h"

class dataCollector {
 private:
  QSharedPointer<library> publications;
  QSharedPointer<users> accounts;
  QSharedPointer<loans> lending;

 public:
  dataCollector();
  dataCollector(const QSharedPointer<library>, const QSharedPointer<users>,
                const QSharedPointer<loans>);

  QSharedPointer<library> p_publications() const;
  QSharedPointer<users> p_accounts() const;
  QSharedPointer<loans> p_loans() const;

  void operator=(const dataCollector &);
};

#endif  // DATAMANAGER_H
