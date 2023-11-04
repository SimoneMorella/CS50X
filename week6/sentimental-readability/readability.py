from cs50 import get_string
from string import ascii_lowercase as alphabet


def count_letters(text):
    count = 0
    text = text.lower()
    for i in alphabet:
        count += text.count(i)
    return count


def count_words(text):
    count = len(text.split())
    return count


def count_sentence(text):
    count = 0
    stop_points = [".", "!", "?"]
    for i in stop_points:
        count += text.count(i)
    return count


def calculation(text):
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentence(text)
    l_value = round(letters / words * 100, 4)
    s_value = round(sentences / words * 100, 3)
    index = 0.0588 * l_value - 0.296 * s_value - 15.8
    return index


def main():
    text = get_string("Text:")
    index = round(calculation(text))
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


main()