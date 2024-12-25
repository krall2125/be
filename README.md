# be - the dumbest text editor based on ed
why would you use it? it'ß not even finished also you have to input ascii codes of characters instead of the actual characters because this dumb shit is made for editing binary files.

# how to install
## windows
good luck
## macos
i don't know
## leenoocks and probably every other unix
requirements:
- preferably a C compiler
- probably cmake (you could also build by hand)
- gnu make (optional) (you could also build and install by hand)
- git

run these dumb commands (not a virus)
```sh
git clone https://github.com/krall2125/be.git
```
also
```sh
cd be
```
&
```sh
mkdir -p build && cd build
```
andalso
```sh
cmake ..
```
also (unless you don'þ want it in your `bin` folder)
```sh
sudo make install
# use gmake instead of make on freebsd
```

# how to use
first of all, don't. there's better editors out there.
but if you're a masochist (should tbh just use ed)
## modes
there are 3 modes `CMD`, `INSERT` and `ASCII`
`CMD` is the main mode where you move around the code and execute commands on it
`INSERT` is a mode where you input the ascii codes of characters you want to insert
`ASCII` is your average insert mode where you just input ascii characters

### switching through modes
`CMD` -> `INSERT` - `i` command
`INSERT` -> `CMD` - `.` or any other non-numeric character
`CMD` -> `ASCII` - `I` command
`ASCII` -> `CMD` - escape character just press `Esc` on your keyboard and enter

## command mode commands
there's only a few commands in this text editor
- `i` enter insert mode
- `s` substitute (currently the only more-than-one-character-long-command)
- `j` go to next line (stay on the same line if there is no next line)
- `k` go to previous line (stay on the same if there's no previous)
- `p` print the current line
- `w` write to the file
- `a` append to the end of the line
- `I` enter ascii mode

### substitute command
the syntax is:
```
s/b1/b2/c/s
```
where:
- b1 is the ascii code of the value to be replaced
- b2 is the ascii code to be replaced with
- c is the amount of replacements to do on the current line
- s is the number of the occurrence of the byte to start replacing on (usually it is 0)
in other words, it replaces `c` bytes of ascii code `b1` with `b2` starting from the `s`th occurrence.
