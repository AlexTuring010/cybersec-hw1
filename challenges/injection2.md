Dr. Bovik made some improvements to his echo server after the last breach. He patched up the obvious holes, filtered out backticks, dollar signs, and some other special characters. This time, it wasn’t as straightforward—but it still wasn’t secure.

He might’ve closed a few doors, but he left a window open.

When I first connected to the server at `shell.hackintro25.di.uoa.gr:14126`, I knew the classic injection tricks were off the table. Special characters like `$`, `` ` ``, and even plain old spaces were filtered.

No command substitution, no argument separation. Tough, but not unbreakable.

I started with the wildcard character:

```
*
```

Since the server runs something like `echo <your_input>`, inputting `*` results in:

```
echo *
```

This gets expanded by the shell into all filenames in the current directory. Jackpot. It revealed the contents of Dr. Bovik’s working directory—one of which was a very suspicious file called `key`.

The next goal was obvious: read the `key` file. But how?

In a Unix shell, the `|` operator takes the **output of the command on the left** and **passes it as input to the command on the right**.

So something like:

```bash
echo a | cat key
```

…would normally echo `a`, and then `cat key` would just read from the `key` file—but since `cat` doesn’t care about the piped input when you give it a filename, it just happily outputs the contents of `key`.

But again, **spaces were blocked**. So I needed another separator.

Turns out: **tabs still worked**.

So I crafted a payload using a tab instead of a space. Like this (using `\t` to represent the actual tab character):

```
echo\ta|cat\tkey
```

When sent to the server, it executed:

```
echo a | cat key
```

And just like that—the contents of the `key` file were dumped to me.

Dr. Bovik thought his fortress was secure, but he forgot the golden rule: **never trust user input**. Even without spaces or special characters, there are always creative ways around filters.
