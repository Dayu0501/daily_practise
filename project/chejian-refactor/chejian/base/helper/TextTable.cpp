#include "TextTable.h"

std::ostream & operator<<(std::ostream & stream, TextTable const & table)
{
    table.determineWidths();
    int i = 0;
    for (; i < table.rows().size();i++)
    {
        stream << table.ruler(i) << "\n";
        TextTable::Row const & row = table.rows()[i];
        stream << table.vertical();
        for (unsigned i = 0; i < row.size(); ++i)
        {
            std::string space = "";
#ifdef __linux
            std::string str="";
            size_t len;
            char* retp=hl::utf82gb2312(row[i], len);
            if(retp)
                str = retp;
            else
                str=row[i];
            len = str.length();
#else
            int len = row[i].length();
#endif
            for (unsigned int j = 0; j<table.width(i)-len; j++)
                space += " ";
            stream << std::setw(table.width(i)) << std::left << row[i] + space;
            stream << table.vertical();
        }
        stream << "\n";
    }
    stream << table.ruler(i) << "\n";
    return stream;
}
