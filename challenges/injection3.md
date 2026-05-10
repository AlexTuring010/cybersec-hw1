Dr. Bovik was clearly shaken after the last breach. This time, he didn’t just patch things up — he went full cloak-and-dagger. No source code to peek at, no obvious tells. Just an echo server and a sense of paranoia.

When I connected to the server at `shell.hackintro25.di.uoa.gr:14127`, I started with the usual: poking around.

I sent:

```
a | ls -a
```

And just like that, the directory spilled its secrets. Among the files was the ever-suspicious one: `key`.

Naturally, I tried the obvious next step:

```
a | cat key
```

But instead of the flag, I got a snarky message:

```
Would never give you the key so easily
```

At first I thought maybe that was the content of the file — but nah, it didn’t take long to realize **any** time the word `"key"` showed up in my input, this generic message came back. I could’ve typed `monkey` and it still would’ve triggered.

So how do you read a file you can’t say out loud?

Simple. Don’t say it.

Instead, I crafted a pipeline to _discover_ the file without directly referencing it. Here's the payload I used:

```
a | ls | grep ke | xargs cat
```

Let me explain the magic:

- `ls` lists all files in the directory
- `grep ke` filters that list to only show filenames containing `"ke"` — which matches `key`, but crucially, I never typed the full word
- `xargs cat` takes the filename output from `grep` and feeds it as an argument to `cat`

So `cat` ends up reading the file **indirectly**, bypassing the word filter entirely.

The program never saw me type `"key"` — the shell pieced it together _for me_.

Dr. Bovik thought he was clever. But in a shell, there’s always more than one way to skin a cat — or in this case, a `cat key`.
