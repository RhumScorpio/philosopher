# philosophers
## Dining philosophers problem
It was originally formulated in 1965 by Edsger Dijkstra as a student exam exercise, presented in terms of computers competing for access to tape drive peripherals.
## Difficulties
- Starvation : Utilise une fonction timestamp() qui utilise gettimeofday et renvoie un long long.
- Data Race: Where the data changes, where a mutex should be. For reading data and changing data.
- Deadlock : ALWAYS unlock mutex.
## Conseils
- Les mutex lock / unlock doivent être le moins éloignés possible. Faire des minis fonctions!
