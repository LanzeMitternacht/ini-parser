# Техническая документация по использованию библиотеки

## 1. Директива включения и алиасы

В данной библиотеке используются заголовочные файлы `<unordered_map>`, `<string>`, и `<fstream>`. 
Существует один алиас для `std::unordered_map<std::string, std::unordered_map<std::string, std::string>>`, который называется **DataMap**. Он хранит данные в формате: секция -> ключ -> значение.

## 2. Использование библиотеки
Чтобы использовать функциональность парсера, необходимо инициализировать две переменные: класс `IniParser` и структуру `ParseResult`.

# IniParser.
Класс `IniParser` предназначен для парсинга INI-файлов и извлечения значений по секциям и ключам. Он содержит следующие методы:

### `parseFile`

- **Описание:** Парсит INI-файл и сохраняет данные в `parseData`.
- **Параметры:**
  - `filepath` (const std::string&): Путь к INI-файлу.
- **Возвращает:** `ParseResult` — Статус выполнения операции.
- **Примечание:** При каждом вызове предыдущие данные в `parseData` удаляются. Если необходимо сохранить предыдущие результаты, их следует скопировать в другую переменную.

### `getValue`

- **Описание:** Извлекает значение по заданной секции и ключу.
- **Параметры:**
  - `section` (const std::string&): Название секции.
  - `key` (const std::string&): Название ключа.
  - `value` (std::string&): Переменная для сохранения найденного значения.
- **Возвращает:** `ParseResult` — Статус выполнения операции.

### `isIniFile`

- **Описание:** Проверяет, имеет ли файл расширение `.ini`.
- **Параметры:**
  - `filepath` (const std::string&): Путь к файлу.
- **Возвращает:** `bool` — `true`, если файл имеет расширение `.ini`, иначе `false`.

### `trim`

- **Описание:** Удаляет начальные и конечные пробелы и табуляции из строки.
- **Параметры:**
  - `str` (const std::string&): Исходная строка.
- **Возвращает:** `std::string` — Обрезанная строка.

### `getDataMap`

- **Описание:** Возвращает текущую **DataMap**, содержащую все спарсенные секции и ключи.
- **Возвращает:** `DataMap&` — Ссылка на `parseData`.

# ParseResult

- **Описание:** Структура, представляющая результат выполнения операций парсинга.
- **Поля:**
  - `errorCode` (enum): Статус выполнения:
    - `SUCCESS`: Операция завершена успешно.
    - `ERROR_FILE_TYPE`: Неверный тип файла.
    - `ERROR_READ_FILE`: Не удалось открыть файл.
    - `ERROR_SECTION_NOT_FIND`: Секция не найдена.
    - `ERROR_KEY_NOT_FIND`: Ключ не найден.
    - `ERROR_VALUE_NOT_FIND`: Значение не найдено.
  - `errorMessage` (std::string): Сообщение о результате выполнения.

## Пример обработки ошибок

```cpp
ParseResult result = parser.parseFile("config.ini");
if (!result.isSuccess()) {
    std::cerr << "Error (" << result.errorCode << "): " << result.errorMessage << std::endl;
}
```
## Пример использования

Вывод `DataMap` в терминал:
```cpp
IniParser parser;
ParseResult result = parser.parseFile("config.ini");
 if (result.isSuccess()) {
     DataMap& data = parser.getDataMap();
     for (const auto& section : data) {
         std::cout << "[" << section.first << "]" << std::endl;
         for (const auto& pair : section.second) {
             std::cout << pair.first << " = " << pair.second << std::endl;
         }
         std::cout << std::endl;
     }    
 }
 else {
     std::cerr << "Error (" << result.errorCode << "): " << result.errorMessage << std::endl;
 }
```
Поиск и вывод в терминал определенное значение из секции->ключ:
```cpp
IniParser parser;
ParseResult result = parser.parseFile("config.ini");

if (result.isSuccess()) {
    std::string section = "User";
    std::string key = "Name";
    std::string value;
    ParseResult valueResult = parser.getValue(section, key, value);
    if (valueResult.isSuccess()) {
        std::cout << "Value found for " << key << " in section " << section << " = " << value << std::endl;
    }
    else {
        std::cerr << "Error: " << valueResult.errorMessage << std::endl;
    }
}
else {
    std::cerr << "Error (" << result.errorCode << "): " << result.errorMessage << std::endl;
}
```
