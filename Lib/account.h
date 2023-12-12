#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QSharedPointer>
#include <QString>

#include "account_permission.h"
#include "userinfo.h"
#include "username.h"

class account {
 private:
  QSharedPointer<userinfo> information;
  QSharedPointer<username> user;
  QSharedPointer<account_permission> permission;

 public:
  account(const QSharedPointer<userinfo>,
          const QSharedPointer<account_permission> =
              QSharedPointer<account_permission>(),
          const QSharedPointer<username> = QSharedPointer<username>());

  void setUser(const QString &, const QString &);
  void setUser(const QSharedPointer<username>);
  void setPermission(const unsigned int &, const unsigned int &,
                     const unsigned int = 0);
  void setPermission(const QSharedPointer<account_permission>);

  QSharedPointer<username> p_user() const;
  QSharedPointer<userinfo> p_info() const;
  QSharedPointer<account_permission> p_permission() const;
};

#endif  // ACCOUNT_H
