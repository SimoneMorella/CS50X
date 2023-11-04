import csv
import sys


def main():
    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Invalid amount of input")
        sys.exit(1)
    if not (sys.argv[1].endswith(".csv") and sys.argv[2].endswith(".txt")):
        print("Invalid type of input")
        sys.exit(2)

    # Read database file into a variable
    profiles = []
    database = open(sys.argv[1], "r")
    rows = csv.DictReader(database)
    for row in rows:
        profiles.append(row)

    # Read DNA sequence file into a variable
    dna_file = open(sys.argv[2], "r")
    dna_seq = dna_file.read()

    # TODO: Find longest match of each STR in DNA sequence
    recurr_dict = {}
    for key in profiles[0]:
        if key == "name":
            continue
        longest = longest_match(dna_seq, key)
        recurr_dict[key] = longest
    # Check database for matching profiles
    the_match = "No match"
    for row in profiles:
        matches = 0
        for key in recurr_dict:
            if int(recurr_dict[key]) == int(row[key]):
                matches += 1
        if matches == len(recurr_dict):
            the_match = row["name"]
            break
    print(the_match)


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
