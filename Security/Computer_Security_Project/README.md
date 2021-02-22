## A Brute Force Test   
### Description:

Think about the following scenario:
SYSTEM: An ATM requires a four digit pin-number (0 to 9999).
ATTACK: A hacker is trying to find a PIN number to access the ATM system by applying a
brute force attack. The hacker believes that he can guess the pin number in about 5000 tries, so
he starts with the value zero and without knowledge of any defense mechanism keeps
incrementing the pin by one. After trying 10,000 times, the attacker may think that the user
changed his PIN number during the attack, so he will try again the full exhaustive search 4 more
times and then give up.
DEFENSE: The security administrator for the ATM system implemented a mechanism that will
randomly change the PIN number if there are 50 wrong attempts.
PROJECT: In order to verify how good the defense system is, the program starts by randomly 
choosing a numeric PIN of length 4 digits (in the range 0 to 9,999). The same
program will run an exhaustive search to find the chosen pin, starting with value zero. The
program must choose a new random PIN after 50 wrong attempts from the attacker. The program
should measure the number of iterations (guesses) required to find a match, if one is not found it
should report that the defense system worked well.
The program must be run at least 10 times, each time with a new initial random value. At the end of all
tests, if the PIN number was found, the defense must change its strategy by reducing the number
of attempts to 25 and rerunning the test. The report contains the results of all tests, the
average number of iterations required to guess the correct PIN number, and a graph
(one for 50 allowed attempts and one for 25 attempts) plotting all the tests
results as a percentage of success against the maximum number of guesses, which implies 100%
will happen when the attacker is unable to find the PIN number as a function of the trial number.  

EXAMPLE: Initial PIN number selected: 241, attacker tries 0 to 49, then system changes PIN to
125, attacker tries 50 to 99, system changes again and so on.
    

### Files

|   #   | File                                                              | Description                                                |
| :---: | ----------------------------------------------------------------- | ---------------------------------------------------------- |
|   1   | [Project Assignment Report.docx](./Project Assignment Report.docx)| Project report                                             |
|   2   | [compsec_data_output.xlsx](./compsec_data_output.xlsx)            | Graph output data                                          |
|   2   | [CompSecProject.cpp](./CompSecProject.cpp)                        | Solution file                                              |
