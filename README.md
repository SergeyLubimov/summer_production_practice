Проходил летнюю практику дважды, так как один раз уходил в академический отпуск.
Для удобства поместил материалы обеих практик в один репозиторий.

# TEMPLATE
Расширение, написанное во время первого прохождения. 
Практика имела структуру заданий:
1) Создать и установить простейшее расширение, добавляющее в базу
данных две функции уровня “Hello, World!”: одну SQL-функцию и
одну С-функцию.
2) Реализовать передачу и возврат численных аргументов в функции
расширения.
3) Реализовать передачу, возврат и обработку строк в функциях
расширения.
4) Добавить в БД новый тип данных. Реализовать передачу и возврат
этого типа в функции.
5) Реализовать передачу и возврат в функцию отдельной записи
таблицы в функции.
6) Реализовать формирование и возврат таблицы в функции.
7) Добавить регрессионные тесты для функций созданных в заданиях 2-7.
8) Реализовать работу с разделяемой памятью в функциях расширения.
9) Реализовать работу с механизмом последовательного доступа latches.

Файл Lyubimov_S_M_PI-02_Otchet_po_proizvodstvennoy_praktike.pdf содержит полный отчет по летней практике.

# conv_units
Так как и в первый раз практика была успешно зачтена пересдавать ее было не нужно.
Но мне разрешили перепрейте летнюю практику за компанию с моей новой группой.
Хотя общее направление практики было сохранено, появились новые материалы.

В рамках второй практики я усложнил себе задание. Обычно требуется разобраться в механизмах, описанных в Заданиях, 
но без особой внутренней логики. Я же захотел попробовать использую полученные в прошлый раз знания реализовать более сложную систему.
К сожалению, задумка оказалась слишком амбициозной. Многое из того, что я думал работает так, работало по-другому и 
изначальную идею реализации приходилось переписывать. Так несколько раз начинал почти с нуля. В результате не успел доделать это расширение даже до жизнеспособного состояния.

Каталог conv_units содержит все наработки.

Идея conv_units:
Расширение для конвертации физических единиц, которое можно научить новым преобразованиям. Оно хранило в себе структуру содержащие инструкции к преобразованию физических единиц.
Так для единиц со стандартным преобладанием хранились обозначения единиц, как строковый тип, и коэффициент преобразования, как число.
Для нестандартных преобразований (например температуры) вместо коэффициента хранился указатель на функцию преобразования.

При этом структура должна была располагаться в shared memory, чтобы преобразования, добавленные в одном подключении к серверу, были доступны во всех.
Во избежание одновременного доступа нескольких подключений можно было использовать механизм lathches. 

Таким образом, по задумке данное расширение позволяло практически применить все изученные ранее технологии для реализации более сложной логики.
 

