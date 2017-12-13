/****************************************************************************
Реализуйте структуру данных типа "множество строк" на основе
динамической хеш-таблицы с открытой адресацией. Хранимые строки непустые
и состоят из строчных латинских букв. Начальный размер таблицы должен
быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в
случае, когда коэффициент заполнения таблицы достигает 3/4.

Хеш-функцию строки реализуйте с помощью вычисления значения многочлена
методом Горнера.

Структура данных должна поддерживать операции добавления строки в
множество, удаления строки из множества и проверки принадлежности данной
строки множеству.
****************************************************************************/

/****************************************************************************

Для разрешения коллизий используйте квадратичное пробирование.
i-ая проба
g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.

*Формат входных данных*

Каждая строка входных данных задает одну операцию над множеством. Запись
операции состоит из типа операции и следующей за ним через пробел
строки, над которой проводится операция.

Тип операции -- один из трех символов:
 + означает добавление данной строки в множество;
 - означает удаление строки из множества;
 ? означает проверку принадлежности данной строки множеству.

При добавлении элемента в множество НЕ ГАРАНТИРУЕТСЯ, что он отсутствует
в этом множестве. При удалении элемента из множества НЕ ГАРАНТИРУЕТСЯ,
что он присутствует в этом множестве.

*Формат выходных данных*

Программа должна вывести для каждой операции одну из двух строк OK или
FAIL, в зависимости от того, встречается ли данное слово в нашем
множестве.

+-----------+--------+
| stdin     | stdout |
+-----------+--------+
| + hello   | OK     |
| + bye     | OK     |
| ? bye     | OK     |
| + bye     | FAIL   |
| - bye     | OK     |
| ? bye     | FAIL   |
| ? hello   | OK     |
+-----------+--------+

****************************************************************************/

#include <vector>
#include <string>
#include <iostream>

using namespace std;

const int InitialHashTableSize = 30;
const int HashParameter = 28;

int Hash( const string &data, int m, int probe ) {
    int hash = 0;
    for ( int i = 0; i < data.length(); ++i )
        hash = ( hash * HashParameter + data[i] ) % m;
    int c1 = 1;
    int c2 = 1;
    return ( hash + c1 * probe + c2 * probe * probe ) % m;
}

struct CHashTableNode {
    string Data;
    bool isDeleted;
    CHashTableNode( const string &data ) :
        Data( data ),
        isDeleted( false )
    {};
};

class CHashTable {
public:
    CHashTable() {
        table.assign( InitialHashTableSize, NULL );
        count = 0;
    }
    bool Has( const string &key ) const {
        for ( int probe = 0; probe < table.size(); ++probe ) {
            int hash = Hash( key, table.size(), probe );
            if ( table[hash] != NULL && table[hash]->Data == key && !table[hash]->isDeleted )
                return true;
            else if ( table[hash] == NULL )
                break;
        }
        return false;
    }

    bool Add( const string &key ) {
        int hash;
        int insert_place = -1;
        for ( int probe = 0; probe < table.size(); ++probe ) {
            hash = Hash( key, table.size(), probe );
            if ( table[hash] != NULL && table[hash]->Data == key && !table[hash]->isDeleted )
            	return false;
            else if ( table[hash] == NULL ) {
			if ( insert_place == -1 )
                    		insert_place = hash;
				break;
			} else if ( table[hash]->isDeleted )
				if (insert_place == -1)
                    			insert_place = hash;
        }
        if ( insert_place == -1 )
        	return false;
        if ( table[insert_place] != NULL )
        	delete table[insert_place];
        table[insert_place] = new CHashTableNode( key );
        ++count;
        if ( count >= table.size() * 3 / 4 )
            Rehash();
        return true;
    }

    bool Delete( const string &key ) {
        int hash;
        for ( int probe = 0; probe < table.size(); ++probe ) {
            hash = Hash( key, table.size(), probe );
            if ( table[hash] != NULL && table[hash]->Data == key && !table[hash]->isDeleted )
                break;
            else if ( table[hash] == NULL )
                return false;
        }
        if ( table[hash] == NULL )
            return false;
        table[hash]->isDeleted = true;
        --count;
        return true;
    }

private:
    vector<CHashTableNode*> table;
    int count;
    void Rehash() {
        vector<CHashTableNode*> old_table = table;
        table.assign(table.size() * 2, NULL);
        count = 0;
        for ( int i = 0; i < old_table.size(); ++i ) {
            if ( old_table[i] != NULL && !old_table[i]->isDeleted ) {
                Add( old_table[i]->Data );
                delete old_table[i];
            }
        }
    }
};

int main() {
    CHashTable strings;
    while (true) {
        if ( cin.eof() )
            break;
        char k;
        string str;
        cin >> k >> str;
        if ( str.empty() )
            break;
        if ( k == '+' )
            cout << ( strings.Add( str ) ? "OK" : "FAIL" ) << endl;
        else if ( k == '-' )
            cout << ( strings.Delete( str ) ? "OK" : "FAIL" ) << endl;
        else if ( k == '?' )
            cout << ( strings.Has( str ) ? "OK" : "FAIL" ) << endl;
    }
    return 0;
}
