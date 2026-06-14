# 📘 NGINX Interview & Learning Notes
> **Target:** DevOps / SRE Interviews | 10–20 LPA Range  
> **Covers:** Core Concepts → Config → Performance → Security → Real-world → Interview Q&A

---

## Table of Contents
1. [Introduction](#1-introduction)
2. [Core Concepts](#2-core-concepts)
3. [Installation & Basic Setup](#3-installation--basic-setup)
4. [Important Configuration Blocks](#4-important-configuration-blocks)
5. [Reverse Proxy & Load Balancing](#5-reverse-proxy--load-balancing)
6. [Performance & Optimization](#6-performance--optimization)
7. [Security Best Practices](#7-security-best-practices)
8. [NGINX + WordPress Case Study](#8-nginx--wordpress-case-study)
9. [Common Interview Questions](#9-common-interview-questions)
10. [Hands-on Mini Project](#10-hands-on-mini-project)
11. [Cheat Sheet](#11-cheat-sheet)

---

## 1. Introduction

### What is NGINX?
NGINX (pronounced *"engine-x"*) is a high-performance, open-source web server that also functions as a **reverse proxy**, **load balancer**, **HTTP cache**, and **API gateway**. It is designed to handle **high concurrency with minimal memory usage**.

### History & Why It Was Created
- Created by **Igor Sysoev** in 2004 to solve the **C10K problem** — the challenge of handling 10,000+ concurrent connections on a single server.
- Apache (the dominant server at the time) used a **process-per-connection** model, which didn't scale well.
- NGINX used an **event-driven, asynchronous, non-blocking** architecture to handle massive concurrency efficiently.
- Open-sourced in 2004; NGINX Inc. was founded in 2011; acquired by **F5 Networks in 2019**.

### Key Use Cases

| Use Case | Description |
|---|---|
| **Web Server** | Serve static files (HTML, CSS, JS, images) directly and extremely fast |
| **Reverse Proxy** | Accept client requests and forward them to backend app servers (Node, Django, etc.) |
| **Load Balancer** | Distribute incoming traffic across multiple backend servers |
| **API Gateway** | Rate limit, authenticate, and route API requests |
| **SSL Termination** | Handle HTTPS at the edge, pass plain HTTP to backends |
| **HTTP Cache** | Cache backend responses to reduce load and improve response time |
| **Media Streaming** | Stream video/audio with efficient chunked transfer |

> **Real-world insight:** In most production setups, NGINX sits at the front (edge) of your infrastructure. The app servers (Node.js, Gunicorn, PHP-FPM) never face the internet directly.

---

## 2. Core Concepts

### Event-Driven Architecture vs Process/Thread-Based Servers

#### Apache (Traditional — Process/Thread-Based)
```
Client 1 ──► [Worker Process 1]  (1 process handles 1 request)
Client 2 ──► [Worker Process 2]
Client 3 ──► [Worker Process 3]
...
Client N ──► [Out of workers → Queue or reject]
```
- Each connection spawns (or is assigned) a thread/process.
- Threads are **expensive** — they consume memory (~8MB stack each) and have **context-switching overhead**.
- Under high load (thousands of simultaneous connections), Apache struggles.

#### NGINX (Event-Driven, Non-Blocking)
```
                      ┌──────────────────────────────────┐
Clients ──────────►  │        Event Loop (Single Thread) │
(thousands)          │  ┌────────────────────────────┐   │
                     │  │  Connection 1 (reading)    │   │
                     │  │  Connection 2 (writing)    │   │
                     │  │  Connection 3 (waiting IO) │   │
                     │  └────────────────────────────┘   │
                     └──────────────────────────────────┘
```
- A **single worker thread** can manage **thousands of connections** using OS-level I/O multiplexing (`epoll` on Linux, `kqueue` on BSD).
- When a connection is waiting for I/O (e.g., disk read, upstream response), the worker moves on to handle other connections.
- No thread is ever "blocked" waiting for slow I/O.

**Key takeaway:** NGINX uses OS event notification mechanisms. It only does work when there is work to do — it doesn't poll or spin-wait.

---

### Master-Worker Process Model

```
┌─────────────────────────────────┐
│         Master Process          │
│  - Reads & validates config     │
│  - Binds privileged ports 80/443│
│  - Spawns/manages worker procs  │
│  - Handles signals (reload/stop)│
└──────────────┬──────────────────┘
               │  forks
    ┌──────────┼──────────┐
    ▼          ▼          ▼
[Worker 1] [Worker 2] [Worker 3]   ← handle actual connections
    │
    └── Each worker runs an independent event loop
        and can handle thousands of connections
```

- **Master Process** runs as `root`, manages lifecycle. It does NOT handle client connections.
- **Worker Processes** run as `nginx` (non-privileged user) and handle all traffic.
- **Cache Manager / Cache Loader** — optional helper processes for proxy caching.

**Zero-downtime reload:** When you run `nginx -s reload`, the master process re-reads config and gracefully replaces workers (old workers finish existing connections, new workers take new ones). No downtime.

---

### How Request Handling Works Internally

```
Client Request
     │
     ▼
[Kernel TCP Stack] → accepts connection → adds to epoll watch list
     │
     ▼
[NGINX Worker's Event Loop]
     │
     ├─ Event: data received from client
     │   └─ Parse HTTP request headers
     │
     ├─ Match request to server{} block (by Host header + port)
     │
     ├─ Match request URI to location{} block
     │
     ├─ Apply directives (proxy_pass, return, try_files, etc.)
     │
     ├─ If proxy_pass → open non-blocking connection to upstream
     │   └─ Wait for upstream via epoll (no blocking!)
     │
     └─ Send response back to client → close or keep-alive
```

**Important detail:** All phases (read request, process, write response) are non-blocking. NGINX registers interest in events and continues the loop.

---

### Difference Between NGINX and Apache

| Feature | NGINX | Apache |
|---|---|---|
| **Architecture** | Event-driven, async | Process/thread per connection |
| **Concurrency** | Very high (10k+ connections/worker) | Limited by process/thread count |
| **Memory Usage** | Very low (predictable) | Grows with connections |
| **Static file serving** | Extremely fast (sendfile syscall) | Good, but slower |
| **Dynamic content** | Via proxy to app server | Via embedded modules (mod_php, etc.) |
| **Configuration** | Context-based blocks | Directive-based (.htaccess) |
| **.htaccess support** | ❌ None | ✅ Per-directory config |
| **Module loading** | Static (compiled in) | Dynamic at runtime |
| **Use in production** | Preferred for high-traffic | Still common, especially with PHP apps |

> **Interview insight:** Apache's `.htaccess` is convenient for shared hosting but terrible for performance — NGINX reads its config once and caches it. With Apache, every request may trigger a filesystem scan for `.htaccess` files up the directory tree.

---

## 3. Installation & Basic Setup

### Install Steps (Ubuntu/Debian)

```bash
# Update package list
sudo apt update

# Install NGINX
sudo apt install nginx -y

# Start and enable on boot
sudo systemctl start nginx
sudo systemctl enable nginx

# Verify status
sudo systemctl status nginx

# Verify NGINX is listening
curl -I http://localhost
# Should return: HTTP/1.1 200 OK

# Check NGINX version and compile options
nginx -V
```

### Install on RHEL/CentOS/Amazon Linux

```bash
# Add NGINX official repo (recommended for latest version)
sudo tee /etc/yum.repos.d/nginx.repo <<EOF
[nginx]
name=nginx repo
baseurl=http://nginx.org/packages/centos/\$releasever/\$basearch/
gpgcheck=0
enabled=1
EOF

sudo yum install nginx -y
sudo systemctl start nginx
sudo systemctl enable nginx
```

---

### Directory Structure

```
/etc/nginx/                     ← Main config directory
│
├── nginx.conf                  ← Main configuration file
├── conf.d/                     ← Drop-in config files (*.conf loaded automatically)
│   ├── default.conf            ← Default server block
│   └── myapp.conf              ← Your custom server blocks go here
│
├── sites-available/            ← Available site configs (Debian/Ubuntu style)
├── sites-enabled/              ← Symlinks to active sites
│
├── snippets/                   ← Reusable config fragments
│   └── fastcgi-php.conf        ← Common PHP-FPM snippet
│
├── mime.types                  ← Maps file extensions to MIME types
└── fastcgi_params              ← FastCGI parameter defaults

/var/log/nginx/                 ← Log files
├── access.log                  ← All HTTP requests
└── error.log                   ← Errors, warnings, debug info

/var/www/html/                  ← Default web root (Ubuntu)
/usr/share/nginx/html/          ← Default web root (CentOS)

/run/nginx.pid                  ← PID file of master process
/usr/sbin/nginx                 ← NGINX binary
```

---

### Basic `nginx.conf` Structure Overview

```nginx
# Global / Main context
worker_processes auto;
error_log /var/log/nginx/error.log warn;
pid /run/nginx.pid;

# Events context — connection handling
events {
    worker_connections 1024;
}

# HTTP context — all web traffic settings
http {
    include       /etc/nginx/mime.types;
    default_type  application/octet-stream;

    # Logging format
    log_format main '$remote_addr - $remote_user [$time_local] "$request" '
                    '$status $body_bytes_sent "$http_referer" '
                    '"$http_user_agent"';

    access_log /var/log/nginx/access.log main;

    sendfile on;
    keepalive_timeout 65;

    # Include virtual host configs
    include /etc/nginx/conf.d/*.conf;

    # Server block (virtual host)
    server {
        listen 80;
        server_name example.com;

        root /var/www/html;
        index index.html;

        location / {
            try_files $uri $uri/ =404;
        }
    }
}
```

---

## 4. Important Configuration Blocks

### `events` Block

Controls how NGINX handles connections at the OS level.

```nginx
events {
    # Max simultaneous connections per worker process
    worker_connections 1024;

    # Accept multiple connections at once (not just one per event)
    # Recommended: on for high-traffic servers
    multi_accept on;

    # I/O event notification method
    # epoll = Linux (most efficient), kqueue = BSD/macOS
    use epoll;
}
```

> **Total max connections** = `worker_processes` × `worker_connections`  
> Example: 4 workers × 1024 connections = **4096 simultaneous connections**

---

### `http` Block

The top-level block for all HTTP configuration. Think of it as global settings inherited by all `server` blocks.

```nginx
http {
    # Include MIME type mappings
    include /etc/nginx/mime.types;
    default_type application/octet-stream;

    # Efficient file transfer — uses sendfile() syscall
    # Kernel sends file directly to socket without user-space copy
    sendfile on;

    # Only send TCP packets when they are full (with sendfile on)
    tcp_nopush on;

    # Disable Nagle algorithm — send packets immediately
    tcp_nodelay on;

    # Keep connections open for this many seconds
    keepalive_timeout 65;

    # Max size of client request body (e.g., file uploads)
    client_max_body_size 10m;

    # Hide NGINX version from error pages and headers
    server_tokens off;

    # Gzip compression (see Performance section)
    gzip on;

    # Logging
    log_format main '$remote_addr - [$time_local] "$request" $status';
    access_log /var/log/nginx/access.log main;
    error_log  /var/log/nginx/error.log warn;
}
```

---

### `server` Block

Defines a virtual host — equivalent to Apache's `<VirtualHost>`. Multiple `server` blocks can run on the same NGINX instance.

```nginx
server {
    # Port to listen on
    listen 80;
    # listen 443 ssl;  # For HTTPS

    # Hostname(s) this block responds to
    # NGINX matches incoming Host header against this
    server_name example.com www.example.com;

    # Document root
    root /var/www/example;
    index index.html index.htm;

    # Access log for this specific vhost
    access_log /var/log/nginx/example.access.log;

    # Redirect HTTP to HTTPS
    # return 301 https://$host$request_uri;

    # ... location blocks go here
}
```

**How NGINX selects a `server` block:**
1. Match by IP address and port (`listen` directive).
2. Match by `Host` header against `server_name`.
3. If no match → use the **default_server** (first defined or explicitly marked).

```nginx
# Mark as default server for port 80
server {
    listen 80 default_server;
    server_name _;    # Catch-all
    return 444;       # Drop connection silently
}
```

---

### `location` Block

The most powerful block — matches request URIs and applies directives.

```nginx
server {
    server_name example.com;
    root /var/www/html;

    # Exact match — only /login exactly
    location = /login {
        proxy_pass http://auth_backend;
    }

    # Prefix match (case-sensitive, highest priority after exact)
    location ^~ /images/ {
        # Serve static images directly, no regex matching attempted
        expires 30d;
        add_header Cache-Control "public";
    }

    # Regex match (case-sensitive)
    location ~ \.php$ {
        fastcgi_pass unix:/run/php/php8.1-fpm.sock;
        include fastcgi_params;
        fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
    }

    # Regex match (case-INsensitive)
    location ~* \.(jpg|jpeg|png|gif|ico|css|js)$ {
        expires 1y;
        add_header Cache-Control "public, immutable";
    }

    # Prefix match (lowest priority — general catch-all)
    location / {
        try_files $uri $uri/ /index.html;
    }
}
```

### Location Match Priority (Memorize This!)

```
Priority Order (highest → lowest):
1.  =    Exact match
2.  ^~   Prefix match (stops regex search if matched)
3.  ~    Regex (case-sensitive)  ─┐ checked in order
4.  ~*   Regex (case-insensitive) ┘ of appearance
5.  /    Longest prefix match (no modifier)
```

### `try_files` Explained

```nginx
location / {
    # Try: 1) exact file, 2) directory, 3) fallback to /index.html
    try_files $uri $uri/ /index.html;
    #         │    │      └─ 404 fallback (SPA routing)
    #         │    └─ Try as directory (serves index.html inside dir)
    #         └─ Try as exact file
}

# Another common pattern
location / {
    try_files $uri $uri/ =404;
    # Return 404 if neither file nor directory found
}
```

> **SPA Insight:** For React/Vue/Angular apps, always use `try_files $uri $uri/ /index.html;` — this ensures client-side routing works. Without it, refreshing `/dashboard` returns 404 because there's no actual `dashboard` file on disk.

---

## 5. Reverse Proxy & Load Balancing

### What Is a Reverse Proxy?

```
WITHOUT reverse proxy:
Client ──────────────────────────────► App Server :3000

WITH reverse proxy:
Client ──► NGINX :80 ──► App Server :3000
               │
               ├─ SSL termination
               ├─ Static file serving  
               ├─ Caching
               ├─ Rate limiting
               └─ Access control
```

A **reverse proxy** sits in front of backend servers. Clients talk to NGINX, NGINX talks to backends. The client never knows the backend's address.

**Benefits:**
- Hide internal architecture
- SSL offloading (decrypt once at NGINX, plain HTTP to backends)
- Single entry point for logging, auth, rate limiting
- Ability to swap backends without affecting clients

---

### Configure NGINX as Reverse Proxy

```nginx
server {
    listen 80;
    server_name api.example.com;

    location / {
        # Forward all requests to backend app server
        proxy_pass http://127.0.0.1:3000;

        # Pass original client IP (not NGINX's IP)
        proxy_set_header X-Real-IP $remote_addr;

        # Pass full chain of IPs for X-Forwarded-For
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;

        # Pass the original Host header (not localhost)
        proxy_set_header Host $host;

        # Tell backend if original request was HTTPS
        proxy_set_header X-Forwarded-Proto $scheme;

        # Timeouts
        proxy_connect_timeout 10s;   # Time to connect to backend
        proxy_read_timeout    60s;   # Time to wait for backend response
        proxy_send_timeout    60s;   # Time to send request to backend

        # Buffer settings
        proxy_buffering on;
        proxy_buffer_size 4k;
        proxy_buffers 8 4k;

        # Handle WebSockets
        # proxy_http_version 1.1;
        # proxy_set_header Upgrade $http_upgrade;
        # proxy_set_header Connection "upgrade";
    }

    # Serve static assets directly (don't proxy to backend)
    location /static/ {
        alias /var/www/myapp/static/;
        expires 1y;
    }
}
```

> **Real-world insight:** Always set `proxy_set_header X-Real-IP` and `X-Forwarded-For`. If you don't, your app sees `127.0.0.1` as every client's IP, which breaks geolocation, rate limiting, and analytics.

---

### Load Balancing Methods

First, define an **upstream** group:

```nginx
http {

    # ── Method 1: Round Robin (default) ──────────────────────────
    # Distributes requests equally in rotation
    upstream backend_rr {
        server 10.0.0.1:3000;
        server 10.0.0.2:3000;
        server 10.0.0.3:3000;
    }

    # ── Method 2: Least Connections ──────────────────────────────
    # Sends new request to server with fewest active connections
    # Best for long-lived connections (WebSockets, file uploads)
    upstream backend_lc {
        least_conn;
        server 10.0.0.1:3000;
        server 10.0.0.2:3000;
        server 10.0.0.3:3000;
    }

    # ── Method 3: IP Hash ─────────────────────────────────────────
    # Same client IP always goes to same backend (sticky sessions)
    # Good when app state is not shared between backends
    upstream backend_iphash {
        ip_hash;
        server 10.0.0.1:3000;
        server 10.0.0.2:3000;
        server 10.0.0.3:3000;
    }

    # ── Method 4: Weighted Round Robin ───────────────────────────
    # Distribute more traffic to powerful servers
    upstream backend_weighted {
        server 10.0.0.1:3000 weight=5;   # Gets 5/7 of traffic
        server 10.0.0.2:3000 weight=2;   # Gets 2/7 of traffic
    }

    # ── Advanced: Health checks + backup ─────────────────────────
    upstream backend_ha {
        server 10.0.0.1:3000;
        server 10.0.0.2:3000;
        server 10.0.0.3:3000 backup;    # Only used when others fail
        server 10.0.0.4:3000 down;      # Manually marked offline

        # NGINX Plus (commercial) has active health checks
        # Open source uses passive: marks server down after failures
        # max_fails=3 fail_timeout=30s
    }

    server {
        listen 80;
        location / {
            proxy_pass http://backend_rr;
            proxy_set_header Host $host;
            proxy_set_header X-Real-IP $remote_addr;
        }
    }
}
```

### Load Balancing Method Comparison

| Method | Algorithm | Best For | Limitation |
|---|---|---|---|
| **Round Robin** | Sequential rotation | Stateless apps, equal servers | Doesn't account for server load |
| **Least Connections** | Fewest active connections | Long connections, mixed workloads | Needs connection tracking overhead |
| **IP Hash** | Hash of client IP | Session-based apps without shared state | Uneven distribution if many clients share IP (NAT) |
| **Weighted** | Proportional to weight | Mixed server capacities | Requires manual tuning |

---

## 6. Performance & Optimization

### Caching

```nginx
http {
    # Define cache storage location and size
    # keys_zone=my_cache:10m → 10MB for cache keys (stores ~80,000 keys)
    # max_size=1g           → 1GB max cache on disk
    # inactive=60m          → Remove items not accessed in 60 mins
    proxy_cache_path /var/cache/nginx
                     levels=1:2
                     keys_zone=my_cache:10m
                     max_size=1g
                     inactive=60m
                     use_temp_path=off;

    server {
        listen 80;

        location / {
            proxy_pass http://backend;

            # Enable caching using the zone defined above
            proxy_cache my_cache;

            # Cache key (what makes a request unique)
            proxy_cache_key "$scheme$request_method$host$request_uri";

            # Cache responses with these status codes
            proxy_cache_valid 200 302 10m;  # Cache 200s for 10 mins
            proxy_cache_valid 404      1m;  # Cache 404s for 1 min

            # Add header so you can see cache hit/miss in browser
            add_header X-Cache-Status $upstream_cache_status;

            # Serve stale cache if backend is down (resilience)
            proxy_cache_use_stale error timeout updating
                                  http_500 http_502 http_503 http_504;

            # Bypass cache for logged-in users (cookie present)
            proxy_cache_bypass $cookie_sessionid;
            proxy_no_cache     $cookie_sessionid;
        }
    }
}
```

**Cache status values** (`X-Cache-Status` header):

| Value | Meaning |
|---|---|
| `HIT` | Served from cache |
| `MISS` | Not in cache, fetched from backend |
| `BYPASS` | Cache bypassed (e.g., user is logged in) |
| `EXPIRED` | Cache entry found but expired, fetched fresh |
| `STALE` | Served stale (backend unavailable) |

---

### Gzip Compression

```nginx
http {
    # Enable compression
    gzip on;

    # Minimum file size to compress (don't compress tiny files)
    gzip_min_length 1000;

    # Compression level: 1 (fastest) to 9 (smallest)
    # Level 5–6 is sweet spot: good compression, reasonable CPU
    gzip_comp_level 5;

    # Compress these MIME types (text/html is always compressed)
    gzip_types
        text/plain
        text/css
        text/javascript
        application/javascript
        application/json
        application/xml
        image/svg+xml
        font/ttf
        font/woff
        font/woff2;

    # Add Vary: Accept-Encoding header (tells CDNs/proxies)
    gzip_vary on;

    # Compress even if client doesn't explicitly request it
    gzip_proxied any;

    # Don't compress for IE6 (ancient compatibility)
    gzip_disable "MSIE [1-6]\.";
}
```

> **Real-world insight:** Gzip can reduce text/JSON response sizes by **60–80%**. For an API returning 100KB JSON, gzip gets it to ~20KB. At scale (millions of requests), this saves significant bandwidth costs and improves perceived latency.

---

### Connection Handling Optimization

```nginx
# Global context
worker_processes auto;            # = number of CPU cores
worker_rlimit_nofile 65535;       # Max open files per worker

events {
    worker_connections 4096;       # Max connections per worker
    multi_accept on;               # Accept all pending connections at once
    use epoll;                     # Fastest event model on Linux
}

http {
    # Enable sendfile — kernel copies file to socket (zero-copy)
    sendfile on;

    # Bundle response headers + start of file in one packet
    tcp_nopush on;

    # Reduce latency for small packets
    tcp_nodelay on;

    # Keep connections alive (avoid TCP handshake overhead)
    keepalive_timeout 65;
    keepalive_requests 1000;      # Max requests per keep-alive connection

    # Keep N idle upstream connections open (reuse connections to backends)
    upstream backend {
        server 127.0.0.1:3000;
        keepalive 32;             # Pool of 32 persistent connections to backend
    }
}
```

---

### Worker Process Tuning

```bash
# Check number of CPU cores
nproc
# or
grep -c ^processor /proc/cpuinfo
```

```nginx
# nginx.conf

# Set to number of CPU cores — or use 'auto'
worker_processes auto;

# Pin each worker to a specific CPU core (reduces cache misses)
# For 4-core system:
worker_cpu_affinity auto;
# Or manual: 0001 0010 0100 1000 (each worker on one core)

# Increase open file limit (required for high-connection servers)
worker_rlimit_nofile 65535;

events {
    worker_connections 4096;
}
```

**Max concurrent connections calculation:**
```
Total connections = worker_processes × worker_connections
For proxy: divide by 2 (each proxied connection = 2 NGINX sockets)

Example:
4 workers × 4096 connections = 16,384 total connections
As proxy: ~8,192 proxied client connections
```

---

## 7. Security Best Practices

### SSL/TLS Setup

```nginx
server {
    listen 443 ssl http2;
    server_name example.com;

    # Certificate files (from Let's Encrypt or CA)
    ssl_certificate     /etc/letsencrypt/live/example.com/fullchain.pem;
    ssl_certificate_key /etc/letsencrypt/live/example.com/privkey.pem;

    # Use only strong protocols (no SSL 2/3, no TLS 1.0/1.1)
    ssl_protocols TLSv1.2 TLSv1.3;

    # Strong cipher suites (Mozilla Modern config)
    ssl_ciphers ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256:ECDHE-ECDSA-AES256-GCM-SHA384:ECDHE-RSA-AES256-GCM-SHA384;
    ssl_prefer_server_ciphers off;    # TLS 1.3 handles this

    # Session caching (reduces TLS handshake overhead)
    ssl_session_cache   shared:SSL:10m;
    ssl_session_timeout 1d;
    ssl_session_tickets off;          # Disable for perfect forward secrecy

    # OCSP Stapling — attach cert validity proof to response
    ssl_stapling on;
    ssl_stapling_verify on;
    resolver 8.8.8.8 8.8.4.4 valid=300s;

    # DH params for DHE cipher suites
    ssl_dhparam /etc/nginx/dhparam.pem;
    # Generate: openssl dhparam -out /etc/nginx/dhparam.pem 2048

    root /var/www/html;
}

# Redirect all HTTP to HTTPS
server {
    listen 80;
    server_name example.com www.example.com;
    return 301 https://example.com$request_uri;
}
```

**Generate Let's Encrypt cert (Certbot):**
```bash
sudo apt install certbot python3-certbot-nginx
sudo certbot --nginx -d example.com -d www.example.com
# Auto-renewal
sudo systemctl enable certbot.timer
```

---

### Rate Limiting

```nginx
http {
    # Define a rate limit zone
    # $binary_remote_addr = client IP (binary = smaller memory)
    # zone=api_limit:10m  = 10MB shared memory for tracking
    # rate=10r/s          = max 10 requests per second per IP
    limit_req_zone $binary_remote_addr zone=api_limit:10m rate=10r/s;

    # Login endpoint — stricter limit
    limit_req_zone $binary_remote_addr zone=login_limit:10m rate=1r/s;

    server {
        # Apply rate limit to all API endpoints
        location /api/ {
            limit_req zone=api_limit burst=20 nodelay;
            # burst=20 → allow burst of 20 extra requests
            # nodelay  → don't queue, process burst immediately
            proxy_pass http://backend;
        }

        # Very strict limit on login (prevent brute force)
        location /login {
            limit_req zone=login_limit burst=5;
            # Without nodelay: excess requests are delayed (queued)
            proxy_pass http://auth_backend;
        }

        # Custom error response for rate-limited requests
        limit_req_status 429;

        error_page 429 /rate_limit.json;
        location = /rate_limit.json {
            return 429 '{"error": "Too many requests", "retry_after": 60}';
            add_header Content-Type application/json;
        }
    }
}
```

---

### Preventing Common Attacks

```nginx
http {
    # ── Hide NGINX version from attackers ────────────────────────
    server_tokens off;

    # ── Limit HTTP methods (allow only GET, POST, HEAD) ──────────
    server {
        if ($request_method !~ ^(GET|POST|HEAD)$) {
            return 405;
        }
    }

    # ── Prevent buffer overflow attacks ──────────────────────────
    client_body_buffer_size    16k;
    client_header_buffer_size   1k;
    client_max_body_size        8m;
    large_client_header_buffers 2 8k;

    # ── Timeout settings (prevent Slowloris attacks) ──────────────
    client_body_timeout   12s;
    client_header_timeout 12s;
    send_timeout          10s;
    keepalive_timeout     15s;

    # ── Block common exploit patterns ─────────────────────────────
    server {
        # Block requests with suspicious User-Agents
        if ($http_user_agent ~* (sqlmap|nikto|nmap|masscan|zgrab)) {
            return 403;
        }

        # Block requests for PHP files in uploads directory
        location ~* /uploads/.*\.php$ {
            deny all;
        }

        # Block access to hidden files (.htaccess, .git, .env)
        location ~ /\. {
            deny all;
            return 404;
        }
    }
}
```

---

### Secure Headers

```nginx
server {
    # Prevent MIME type sniffing
    add_header X-Content-Type-Options nosniff;

    # Prevent clickjacking
    add_header X-Frame-Options SAMEORIGIN;

    # Enable browser XSS protection
    add_header X-XSS-Protection "1; mode=block";

    # HTTP Strict Transport Security (only HTTPS for 1 year)
    add_header Strict-Transport-Security "max-age=31536000; includeSubDomains; preload" always;

    # Content Security Policy (customize per application)
    add_header Content-Security-Policy "default-src 'self'; script-src 'self' 'unsafe-inline'; style-src 'self' 'unsafe-inline'";

    # Referrer Policy
    add_header Referrer-Policy "strict-origin-when-cross-origin";

    # Permissions Policy
    add_header Permissions-Policy "camera=(), microphone=(), geolocation=()";

    # Remove server information
    server_tokens off;
    more_clear_headers Server;    # Requires nginx-extras or headers-more module
}
```

> **Interview insight:** HSTS with `preload` means browsers will never attempt HTTP to your domain — even on first visit. Once submitted to the HSTS preload list, this cannot be easily undone. Be careful.

---

## 8. NGINX + WordPress Case Study

### Why WordPress Sites Use NGINX

- WordPress is PHP-based and generates pages dynamically — NGINX + PHP-FPM handles this efficiently.
- NGINX excels at serving WordPress's many static assets (images, JS, CSS).
- NGINX caching (FastCGI cache) can serve WordPress pages without PHP/MySQL for 99% of traffic.
- Better performance than Apache + mod_php for high-traffic blogs.

---

### Architecture Diagram (Text-Based)

```
Internet
    │
    ▼
[Client Browser]
    │  HTTPS :443
    ▼
┌─────────────────────────────────────────────────────┐
│                    NGINX (Edge)                     │
│                                                     │
│  ┌────────────────┐    ┌─────────────────────────┐  │
│  │  Static Assets │    │   FastCGI Cache         │  │
│  │  /wp-content   │    │   /var/cache/nginx      │  │
│  │  /wp-includes  │    │   (Cached PHP pages)    │  │
│  └────────────────┘    └──────────┬──────────────┘  │
│                                   │ Cache MISS       │
└───────────────────────────────────┼─────────────────┘
                                    │
                                    ▼ FastCGI (unix socket)
                         ┌──────────────────────┐
                         │     PHP-FPM 8.1      │
                         │  (PHP Process Pool)  │
                         └──────────┬───────────┘
                                    │ MySQL queries
                                    ▼
                         ┌──────────────────────┐
                         │  MySQL / MariaDB     │
                         │  (WordPress DB)      │
                         └──────────────────────┘
```

**Cache hit flow:** Client → NGINX → Serve from FastCGI cache ✓ (No PHP, No MySQL)  
**Cache miss flow:** Client → NGINX → PHP-FPM → MySQL → Generate page → Cache it → Serve

---

### Steps to Deploy WordPress with NGINX + PHP-FPM + MySQL

```bash
# ── Step 1: Install dependencies ────────────────────────────────

sudo apt update
sudo apt install nginx mysql-server php8.1-fpm php8.1-mysql \
                 php8.1-xml php8.1-curl php8.1-gd php8.1-mbstring \
                 php8.1-zip php8.1-intl -y

# ── Step 2: Configure MySQL ──────────────────────────────────────

sudo mysql -u root -p
```

```sql
CREATE DATABASE wordpress CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
CREATE USER 'wpuser'@'localhost' IDENTIFIED BY 'StrongPassword123!';
GRANT ALL PRIVILEGES ON wordpress.* TO 'wpuser'@'localhost';
FLUSH PRIVILEGES;
EXIT;
```

```bash
# ── Step 3: Download WordPress ──────────────────────────────────

cd /var/www
sudo wget https://wordpress.org/latest.tar.gz
sudo tar -xzf latest.tar.gz
sudo mv wordpress /var/www/myblog
sudo chown -R www-data:www-data /var/www/myblog
sudo chmod -R 755 /var/www/myblog

# ── Step 4: Configure PHP-FPM ───────────────────────────────────
# Edit /etc/php/8.1/fpm/pool.d/www.conf
# Ensure socket is:
# listen = /run/php/php8.1-fpm.sock

sudo systemctl enable php8.1-fpm
sudo systemctl start php8.1-fpm
```

```bash
# ── Step 5: NGINX Virtual Host Config ───────────────────────────

sudo nano /etc/nginx/conf.d/myblog.conf
```

```nginx
# FastCGI Cache Configuration
fastcgi_cache_path /var/cache/nginx/myblog
                   levels=1:2
                   keys_zone=WORDPRESS:100m
                   max_size=1g
                   inactive=60m;

fastcgi_cache_key "$scheme$request_method$host$request_uri";

server {
    listen 80;
    server_name myblog.com www.myblog.com;
    root /var/www/myblog;
    index index.php;

    # FastCGI cache toggle
    set $skip_cache 0;

    # Don't cache POST requests
    if ($request_method = POST) { set $skip_cache 1; }

    # Don't cache URLs with query strings
    if ($query_string != "") { set $skip_cache 1; }

    # Don't cache logged-in users or commenters
    if ($http_cookie ~* "comment_author|wordpress_[a-f0-9]+|wp-postpass|wordpress_no_cache|wordpress_logged_in") {
        set $skip_cache 1;
    }

    # WordPress-specific location rules
    location / {
        try_files $uri $uri/ /index.php?$args;
    }

    # Block direct PHP execution in uploads
    location ~* /(?:uploads|files)/.*\.php$ {
        deny all;
    }

    # Process PHP files via PHP-FPM
    location ~ \.php$ {
        try_files $uri =404;
        fastcgi_split_path_info ^(.+\.php)(/.+)$;
        fastcgi_pass unix:/run/php/php8.1-fpm.sock;
        fastcgi_index index.php;
        include fastcgi_params;
        fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
        fastcgi_param PATH_INFO $fastcgi_path_info;

        # FastCGI cache settings
        fastcgi_cache WORDPRESS;
        fastcgi_cache_valid 200 60m;
        fastcgi_cache_bypass $skip_cache;
        fastcgi_no_cache $skip_cache;
        add_header X-FastCGI-Cache $upstream_cache_status;
    }

    # Static assets — long expiry, no PHP
    location ~* \.(js|css|png|jpg|jpeg|gif|ico|svg|woff|woff2|ttf)$ {
        expires 1y;
        add_header Cache-Control "public, immutable";
        log_not_found off;
    }

    # Block access to sensitive files
    location ~* /\.(htaccess|htpasswd|git|svn|env) {
        deny all;
    }

    location = /robots.txt  { log_not_found off; access_log off; }
    location = /favicon.ico { log_not_found off; access_log off; }
}
```

```bash
# ── Step 6: Test and Enable ─────────────────────────────────────

sudo nginx -t
sudo systemctl reload nginx

# ── Step 7: Create cache purge script ───────────────────────────

sudo mkdir -p /var/cache/nginx/myblog
sudo chown www-data:www-data /var/cache/nginx/myblog

# Purge entire cache when needed:
# sudo find /var/cache/nginx/myblog -type f -delete
```

---

### Performance Improvements Observed

| Metric | Without FastCGI Cache | With FastCGI Cache |
|---|---|---|
| Response Time (cached) | 450–800ms | 5–15ms |
| PHP-FPM CPU Usage | 80–100% at 100 RPS | <5% at 100 RPS |
| MySQL Query Load | High | Near zero (for cached pages) |
| Concurrent Users | ~50 | 1000+ |
| TTFB (Time to First Byte) | 400ms+ | <20ms |

---

### Problems Faced & Solutions

| Problem | Cause | Solution |
|---|---|---|
| Logged-in users saw cached pages from other users | Cache not bypassing sessions | Add `wordpress_logged_in` cookie check to `$skip_cache` |
| 413 error on image upload | `client_max_body_size` too small | Set `client_max_body_size 64m;` |
| Permalinks returning 404 | `try_files` not passing to WordPress | Add `try_files $uri $uri/ /index.php?$args;` |
| PHP files executed in uploads | Missing location block | Block `*.php` in `/uploads/` with `deny all` |
| Slow admin panel | Admin was being cached | Exclude `/wp-admin/` from cache |
| HTTPS mixed content | WordPress site URL still HTTP | Update WP config + add `fastcgi_param HTTPS on;` |

---

## 9. Common Interview Questions

### Conceptual Questions

**Q1. What is the difference between NGINX and Apache?**  
NGINX uses an event-driven, non-blocking architecture — a single worker thread handles thousands of connections via OS event loops (epoll). Apache traditionally uses a process-per-connection or thread-per-connection model, consuming much more memory. NGINX is better for static content and high concurrency; Apache is more flexible for dynamic content via modules and `.htaccess`.

---

**Q2. Explain NGINX's master-worker model.**  
The master process reads config, binds privileged ports (80/443), and manages worker lifecycles. Workers (one per CPU core typically) handle all client connections using event loops. This isolation means a worker crash doesn't kill the whole server, and config reloads are zero-downtime.

---

**Q3. What is the C10K problem and how does NGINX solve it?**  
C10K = challenge of handling 10,000 concurrent connections on one server. Traditional servers spawned one thread per connection — at 10K connections, you need 10K threads, which is ~80GB RAM just for stacks. NGINX solves this by using async I/O: one thread manages thousands of connections. When a connection waits for I/O, the thread handles other connections. No blocking, no per-connection memory overhead.

---

**Q4. What is the `try_files` directive?**  
`try_files` checks file locations in order and serves the first match. Common usage: `try_files $uri $uri/ /index.html;` — try as exact file, then directory, then fall back to index.html. The final argument can be a URI or `=404` to return a 404 error.

---

**Q5. How does location block matching work?**  
Matching priority: exact (`=`) → prefix with no-regex stop (`^~`) → case-sensitive regex (`~`) → case-insensitive regex (`~*`) → longest prefix match (no modifier). NGINX finds the best match, not the first match.

---

**Q6. What is the difference between `proxy_pass` with and without trailing slash?**  
```nginx
# Without trailing slash: passes full URI
location /app {
    proxy_pass http://backend;        # /app/page → backend/app/page
}

# With trailing slash: strips location prefix
location /app/ {
    proxy_pass http://backend/;       # /app/page → backend/page
}
```
This catches many people off guard in production.

---

**Q7. How does NGINX handle SSL termination?**  
NGINX decrypts HTTPS at the edge and forwards plain HTTP to backends. This offloads CPU-intensive TLS operations to one place, simplifies backend apps (no SSL handling), and enables centralized certificate management. Use `X-Forwarded-Proto: https` header to tell backends the original request was secure.

---

**Q8. What is FastCGI and why is it used with PHP?**  
FastCGI is a protocol for communicating between NGINX and application runtimes (like PHP-FPM). PHP can't run inside NGINX as a module (unlike Apache's mod_php), so PHP-FPM maintains a pool of PHP worker processes. NGINX sends PHP requests to PHP-FPM via a Unix socket or TCP, PHP executes the script, returns output to NGINX, which returns it to the client.

---

**Q9. How does NGINX load balancing differ from hardware load balancers (like F5)?**  
NGINX is a software load balancer — free, flexible, runs on commodity hardware, configurable in code (infra-as-code friendly). Hardware load balancers have dedicated ASICs for line-rate performance, built-in redundancy, but cost hundreds of thousands of dollars. For most web workloads, NGINX (or HA NGINX pair) is sufficient.

---

**Q10. What is `upstream keepalive` and why is it important?**  
Without keepalive, NGINX opens a new TCP connection to the backend for every proxied request. With `keepalive 32`, NGINX maintains a pool of 32 persistent connections to the backend. This eliminates TCP handshake overhead on every request, significantly reducing latency under load.

---

### Scenario-Based Questions

**Q11. Scenario: Your NGINX server is getting thousands of requests per second from a single IP attempting brute force on `/login`. How do you stop it?**  
```nginx
http {
    limit_req_zone $binary_remote_addr zone=login:10m rate=1r/s;
    server {
        location /login {
            limit_req zone=login burst=5 nodelay;
            limit_req_status 429;
        }
    }
}
```
Then add that IP to `deny` list in a geo block if it persists. Also consider fail2ban monitoring NGINX logs.

---

**Q12. Scenario: You need zero-downtime deployment of a new app version. How do you use NGINX?**  
- Deploy new version on a different port (e.g., `:3001`) alongside old (`:3000`).
- Update NGINX upstream to point to `:3001`.
- Run `nginx -s reload` — master process gracefully replaces workers, old connections finish on `:3000`, new connections go to `:3001`.
- Old app can be stopped after connections drain.

---

**Q13. Scenario: A client reports intermittent 502 errors from your NGINX reverse proxy. How do you debug?**  
1. Check `error.log`: `tail -f /var/log/nginx/error.log`
2. Common causes: backend app crashed, backend response timeout, PHP-FPM pool exhausted.
3. Check if backend is running: `curl http://127.0.0.1:3000/health`
4. Check PHP-FPM logs: `tail -f /var/log/php8.1-fpm.log`
5. Adjust `proxy_read_timeout` if backend is slow.
6. Increase PHP-FPM `pm.max_children` if pool is exhausted.

---

**Q14. Scenario: How would you configure NGINX for a microservices API gateway?**  
```nginx
upstream auth_service    { server localhost:3001; }
upstream user_service    { server localhost:3002; }
upstream product_service { server localhost:3003; }

server {
    listen 443 ssl;
    server_name api.example.com;

    location /api/auth/    { proxy_pass http://auth_service; }
    location /api/users/   { proxy_pass http://user_service; }
    location /api/products/ { proxy_pass http://product_service; }

    # Rate limiting, auth, logging at gateway level
}
```

---

**Q15. Scenario: How do you configure NGINX for WebSocket support?**  
WebSockets require the HTTP connection to be upgraded. NGINX doesn't do this by default.
```nginx
location /ws/ {
    proxy_pass http://backend;
    proxy_http_version 1.1;
    proxy_set_header Upgrade $http_upgrade;
    proxy_set_header Connection "upgrade";
    proxy_set_header Host $host;
    proxy_read_timeout 3600s;    # Long timeout for persistent WS connection
}
```

---

**Q16. What happens when you run `nginx -s reload`? Is there any downtime?**  
No downtime. The master process re-reads the config, validates it, then forks new worker processes with the new config. Old workers stop accepting new connections but finish serving their existing connections gracefully. Once all old connections are done, old workers exit. Traffic continues uninterrupted throughout.

---

**Q17. Difference between `return` and `rewrite` in NGINX?**  
- `return` is simpler and faster — NGINX immediately responds without further processing. Use for redirects and simple responses.
- `rewrite` modifies the URI and continues processing location matching — useful for complex URL rewriting.
```nginx
# Prefer return for redirects
return 301 https://example.com$request_uri;

# Use rewrite for URI manipulation
rewrite ^/old/(.*)$ /new/$1 permanent;
```

---

**Q18. How do you test an NGINX config before applying it?**  
```bash
nginx -t                    # Test config syntax
nginx -T                    # Test + print entire resolved config
nginx -s reload             # Reload after testing
```
Always run `nginx -t` before reload in production. A bad config with `nginx -s reload` will print an error and keep the old config running — it won't break a live server.

---

**Q19. What is NGINX Plus vs open-source NGINX?**  
NGINX Plus is the commercial version with: active health checks (proactively remove unhealthy upstreams), session persistence (sticky cookies), live activity monitoring dashboard, JWT authentication, dynamic upstream reconfiguration via API, and commercial support. Open-source requires third-party modules (lua, nginx-upstream-check) for some of these features.

---

**Q20. How does NGINX handle the `Vary: Accept-Encoding` header with gzip?**  
When gzip is enabled and `gzip_vary on` is set, NGINX adds `Vary: Accept-Encoding` to responses. This tells downstream caches (CDNs, browser caches) that the cached response varies based on the `Accept-Encoding` request header — so they store both compressed and uncompressed versions and serve the appropriate one. Without this, a CDN might serve gzipped content to a client that doesn't support gzip.

---

## 10. Hands-on Mini Project

### Build a Simple NGINX Reverse Proxy Setup

**Goal:** Set up NGINX as a reverse proxy in front of two Node.js app instances with load balancing, logging, and rate limiting.

**Architecture:**
```
Client → NGINX :80 → [Node App 1 :3000, Node App 2 :3001]
```

---

#### Step 1: Install NGINX and Node.js

```bash
sudo apt update && sudo apt install nginx -y
curl -fsSL https://deb.nodesource.com/setup_20.x | sudo -E bash -
sudo apt install nodejs -y
```

---

#### Step 2: Create Two Simple Node.js Apps

```bash
mkdir -p ~/apps/app1 ~/apps/app2

# App 1
cat > ~/apps/app1/server.js << 'EOF'
const http = require('http');
const PORT = 3000;
http.createServer((req, res) => {
    res.writeHead(200, {'Content-Type': 'application/json'});
    res.end(JSON.stringify({
        server: 'APP-1',
        port: PORT,
        url: req.url,
        time: new Date().toISOString()
    }));
}).listen(PORT, () => console.log(`App 1 running on :${PORT}`));
EOF

# App 2 (copy and change port)
sed 's/3000/3001/g; s/APP-1/APP-2/g' ~/apps/app1/server.js > ~/apps/app2/server.js

# Start both apps in background
node ~/apps/app1/server.js &
node ~/apps/app2/server.js &

# Verify both are running
curl http://localhost:3000
curl http://localhost:3001
```

---

#### Step 3: Configure NGINX

```bash
sudo nano /etc/nginx/conf.d/myproxy.conf
```

```nginx
# Rate limiting zone
limit_req_zone $binary_remote_addr zone=api:10m rate=30r/s;

# Upstream pool with both app instances
upstream node_apps {
    least_conn;                         # Route to least busy server
    server 127.0.0.1:3000;
    server 127.0.0.1:3001;
    keepalive 16;                       # Reuse connections to apps
}

# Custom log format with upstream info
log_format proxy_log '$remote_addr - [$time_local] "$request" '
                     '$status $body_bytes_sent '
                     'upstream: $upstream_addr '
                     'rt=$request_time uct=$upstream_connect_time '
                     'urt=$upstream_response_time';

server {
    listen 80;
    server_name localhost;

    access_log /var/log/nginx/proxy_access.log proxy_log;
    error_log  /var/log/nginx/proxy_error.log warn;

    # API endpoints — reverse proxied
    location /api/ {
        limit_req zone=api burst=10 nodelay;

        proxy_pass http://node_apps/;
        proxy_http_version 1.1;
        proxy_set_header Connection "";           # Required for keepalive
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        proxy_set_header X-Forwarded-Proto $scheme;

        proxy_connect_timeout 5s;
        proxy_read_timeout    30s;

        # Retry on error
        proxy_next_upstream error timeout http_502 http_503;
    }

    # Health check endpoint (bypass app)
    location /health {
        return 200 '{"status":"ok","nginx":"running"}';
        add_header Content-Type application/json;
    }

    # Status page (restrict to internal/monitoring)
    location /nginx_status {
        stub_status on;
        allow 127.0.0.1;
        deny all;
    }
}
```

---

#### Step 4: Test and Activate

```bash
# Test configuration
sudo nginx -t

# Reload NGINX
sudo systemctl reload nginx

# Test the proxy
curl http://localhost/api/test
# Should return JSON from App 1 or App 2

# Test load balancing (run several times, observe server field)
for i in {1..6}; do curl -s http://localhost/api/ | python3 -m json.tool; done

# Check logs
tail -f /var/log/nginx/proxy_access.log

# Check NGINX status
curl http://localhost/nginx_status
```

---

#### Step 5: Simulate Failover

```bash
# Kill App 1
kill $(lsof -t -i:3000)

# All requests should now go to App 2
for i in {1..5}; do curl -s http://localhost/api/ | grep server; done

# Restart App 1
node ~/apps/app1/server.js &

# Both backends resume receiving traffic
for i in {1..5}; do curl -s http://localhost/api/ | grep server; done
```

---

#### Step 6: Load Test with `ab` (Apache Bench)

```bash
sudo apt install apache2-utils -y

# 1000 requests, 50 concurrent
ab -n 1000 -c 50 http://localhost/api/

# Analyze output:
# - Requests per second
# - Mean time per request
# - Failed requests (should be 0)
```

**Expected output insight:** NGINX should easily handle 50 concurrent users with sub-millisecond proxy overhead. The bottleneck will be Node.js throughput, not NGINX.

---

## 11. Cheat Sheet

### Essential Commands

```bash
# ── Service Management ──────────────────────────────────────────
sudo systemctl start nginx          # Start NGINX
sudo systemctl stop nginx           # Stop NGINX
sudo systemctl restart nginx        # Full restart (brief downtime)
sudo systemctl reload nginx         # Zero-downtime config reload
sudo systemctl enable nginx         # Auto-start on boot
sudo systemctl status nginx         # Check status

# ── Config Testing ──────────────────────────────────────────────
sudo nginx -t                       # Test config syntax
sudo nginx -T                       # Test + dump full resolved config
sudo nginx -V                       # Show version + compile options

# ── Signal-Based Control ────────────────────────────────────────
sudo nginx -s reload                # Graceful reload
sudo nginx -s stop                  # Fast shutdown
sudo nginx -s quit                  # Graceful shutdown (finish requests)
sudo nginx -s reopen                # Reopen log files (for log rotation)

# ── Log Management ──────────────────────────────────────────────
tail -f /var/log/nginx/access.log   # Live access log
tail -f /var/log/nginx/error.log    # Live error log
sudo truncate -s 0 /var/log/nginx/access.log  # Clear log
sudo logrotate -f /etc/logrotate.d/nginx      # Force log rotation

# ── Diagnostics ─────────────────────────────────────────────────
sudo nginx -c /path/to/alt.conf     # Test with alternate config
ps aux | grep nginx                 # Check running processes
ss -tlnp | grep nginx               # Check listening ports
sudo lsof -p $(cat /run/nginx.pid)  # Open files by NGINX master
```

---

### Key Config Snippets

```nginx
# ── Redirect HTTP → HTTPS ───────────────────────────────────────
server {
    listen 80;
    server_name example.com;
    return 301 https://$host$request_uri;
}

# ── Redirect www → non-www ──────────────────────────────────────
server {
    listen 443 ssl;
    server_name www.example.com;
    return 301 https://example.com$request_uri;
}

# ── Basic Auth ──────────────────────────────────────────────────
location /admin {
    auth_basic "Admin Area";
    auth_basic_user_file /etc/nginx/.htpasswd;
    # Generate: htpasswd -c /etc/nginx/.htpasswd username
}

# ── Custom Error Pages ──────────────────────────────────────────
error_page 404 /404.html;
error_page 500 502 503 504 /50x.html;
location = /50x.html { root /var/www/errors; }

# ── CORS Headers ────────────────────────────────────────────────
location /api/ {
    add_header 'Access-Control-Allow-Origin' '*';
    add_header 'Access-Control-Allow-Methods' 'GET, POST, OPTIONS';
    add_header 'Access-Control-Allow-Headers' 'Authorization, Content-Type';
    if ($request_method = 'OPTIONS') { return 204; }
    proxy_pass http://backend;
}

# ── Deny specific IPs ───────────────────────────────────────────
location / {
    deny  192.168.1.100;
    deny  10.0.0.0/24;
    allow all;
}

# ── Geo blocking (requires ngx_http_geo_module) ─────────────────
geo $blocked_country {
    default 0;
    CN 1;   # Block China
    RU 1;   # Block Russia
}
server {
    if ($blocked_country) { return 403; }
}

# ── Maintenance mode ────────────────────────────────────────────
location / {
    if (-f /var/www/maintenance.html) {
        return 503;
    }
    error_page 503 /maintenance.html;
}

# ── WebSocket Proxy ─────────────────────────────────────────────
location /ws {
    proxy_pass http://backend;
    proxy_http_version 1.1;
    proxy_set_header Upgrade $http_upgrade;
    proxy_set_header Connection "upgrade";
}

# ── Force file download ─────────────────────────────────────────
location /downloads/ {
    add_header Content-Disposition "attachment";
}

# ── Proxy with path rewrite ─────────────────────────────────────
location /api/v1/ {
    rewrite ^/api/v1/(.*) /$1 break;
    proxy_pass http://backend;
}
```

---

### Variable Quick Reference

| Variable | Value |
|---|---|
| `$host` | Host header (or server name) |
| `$request_uri` | Full URI including query string |
| `$uri` | Normalized URI without query string |
| `$args` | Query string |
| `$remote_addr` | Client IP address |
| `$scheme` | `http` or `https` |
| `$server_port` | Port NGINX is listening on |
| `$upstream_addr` | Backend server address |
| `$upstream_response_time` | Time backend took to respond |
| `$request_time` | Total request time (client to response) |
| `$status` | HTTP response status code |
| `$body_bytes_sent` | Bytes sent to client |
| `$http_user_agent` | Client's User-Agent header |
| `$http_referer` | Referrer header |
| `$sent_http_*` | Any response header sent |
| `$upstream_cache_status` | HIT / MISS / BYPASS |

---

### HTTP Status Codes to Know

| Code | Meaning | Common NGINX Context |
|---|---|---|
| `200` | OK | Normal response |
| `301` | Moved Permanently | Redirect (use `return 301`) |
| `302` | Found (Temp Redirect) | Temp redirect |
| `304` | Not Modified | Cache hit (ETag/Last-Modified) |
| `400` | Bad Request | Malformed request |
| `401` | Unauthorized | Auth required |
| `403` | Forbidden | `deny all` matched |
| `404` | Not Found | `try_files` exhausted |
| `405` | Method Not Allowed | Blocked HTTP method |
| `413` | Payload Too Large | Exceeded `client_max_body_size` |
| `429` | Too Many Requests | Rate limit hit |
| `444` | No Response (NGINX) | Drop connection silently |
| `499` | Client Closed Request | Client disconnected |
| `502` | Bad Gateway | Backend down / unreachable |
| `503` | Service Unavailable | Upstream pool full |
| `504` | Gateway Timeout | Backend too slow |

---

> **Final Interview Tip:** Interviewers at the 10–20 LPA level love scenario questions. Don't just memorize config — practice explaining *why* each directive exists. NGINX decisions are driven by either **performance** (reduce overhead), **security** (reduce attack surface), or **reliability** (graceful handling of failures). Frame every answer around these three pillars.

---

*Last Updated: 2024 | Covers NGINX 1.24+ (stable) and 1.25+ (mainline)*
