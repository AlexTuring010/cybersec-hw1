I connected to the service using:

```
nc shell.hackintro25.di.uoa.gr 9957
```

It told me my cup still had **770,777,371 drops** of water, and I needed to bring it to **0**. The catch: I could only **add** drops, not drink.

From the source code, I knew the program used a **32-bit unsigned integer** to store the water drops, meaning the max value was **2^32 - 1** (4,294,967,295). To make the cup empty, I needed to cause an **overflow**.

I calculated:

```
2^32 - 770,777,371 = 428,241,245
```

So I added **428,241,245** drops, which caused the overflow, and the program gave me the flag:  
`4c7bef92996fc2f463fcefd93749715f`.
