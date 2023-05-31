# Игра Flappy Bird

Это простая реализация игры Flappy Bird с использованием библиотеки SFML (Simple and Fast Multimedia Library). В игре игрок управляет птицей и должен пролететь сквозь просветы между трубами. Цель игры - набрать максимальное количество очков, пролетая через как можно больше просветов без столкновений с трубами или землей.

## Подготовка
Для компиляции и запуска этой игры вам нужно установить библиотеку SFML на вашей системе. Убедитесь, что у вас есть необходимые зависимости SFML, а также заголовочные файлы и библиотеки SFML.

## Сборка и запуск игры
Чтобы собрать игру, выполните следующие шаги:

1. Настройте вашу среду разработки с необходимыми зависимостями и SFML.
2. Создайте новый проект или исходный файл в выбранной вами среде разработки на C++.
3. Скопируйте и вставьте предоставленный код в ваш проект или исходный файл.
4. Убедитесь, что вы обновили пути к файлам текстур в вызовах `loadFromFile`, чтобы они соответствовали расположению файлов изображений на вашей системе.
5. Соберите проект, убедившись, что вы связали его с библиотеками SFML.
6. Запустите скомпилированный исполняемый файл, чтобы начать игру.

## Управление в игре
- **Левая кнопка мыши**: Начать игру или заставить птицу прыгнуть во время игры.
- **Клавиша R**: Перезапустить игру, когда игра окончена.
- **Клавиша Escape**: Закрыть игру.

## Геймплей
- Когда игра начинается, игрок может нажать левую кнопку мыши, чтобы заставить птицу прыгнуть и избежать столкновения с трубами или землей.
- Цель игрока - пролететь птицей сквозь просветы между трубами, не сталкиваясь с ними.
- Каждый раз, когда птица успешно проходит через просвет, счет игрока увеличивается на одно очко.
- Если птица сталкивается с трубой или землей, игра заканчивается, и игрок может перезапустить игру, нажав клавишу "R".
- Максимальный счет, достигнутый игроком во время сессии, отображается как High score.

Приятной игры в Flappy Bird!

## Скриншоты
Стартовый экран
![image](https://github.com/s0oosauge/FlappyBird-sfml/assets/135156093/a2a6c1e9-4977-4e71-9ac6-adec9088d904)

Игровой процесс
![image](https://github.com/s0oosauge/FlappyBird-sfml/assets/135156093/3b5dac96-e7c4-446b-8d8a-efd7c0abdc8d)

