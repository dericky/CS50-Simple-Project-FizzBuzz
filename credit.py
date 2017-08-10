def main():
    number = "0"

    while (len(number) != 13 and len(number) != 15 and len(number) != 16):
        number = input("Number: ")
    length = len(number)
    number = int(number)
    if(checkValidity(number)):
        cardType = getCardType(number, length)
        print(cardType)
    else:
        print("INVALID")


def checkValidity(number):
    sumofTimes = 0
    sumOthers = 0
    temp = number
    temp3 = number
    while(temp != 0):
        temp2 = ((temp % 100) // 10)
        temp //= 100
        temp2 *= 2
        i = temp2
        while(i != 0):
            sumofTimes += i % 10
            i//=10
    while(temp3 != 0):
        temp2 = ((temp3 % 100) % 10)
        temp3 //= 100
        sumOthers += temp2
    if((sumOthers + sumofTimes) % 10 == 0):
        return True
    return False

def getCardType(number, length):
    if(length == 15):
        firstTwo = number // 10000000000000
        if(firstTwo == 37 or firstTwo == 34):
            return "AMEX"
        elif(length == 16):
            firstTwo = number // 100000000000000
            if(firstTwo == 51 or firstTwo == 52 or firstTwo == 53 or firstTwo == 54 or firstTwo == 55):
                return "MASTERCARD"
            else:
                firstTwo //= 10
                if(firstTwo == 4):
                    return "VISA"
        else:
            firstTwo = number // 1000000000000
            if(firstTwo == 4):
                return "VISA"
    return "INVALID"

if __name__ == "__main__":
    main()