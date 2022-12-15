# [Krafton Jungle Week07] proxy server 구현

<br>

- 📅 진행 기간 : 2022. 12. 08. ~ 2022. 12. 14.
- 📃 과제 설명 : [GUIDELINES.md](./GUIDELINES.md)
- 🗂 함수 설명 관련 도큐먼트 : [Jungle olive-su | webproxy-Lab](https://jungle-olivesu.netlify.app/webproxy-lab/html/proxy_8c.html) © doxygen
- 📖 참고 자료 : [cmu_proxylab](./proxylab.pdf)

<br>

---

### 🎉 TEST RESULT

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
