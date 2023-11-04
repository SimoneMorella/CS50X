from cs50 import get_int


def main():
    while True:
        height = get_int("Height:")
        if height >= 1 and height <= 8:
            break
    for i in range(1, height + 1, 1):
        print(" " * (height - i) + "#" * i + "  " + "#" * i)


main()