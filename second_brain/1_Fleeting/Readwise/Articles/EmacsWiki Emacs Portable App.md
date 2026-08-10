# EmacsWiki: Emacs Portable App

![rw-book-cover](https://readwise-assets.s3.amazonaws.com/static/images/article2.74d541386bbf.png)

## Metadata
- Author: [[emacswiki.org]]
- Full Title: EmacsWiki: Emacs Portable App
- Category: #articles
- Summary: The standard MS-Windows binaries is already portable, in that you can just unzip it anywhere and run it directly. To keep your .
- URL: https://www.emacswiki.org/emacs/EmacsPortableApp

## Highlights
- To keep your `.emacs.d` in a directory called `emacshome` on your USB stick next to the unzipped Emacs, create a `runemacs.bat` file in Emacs’ `bin/` directory with contents:
  set HOME=%~dp0..\..\emacshome
  "%~dp0runemacs.exe" %*
  and then use that instead of `runemacs.exe`. ([View Highlight](https://read.readwise.io/read/01kh748vfpdtzwb7xqftfvfk0k))
