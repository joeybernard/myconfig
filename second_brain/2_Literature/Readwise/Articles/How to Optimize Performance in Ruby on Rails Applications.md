# How to Optimize Performance in Ruby on Rails Applications

![rw-book-cover](https://miro.medium.com/v2/resize:fit:1200/1*8QR3do3bBcWgu0ziKvqbYw.jpeg)

## Metadata
- Author: [[bernard bebeni]]
- Full Title: How to Optimize Performance in Ruby on Rails Applications
- Category: #articles
- Summary: Enhancing Speed and Efficiency: Strategies for Boosting Performance in Ruby on Rails Applications
- URL: https://medium.com/@bernardbebeni/how-to-optimize-performance-in-ruby-on-rails-applications-28023613cf9a

## Highlights
- Properly designed and optimized database queries can significantly improve performance. Utilize query optimization techniques like eager loading, selective column retrieval, and efficient joins to minimize query execution time.
  Example of using eager loading in Rails ActiveRecord. ([View Highlight](https://read.readwise.io/read/01kg8xnxs1gznrdh21wz03jd9m))
- Properly indexed database tables can accelerate query execution. Identify frequently accessed columns and create indexes on them to optimize query performance. ([View Highlight](https://read.readwise.io/read/01kg8xphcj3a9t6v3t8dqh60n2))
- Efficiently managing database connections and connection pooling can reduce the overhead of establishing new connections, improving performance. ([View Highlight](https://read.readwise.io/read/01kg8xqc6cvq3mafbmsas3d84q))
- Page caching stores the entire HTML output of a page and serves it directly without invoking Rails. Action caching stores the result of a specific action in the cache, allowing subsequent requests to be served from the cache. ([View Highlight](https://read.readwise.io/read/01kg8xrrmzavn7gtywsa4vjhvn))
- Avoid making excessive database queries directly in views. Instead, eager load necessary data in the controller to reduce the number of database hits. ([View Highlight](https://read.readwise.io/read/01kg8xt541er0j8f3r7qzmhpqj))
