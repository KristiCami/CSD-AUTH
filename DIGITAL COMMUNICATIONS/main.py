import random


# Function that creates a k-bit random binary message.
def createMessage(k):
    message = []  # Initialize list to store the message
    for i in range(0, k):  # Fill the message with k bits
        num = random.randrange(0, 2)  # Generate a random binary number
        message.append(num)  # Append the generated number in the message
    return message  # Return the k bit random message


# Function that calculates the XOR of list A and B (lists are the same length).
def xor(A, B):
    result = []  # Initialize a list that will store the XOR of A and B
    # Calculate the XOR for each position of A and B lists. Ignore the most significant bit.
    for i in range(1, len(B)):
        if A[i] == B[i]:  # Definition of XOR
            result.append(0)
        else:
            result.append(1)
    # Return the result
    return result


# Function that calculates the modulo-2 division of two numbers A and B. A is the dividend and B is the divisor.
def division(A, B):
    counter = len(B)  # initialize counter that stores the size of bits that have to be XORed each time.
    result = A[0:counter].copy()  # Initialize the result-dummy list that will store the individual remainder.
    # Loop that puts 1 bit down each time and XORs with the divisor.
    while counter < len(A):
        # If leftmost bit is 1 then XOR with the divisor.
        if result[0] == 1:
            result = xor(result, B)
        elif result[0] == 0:  # If leftmost bit is 0 then drop down zeros.
            dummy = [0 for i in range(0, len(B))]  # Create a divisor representing 0 with counter-bits.
            result = xor(result, dummy)  # XOR with 0.

        # Drop down the next bit.
        result.append(A[counter])

        # Increase by one the size counter.
        counter = counter + 1
    # Make one last loop for the nth bit.
    if result[0] == 1:
        result = xor(result, B)
    else:
        dummy = [0 for i in range(0, len(B))]
        result = xor(result, dummy)
    # Return the final result.
    return result


# Function that constructs the FCS for a message D, key P and n total bits.
def constructFCS(D, P, n):
    D2nk = []  # Initialize a list to store the 2^(n-k)D number.
    D2nk = D.copy()  # Fill the most significant bits with the number D.
    # Fill the rest number with zeros.
    k = len(D)
    for i in range(0, n - k):
        D2nk.append(0)
    # Calculate the FCS as the remainder of the mod-2 division of 2^n-k/P.
    FCS = division(D2nk, P)
    # Return the FCS
    return FCS


# Function that creates Cyclic Redundancy Check for a message total of n bits, with data message D and key P.
def createCRC(D, P, n):
    FCS = constructFCS(D, P, n)  # Calculate the FCS.
    T = D.copy()  # initialize the total message T with data message D.
    # Fill the rest of n bits with the FCS.
    for i in range(0, len(FCS)):
        T.append(FCS[i])
    # Return the final message(Data + FCS).
    return T


# Function that creates Error in a message based on a BER value.
def createError(message, BER):
    transmitted = message.copy()  # initialize a list to store the transmitted message.
    for i in range(0, len(transmitted)):  # For every bit in the message to be transmitted
        num = random.random()  # Generate a random float number in range 0 to 1.
        if num < BER:  # If the number is smaller than the BER
            # then create an error in the specific bit.
            if transmitted[i] == 0:
                transmitted[i] = 1
            else:
                transmitted[i] = 0
    # Return the transmitted message.
    return transmitted


# Function to check if a message has been transmitted with an error using the CRC method.
def checkMessage(message, P):
    # Calculate the remainder of mod-2 division message/p.
    rem = division(message, P)
    # If remainder is not zero then there is an error. Function returns false.
    for i in range(0, len(rem)):
        if rem[i] != 0:
            return False
    # If remainder is zero then there is no error. Function returns true.
    return True


# Creates a random message and its FCS and then checks it with CRC for errors.
def runCRC():
    n = int(input("Give number of bits of message:"))
    string = input("Give divider P in binary with spaces :")
    P = string.split(" ")
    P = [int(i) for i in P]
    BER = float(input("Give Bit Error Rate (BER):"))
    error = False
    message = createMessage(n)
    string = [str(bit) for bit in message]
    string = ''.join(string)
    print("n-bit message created: ", string)
    message = createCRC(message, P, n)
    string = [str(bit) for bit in message]
    string = ''.join(string)
    print("CRC created for n-bit message: ", string)
    message2 = createError(message, BER)
    string = [str(bit) for bit in message2]
    string = ''.join(string)
    print("Message transmitted: ", string)
    if message != message2:
        print("Error occurred!")
        error = True
    else:
        print("No error occurred!")
    if not checkMessage(message2, P) and error:
        print("CRC detected error!")
    elif checkMessage(message2, P) and error:
        print("CRC didn't detect error")


# Creates a massive number of messages with their FCS and then checks them with CRC for errors.
def massiveMessages():
    k = int(input("Give length of data messages:"))  # Length of data messages
    string = input("Give divider P in binary with spaces :")  # CRC key
    P = string.split(" ")
    P = [int(i) for i in P]
    BER = float(input("Give Bit Error Rate (BER):"))  # Bit Error Rate
    n = int(input("Give number of transmitted messages:"))  # Number of transmitted messages
    error_counter = 0  # Counter that stores the number of errors that occur
    detected = 0  # Counter that stores the number of errors that CRC detects
    undetected = 0  # Counter that stores the number of errors that CRC doesn't detect
    for i in range(0, n):
        error = False
        # Create a random message length k bit.
        M1 = createMessage(k)
        # Calculate the CRC for the message.
        M1 = createCRC(M1, P, k)
        # Transmit the message through a channel with noise.
        M2 = createError(M1, BER)
        # Check if message transmitted with error.
        if M1 != M2:
            error = True
            error_counter = error_counter + 1
        # Check if CRC detects the error
        if not checkMessage(M2, P) and error:
            detected = detected + 1
        elif checkMessage(M2, P) and error:
            undetected = undetected + 1

    # Calculate the requested percentages
    error_percentage = (error_counter / n) * 100
    detected_percentage = (detected / n) * 100
    undetected_percentage = (undetected / n) * 100
    print("Total of messages transmitted:", n)
    print("Number of errors:", error_counter, "with error percentage:", error_percentage, "%")
    print("Number of detected errors from CRC:", detected, "with detected error percentage:", detected_percentage, "%")
    print("Number of undetected errors from CRC:", undetected, "with undetected error percentage:",
          undetected_percentage,
          "%")


runCRC()
massiveMessages()
