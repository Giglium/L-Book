#ifndef ACCOUNT_PERMISSION_H
#define ACCOUNT_PERMISSION_H

class account_permission {
 private:
  unsigned int type; /* 0:ban, 1:student, 2:professor, 3:librarian */
  unsigned int maxloan;
  unsigned int lockedloan;

  void setLockedLoan(const unsigned int &);

 public:
  account_permission(const unsigned int &, const unsigned int &,
                     const unsigned int = 0);

  void setType(const unsigned int &);
  bool setMaxLoan(const unsigned int &);

  bool makeLoan();
  bool returnLoan();

  int showType() const;
  int showMaxLoan() const;
  int showFreedomLoan() const;
  int showLockedLoan() const;
};

#endif  // ACCOUNT_PERMISSION_H
