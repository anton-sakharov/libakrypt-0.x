
Это сборка mo для конкретной системы
mo:
	msgfmt akrypt.po -o akrypt.mo

Это запуск для первичной инициализации файла .po
initial_create:
        xgettext -a --from-code=UTF-8 -d akrypt -C ../akrypt.c


pandoc -s -t man akrypt.md -o akrypt.1
