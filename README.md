# FinHawk-Assignment
Internship Assignment
Read me-

The application contains 3 .c files, namely: human.c, clie.c, serv.c
We need to compile and run all the three application. The server needs to be compiled and run before human or clie is run.Command for compiling serv.c is- gcc serv.c -o serv -pthread. (And similar for other two)
Once all connections are done, the client (clie.c) can enter queries. Queries the bot can handle are:
1. How to signup/create new account etc.
2. Not able to login
3. My name
4. Date Today
The above queries are case insensitive and can be asked in different forms. Bot will answer back if it recognises the form and the question, else it will transfer control to human. Human is informed about the question by the bot and the client is informed that a human has been introduced.

Note: username for human.c should be human.

