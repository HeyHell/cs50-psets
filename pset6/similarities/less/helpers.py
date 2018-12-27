from nltk.tokenize import sent_tokenize

def lines(a, b):
    """Return lines in both a and b"""

    alines = set(a.splitlines())
    blines = set(a.splitlines())
    return alines & blines


def sentences(a, b):
    """Return sentences in both a and b"""

    asentences = set(sent_tokenize(a))
    bsentences = set(sent_tokenize(b))
    return list(asentences & bsentences)

def substrs_str(str, n):
    """Return list of substrings of length n from string s"""

    substrings = []
    for i in range(n, len(str) + 1):
        substrings.append(str[i - n:i])
    return substrings


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    a_substrs = set(substrs_str(a, n))
    b_substrs = set(substrs_str(b, n))
    return a_substrs & b_substrs