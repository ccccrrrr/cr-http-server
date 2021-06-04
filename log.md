# http-server
## socket
Client: socket() ---------------------------> connect() -> I/O -> close()

replace client to chrome...

Server: socket() --> bind() --> listen() --> accept() --> I/O --> close()

content:

receive this:

```html
GET /index.html HTTP/1.1
Host: localhost:8080
Connection: keep-alive
sec-ch-ua: " Not;A Brand";v="99", "Google Chrome";v="91", "Chromium";v="91"
sec-ch-ua-mobile: ?0
Upgrade-Insecure-Requests: 1
User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.77 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9
Sec-Fetch-Site: none
Sec-Fetch-Mode: navigate
Sec-Fetch-User: ?1
Sec-Fetch-Dest: document
Accept-Encoding: gzip, deflate, br
Accept-Language: zh-CN,zh;q=0.9,en-US;q=0.8,en;q=0.7
Cookie: Goland-4d324af9=71ed9c14-8c23-4367-b5bd-025f47290ebe
```

send this:

```
HTTP/1.1 200 OK
Content-Type:text/html
Content-Length:364

<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport"
          content="width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>root</title>
</head>
<body>
<div>
    Hello, my name is cccrrr!
</div>
</body>
</html>
```

day 1: create `client.c` and `server.c`，完成基本的客户端和服务器端的数据传输

day 2: 明天考数电了，没什么时间写，修改好了服务器端返回GET请求，目前只能返回html文件，并且代码写的有点乱，需要后续更加合理的设计。



### to-do list

| element                          | check |
| -------------------------------- | ----- |
| show html file                   |       |
| refractor                        |       |
| 200, 404, ..., different headers |       |
| refractor                        |       |
| TBC                              |       |
|                                  |       |
|                                  |       |
| epoll                            |       |
| refractor                        |       |
