#ifndef TEXT_TABLE_H
#define TEXT_TABLE_H

#include <iostream>
#include <map>
#include <iomanip>
#include <vector>
#include <string>
#include "HelperString.h"

class TextTable {

public:
    typedef std::vector< std::string > Row;
    TextTable(char horizontal = '-', char vertical = '|', char corner = '+') :
        _horizontal(horizontal),
        _vertical(vertical),
        _corner(corner)
    {}

    char vertical() const
    {
        return _vertical;
    }

    char horizontal() const
    {
        return _horizontal;
    }

    void add(std::string const & content)
    {
        _current.push_back(content);
    }

    void endOfRow()
    {
        _rows.push_back(_current);
        _current.assign(0, "");
    }

    template <typename Iterator>
    void addRow(Iterator begin, Iterator end)
    {
        for (auto i = begin; i != end; i++) {
            add(*i);
        }
        endOfRow();
    }

    std::vector< Row > const & rows() const
    {
        return _rows;
    }

    std::string ruler(int i) const
    {
        std::string result;
        unsigned int maxSize = 0;
        unsigned int k = i;
        if (k == 0)
        {
            maxSize = _rows[k].size();
        }
        else if (k == _rows.size())
        {
            maxSize = _rows[_rows.size()-1].size();
        }
        else
        {
            maxSize = _rows[k].size() > _rows[k - 1].size() ? _rows[k].size() : _rows[k - 1].size();
        }
        result += _corner;
        for (unsigned int j = 0; j< maxSize; j++)
        {
            result += repeat(_width[j], _horizontal);
            result += _corner;
        }
        return result;
    }

    int width(unsigned i) const
    {
        return _width[i];
    }

public:
    char _horizontal;
    char _vertical;
    char _corner;
    Row _current;
    std::vector< Row > _rows;
    std::vector< unsigned > mutable _width;

    static std::string repeat(unsigned times, char c)
    {
        std::string result;
        for (; times > 0; --times)
            result += c;
        return result;
    }

    unsigned columns() const
    {
        unsigned int maxSize = 0;
        for (auto& r : _rows)
        {
            if (r.size() > maxSize)
                maxSize = r.size();
        }
        return maxSize;
    }

    void determineWidths() const
    {
        _width.assign(columns(), 0);
        for (auto& row:_rows)
        {
            for (unsigned i = 0; i < row.size(); i++)
            {
#ifdef __linux
                std::string str="";
                size_t len;
                char* retp=hl::utf82gb2312(row[i], len);
                if(retp)
                    str = retp;
                _width[i] = _width[i] > str.length() ? _width[i] : str.length();
#else
                _width[i] = _width[i] > row[i].length() ? _width[i] : row[i].length();
#endif
            }
        }
    }
};

std::ostream & operator<<(std::ostream & stream, TextTable const & table);

#endif
