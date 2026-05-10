Of course I could do it in time. I am Agent X, after all — the one they call when _everything else fails_. A mission like this? Just a walk in the park. A very explosive park, maybe, but a park nonetheless.

I opened my laptop, connected to the Chimera spy server using the provided credentials — `agent:agent42`. The enemy thought they were clever, rigging their systems with a time bomb that wipes the data after mere minutes. But they forgot one thing: I _thrive_ under pressure.

Naturally, I spent the first five minutes making myself some mint tea. You see, mint isn't just my favorite flavor — it sharpens the mind, soothes the nerves, and relieves the headaches caused by having to diffuse bombs every other Monday. The kettle whistled just as the countdown hit five minutes.

I took a sip.

Back to work.

The `/bomb/flag` file? Inaccessible. No surprise there — too easy. But `/bomb/bomb`? That was the real target. An executable, clearly rigged with group privileges granting access to the flag if — and only if — the correct input was provided.

I knew better than to trust surface-level tricks. So I pulled out my toolset — `objdump -d /bomb/bomb` — and dove into the assembly. I spotted the main function, and in it, a golden clue: a call to a `reveal_flag` function. But it was guarded — the program was checking for a specific argument to be passed before it would call it.

No `strcmp` — just raw, low-level `cmp` instructions. That’s how I knew I was dealing with professionals.

They compared my input directly to two 32-bit hex values:

- `0x76617274`
- `0x79747365`

I didn’t even flinch.

Most would stop, google, open up an ASCII table. Not me. I’ve had the ASCII table memorized since the academy. I took one look:

- `0x76617274` = bytes `74 72 61 76` → `"trav"`
- `0x79747365` = bytes `65 73 74 79` → `"esty"`

Put them together?

**"travesty"**.

A cruel joke, maybe. But the only joke was how easy this was for someone like me.

I ran the program:

```bash
./bomb travesty
```

And just like that — the flag appeared, seconds before the bomb’s digital clock hit zero.

I didn’t even spill my tea.

Mission accomplished.

Because I don’t just get the job done.  
I _am_ the job.

— Agent X ☕💻  
_Encrypted. Extracted. Exfiltrated._
