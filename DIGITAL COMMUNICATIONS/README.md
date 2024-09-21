CODE ANALYSIS

• The createMessage(k) function accepts a number k and creates one
random binary message of size k. To generate the random bits
the random.randrange(0,2) function is used. The message is stored in a list.


• The xor(A, B) function accepts two lists with the same size and returns the XOR operation of the two numbers. 
The function calculates and returns the logical xor for each bit position of the two
of numbers ignoring the first (most significant bit).


• The division(A,B) function accepts two lists and
returns the remainder of their division by modulo-2 arithmetic. For
the division is used a counter variable which counts the
position the division is in. The result list contains the quotient of the division in each
previous step and is initialized with its leftmost bits
of the divisor. Then there are repeated
divisions in which if the most significant bit of the result is 1 then
the quotient is divided by the divisor, otherwise it is divided by 0. At each step, the next bit of it
divisor goes down and enters the end of the quotient. This process terminates when all bits of the divisor are down.
Finally, one last iteration is performed for its last bit
divisor and the function returns the remainder of the division, the
which is the FCS (Frame Check Sequence) for the CRC method.


• The function constructFCS(D, P, n) accepts a message of length k, one
number P by which the final message should be divisible,
and n the size of the total message to be transmitted. The function
places n-k zeros to the right of D and yields 2n-kD, which
stored in the variable D2nk. Then, with the help of the function
division(D2nk, P) the message is divided by the number P and the remainder
of the division is returned to the variable FCS. Finally, the function
returns the FCS.


• The function createCRC(D, P, n) accepts a message D of length k, one
number P by which the final message should be divisible,
and n the size of the total message to be transmitted. The function
generates an error check with the CRC method and returns the final one
message (Data + FCS). Calculates the FCS with the help of the function
constructFCS(D, P, n) and sticks it at the end of message D. Finally,
returns the final message T.


• The createError(message, BER) function accepts a message and a
Bit Error Rate BER value and simulates a transmission channel.
A random real number is calculated for each bit of the message
num -using the library's random.random() function
random- located in the interval [0,1]. If the number num is
smaller than the BER value then there is an error in the specific bit
and the function changes its value. Otherwise, it keeps the same
value. At the end, the "corrupted" transmitted message is returned.


• The function checkMessage(message, P) accepts a message and a message
number P by which the final message should be divisible and
decides whether there is an error in the message or not. Splits the message message
with the number P. If the remainder is 0 then it returns True,
otherwise it returns False.
