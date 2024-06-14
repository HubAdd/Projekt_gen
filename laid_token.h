#ifndef LAID_TOKEN_H
#define LAID_TOKEN_H

#include "engine.h"
class laid_Token
{
public:
    laid_Token();

    //metoda statyczna odpowiadająca za położenie tokenu na planszy
    static void laid (Engine & E);
};

#endif // LAID_TOKEN_H
