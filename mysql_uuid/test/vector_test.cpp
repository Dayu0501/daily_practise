#include <vector>
#include <iostream>

using namespace std;

typedef struct _DB_OPTION {
    bool dbLink;        // 是否关联数据库操作
    string dbFieldType; //数据库对应类型生成sql，需要符合数据语法
    string dbFieldDefaultValue; //数据库对应字段默认值
    string dbIndexName;
} DB_OPTION;

int main() {
    DB_OPTION ins = {true, "hello", "world"};

    cout << ins.dbFieldType << endl;

    cout << ins.dbFieldDefaultValue << endl;

    cout << ins.dbIndexName << endl;

    return 0;
}