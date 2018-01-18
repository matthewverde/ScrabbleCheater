# ScrabbleCheater
Command line tool used for cheating in scrabble

The order of required inputs are
1.Letters to make words from (Or '-' to use all characters)
2.Requested length of words to find
3.(Optional) Location of known letters ex. a--b-d would find all words with 'a' as the first character 'b' as the fourth character, and 'd' as the sixth character.

ex. ./scrabbleCheater abcdefghijk 4 ag--

output:
Loading Dictionary
Done Loading
aged
Total Nodes Made: 	84
Total Words Found: 	1

Number of Nodes refers to the number of recusive calls made within the program
