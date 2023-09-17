# Philosophers

🧠 Aquest arxiu està escrit en català i en anglès.
🧠 This file is written in Catalan and English.

🍝 Imagina que tens un grup de filòsofs asseguts al voltant d'una taula rodona, i al mig d'aquesta taula hi ha un gran bol de espagueti.

🤔 Aquests filòsofs poden fer tres coses: menjar, pensar o dormir. Però hi ha algunes regles estrictes:

    - Mentre mengen, no poden pensar ni dormir.
    - Quan estan pensant, no poden menjar ni dormir.
    - I, per descomptat, mentre dormen, no poden menjar ni pensar.

🍴 A més, hi ha tantes forquilles a la taula com filòsofs. Ara bé, menjar espagueti amb només una forquilla és molt incòmode, així que cada filòsof agafa les dues forquilles que té a la seva disposició, una a cada mà, per menjar.

🍽️ Quan un filòsof ha acabat de menjar, posa les forquilles a la taula i comença a dormir. Un cop despert, torna a començar a pensar. La simulació acaba quan un filòsof mor de gana.

🤯 El repte és assegurar-se que cap filòsof mori de gana i que tots mengin adequadament, sense parlar entre ells, ja que els filòsofs no es comuniquen entre ells.

🕒 A més, has de tenir en compte temps específics:

    - time_to_die (en mil·lisegons): Si un filòsof no comença a menjar en aquest temps des de l'inici de la seva última menjada o de la simulació, morirà de gana.
    - time_to_eat (en mil·lisegons): El temps que un filòsof triga a menjar mentre agafa dues forquilles.
    - time_to_sleep (en mil·lisegons): El temps que un filòsof passa dormint.
    - number_of_times_each_philosopher_must_eat (argument opcional): Si tots els filòsofs han menjat almenys aquest nombre de vegades, la simulació s'atura. Si no s'especifica, la simulació s'atura quan un filòsof mor.

🪄 La vostra tasca és escriure un programa que simuli aquesta situació. També cal registrar tots els esdeveniments de cada filòsof amb marques de temps i assegurar-se que no hi ha curses de dades al programa.

📜 Les accions dels filòsofs han d'estar ben formatejades:

    - "timestamp_en_ms X ha agafat una forquilla"
    - "timestamp_en_ms X està menjant"
    - "timestamp_en_ms X està dormint"
    - "timestamp_en_ms X està pensant"
    - "timestamp_en_ms X ha mort"

I recorda, no deixis que els filòsofs morin de gana! 😄


Aquesta és l'explicació per a la línia 86 del fitxer «loop.c»:
  printf("%04li\t%i\t%s\n", (get_time() - philo->all->start), philo->num, s);

  - %04li: Aquest és un especificador de cadena de format printf que indica que s'imprimirà un nombre llarg amb una amplada de camp de 4 dígits. Qualsevol dígit que falti s'omplirà amb zeros a l'esquerra. El valor que s'imprimeix prové de l'expressió (get()time() - philo-).all-).start).
  - \t: Aquest és un caràcter d'escapada interpretat com una tabulació.
  - %i: Aquest és un especificador de format a la cadena de format que indica que s'ha d'imprimir un enter (int). El valor que s'imprimeix prové de la variable philo-.num.
  - \t: Com abans.
  - %s: Aquest és un especificador de format a la cadena de format que indica que s'ha d'imprimir una cadena de caràcters (cadena). El valor que s'imprimeix prové de la variable 's', que és una cadena de text que representa l'estat del filòsof.


## Translate it into English:

🍝 Imagine you have a group of philosophers seated around a round table, and in the middle of this table, there is a large bowl of spaghetti.

🤔 These philosophers can do three things: eat, think, or sleep. But there are some strict rules:

- While they are eating, they cannot think or sleep.
- When they are thinking, they cannot eat or sleep.
- And, of course, while they are sleeping, they cannot eat or think.

🍴 In addition, there are as many forks on the table as there are philosophers. However, eating spaghetti with just one fork is very uncomfortable, so each philosopher takes both forks available to them, one in each hand, to eat.

🍽️ When a philosopher has finished eating, they put the forks on the table and start sleeping. Once they wake up, they start thinking again. The simulation ends when a philosopher dies of hunger.

🤯 The challenge is to ensure that no philosopher dies of hunger, and that everyone eats properly, without communicating with each other, as the philosophers do not communicate with each other.

🕒 In addition, you have to consider specific times:

- time_to_die (in milliseconds): If a philosopher does not start eating within this time from the start of their last meal or the start of the simulation, they will die of hunger.
- time_to_eat (in milliseconds): The time a philosopher takes to eat while using two forks.
- time_to_sleep (in milliseconds): The time a philosopher spends sleeping.
- number_of_times_each_philosopher_must_eat (optional argument): If all philosophers have eaten at least this number of times, the simulation stops. If not specified, the simulation stops when a philosopher dies.

🪄 Your task is to write a program that simulates this situation. You also need to log all events of each philosopher with timestamps and ensure that there are no data races in your program.

📜 The actions of the philosophers should be well-formatted:

- "timestamp_in_ms X has picked up a fork"
- "timestamp_in_ms X is eating"
- "timestamp_in_ms X is sleeping"
- "timestamp_in_ms X is thinking"
- "timestamp_in_ms X has died"

And remember, don't let the philosophers die of hunger! 😄

Here's the explanation  for line 86 of the "loop.c" file:
  printf("%04li\t%i\t%s\n", (get_time() - philo->all->start), philo->num, s);
  
  - %04li: This is a printf format string specifier indicating that a long number is to be printed with a field width of 4 digits. Any missing digits will be padded with zeros on the left. The value being printed comes from the expression (get_time() - philo->all->start).
  - \t: This is an escape character interpreted as a tabulation.
  - %i: This is a format specifier in the format string indicating that an integer (int) is to be printed. The value being printed comes from the variable philo->num.
  - \t: As before.
  - %s: This is a format specifier in the format string indicating that a string of characters (string) is to be printed. The value being printed comes from the variable 's,' which appears to be a text string representing the state of the philosopher.
