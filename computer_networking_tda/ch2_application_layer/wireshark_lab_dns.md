# Wireshark Lab [DNS]
* Link to the lab is [here](https://www-net.cs.umass.edu/wireshark-labs/Wireshark_DNS_v8.0.pdf)

## Lab

### 1) Anwers
1. Zerodha.com -> 104.18.116.40, 104.18.117.40
2. Oxford.ac.uk -> 151.101.194.216, 151.101.130.216, 151.101.66.216, 151.101.2.216
3. mta7.am0.yahoodns.net.

### 3) Answers
1. Yes. UDP
2. Source -> 51005, Dest -> 53
3. 192.168.29.1. Yes
4. Standard query.No
5. 2
   
  ```www.ietf.org: type A, class IN, addr 104.16.45.99
    Name: www.ietf.org
    Type: A (1) (Host Address)
    Class: IN (0x0001)
    Time to live: 237 (3 minutes, 57 seconds)
    Data length: 4
    Address: 104.16.45.99
    ```
    
   
    ```
    www.ietf.org: type A, class IN, addr 104.16.44.99
    Name: www.ietf.org
    Type: A (1) (Host Address)
    Class: IN (0x0001)
    Time to live: 237 (3 minutes, 57 seconds)
    Data length: 4
    Address: 104.16.44.99
   
   ```

6. Yes. ipv6 address in AAAA records returned
7. No.
8. Both 53
9. Yes, ipv6 -> 2405:201:a40e:4052::c0a8:1d01
10. Standard query. Yes.
11.  3

    ```
    Answers
    www.mit.edu: type CNAME, class IN, cname www.mit.edu.edgekey.net
        Name: www.mit.edu
        Type: CNAME (5) (Canonical NAME for an alias)
        Class: IN (0x0001)
        Time to live: 1 (1 second)
        Data length: 25
        CNAME: www.mit.edu.edgekey.net
    www.mit.edu.edgekey.net: type CNAME, class IN, cname e9566.dscb.akamaiedge.net
        Name: www.mit.edu.edgekey.net
        Type: CNAME (5) (Canonical NAME for an alias)
        Class: IN (0x0001)
        Time to live: 1 (1 second)
        Data length: 24
        CNAME: e9566.dscb.akamaiedge.net
    e9566.dscb.akamaiedge.net: type A, class IN, addr 2.23.33.163
        Name: e9566.dscb.akamaiedge.net
        Type: A (1) (Host Address)
        Class: IN (0x0001)
        Time to live: 1 (1 second)
        Data length: 4
        Address: 2.23.33.163
            
     ```
     
11. ![image](https://github.com/user-attachments/assets/5dbbd60c-a1bc-4afd-9103-622b8213750f)

12. Yes, ipv6 -> 2405:201:a40e:4052::c0a8:1d01
13. Standard query of NS type. Yes
14. 8
15. 
    ```
    
    Answers
    mit.edu: type NS, class IN, ns usw2.akam.net
        Name: mit.edu
        Type: NS (2) (authoritative Name Server)
        Class: IN (0x0001)
        Time to live: 167905 (1 day, 22 hours, 38 minutes, 25 seconds)
        Data length: 15
        Name Server: usw2.akam.net
    mit.edu: type NS, class IN, ns asia1.akam.net
        Name: mit.edu
        Type: NS (2) (authoritative Name Server)
        Class: IN (0x0001)
        Time to live: 167905 (1 day, 22 hours, 38 minutes, 25 seconds)
        Data length: 8
        Name Server: asia1.akam.net
    mit.edu: type NS, class IN, ns asia2.akam.net
        Name: mit.edu
        Type: NS (2) (authoritative Name Server)
        Class: IN (0x0001)
        Time to live: 167905 (1 day, 22 hours, 38 minutes, 25 seconds)
        Data length: 8
        Name Server: asia2.akam.net
    mit.edu: type NS, class IN, ns use2.akam.net
        Name: mit.edu
        Type: NS (2) (authoritative Name Server)
        Class: IN (0x0001)
        Time to live: 167905 (1 day, 22 hours, 38 minutes, 25 seconds)
        Data length: 7
        Name Server: use2.akam.net
    mit.edu: type NS, class IN, ns ns1-37.akam.net
        Name: mit.edu
        Type: NS (2) (authoritative Name Server)
        Class: IN (0x0001)
        Time to live: 167905 (1 day, 22 hours, 38 minutes, 25 seconds)
        Data length: 9
        Name Server: ns1-37.akam.net
    mit.edu: type NS, class IN, ns ns1-173.akam.net
        Name: mit.edu
        Type: NS (2) (authoritative Name Server)
        Class: IN (0x0001)
        Time to live: 167905 (1 day, 22 hours, 38 minutes, 25 seconds)
        Data length: 10
        Name Server: ns1-173.akam.net
    mit.edu: type NS, class IN, ns eur5.akam.net
        Name: mit.edu
        Type: NS (2) (authoritative Name Server)
        Class: IN (0x0001)
        Time to live: 167905 (1 day, 22 hours, 38 minutes, 25 seconds)
        Data length: 7
        Name Server: eur5.akam.net
    mit.edu: type NS, class IN, ns use5.akam.net
        Name: mit.edu
        Type: NS (2) (authoritative Name Server)
        Class: IN (0x0001)
        Time to live: 167905 (1 day, 22 hours, 38 minutes, 25 seconds)
        Data length: 7
        Name Server: use5.akam.net
        
    ```

16. <img width="779" alt="image" src="https://github.com/user-attachments/assets/22fa614b-038e-48c6-abea-41eebc3ed896" />

   
