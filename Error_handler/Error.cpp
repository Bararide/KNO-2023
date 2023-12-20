#include "Error.h"

namespace Error
{
	ERROR errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0,    "Недопустимый символ"),
		ERROR_ENTRY(1,    "Символ не найден"),
		ERROR_ENTRY_NODEF(2),
		ERROR_ENTRY_NODEF(3),
		ERROR_ENTRY_NODEF(4),
		ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6),
		ERROR_ENTRY_NODEF(7),
		ERROR_ENTRY_NODEF(8),
		ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10),
		ERROR_ENTRY_NODEF10(20),
		ERROR_ENTRY_NODEF10(30),
		ERROR_ENTRY_NODEF10(40),
		ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60),
		ERROR_ENTRY_NODEF10(70),
		ERROR_ENTRY_NODEF10(80),
		ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100,  "Ошибка -in должен быть указан"),
		ERROR_ENTRY_NODEF(101),
		ERROR_ENTRY_NODEF(102),
		ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104,  "Неправильная длина аргумента"),
		ERROR_ENTRY_NODEF(105),
		ERROR_ENTRY_NODEF(106),
		ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108),
		ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110, "Ошибка при чтении файла с исходным кодом (-in)"),
		ERROR_ENTRY(111, "Недопустимый символ в исходном коде (-in)"),
		ERROR_ENTRY(112, "Ошибка при создании файла листинга (-log)"),
		ERROR_ENTRY(113, "Ошибка при создании файла вывода (-out)"),
		ERROR_ENTRY_NODEF(114),
		ERROR_ENTRY_NODEF(115),
		ERROR_ENTRY_NODEF(116),
		ERROR_ENTRY_NODEF(117),
		ERROR_ENTRY_NODEF(118),
		ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY(120, "Таблица идентификаторов: превышен размер таблицы"),
		ERROR_ENTRY(121, "Лексическая ошибка: Неправильное имя переменной или неправильное имя функции"),
		ERROR_ENTRY(122, "Таблица лексем: превышен размер таблицы"),
		ERROR_ENTRY(123, "Синтаксическая ошибка: неизвестный символ"),
		ERROR_ENTRY(124, "Синтаксическая ошибка: некорректный формат строки"),
		ERROR_ENTRY(125, "Синтаксическая ошибка: пропущен оператор"),
		ERROR_ENTRY(126, "Синтаксическая ошибка: недопустимая литеральная константа"),
		ERROR_ENTRY(127, "Синтаксическая ошибка: неправильный формат строки"),
		ERROR_ENTRY(128, "Лексическая ошибка: Не удалось создать файл с выходными данными и файлом листинга"),
		ERROR_ENTRY(129, "Лексическая ошибка: указан неверный входной аргумент (main)"),
		ERROR_ENTRY(130, "Лексическая ошибка: превышена максимальная длина объявляемой переменной"),
		ERROR_ENTRY(131, "Синтаксическая ошибка: вложенные условные операторы"),
		ERROR_ENTRY(132, "Лексическая ошибка: превышен размер переменной"),
		ERROR_ENTRY_NODEF(133),
		ERROR_ENTRY_NODEF(134),
		ERROR_ENTRY_NODEF(135),
		ERROR_ENTRY_NODEF(136),
		ERROR_ENTRY_NODEF(137),
		ERROR_ENTRY_NODEF(138),
		ERROR_ENTRY_NODEF(139),
		ERROR_ENTRY_NODEF10(140),
		ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160),
		ERROR_ENTRY_NODEF10(170),
		ERROR_ENTRY_NODEF10(180),
		ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200),
		ERROR_ENTRY_NODEF100(300),
		ERROR_ENTRY_NODEF100(400),
		ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY(600, "Семантическая ошибка: Некорректная строка программы"),
		ERROR_ENTRY(601, "Семантическая ошибка: Ошибка компилятора"),
		ERROR_ENTRY(602, "Семантическая ошибка: Ошибка в аргументах"),
		ERROR_ENTRY(603, "Семантическая ошибка: Ошибка в параметрах функции"),
		ERROR_ENTRY(604, "Семантическая ошибка: Ошибка в параметрах внешней функции"),
		ERROR_ENTRY(605, "Семантическая ошибка: Такая переменная в этой области видимости уже существует"),
		ERROR_ENTRY(606, "Семантическая ошибка: Не ожидался целочисленный тип"),
		ERROR_ENTRY(607, "Семантическая ошибка: Не ожидался строковый тип"),
		ERROR_ENTRY(608, "Семантическая ошибка: Не ожидалось значение типа bool"),
		ERROR_ENTRY(609, "Семантическая ошибка: Укороченная функция не может иметь область видимости"),
		ERROR_ENTRY(610, "Семантическая ошибка: Переменная неизвестного типа"),
		ERROR_ENTRY(611, "Семантическая ошибка: Переменная не имеет значения"),
		ERROR_ENTRY(612, "Семантическая ошибка: Встречена неизвестная переменнная"),
		ERROR_ENTRY(613, "Семантическая ошибка: Деление на ноль"),
		ERROR_ENTRY(614, "Семантическая ошибка: Первый операнд при сдвиге равен 0"),
		ERROR_ENTRY(615, "Семантическая ошибка: Одинаковые названия переменной и функции"),
		ERROR_ENTRY(616, "Семантическая ошибка: Найдена строка в математическом выражении"),
		ERROR_ENTRY(617, "Семантическая ошибка: Нельзя привести к типу byte"),
		ERROR_ENTRY(618, "Семантическая ошибка: Неверные передаваемые переменные"),
		ERROR_ENTRY(619, "Семантическая ошибка: Неверное число аргументов функции"),
		ERROR_ENTRY(620, "Семантическая ошибка: Встречена неизвестная функция"),
		ERROR_ENTRY(621, "Семантическая ошибка: Функция main встречается дважды"),
		ERROR_ENTRY(622, "Семантическая ошибка: Число превышает максимально возможное значение"),
		ERROR_ENTRY(623, "Семантическая ошибка: Найден вызов функции в математическом выражении"),
		ERROR_ENTRY(624, "Семантическая ошибка: Нет аналоговой функции без рекурсии"),
		ERROR_ENTRY(625, "Семантическая ошибка: Арифметическое выражение в условном операторе с вызовом функции"),
		ERROR_ENTRY(626, "Семантическая ошибка: Второй операнд при сдвиге равен 0"),
		ERROR_ENTRY(627, "Семантическая ошибка: Ошибка при подключении библиотеки"),
		ERROR_ENTRY(628, "Семантическая ошибка: Такой библиотеки не существует"),
		ERROR_ENTRY(629, "Семантическая ошибка: Ошибка преобразования"),
		ERROR_ENTRY(630, "Семантическая ошибка: Функция с такой сигнатурой не найдена"),
		ERROR_ENTRY(631, "Семантическая ошибка: Такая сигнатура функции ещё не обрабатывается компилятором"),
		ERROR_ENTRY(632, "Семантическая ошибка: Несколько операций в выражении подряд"),
		ERROR_ENTRY_NODEF(633),
		ERROR_ENTRY_NODEF(634),
		ERROR_ENTRY_NODEF(635),
		ERROR_ENTRY_NODEF(636),
		ERROR_ENTRY_NODEF(637),
		ERROR_ENTRY_NODEF(638),
		ERROR_ENTRY_NODEF(639),
		ERROR_ENTRY_NODEF10(640),
		ERROR_ENTRY_NODEF10(650),ERROR_ENTRY_NODEF10(660),ERROR_ENTRY_NODEF10(670),ERROR_ENTRY_NODEF10(680),
		ERROR_ENTRY_NODEF10(690),

		ERROR_ENTRY_NODEF100(700),
		ERROR_ENTRY_NODEF100(800),
		ERROR_ENTRY_NODEF100(900)
	};
	ERROR geterror(int id)
	{
		if (id > ERROR_MAX_ENTRY - 1 || id < 1)
			return errors[0];
		else
			return errors[id];
	}
	ERROR geterrorin(int id, int line = -1, int col = -1)
	{
		if (id > ERROR_MAX_ENTRY - 1 || id < 1)
			return errors[0];
		else
		{
			errors[id].inext.col = col;
			errors[id].inext.line = line;
			return errors[id];
		}
	}
};