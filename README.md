Implementation of the mathematical concept of a matrix.
----------------
Matrix concept is geimplenteerd in Matrix.hpp als een template class. De overige source files zijn nodig voor unittest. 

### Compilatie benodigtheden ###
- C++11 (in theorie ook hoger, maar niet getest)
- GCC 6.3 of hoger (laatst getest met 7.3)
- Boost 1.65.1 (Alleen nodig als je de unittests wilt uitvoeren)

### Hoe gebruiken in Eclipse? ###

1. Maak een project C++
 ![Afb1](Afb1.png?raw=true "Project aanmaken")
2. Sleep alle betanden in de file explorer.
3. Installeer boost 1.65.1 
4. Link boost zoals de onderstaande afbeeldingen:
![Afb2](Afb2.png?raw=true "Include 1")
![Afb3](Afb3.png?raw=true "Include 2")
![Afb4](Afb4.png?raw=true "Include 3")

5. Build je project en run het :).


Stap 3 en 4 is alleen nodig als je unittest wilt uitvoeren. Je kan er ook voor kiezen om dit niet te doen dan kan je de code dat in main.cpp in comentaar staat als test gebruiken. Haal dan wel Matrix_test.cpp uit je project en in je main alles m.b.t. boost.

