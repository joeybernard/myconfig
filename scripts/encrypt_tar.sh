tar -czf - * | openssl enc -e -aes256 -out $1
