#include <string>

// Find and Replace from stackoverflow returns count of replaces made.
template<class T>
int inline findAndReplace(T& source, const T& find, const T& replace)
{
    int num=0;
    T::size_type fLen = find.size();
    T::size_type rLen = replace.size();
    for (T::size_type pos=0; (pos=source.find(find, pos))!=T::npos; pos+=rLen)
    {
        num++;
        source.replace(pos, fLen, replace);
    }
    return num;
}