#include "account.h"

account::account(const QSharedPointer<userinfo> info,
                 const QSharedPointer<account_permission> authorization,
                 const QSharedPointer<username> name)
    : information(info), user(name), permission(authorization) {}

void account::setUser(const QString &name, const QString &pass) {
  user.QSharedPointer::reset(new username(name, pass));
}

void account::setUser(const QSharedPointer<username> name) { user = name; }

void account::setPermission(const unsigned int &type,
                            const unsigned int &maxloan,
                            const unsigned int lockedloan) {
  permission.QSharedPointer::reset(
      new account_permission(type, maxloan, lockedloan));
}

void account::setPermission(
    const QSharedPointer<account_permission> authorization) {
  permission = authorization;
}

QSharedPointer<username> account::p_user() const { return user; }

QSharedPointer<userinfo> account::p_info() const { return information; }

QSharedPointer<account_permission> account::p_permission() const {
  return permission;
}
