from cs50 import get_float

# always better working with int than float!


def get_count(change):
    count = 0
    while change > 0:
        if change >= 25:
            change -= 25
            count += 1
            #continue
        elif change >= 10:
            change -= 10
            count += 1
            #continue
        elif change >= 5:
            change -= 5
            count += 1
            #continue
        else:
            change -= 1
            count += 1
    return count


def main():
    while True:
        change = get_float("change owed:")
        if change > 0:
            break
    change = round(change * 100)
    coins = get_count(change)
    print(coins)


main()