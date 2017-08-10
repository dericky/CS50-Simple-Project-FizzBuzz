import sys

def main():
    if(len(sys.argv) == 2):
        plainInput = input("plaintext: ")
        key = int(sys.argv[1])
        print(getCipher(plainInput, key))
    else:
        print("Usage: python caesar.py k")


def getCipher(plainInput, key):
    if(len(plainInput) > 0):
        cipherOutput = ""
        for i in range(0, len(plainInput)):
            letter = plainInput[i]
            if(letter.isalpha()):
                    letter = ord(letter)
                    letter += key
                    cipherOutput += chr(letter)
            else:
                cipherOutput += letter
        return cipherOutput
    return ""
                    

if __name__ == "__main__":
    main()