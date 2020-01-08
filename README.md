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
The human.c file has to be connected to the server since the start of chat support system, but it will get involved only when the bot is unable to answer the query. The human will be informed of the query and human can answer the query by typing in the answer on the human terminal. Once human feels it has answered the query, human needs to type "123exitsupport" (No need of double quotes) in order to transfer the control back to the server.

Note: username for human.c should be human.

