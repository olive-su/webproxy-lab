# [Krafton Jungle Week07] proxy server κ΅¬ν

<br>

- π μ§ν κΈ°κ° : 2022. 12. 08. ~ 2022. 12. 14.
- π κ³Όμ  μ€λͺ : [GUIDELINES.md](./GUIDELINES.md)
- π­ κ°λ° μΌμ§ : [[Krafton Jungle | TIL_22.12.12 - 13] Webproxy Lab κ΅¬ν](https://olive-su.tistory.com/434)
- π ν¨μ μ€λͺ κ΄λ ¨ λνλ¨ΌνΈ : [Jungle olive-su | Webproxy-Lab](https://jungle-olivesu.netlify.app/webproxy-lab/html/proxy_8c.html) Β© doxygen
- π μ°Έκ³  μλ£ : [cmu_proxylab](./proxylab.pdf)

<br>

---

### π TEST RESULT

- Dealing with multiple concurrent requests

<br>

- input

```bash
>>> make
>>> ./driver.sh
```

<br>
- score : 55/70

<br>

- output

```bash
*** Basic ***
>>> Starting tiny on 6635
>>> Starting proxy on 2248
>>> 1: home.html
>>>    Fetching ./tiny/home.html into ./.proxy using the proxy
>>>    Fetching ./tiny/home.html into ./.noproxy directly from Tiny
>>>    Comparing the two files
>>>    Success: Files are identical.
>>> 2: csapp.c
>>>    Fetching ./tiny/csapp.c into ./.proxy using the proxy
>>>    Fetching ./tiny/csapp.c into ./.noproxy directly from Tiny
>>>    Comparing the two files
>>>    Success: Files are identical.
>>> 3: tiny.c
>>>    Fetching ./tiny/tiny.c into ./.proxy using the proxy
>>>    Fetching ./tiny/tiny.c into ./.noproxy directly from Tiny
>>>    Comparing the two files
>>>    Success: Files are identical.
>>> 4: godzilla.jpg
>>>    Fetching ./tiny/godzilla.jpg into ./.proxy using the proxy
>>>    Fetching ./tiny/godzilla.jpg into ./.noproxy directly from Tiny
>>>    Comparing the two files
>>>    Success: Files are identical.
>>> 5: tiny
>>>    Fetching ./tiny/tiny into ./.proxy using the proxy
>>>    Fetching ./tiny/tiny into ./.noproxy directly from Tiny
>>>    Comparing the two files
>>>    Success: Files are identical.
>>> Killing tiny and proxy
>>> basicScore: 40/40
>>>
*** Concurrency ***
>>> Starting tiny on port 7890
>>> Starting proxy on port 24826
>>> Starting the blocking NOP server on port 4254
>>> Trying to fetch a file from the blocking nop-server
>>> Fetching ./tiny/home.html into ./.noproxy directly from Tiny
>>> Fetching ./tiny/home.html into ./.proxy using the proxy
>>> Checking whether the proxy fetch succeeded
>>> Success: Was able to fetch tiny/home.html from the proxy.
>>> Killing tiny, proxy, and nop-server
>>> concurrencyScore: 15/15
>>>
>>> *** Cache ***
>>> Starting tiny on port 29345
>>> Starting proxy on port 19209
>>> Fetching ./tiny/tiny.c into ./.proxy using the proxy
>>> Fetching ./tiny/home.html into ./.proxy using the proxy
>>> Fetching ./tiny/csapp.c into ./.proxy using the proxy
>>> Killing tiny
>>> Fetching a cached copy of ./tiny/home.html into ./.noproxy
>>> Failure: Was not able to fetch tiny/home.html from the proxy cache.
>>> Killing proxy
>>> cacheScore: 0/15
>>>
>>> totalScore: 55/70
```

<br>

<br>

|[<img src="https://user-images.githubusercontent.com/67156494/210132307-34f87ef7-3e26-4b00-8fc1-a73c971865b4.png" width=120>](https://github.com/Krafton-Jungle-W07-Team01/Team01-webproxy-lab)
|-----|
| [Week07 Team 1 Repository](https://github.com/Krafton-Jungle-W07-Team01/Team01-webproxy-lab) |
