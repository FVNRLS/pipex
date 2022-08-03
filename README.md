# pipex

<br>**About The Project**

The program mimics the actual C system/bash command ' | ' (Pipe).


<br>**Getting Started**

to compile only the mandatory part:

`make all`

to compile the bonus part:

`make bonus`

<br>**Prerequisites**

Installed C compiler like gcc, cc or clang.


<br>**Usage**

Mandatory part: The program should repeat the behaviour of the next shell command: 

`file1 cmd1 | cmd2 > file2`

<br>Bonus Part:

_Program need handle multiple pipes_

`./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2`

_Support << and >>, when instead of file1 is here_doc:_

`./pipex here_doc LIMITER cmd1 cmd2 file2
`

<br>**Contributing**

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement". Don't forget to give the project a star! Thanks again!


<br>**Acknowledgments**

Many thanks for support and patience to:
<br>Didar [https://github.com/4funoO/]