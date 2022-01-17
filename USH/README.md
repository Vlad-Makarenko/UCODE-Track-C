# This is my solution for the ``` USH ``` challenge.

## Description
This is a basic command line interpreter with features that no shell can be without. 
```zsh``` was taken as reference.

The program:
 * has the default prompt  look like ```u$h> ```, followed by a space character
 * works with only one line of user input. Otherwise, an appropriate descriptive error message will appear
 * implements builtin commands without flags: ```export, unset, exit, fg```
 * implements the following builtin commands with flags:
    * ```env``` with ```-i```, ```-P```, ``-u``
    * ```cd``` with ```-s```, ```-P``` and ``-`` argument
    * ```pwd``` with ```-L```, ```-P```
    * ```which``` with ```-a```, ```-s```
    * ```echo``` with ```-n```, ```-e```, ``-E``
 * correctly manages errors 
 * manages signals ```CTRL+D```,``CTRL+C`` and ```CTRL+Z```
 * run programs located in the directories listed in the ``PATH`` variable
 * implements the command separator ```;```
 * manages these expansions correctly:
    * the tilde expansion ``~``  with the following tilde-prefixes: ``~`` ,```~/dir_name```,```~username/dir_name```,```~+/dir_name```,```~-/dir_name```
    * the basic form of parameter expansion ```${parameter}```
    * the two-level-nested command substitution ```$(command)```
    