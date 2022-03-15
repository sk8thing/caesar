# Description
Application that cracks the [Caesar cipher](https://en.wikipedia.org/wiki/Caesar_cipher) using frequency analysis of letters. 
Each language has a different letter frequency distribution, the graph below shows the frequency of each letter in Romanian, which is the language the application was written for.\
![1](https://user-images.githubusercontent.com/101511232/158178475-fe39e0a2-8152-412a-8db8-62578875636c.png)
## Running the application
You can download the executable from the release tab, or you can compile it yourself. 
To run the application you need to create a text file containing the cipher text. 
The cipher text should only contain letters from A-Z, diacritics, punctuation marks and other symbols should be unencrypted. 
After creating the file simply do:
```
./ccaesar.exe path/to/example.txt
```
## How it works
Considering the alphabet has 26 letters, there's 25 possible shifts, the cipher string is decrypted using every possible shift and each time the result gets assigned a letter frequency score. 
After getting the score of each shift, the string with the highest frequency score is considered the correct one and it gets printed.