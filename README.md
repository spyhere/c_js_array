# Implementation of JS array in C (for fun).

Since C doesn't support optional arguments or function overloading I couldn't implement some methods the same way they are done in JS (for example "slice" or "splice").

This was a really good small project to fully understand pointers, pointers on pointers, memory allocation and some other C aspects.

**Implemented methods:**
- new_array
- array_foreach
- array_filter
- array_find
- array_map
- array_push
- array_pop
- array_shift
- array_unshift
- array_sort
- array_slice
- array_splice

Regarding "new_array": I found a limitation that you must provide a terminator (or "sentinel value" as AI told me) as `0` at the end, otherwise `v_args` will not stop at the last argument and will bring garbage from heap.
AI and googling couldn't help me solve this problem. Though with my poor debugging skills I found out that when function is not returning anything (`void`) then it works without `0`, but when function is returning a pointer then this happens.
Would be nice to understand what's going there.

### AI 
I used AI to answer some of the questions I couldn't find answers online or to explain something I couldn't find explanation online.
[My conversation with AI](https://copilot.microsoft.com/shares/226V85MQp9CJ13Y3jPXCs)
