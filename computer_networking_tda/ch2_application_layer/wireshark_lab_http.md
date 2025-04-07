# WireShark Lab [HTTP]
* Link to the lab is [here](https://www-net.cs.umass.edu/wireshark-labs/Wireshark_HTTP_v8.0.pdf) 

## Lab
###1) Answers
1. HTTP/1.1
2. en-US, en
3. 192.168.29.113
4. 128.119.245.12
5. 200
6. Mon, 07 Apr 2025 05:59:01 GMT
7. 128
8. No, all headers are visible in the packet content

###2) Answers
1. No
2. Yes. The data is appended to the response body at the end
3. Yes. If-Modified-Since: Mon, 07 Apr 2025 05:59:01 GMT
4. 304 Not Modified. No, it didn't return the content since the contents of the file were not modified since the time value mentioned in the If-Modified-Since header.

###3) Answers
1. One, 724
2. 737
3. 200 OK
4. Three. 734, 735, 736.

###4) Answers
1. 3. Logo -> 128.119.245.12, Book -> 178.79.137.164
2. Sequential. Since the response packet for image1 arrived before the request packet for image 2 was sent

###5) Answers
1. HTTP/1.1 401 Unauthorized
2. Authorization: Basic d2lyZXNoYXJrLXN0dWRlbnRzOm5ldHdvcms=


