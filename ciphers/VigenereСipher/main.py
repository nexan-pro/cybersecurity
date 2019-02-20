def encrypt(sequence, secretKey):
    secretKey *= len(sequence) // len(secretKey) + 1 
    return (''.join([chr((ord(j) + ord(secretKey[i])) % 26 + ord('A')) for i, j in enumerate(sequence)]))

def decrypt(sequence, secretKey):
    secretKey *= len(sequence) // len(secretKey) + 1
    return (''.join([chr((ord(j) - ord(secretKey[i])) % 26 + ord('A')) for i, j in enumerate(sequence)]))

def main():
    srcSecretKey = raw_input("Enter secret key: ")
    inputFile = open("src.txt")
    srcSequence = inputFile.read()
    ecryptedData = encrypt(srcSequence, srcSecretKey)
    outputFile = open("encrypted.txt", 'w')
    outputFile.write(ecryptedData)
    print (ecryptedData)
    print (decrypt(ecryptedData, srcSecretKey))

if __name__ == '__main__':
    main()

#TODO: fix symbols && make for lowercase
