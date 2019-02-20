import random

def gen(sequence, size, PWD):
    for i in range(size):
        rand = random.randint(0, len(sequence)-1)
        PWD += sequence[rand]
    return (PWD)

def main():
    sequence = ["abcdefghijklmnopqrstuvwxyz", "ABCDEFGHIJKLMNOPQRSTUVWXYZ", \
                "abcdefghijklmnopqrstuvwxyz0123456789", "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", \
                "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", \
                "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", "0123456789"]
    PWD, size, choice = "", input("Enter size of array: "), input("Configure generation: \
                                                                   \r\n1.onlyLowerCaseWithoutDigits \
                                                                   \r\n2.onlyUpperCaseWithoutDigits \
                                                                   \r\n3.onlyLowerCaseWithDigits \
                                                                   \r\n4.onlyUpperCaseWithDigits \
                                                                   \r\n5.lowerCaseWithUpperCase \
                                                                   \r\n6.lowerCaseWithUpperCaseWithDigits \
                                                                \r\n7.onlyDigits\r\n")
    configuration = {
        1 : gen(sequence[choice-1], size, PWD),
        2 : gen(sequence[choice-1], size, PWD),
        3 : gen(sequence[choice-1], size, PWD),
        4 : gen(sequence[choice-1], size, PWD),
        5 : gen(sequence[choice-1], size, PWD),
        6 : gen(sequence[choice-1], size, PWD),
        7 : gen(sequence[choice-1], size, PWD)
        }
    print ('PWD: {}'.format(configuration[choice]))
if __name__ == '__main__':
        main()
