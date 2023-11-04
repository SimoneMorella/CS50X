from cs50 import get_float

def get_count(change):
    count = 0
    while change > 0:
        if change >= 0.25:
            change -= 0.25
            count += 1
            #continue
        elif change >= 0.10:
            change -= 0.10
            count += 1
            #continue
        elif change >= 0.05:
            change -= 0.05
            count += 1
            #continue
        else:
            change -= 0.01
            count += 1
    return count


def main():
    while True:
        change = get_float("change owed:")
        if change > 0:
            break
    change = round(change, 2)
    coins = get_count(change)
    print(coins)


main()