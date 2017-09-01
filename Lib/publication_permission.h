#ifndef PUBLICATION_PERMISSION_H
#define PUBLICATION_PERMISSION_H

class publication_permission
{
private:
    bool type; //0 sola lettura; 1 disponibile
    unsigned int copynumber;
    unsigned int lockedcopy;

    void setLockedCopy( const unsigned int & );

public:
    publication_permission( const bool &, const unsigned int &, const unsigned int =0);

    void setType ( const bool & );
    bool setCopyNumber( const unsigned int & );

    bool makeLoan();
    bool returnLoan();

    int showType() const; /* 0 Read only in the library; 1 Not Avalidable; 2 Avalidable */
    int showCopyNumber() const;
    int showFreedomCopy() const;
    int showLockedCopy() const;
};

#endif // PUBLICARION_BOOK_H
