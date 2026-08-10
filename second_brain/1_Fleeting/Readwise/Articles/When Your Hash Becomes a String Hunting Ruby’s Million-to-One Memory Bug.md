# When Your Hash Becomes a String: Hunting Ruby’s Million-to-One Memory Bug

![rw-book-cover](https://cdn.mensfeld.pl/wp-content/uploads/2025/11/bug.jpg)

## Metadata
- Author: [[Maciej Mensfeld]]
- Full Title: When Your Hash Becomes a String: Hunting Ruby’s Million-to-One Memory Bug
- Category: #articles
- Summary: FFI versions before 1.17.0 missed write barriers in their C extension, so Ruby's GC could free internal Hash objects that FFI still pointed to. Ruby could then allocate a new object (like a String) at the same memory address, causing bizarre runtime errors. The fix is to use RB_OBJ_WRITE write barriers so the GC knows about those C-held references.
- URL: https://mensfeld.pl/2025/11/ruby-ffi-gc-bug-hash-becomes-string

## Highlights
- Sometimes the obvious answer is wrong. ([View Highlight](https://read.readwise.io/read/01kezvsjp1e60vxk1q5q3msr9v))
- **The timing of GC matters as much as whether GC happens.** ([View Highlight](https://read.readwise.io/read/01kezvsyg3efegxswdqtp4pmys))
- Million-to-one bugs are real, not theoretical. ([View Highlight](https://read.readwise.io/read/01kezvtd1a9mv3p6vfm604xvsk))
- Diagnostic scripts can test the wrong layer. ([View Highlight](https://read.readwise.io/read/01kezvtkxcrdcemq28r6hqbmt8))
- Patience and persistence matter. ([View Highlight](https://read.readwise.io/read/01kezvtv03z14dcfa4acp5t4ye))
