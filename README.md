Tron

Jedlička a Knorová
Pro nové hráče:
  Projekt:
  -	Hra Tron vychází ze známého stejnojmenného filmu z roku 1982. Každý hráč za sebou zanechává barevnou stopu a pomocí ní se snaží eliminovat soupeře, nebo aby se soupeř eliminoval o vlastní stopu.
  -	Hra je určena pro dva hráče, rozlišení bude barvou. (výběr z 5 možností)
  -	Hra obsahuje menu (objeví se v konzoli po spuštění programu), kde si každý hráč vybere svoji barvu a rychlost hry.
  -	RGB diody v průbehu hry svítí barvou, kterou si hráč na každé straně vybral a po konci hry se rozsvití barvou vítěze.
  Ovládání:
  -	Hra se ovládá pomocí dvou otočných voličů. S každým tikem voliče se had otočí daným směrem o 90 stupňů.
  -	Hra se vykresluje na displej.

Model:
- model se skládá z hlavního komponentu (main.c) a ze zbylých podkomponentů
  Podkomponenty:
  - array_functions -> model se zabývá vytvářením hracího pole
  - knobs -> model slouží k přijímání, zpracovávání a kontrolování vstupu z ovládacích knobs
  - menu -> model slouží k obládání menu a ukládání zadaných informaci do herních dat
  - player_functions -> model obsahuje veškeré funkce k pohybu obou hráčů a podmínek k vyhodnocení hry
  - printWinner -> model slouží k tisknutí výsledku na konci hry
  - RGB -> model slouží k ovládání a nastavení RGB diod na správnou barvu  
