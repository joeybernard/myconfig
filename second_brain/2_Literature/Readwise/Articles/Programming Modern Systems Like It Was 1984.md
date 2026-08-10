# Programming Modern Systems Like It Was 1984

![rw-book-cover](https://readwise-assets.s3.amazonaws.com/static/images/article0.00998d930354.png)

## Metadata
- Author: [[dadgum.com]]
- Full Title: Programming Modern Systems Like It Was 1984
- Category: #articles
- Summary: Imagine a 1984 programmer waking in 2014 and choosing simplicity over hyper-optimization. Build small, self-contained programs that talk to each other and avoid heavy, fragile toolchains. Use high-level languages and keep things fast by design, not by micro-tuning.
- URL: https://prog21.dadgum.com/201.html

## Highlights
- **Something is wrong if most programs don't run instantaneously.** Why does this little command line program take two seconds to load and print the version number? It would take serious effort to make it that slow. Why does a minor update to a simple app require re-downloading all 50MB of it? Why are there 20,000 lines of code in this small utility? Why is no one questioning any of this? ([View Highlight](https://read.readwise.io/read/01kvzpwhxhwjx3j6dxerk534xg))
- **Design applications as small executables that communicate.** Everything is set-up for this style of development: multi-core processors, lots of memory, native support for pipes and sockets. This gives you multi-core support without dealing with threads. It's also the most bulletproof way of isolating components, instead of the false confidence of marking class members "private." ([View Highlight](https://read.readwise.io/read/01kvzpxpj472b9jkc67r0qwy6x))
- **Don't write temporary files to disk, ever.** There's so much RAM you can have nightmares about getting lost in it. On the most fundamental level, why isn't it possible to create and execute a script without saving to a file first? Why does every tweak to a learning-the-language test program result in a two megabyte executable that shortly gets overwritten? ([View Highlight](https://read.readwise.io/read/01kvzpy7kj9ye78s6a78vt3a7z))
- **C still doesn't have a module system?** Seriously? And people are still using it, despite all the alternatives? ([View Highlight](https://read.readwise.io/read/01kvzpyqqty4wavy92se0623m7))
