#include <assert.h>

/** Standard flags */
#define FINIT (1 << 0)
#define FCLOSED (1 << 1)

/**
 * Returns 1 if FINIT flag is set.
 * NOTE: struct x must have .flags field!
 */
#define ISINIT(X) (X.flags & FINIT)


/** Set FLAG on struct X */
#define FSET(X, FLAG) (X.flags |= FLAG)

/** Unset FLAG on struct X */
#define FUSET(X, FLAG) (X.flags &= ~FLAG)


