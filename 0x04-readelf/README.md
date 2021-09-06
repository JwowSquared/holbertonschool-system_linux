# Read ELF #

Many functions in this project come in pairs.
This could be fixed if there was some way to cheese out iheritance or templates or generics or something.

The differences are extremely minor, namely different format strings for printf and a few different values depending on 32 or 64.

A possible solution would be to always use a 64 bit header.
if the magic numbers specify that it should be 32, you could fread into a 32 bit struct and move the numbers to a 64 bit struct.
64 would be unchanged.


You would need to do this with all 3 types of struct, every time you fread, potentially requiring 3 unique but similar functions to do so.
Otherwise you could read into a 64 bit struct with 64 bit size, but you would need to rewind the FILE pointer to account for the difference in size between 64 and 32, and typecast into 32 before translating back to 64.
This would also require some way of differentiating between which printf format strings to use where applicable.

From how it sounds, it would be possible to do it this way at the heavy price of readabilty.
Doesn't seem worth it at this time.
