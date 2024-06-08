# Virtual CPU(SPU)

### Описание

Процессор(виртуальная машина) может исполнять программы написанные на специальном языке, синтаксис которого будет изложен ниже.
Также процессор имеет отдельное видеоядро, которое позволяет выводить на экран чёрно-белые изображения.

#### Ассемблер
Эта часть проекта занимается трансляцией файла исходного кода в бинарный исполняемый файл, который может быть исполнен виртуальной машиной.
Так же ассемблер может генерировать отчёт о компиляции в виде файла листинга.

#### Дизассемблер
Эта программа преобразует бинарный код обратно в исходный код, написанный на языке, который может прочитать человек.

#### Процессор
Эта программа занимается исполнением скомпилированных программ.

### Сборка

#### Зависимости
В проекте используется библиотека [sfml](https://www.sfml-dev.org/index.php "sfml"). Установите её для работы с видеоядром виртуальной машины.

Для клонирования и сборки проекта склонируйте репозиторий следующей командой:

```bash
git clone --recurse-submodules https://github.com/dmitry131131/Simple_processor.git
```

После чего выполните сборку с помощью следующей команды:

```bash
make
```

Готово! 

### Использование

#### Ассемблер

Для запуска компиляции введите в командную строку `./asm` и имя файла с исходным кодом. Тогда ассемблер скомпилирует исходник в файл с именем исходника, но с другим расширением. Для компиляции в файл с другим именем или расширением следует использовать флаг `-o` и после него вписывать имя выходного файла.

```bash
./asm <имя_исходника> -o <имя_бинарника>
``` 

#### Дизассемблер

Для запуска дизассемблера нужно ввести в командную строку `./disasm` и имя бинарного файла.

```bash
./disasm <имя_бинарника>
```

#### Процессор

Для запуска исполнения программы нужно ввести команду `./proc` и имя бинарного файла с исполняемым кодом.

```bash
./proc <имя_бинарника>
```

### Синтаксис

Программа состоит из инструкций, каждая из которых должна быть записана на отдельной строке(включая аргументы).
Символом `;` обозначаются комментарии, они игнорируются ассемблером и служат только ради повышения удобства работы с кодом.

#### Инструкции

| Инструкция  | Аргументы                               | Описание                                                                            |
|-------------|-----------------------------------------|-------------------------------------------------------------------------------------|
| push        | Число, регистр или адрес ОЗУ            | Кладёт число в стек процессора                                                      |
| pop         | Регистр или адрес ОЗУ                   | Забирает число из стека и кладёт значение в регистр или в ОЗУ                       |
| hlt         | Нет аргументов                          | Останавливает программу и завершает работу процессора                               |
| in          | Нет аргументов                          | Читает число из стандартного потока ввода и кладёт его в стек                       |
| out         | Нет аргументов                          | Берёт число из стека и печатает его в стандартный поток вывода                      |
| add         | Нет аргументов                          | вычисляет сумму двух последних чисел из стека и возвращает результат в стек         |
| sub         | Нет аргументов                          | Вычисляет разность двух последних чисел из стека и результат возвращает в стек      |
| mul         | Нет аргументов                          | Умножает двух последних числа из стека и возвращает результат в стек                |
| div         | Нет аргументов                          | Вычисляет частное двух последних чисел из стека и возвращает результат в стек       |
| floor       | Нет аргументов                          | Конвертитует последнее число в стеке в целое путём отбрасывания дробной части       |
| sin         | Нет аргументов                          | Вычисляет синус последнего числа в стеке                                            |
| cos         | Нет аргументов                          | Вычисляет косинус последнего числа в стеке                                          |
| sqrt        | Адрес команды в байткоде или метка      | Вычисляет квадратный корень последнего числа в стеке                                |
| jmp         | Адрес команды в байткоде или метка      | Переходит на указанный адрес в байткоде и продолжает исполнение оттуда              |
| ja          | Адрес команды в байткоде или метка      | Переходит на указанный адрес если последнее число в стеке больше чем первое         |
| jae         | Адрес команды в байткоде или метка      | Переходит на указанный адрес если последнее число в стеке больше либо равно первому |
| jb          | Адрес команды в байткоде или метка      | Переходит на указанный адрес если последнее число в стеке меньше чем первое         |
| jbe         | Адрес команды в байткоде или метка      | Переходит на указанный адрес если последнее число в стеке меньше либо равно первому |
| je          | Адрес команды в байткоде или метка      | Переходит на указанный адрес если два последних числа в стеке равны                 |
| jne         | Адрес команды в байткоде или метка      | Переходит на указанный адрес если два последних числа в стеке не равны              |
| call        | Адрес команды в байткоде или метка      | Записывает адрес вызова в стек вызовов и переходит по указанному адресу             |
| ret         | Адрес команды в байткоде или метка      | Переходит по адресу равному значению последнего элемента в стеке вызовов            |

#### Метки
Метки - адреса внутри байткода, которые замаскированы под строки, что облегчает написание программ.
Метка обозначается одним словом с символом `:` перед ним.Например `:point` или `:function`.

#### Простейший пример программы
Вот простейший пример программы, которая считает сумму числа `3` и числа `5`:

```asm
push 3      ; кладёт число 3 в стек
push 5      ; кладёт число 5 в стек
add         ; складывает два последних числа в стеке и кладёт результат в стек
out         ; выводит результат из стека в консоль

hlt         ; завершает программу
```

#### Пример программы с использованием регистров
Программа считает результат вычитания введённого числа из числа `5`

```asm
in            ; ввод числа из консоли и отправка его в стек
pop rax       ; перемещение числа из стека в регистр rax

push 5        ; кладёт 5 в стек
push rax      ; кладёт значение из регистра rax в стек
sub           ; выполняет вычитание
out           ; выводит результат из стека в консоль

hlt           ; завершает программу
```

#### Пример программы с использованием оперативной памяти
Программа считает результат вычитания введённого числа из числа `5`

```asm
in            ; ввод числа из консоли и отправка его в стек
pop [1]       ; перемещение числа из стека в ячейку ОЗУ с адресом 1 

push 5        ; кладёт 5 в стек
push [1]      ; кладёт значение из ячейки ОЗУ с адресом 1 в стек
sub           ; выполняет вычитание
out           ; выводит результат из стека в консоль

hlt           ; завершает программу
```

#### Пример программы с использованием регистров и оперативной памяти:
Программа считает сумму введённого числа и числа `1`

```asm
in              ; ввод числа из консоли и отправка его в стек

push 1          ; кладёт число 1 в стек
pop rax         ; перемещение числа из стека в регистр rax
pop [rax+1]     ; перемещает число из стека в ячейку ОЗУ с адресом rax+1

push [2]        ; кладёт значение из ячейки ОЗУ с адресом 2 в стек(в нашем случае rax+1)
push 1          ; кладёт число 1 в стек
add             ; выполняет сложение
out             ; выводит результат из стека в консоль

hlt             ; завершает программу 

```

#### Пример программы с использованием меток и вызово функций
Программа вычисляет произведение введённого числа на 2 и выводит его на экран

```asm
call func   ; вызов функции с именем метки func
out         ; вывод последнего значения из стека

hlt         ; завершение работы

:func       ; объявление метки `func`
in          ; ввод числа из консоли и отправка его в стек
push 2      ; кладёт число 2 в стек
mul         ; выполняет умножение
ret         ; заканчивает выполнение функции и возвращается на адрес последнего вызова
```






