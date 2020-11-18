//
// Created by yulichao on 2020/11/18.
//

#ifndef DESIGN_MODE_HEAD_H
#define DESIGN_MODE_HEAD_H

#include <vector>
#include <string>

using namespace std;

class EmployeeDO {};

class SqlConnection {
public:
	string ConnectionString;
};

class SqlDataReader;
class SqlCommand {
public:
	string CommandText;
	SqlDataReader*  ExecuteReader() {}
	void SetConnection(SqlConnection* hello) {}
};

class SqlDataReader {
public:
	bool Read() {}
};

#endif //DESIGN_MODE_HEAD_H
