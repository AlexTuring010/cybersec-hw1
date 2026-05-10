I started by running `ltrace` on the `path` binary to see what it was doing behind the scenes. It was making a `strcmp` call, comparing my input with the string `"feeling lucky"`. So I typed that in, and when I did, it made an `execlp` call to run a program called `fortune`.

The actual output of `fortune` didn’t really matter. What caught my attention was that it was using `execlp`, and it was resolving the `fortune` binary using the `PATH` environment variable. I checked, and the real `fortune` it was trying to run was in `/usr/games/`.

Since I had write access in my home directory, I realized I could make my own `fortune` binary there, and then change the `PATH` so my version would get run instead of the real one.

The reason this mattered is because the `path` binary had the group `choose-your-path_0`, and the `flag` file could be read by that group. Since the binary was setgid, anything it executed would inherit those group privileges. So if I could get it to run my own program, that program would be able to read the flag.

At first, I tried doing this with a shell script, just using `cat` to read the flag. But that didn’t work — I think the group privileges didn’t carry over when running a script like that.

So next, I wrote a simple C program that opened the `flag` file and printed it. I compiled it, named it `fortune`, and put it in my home directory. Then I updated the `PATH` to point to my directory first, ran the `path` binary, typed `"feeling lucky"`, and boom — my `fortune` program got executed with the right group privileges, and it printed the flag.
