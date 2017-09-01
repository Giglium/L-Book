#include "publication_permission.h"

void publication_permission::setLockedCopy( const unsigned int &locked ) {
    if( locked > copynumber )
        lockedcopy = copynumber;
    else
        lockedcopy = locked;
}

publication_permission::publication_permission( const bool &variety, const unsigned int &max, const unsigned int locked )
                       :type( variety ) {
    if( locked > max )
        copynumber = locked;
    else
        copynumber = max;
    setLockedCopy( locked );
}

void publication_permission::setType( const bool &variety ) {
    type = variety;
}

bool publication_permission::setCopyNumber( const unsigned int &max ) {
    if ( max > lockedcopy && type ) {
        copynumber = max;
        return true;
    }
    copynumber = lockedcopy;
    return false;
}

bool publication_permission::makeLoan() {
    if( type && copynumber - lockedcopy ) {
        lockedcopy++;
        return true;
    }
    return false;
}

bool publication_permission::returnLoan() {
    if( lockedcopy ) {
        lockedcopy --;
        return true;
    }
    return false;
}

int publication_permission::showType() const {
    if( type ) {
        if( copynumber == lockedcopy ) return 1;
        return 2;
    }
    return 0;
}

int publication_permission::showCopyNumber() const {
    return copynumber;
}

int publication_permission::showFreedomCopy() const {
    return copynumber-lockedcopy;
}

int publication_permission::showLockedCopy() const {
    return lockedcopy;
}
