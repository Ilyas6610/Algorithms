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

Для разрешения коллизий используйте двойное хеширование.

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

#include <iostream>

int main()
{
    return 0;
}

