| typ danych | rozmiar w pamięci |
|------------|-------------------|
| GLfloat    | 4 bajty           |
| GLushort   | 2 bajty           |

# "Ile bajtów oszczędziliśmy?"

> Usunięcie 3 wierzchołków po 7 wartości typu _GLfloat_
> 
> ``3 * 7 * 4 = 84``
>
> 84 bajty zwolniono

> Dodanie 9 indeksów typu _GLushort_
>
> ``9 * 2 = 18`` 
> 
> 18 bajtów zajęto

>``84 - 18 = 66``
> 

>**Zaoszczędzono 66 bajtów**

# "Ile więcej bajtów moglibyśmy jeszcze oszczędzić?"

> Aby zwolnić większą ilość pamięci możnaby przenieść kolory do innego wektora pozbywając się 18 zmiennych typu _GLfloat_ w wektorze ``vertices``.
> Następnie należałoby stworzyć wektor ``colorIndices`` z 9 wartościami _GLushort_.

> Usunięcie 18 zmiennych typu _GLfloat_
>
> ``24 * 4 = 96``
>
> 96 bajty zwolniono

> Dodanie 9 indeksów typu _GLushort_
>
> ``9 * 2 = 18``
>
> 18 bajtów zajęto

>``96 - 18 = 78``
>

>**Zaoszczędzono 78 bajtów**