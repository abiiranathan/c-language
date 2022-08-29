# Using curl effectively

curl <url>

1. -s /--silent : Silence verbose output
2. -i : Include response headers in output
3. -I : Show only headers
4. -L : Follow redirects
5. curl https://example.com/[1-9].html /[a-z].html/[01-99].html : URL globbing
6. -o : Save to file: curl https://example.com[1-9].html -o save_#1.html
7. curl https://archive.example/issue[1996-1999]/vol[1-4]/part{a,b,c}.html
8. -v/--verbose: Verbose mode
9. -H: Custom header -H "User-agent: disco" -H "Magic: disco"
10. -H: Remove Header by ignoring header value: -H "User-agent:"
11. -d : POST data -d name=Daniel https://server.com
12. -d @file: POST a file: -d @file https://server.com/upload -o saved
13. ls -l | curl -d @- https://server.com : Read from stdin
14. ls -l | curl --data-binary @- https://server.com -o saved : Send binary data(as is)
15. curl --data-binary @file.json -H "Content-Type: application/json" url
16. curl -T localfile -i https://remote_server : PUT a file(replace)
17. Avoid -X if possible. -X means use this method for all requests(even redirects)
18. curl -c cookiejar.txt https://example.com : Save all cookies
19. curl -b cookiejar.txt https://example.com : Read back all the cookies
    
## Cookie usage login
curl -c cookiejar.txt https://example.com/login_form
curl -b cookiejar.txt -c cookiejar.txt https://example.com/login -d user=daniel -d password=1234
curl -b cookiejar.txt -c cookiejar.txt https://example.com/profile

20. -k : Ignore certificate problems on https(does not work with cookies). Avoid
21. curl https://example.com/ --resolve example.com:443:127.0.0.1 (works with cookies and virtual servers)
22. --trace-ascii - : More verbosity > -v option: curl https://example.com --trace-ascii -
23. -w/--write-out: curl https://example.com -o saved -w "%{json}" | jq : Extract metadata from the request
24. --libcurl: curl https://example.com --libcurl sourcecode.c
25. --http1.0/--http1.1/--http2/--http3: Specify http version
26. curl -d user=nathan https://server.com --next https://server.com : Chain requests