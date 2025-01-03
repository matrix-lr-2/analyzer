January 2025.
This work was done by Pechenin Danila (emails: dmpechenin@edu.hse.ru / dpechenin@icloud.com),
a student studying at the HSE University on the Bachelor's Program in Applied Mathematics (2nd year, group "БПМ233").
It is a programm that analyzes Complex matrices using library on Linear Algebra, developed by me.
------------------------------------------------------------------------------------------------------------------------
To use it you need to compile it and then run programm using the terminal and do not forget
to write the directory of the file with the matrix as an argument.
It should look like this:
./ComplexMatrixAnalyzer <file_path>
------------------------------------------------------------------------------------------------------------------------
This file should look like this:

| 0 0 1|
| 0 1 0|
|-1 0 0|

or

|  i 5+9i -10+1i|
|4+i    i      i|
|  i   -4      i|

------------------------------------------------------------------------------------------------------------------------
The output will look like this:

The original matrix was read from file rotation.txt:
|-0.6 0.8   0|
| 0.8 0.6   0|
|   0   0  -1|

Transposed matrix:
|-0.6 0.8   0|
| 0.8 0.6   0|
|   0   0  -1|

Row reduced echelon form:
|1 0 0|
|0 1 0|
|0 0 1|

Rank: 3
Trace: -1
Determinant: 1

Inverted matrix:
|-0.6 0.8   0|
| 0.8 0.6   0|
|   0   0  -1|

Orthogonal transformations:
Transformation type: rotation
Rotation axis: [1, 2, 0]
Rotation angle (degrees): 180
------------------------------------------------------------------------------------------------------------------------
But sure not all matrices can be analyzed fully programm will show you the reason of it.
For example: not squared matrices can only support transposition, rank calculation, row reduced echelon form.
------------------------------------------------------------------------------------------------------------------------
The programm was written in C++.