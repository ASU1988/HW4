# HW4
Задание
Написать программу, скачивающую с помощью libcurl и разбирающую с помощью произвольной сторонней
библиотеки для JSON в C текущие погодные данные со следующего API для заданного аргументом
командной строки города.
Сложность
★★★☆☆
Цель задания
Получить навык работы со сторонними прикладными библиотеками.
Критерии успеха
1. Выбрана библиотека для работы с JSON в C.
2. Создано консольное приложение, принимающее аргументом командной строки название города
(например, Moscow).
3. Приложение выводит на экран прогноз погоды на текущий день: текстовое описание погоды,
направление и скорость ветра, температура.
4. Приложение корректно обрабатывает ошибочно заданную локацию и сетевые ошибки.
5. Код компилируется без предупреждений с ключами компилятора -Wall -Wextra -Wpedantic -
std=c11.
6. Далее успешность определяется ревью кода.
Обратная связь
Cтудент коммитит все необходимое в свой github/gitlab репозиторий. Далее необходимо зайти в ЛК, найти
занятие, ДЗ по которому выполнялось, нажать “Чат с преподавателем” и отправить ссылку. После этого
ревью и общение на тему ДЗ будет происходить в рамках этого чата.
Вспомогательные материалы
1. wttr.in help
2. JSON - список библиотек внизу страницы.
3. Native JSON Benchmark
4. libcurl example - getinmemory.c