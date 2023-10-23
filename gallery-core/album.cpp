#include "album.h"

Album::Album(const QString& name):
    mId{-1},
    mName{name}
{
}

void Album::setName(const QString& name)
{
    mName = name;
}

void Album::setId(int id)
{
    mId = id;
}

QString Album::name() const
{
    return mName;
}


int Album::id() const
{
    return mId;
}

