# ДЗ C++ №2


## Сборка и запуск

Из папки `untitled`:

```sh
git clone --branch homework2 --single-branch https://github.com/bySaf/mipt-cpp-homework.git untitled
cd untitled
cmake -S . -B build
cmake --build build --target fizkat
./build/homework2/fizkat
```


## Команды


| Команда | Действие                                                   |
| --- |------------------------------------------------------------|
| `add scooter id name energy score` | добавить электросамокат                                    |
| `add bike id name score` | добавить велосипед                                         |
| `add ebike id name energy score` | добавить электровелосипед                                  |
| `add helmet id name` | добавить шлем (айтем)                                      |
| `add dock id name energy` | добавить док-станцию (айтем)                               |
| `add skateboard id name score` | добавить скейтбор                                          |
| `list` | вывод всех позиций по возрастанию строкового id            |
| `novice` | транспорт с простотой не меньше порога; порядок добавления |
| `novice_score score` | новый порог простоты 1..10, изначально 6                   |
| `energy` | суммарные кВт·ч/сутки, один знак после точки               |
| `report` | число позиций и суммарная энергия                          |
| `focus id` | выбрать позицию для витрины                                |
| `show_focus` | `id name` или `expired`                                    |
| `remove id` | удалить позицию                                            |
| `max_energy` | `id name energy` для позиции с наибольшим расходом         |
| `quit` | завершить программу                                        |

Пример для проверки:

```text
add scooter S-1 ModelX 2.5 8
add bike B-1 City 4
add scooter S-2 brokenX 1.0 9
add helmet H-1 Pro
add dock D-1 Hub 10.0
list
novice
energy
quit
```

Ожидаемый вывод:

```text
error: inspection rejected
B-1 City
D-1 Hub
H-1 Pro
S-1 ModelX
S-1 ModelX
12.5
```

## Классы и наследование



```text
InventoryItem (абстрактный)
└── NamedItem (общие id, name и печать)
    ├── Transport (абстрактный, простота для новичка)
    │   ├── ElectricScooter + EnergyConsumer (мультипл)
    │   ├── Bike
    │   ├── ElectricBike + EnergyConsumer (мультипл)
    │   └── Skateboard
    ├── Helmet
    └── Dock + EnergyConsumer

EnergyConsumer (отдельный абстрактный)
```


## Владение и техосмотр


1. [Commands.cpp](Commands.cpp) создаёт объект через `make_unique`.
2. `Fleet::Add` получает `unique_ptr<InventoryItem>`, проверяет дубликат и
   вызывает [ServiceCenter](ServiceCenter.cpp). Имя транспорта с подстрокой
   `broken` без учёта регистра вызывает `InspectionError`. Вещи не проходят
   техосмотр.
3. При исключении локальный `unique_ptr` уничтожает объект, парк не меняется.
4. После успеха владение переносится из `unique_ptr` в `shared_ptr
5. Витрина хранит `weak_ptr`. `show_focus` временно получает `shared_ptr`
   через `lock()`. После `remove` объект уничтожается и витрина печатает
   `expired`. Повторное добавление того же id не оживляет старую витрину:
   нужно снова вызвать `focus`.

## Шаблоны и исключения

[Registry.h](Registry.h)  шаблонный журнал `Registry<T>`:
`Add`, `Size`, `operator[]`, `Remove`, обход, сортировка и `operator<<`.
Парк использует его для `shared_ptr<InventoryItem>`. Шаблон печати
`PrintRegistryValue` имеет явную специализацию для таких указателей:
печатает инвентарь, а не адрес. `list` использует эту специализацию.


[Errors.h](Errors.h): `FleetError : std::exception` — общий базис

`InspectionError` — отказ техосмотра.

`CommandError` — ошибки команд и данных.

Ошибочный `focus` сохраняет
прежнюю витрину, ошибочный `novice_score` сохраняет прежний порог.

## Креатив и проверка

Новый класс: `Skateboard`, с соответсвующий командой `add skateboard`. 
Новый отчёт - `max_energy`. 
Дополнительно есть `report` и настройка порога `novice_score`.


## Помощь ИИ

При выполнении был использован ChatGpt 6 Astra. Мной были написаны хедер файлы (ну и получается продумана архитектура соответственно), 
а большая часть именно реализации была написана уже агентом. Все изменения и их причины указывал в коде коммнетами
