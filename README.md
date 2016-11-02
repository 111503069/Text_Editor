# Text_Editor
# Text_Editor
MIS No. - 111503069
Valakonda Anusha
I have took data structure as doubly linked list of strings(lines).
1. Run the programme by ./editor
2. User can give file name in command line argument after ./editor
ex :- if file name is anusha
then run the programme by giving ./editor anusha
if file named anusha do not exist the file named anusha gets created.
3. If file name is not given in command line argument then Untitled File is created.
ctrl + w :- the presently open file gets saved.
edited file also gets changed.

ctrl + e :- exit from text editor.
if file is not saved asks for doing permanent changes y/n
n - do not edit and get exit from text editor.
y -  save the modified changes and then get exit.

ctrl + d :- line at which the cursor is present gets deleted.

ctrl + r :- replaces the string to another entered by user.
y - replace the highlighted string.
n - do not replace the highlighted string.
a - replaces all strings present in that file.

ctrl + b :- copy the string.
string should be copied by pressing (shift + left/right key).

ctrl + x :- cut the selected string.

ctrl + p :- paste the string which is being cut or copied at the cursor position.
