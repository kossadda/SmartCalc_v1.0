# s21_smartcalc v_1.0

## Содержание
1. [О проекте](#о-проекте)
2. [Команда разработки](#команда-разработки)
3. [Реализованные задачи](#реализованные-задачи)
4. [Особенности реализации](#особенности-реализации)
5. [Сборка проекта](#сборка-проекта)
6. [Обратная связь](#обратная-связь)

## О проекте 

Данный проект является частью базы проектов "Школы 21" от Сбера. Целью данного проекта является реализация собственной версии инженерного калькулятора с дополнительными режимами депозитного и кредитного калькуляторов.

## Команда разработки

Состав команды, реализовавшей проект: <br>
**kossadda** (https://github.com/kossadda) <br>

## Реализованные задачи

В рамках проекта было реализовано:

| №  | Режим калькулятора                         | Описание                                                                                                                  |
|----|--------------------------------------------|---------------------------------------------------------------------------------------------------------------------------|
| 1  | Инженерный калькулятор                     | Позволяет производить расчеты сложных математических выражений длиной до 255 символов с возможностью построения графиков. |
| 2  | Кредитный калькулятор                      | Позволяет получить полную информацию о ежемесячных платежах при кредитовании.                                             |
| 3  | Депозитный калькулятор                     | Позволяет получить полную информацию  о доходах за периоды капитализации счета.                                           |

## Особенности реализации

В ходе написания проекта было принято решение произвести реализацию вычислений на бэкенде на языке C (исходя из ТЗ), GUI-составляющей - на языке C++ с применением фреймворка qt (что позволяется ТЗ нашего проекта, несмотря на то, что проект входит в ветку C языка). Сборка проекта осуществляется при помощи CMake, хоть и на запасной случай есть возможность сборки по QMake.  

Коротко об инженерном калькуляторе: <br>

1) Поддержка ввода математических выражений до 255 символов. <br>
2) Поддержка построения графиков. <br>
3) Поддержка зумирования графиков. <br>
4) Поддержка трассировки графиков. <br>
5) Интерактивная валидация ввода. <br>

Коротко о кредитном калькуляторе: <br>

1) За основу взят калькулятор расширенный кредитный калькулятор с calcus.ru. <br>
2) Поддержка обоих видов ежемесячных платежей. <br>
3) Поддержка операций досрочных погашений двух типов. <br>
4) Полный отчет по всем периодам ежемесячных выплат. <br>
5) Полный отчет по итоговым показателям кредитования. <br>

Коротко о депозитном калькуляторе:

1) За основу взят калькулятор расширенный кредитный калькулятор с calcus.ru. <br>
2) Поддержка операций пополнений и частичных снятий средств с депозита. <br>
3) Поддержка любой периодичности капитализации счета. <br>
4) Полный отчет по всем периодам капитализации счета. <br>
5) Полный отчет по итоговым показателям депозита. <br>

Для более подробного ознакомления со всем доступным функционалом следует перейти к manual по проекту, где можно найти и инструкции к их применению.

## Сборка проекта

В Makefile добавлены следующие основные цели для работы с проектом:

| #  | Command            | Description                                                                  |
|----|--------------------|------------------------------------------------------------------------------|
| 1  | `all`              | Формирует документацию к проекту и запускает тестирование модулей.           |
| 2  | `s21_smartcalc`    | Осуществляет сборку модулей в статическую библиотеку.                        |
| 3  | `test`             | Производит тестирование модулей.                                             |
| 4  | `gcov_report`      | Производит тестирование модулей и формирует отчет о покрытии в html формате. |
| 5  | `dvi`              | Формирует документацию в формате html и manual к функционалу.                |
| 6  | `rebuild`          | Пересборка проекта.                                                          |
| 7  | `clang_check`      | Тестирование модулей на соответствие Google style.                           |
| 8  | `valgrind`         | Тестирование модулей на работу с памятью через Valgrind.                     |
| 9  | `install`          | Производит установку необходимых зависимостей для тестирования проекта.      |
| 10 | `clean`            | Производит очистку репозитория от сгенерированных файлов.                    |

## Обратная связь

Если имеются вопросы касаемо особенностей или других интересующих вас моментов проекта, то обращайтесь на почту:

gabilov1997@gmail.com <br>

Спасибо за внимание. Надеюсь, что данный проект вам придет по душе.