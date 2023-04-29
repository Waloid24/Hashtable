# Хэш-таблица
## О проекте
В этом проекте реализована хэш-таблица с обработкой коллизий методом цепочек. В первой части проекта было проведено исследование эффективности нескольких хэш-функций. Во второй части проводилась оптимизация с помощью:
1) AVX-инструкций;
2) вставки фрагмента кода на ассемблере;
3) замены хэш-функцию на её ассемблерную версию;
4) алгоритмических оптимизаций.

## Теоретическое отступление
Для тех, кто впервые встретился с этим понятием, быстро объясню суть хэш-таблиц.

*Хэш-таблица* - это структура данных, в которой информация хранится парами: первый элемент - "ключ", второй - "значение". Поиск по хэш-таблице начинается с высчитывания значения хэш-функции от ключа. Полученное значение будет являться индексом ячейки в хэш-таблице, где лежит информация, соответствующая этому ключу. Пример, на котором всё станет ясно. Пусть есть дом, в нём 4 комнаты: "зелёная", "красная", "синяя", "серая". В "серой" комнате лежит гора алмазов, в "синей" - гора сапфиров, в "красной" - гора рубинов, в "зелёной" - гора изумрудов. Предположим, что функция, когда ей передаешь слово "зелёная", возвращает 0, когда передаёшь "красная" - возвращает 1, когда передаёшь "синяя" - возвращает 2, когда передеаёшь "серая" - возвращает 3. Эти значения и будут индексами в соответствующей хэш-таблице, которая будет иметь вид:
| 0 | 1 | 2  | 3 |
| ------------- | ------------- | ------------- | ------------- |
| "зелёная"  | "красная"  | "синяя"  | "серая"  |
| изумруды  | рубины  | сапфиры  | алмазы  |

То есть время поиска по ней будет составлять O(1) - просто назовите слово и получите всю информацию, которая ему соответствует. Для оптимизации поиска и используют хэш-таблицы.

## Часть 1 - исследование хэш-фукнций
### Hash function returning 1
Эта хэш-функция самая плохая из тех, что здесь представлены. Она всегда возвращает 1.

```c
size_t hashRet1 (char * word, size_t length)
{
    return 1;
}
```

### Hash function returning 1-st byte
Чуть лучше, чем предыдущая, возвращает 1-ый байт слова в кодировке ASCII. Для узкого круга задач она может подойти, но всё равно безумное количество коллизий.

```c
size_t hashFirstByte (char * word, size_t length)
{
    return word[0];
}
```

### HashLength
Возвращает длину слова. Хэш-функция так же плоха, но... она хотя бы представляет интерес в научном плане: теперь мы знаем среднюю длину слова в английском тексте.

```c
size_t hashLength (char * word, size_t length)
{
    return length;
}
```

### HashSum
Возвращает сумму ASCII-кодов букв слова. Ситуация становится лучше.

```c
size_t hashSumAscii (char * word, size_t length)
{
    size_t sum = 0;
    for (size_t i = 0; i < length; i++)
    {
        sum += word[i];
    }

    return sum;
}
```

### HashRol
Использует операцию rol. Вполне приемлемая функция, коллизий не так много по сравнению с предыдущими функциями.

```cтакая
size_t hashRol (char * word, size_t length)
{
    size_t h = 0;
    for (size_t i = 0; i < length; i++)
    {
        h = rol(h)^word[i];
    }
    return h;
}
```

### HashRor
Использует операцию ror. Несколько хуже предыдущей, но использовать в некоторых задачах можно.

```c
size_t hashRor (char * word, size_t length)
{
    size_t h = 0;
    for (size_t i = 0; i < length; i++)
    {
        h = ror(h)^word[i];
    }
    return h;
}
```

### HashBkdr
Реализация хэш-функции BKDR. Лучшая функция в этой подборке.

```c
size_t hashBkdr (char * word, size_t lengthWord)
{
    unsigned int seed = 131;
    unsigned int hash = 0;

    while (*word){
        hash = hash * seed + (*word++);
    }

    return (hash & 0x7FFFFFFF);
}
```

## Вывод

Графики распределения соответствующих хэш-функций.

![Распределение хэш-функций](./tables/graphs.png)

Лучше всего себя показала последняя хэш-функция - BKDR. Именно её из всех предложенных я бы советовал использовать при анализе текста, так как поиск по хэш-таблице, полученной с её использованием, будет достаточно быстрым.

## Часть 2 - оптимизация

### Как проводилась обработка

Для профилирования использовался perf, запись данных происходила с помощью команды
```
perf record -g --call-graph dwarf -F 99 <a name of the executable file>
```
Важно, чтобы имя исполняемого файла находилось после используемых флагов, так как в противном случае всё, что будет после имени учитываться при сборе информации не будет. Результат выводился с помощью команды
```
sudo perf report -g fractal
```
Время работы и прочая статистика собиралась с помощью команды
```
perf stat -r 1 <a name of the executable file>
```
Благодаря флагу `-r` выводится среднее значение и стандартное отклонение.


### Версия 0
Поправки: 
- размер хэш-таблицы составляет 107 ячеек;
- оставлена единственная хэш-функция hashBkdr;
- добавлен стресс-тест.

Стресс-тест представляет собой поиск всех слов из текста 1000 раз, т.е. это приблизительно 8.000.000 уникальных слов. Выбран именно этот способ измерений потому, что всегда искать лишь одно слово - значит постоянно работать только с одной ячейкой хэш-таблицы, тогда как нам нужна эффективность поиска в среднем. Также при этом количестве итераций случайная погрешность измерений минимальна и составляет `...%`. 

Скомпилируем программу:
```
make
```
и запустим с помощью профилировщика. Время работы программы: `5.75` секунд.

![Версия 0](./imgs/version0.png)

Время работы: 

Такие функции как `_start`, `__libc_start_main_impl` и `__libc_start_call_main` являются служебными и оптимизировать мы их не будем. Функция `main` работает всего лишь `1.63%` от общего времени, оптимизировать её тоже не имеет смысла, а вот к её потомкам приглядеться стоит.
Видим, что функция `htFind_0` - в дальнейшем "базовая версия функции поиска" - является самой горячей. Вот, как она выглядит (логирование и обработка ошибок на время тестирования отключены):

```c
struct listElement_t * htFind_0 (htMainElem hashtable, char * word)
{
    MY_ASSERT (word == nullptr, "There is no access to this word");

    size_t index = hashBkdr_0 (word) % hashtable.capacity;
    size_t lengthList = hashtable.htElem[index].size;
    listElement_t * listElem = hashtable.htElem[index].ptrToList->next; 

    size_t lengthWord = strlen (word);
    char * data = nullptr;

    for (size_t i = 0; i < lengthList; i++)
    {
        data = listElem->data;
        size_t lengthData = strlen (data);
        if (lengthData != lengthWord)
        {
            listElem = listElem->next;
            continue;
        }

        if (strcmp (data, word) == 0)
        {
            return listElem;
        }
        listElem = listElem->next;
    }

    return nullptr;
}
```

Из данных, которые мы получили с помощью perf, мы видим, что `1.67%` времени тратится на загрузку данных в переменные, счётчики циклов и прочее, а `98.33%` тратится на функций-потомков: `__strlen_avx2`, `__strcmp_avx2`, `hashBkdr_0`. Отметим, что мы не использовали в теле функции avx2 оптимизацию функций `strlen` и `strcmp`, это сделал компилятор, хоть мы и компилировали проект с флагом `-O0`. Попробуем оптимизировать работу этих инструкций.

### Версия 1

Поправки:
- добавлена предварительная обработка текста;
- все слова хранятся в 32-байтных областях.

Снова посмотрим на данные профилировщика с версией:

![Версия 1](./imgs/version1_mem_hash0_O0.png)

Время работы: `7.51` секунды. Результат ухудшился по сравнению с предыдущим экспериментом.

Видим, что самой горячей является функция `__memcmp_avx2_movbe`, попробуем её оптимизировать. Сначала реализуем её с помощью ассемблерной вставки:
```c
inline static int memcmpAsm (const void * str1, const void * str2, size_t length)
{
    int result = 0; 

    asm
    (
        ".intel_syntax noprefix\n\t"
        "cld\t\n"
        "mov %0, 1\t\n"
        "repe cmpsb\t\n"
        "je 1f\t\n"
        "jmp 2f\t\n"
        "1:\t\n"
        "xor %0, %0\t\n"
        "2:\t\n"
        ".att_syntax\t\n"
        : "=a" (result)
        : "S" (str1), "D" (str2), "c" (length)
    );

    return result;
}
```

Время работы: `19.51` секунды. 

Эта оптимизация себя не оправдала. Напишем фукнцию memcmp с помощью avx2 инструкций:

```c
static int memcmpAvx (const __m256i * ar1, const __m256i * ar2)
{
    __m256i cmp = _mm256_cmpeq_epi8 (*ar1, *ar2);
    unsigned int mask = (unsigned int) _mm256_movemask_epi8 (cmp);

    if (mask == 0xffffffff)
    {
        return 0;
    }
    return 1;
}
```

Время работы: `7.65` секунды. Опять неудачная оптимизация. 

Видимо, вызов нескольких функций `strlen` и функции `strcmp` для слов разной длины эффективнее, чем вызов функции `memcmp` для 32-байтного слова. Думаю, это происходит благодаря отсутствию множественного вызова функции `strcmp`, так как если сравниваемая пара не проходит проверку на одинаковую длину, то мы переходим к следующей. 

Итак, возвращаемся к исходной версии и продолжаем оптимизировать её.  

### Версия 2

Поправки:
- в списках хэш-таблицы храним длины слов.

Предыдущие рассуждения наталкивают на следующую мысль. Давайте предварительно обработаем текст так, чтобы длины слов в хэш-таблице на момент вызова функции поиска мы уже знали.

Посмотрим на данные профилировщика:

![Версия 2](./imgs/version2_mem_hash0_O0.png)

Время работы: `5.04` секунды. 
Относительное ускорение: `1.14`.

Функцию `__strcmp_avx2` пытаться оптимизировать мы заново не будем. Таким образом, осталась только функция `hashBkdr_0`, ей и займёмся.

### Версия 3

Поправки:
- функция хэширования переведена на ассемблер.

![Версия 3](./imgs/version3_mem_hash1_O0.png)

Время работы: `4.71` секунды.
Относительное ускорение: `1.07`.
Абсолютное ускорение: `1.22`.

Больше ускорять в функции поиска нечего. Попробуем последнее: увеличим размер хэш-таблицы приблизительно в 10 раз.

Время работы: `1.86` секунды.
Относительное усорение: `2.53`
Абсолютное ускорение: `3.09`. 

Результат понятен: производится меньше сравнений внутри списка, соответствующего ячейке хэш-таблице, что сильно ускоряет работу программы.

Добавим к тому же флаги оптимизации. 

| O0  | O2 | O3 |
| -- | -- | -- |
| 4.71 | 1.53 |  1.48  |

Итоговое усорение: `3.88` раза.

### Вывод

Общий прирост скорости составляет 388% по тактам. Рассчитаем коэффициент Деда по формуле:

$\frac{\text{acceleration value}}{\text{number of assembly lines}} \cdot 1000$.

Не будем учитывать имена меток, названия функций и комментарии. Таким образом, получим:

$\frac{3.88}{18} \cdot 1000 = 215.55$

Из всех оптимизаций видно, что наибольшую дают изменения, связанные с алгоритмической частью.
