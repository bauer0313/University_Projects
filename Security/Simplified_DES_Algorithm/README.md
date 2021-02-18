## Simplified DES Algorithm  
### Description:

This is a program that inputs a number k from the keyboard, such that 0 ≤ k < 210 (KEY),
and then requests a plaintext sentence to be encrypted using a simplified DES algorithm.
Plaintexts may contain any of the 26 alphabetic characters (capitalized) and 10 numeric
digits (0 to 9). Spaces in the text are ignored. No special characters or lower case
text should be entered. The algorithm is based on the Simplified DES cipher
described in the included pdf document. The algorithm
runs 4 rounds of encryption. The sub-keys are generated from the original key
by alternating the circular shift by one and two bits (one in the first rotation). It is easy to
notice that the text blocks entering the encryption algorithm will be transformed one byte
at a time. The program output is the encrypted text (shown in hexadecimal).
    

### Files

|   #   | File                                    | Description                                                |
| :---: | --------------------------------------- | ---------------------------------------------------------- |
|   1   | [SimplifiedDES.cpp](./SimplifiedDES.cpp)| Solution file                                              |
|   2   | [SimplifiedDES.pdf](./SimplifiedDES.pdf)| Simplified DES Algorithm                                   |
