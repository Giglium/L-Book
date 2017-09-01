#include "account_permission.h"

void account_permission::setLockedLoan( const unsigned int &locked ) {
    if( locked > maxloan )
        lockedloan = maxloan;
    else
        lockedloan = locked;
}

account_permission::account_permission( const unsigned int &type, const unsigned int &max, const unsigned int locked )
                   :type( type ), maxloan( max ) {
    if( !type )
        maxloan = locked;
    setLockedLoan( locked );
}

void account_permission::setType( const unsigned int &variety ) {
    type = variety;
    if( !type )
        maxloan = lockedloan;
}

bool account_permission::setMaxLoan( const unsigned int &max ) {
    if ( max > lockedloan && type ) {
        maxloan = max;
        return true;
    }
    maxloan = lockedloan;
    return false;
}

bool account_permission::makeLoan() {
    if( maxloan - lockedloan ) {
        lockedloan ++;
        return true;
    }
    return false;
}

bool account_permission::returnLoan() {
    if( lockedloan ) {
        lockedloan --;
        return true;
    }
    return false;
}

int account_permission::showType() const {
    return type;
}

int account_permission::showMaxLoan() const {
    return maxloan;
}

int account_permission::showFreedomLoan() const {
    return maxloan - lockedloan;
}

int account_permission::showLockedLoan() const {
    return lockedloan;
}
