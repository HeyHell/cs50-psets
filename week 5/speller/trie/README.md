# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

This is the longest word (consists of 45 letters) and
was invented by Everett M. Smith, president of the National Puzzlers' League as a synonym for silicosis.


## According to its man page, what does `getrusage` do?

This function returns statistics about resource usage.

## Per that same man page, how many members are in a variable of type `struct rusage`?

16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

Because it would take more memory if the whole structure was passed to the function.
Passing a structure by reference only copies the address of this function.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

First, this function try opens the dictionary file and, if possible, copies all the words into memory.
Then, it opens the file in which the words will be checked.

After this, every word is added to the dictionary.
Each word must contain only alphabetic letters or apostrophes and the length must be no more than 45 characters.
A word can not contain numbers. But if it is, then this word is skipped.

*fgetc* reads character by character from a text file and adds is to the buffer.
If the next character is neither alphabetical nor apostrophe, and the buffer contains at least one character,
then the other function *check* checks the word for spelling errors.
This is repeated to the end of the file.

Then the dictionary is unloaded and * main * shows the result:
- misspelled words;
- time to work functions (*load*, *check*, *size* and *unload*);
- the number of words in the dictionary and text;

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

*fscanf* with parametr "%s" returns the sequence of non-whitespace characters.
Thus, some words may contain invalid characters, such as numbers or any non-alphabetic characters.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

Parameters were declared as constants, because at the runtime the data should not be changed.