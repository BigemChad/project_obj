### Importante

Należy:
- zdefiniować poszczególne składowe każdej z klas (pola i metody) – nazwy i liczność pół i metod są zależne od osoby realizującej projekt;
- określić sposób dziedziczenia klas, czyli zaimplementować przedstawioną hierarchię.

Jako liść rozumiana jest klasa, która nie ma potomka.
- Program powinien umożliwiać następujące operacje na zbiorze obiektów:
- dodawanie obiektu (tylko do liści);
- usuwanie obiektu (tylko z liści);
- modyfikacje obiektu;
- zapis zbioru do pliku;
- odczyt zbioru z pliku;
- przeglądanie podzbioru obiektów zgodnie z przedstawioną na rysunku hierarchią - z dowolnego węzła drzewa, wyświetlane zostaną tylko obiekty należące do liści, które z danego węzła dziedziczą, lub w przypadku liścia – jedynie obiekty do niego należące

Każda klasa powinna posiadać co najmniej 1 pole prywatne i 1 pole protected

### Todo

- [] Poruszanie się w strukturze z linii komend:
  - W systemie znajdują się obiekty.
  - Tylko liść zawiera w sobie listę obiektów. Długość listy jest nieograniczona
- [] Struktura - operacje: 
  - [nazwa węzła(klasy)]- zmiana węzła w strukturze
- [] Obiekty - operacje:
  - MO  [obiekt]- tworzy obiekt o nazwie „obiekt” dla bieżącego liścia– należy podać parametry obiektu
  - DO  [obiekt]- usuwa obiekt o nazwie „obiekt”dla bieżącego liścia
  - MDO [obiekt]– modyfikacja obiektu o nazwie „obiekt”dla bieżącego liścia
- [] Polecenie DIR - wyświetla informacje o obiektach widocznych z danego poziomu - domyślnie tylko informacje o nazwach obiektów (wyświetla listę wszystkich obiektów należących do liści, które dziedziczą z danej klasy
- [] Polecenie SHOW [obiekt] – wyświetla szczegółowe informacje o obiekcie
- [] Operacje z plików
  - SAVE – zapis zbioru do pliku
  - READ – odczyt zbioru z pliku
- [] Polecenie TREE - wyświetla całą strukturę przedstawioną na rysunku np. w formie wcięć
- 
### Done ✓

- [X] Początek menu
