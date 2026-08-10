# How I Track Books and Reading With Obsidian

![rw-book-cover](https://readwise-assets.s3.amazonaws.com/static/images/article3.5c705a01b476.png)

## Metadata
- Author: [[ajy.co]]
- Full Title: How I Track Books and Reading With Obsidian
- Category: #articles
- Summary: The author discusses how they use Obsidian to track their book reading, as an alternative to platforms such as Goodreads or Bookwyrm. They describe a unique system that allows for rereads and provides a template for adding book notes to Obsidian. The author also provides instructions for configuring the necessary plugins and using DataviewJS to visualize book data. They suggest using the Air Quotes plugin to take notes and quote from books for further extension of the system.
- URL: https://ajy.co/how-i-track-books-and-reading-with-obsidian/

## Highlights
- --- title: "{{title}}" author: {{author}} series: seriesnumber: rating: readdates: - started: finished: shelf: toread list: publisher: {{publisher}} publish: {{publishDate}} pages: {{totalPage}} isbn: {{isbn10}} {{isbn13}} cover: <%=book.coverUrl ? `https://books.google.com/books/publisher/content/images/frontcover/${[...book.coverUrl.split("&")[0].matchAll(/id.?(.*)/g)][0][1]}?fife=w600-h900&source=gbs_api` : ''%> dateCreated: {{date}} --- ![cover|150]({{coverUrl}}) ## {{title}} ### Description {{description}} ([View Highlight](https://read.readwise.io/read/01krfc61eckdzhwkzt80cw759j))
- TABLE WITHOUT ID "![cover|80](" + cover + ")" AS "Cover", title, author, series FROM "books" WHERE shelf="toread" SORT title ASC ([View Highlight](https://read.readwise.io/read/01krfcgj3156cgmjkme3wjczsa))
- TABLE WITHOUT ID
  "![cover|80](" + cover + ")" AS "Cover",
  title,
  author, series
  FROM "books"
  WHERE shelf="reading"
  SORT started ASC
  **Bookshelf: stopped reading** ([View Highlight](https://read.readwise.io/read/01krfcmtjq7pvr0qvxj08d6qnr))
