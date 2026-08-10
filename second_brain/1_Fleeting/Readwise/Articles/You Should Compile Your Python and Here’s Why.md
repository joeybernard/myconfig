# You Should Compile Your Python and Here’s Why

![rw-book-cover](https://glyph.twistedmatrix.com/images/favicon.ico)

## Metadata
- Author: [[twistedmatrix.com]]
- Full Title: You Should Compile Your Python and Here’s Why
- Category: #articles
- Summary: The text discusses ways to make Python code faster, such as optimizing with type annotations and using tools like Mypyc. It emphasizes the importance of improving Python's performance without sacrificing readability. The author encourages using Mypyc to enhance Python's speed and challenges the passive consensus on relying solely on the standard interpreter for performance gains.
- URL: https://glyph.twistedmatrix.com/2022/04/you-should-compile-your-python-and-heres-why.html

## Highlights
- The progression from “idiomatic Python” to “optimized Python” to “C” is a *one-way process* that gradually loses the advantages that brought us to Python in the first place. ([View Highlight](https://read.readwise.io/read/01kh76e2snwf2sn8fd9xtk79va))
- There are also a number of tools that have long been in use for addressing this problem: PyPy, Pyrex, Cython, Numba, and Numpy to name a few. ([View Highlight](https://read.readwise.io/read/01kh76r13nk9cjrrknpnj9n050))
- Cython and Numba aren’t really “Python” any more, because they require special-purpose performance-oriented annotations. ([View Highlight](https://read.readwise.io/read/01kh76s655m54ntr2jg6nyk9jp))
- PyPy gets the closest — it’s definitely regular Python — but its strategy has important limitations. Primarily, despite the phenomenal and heroic effort that went into [`cpyext`](https://morepypy.blogspot.com/2018/09/inside-cpyext-why-emulating-cpython-c.html), it seems like [there’s always just *one* PyPy-incompatible library](https://towardsdatascience.com/pypy-is-faster-than-python-but-at-what-cost-12739bf2b8e9) in every large, existing project’s dependency list which makes it impossible to just drop in PyPy without doing a bunch of arcane debugging first. ([View Highlight](https://read.readwise.io/read/01kh76sqr5r2asb7mk417rkny7))
