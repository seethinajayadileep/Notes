# 📘 K6 Interview & Learning Notes
### For Performance Testing / SRE Roles (10–20 LPA)

---

## Table of Contents
1. [Introduction](#1-introduction)
2. [Core Concepts](#2-core-concepts)
3. [Installation & Setup](#3-installation--setup)
4. [Basic Script Structure](#4-basic-script-structure)
5. [Writing Test Scripts](#5-writing-test-scripts)
6. [Load Testing Types](#6-load-testing-types)
7. [Advanced Features](#7-advanced-features)
8. [Performance Optimization Insights](#8-performance-optimization-insights)
9. [K6 + Real-World Case Study](#9-k6--real-world-case-study)
10. [CI/CD Integration](#10-cicd-integration)
11. [Common Interview Questions](#11-common-interview-questions)
12. [Hands-on Mini Project](#12-hands-on-mini-project)
13. [Cheat Sheet](#13-cheat-sheet)

---

## 1. Introduction

### What is K6?

K6 (formerly Loadimpact) is an **open-source, developer-centric performance testing tool** built by Grafana Labs. Tests are written in **JavaScript (ES6+)**, and the engine is built in **Go**, giving it high performance with low resource usage.

- Website: [https://k6.io](https://k6.io)
- GitHub: [https://github.com/grafana/k6](https://github.com/grafana/k6)
- License: AGPL v3

### Why It Is Used

- Validate system behavior under expected and peak load
- Catch performance regressions before production
- Integrate seamlessly into CI/CD pipelines
- Test REST APIs, gRPC, WebSockets, and Browser flows
- Define **SLOs (Service Level Objectives)** as code via thresholds

### Key Advantages Over JMeter

| Feature | K6 | JMeter |
|---|---|---|
| **Scripting Language** | JavaScript (ES6+) | Java / Groovy / XML |
| **Resource Usage** | Very low (Go runtime) | High (JVM-based) |
| **CI/CD Friendly** | Native (CLI-first) | Complex XML, needs plugins |
| **Version Control** | Easy (plain JS files) | Difficult (binary XML) |
| **Modern Protocol Support** | HTTP/2, gRPC, WebSocket, Browser | HTTP/1.1 focused |
| **Real-time Metrics** | Grafana/InfluxDB native | Requires extra config |
| **Threshold as Code** | Built-in pass/fail criteria | Manual, plugin-based |
| **Learning Curve** | Low (dev-friendly) | Medium-High |

> **Engineer Insight:** JMeter is still valid for legacy enterprise environments with GUI-heavy workflows. K6 wins in modern microservices / cloud-native stacks. If you're in a DevOps/SRE role, K6 is the go-to.

---

## 2. Core Concepts

### VUs (Virtual Users)

VUs are simulated concurrent users. Each VU runs the default function in a loop. They are **not OS threads** — K6 uses goroutines, so 1000 VUs is lightweight.

```javascript
export const options = {
  vus: 50,        // 50 concurrent virtual users
  duration: '30s' // run for 30 seconds
};
```

Each VU maintains its own:
- HTTP connection pool
- Cookies and session state
- Variable scope

### Iterations

An **iteration** is one complete execution of the `default` function by one VU.

```javascript
export const options = {
  vus: 10,
  iterations: 100, // total 100 iterations split across 10 VUs
};
```

> **Key Formula:** `iterations = vus × (duration / avg_response_time)` (roughly)

### Stages (Ramping Up/Down)

Stages allow you to **shape the load profile** — mimicking real-world traffic patterns.

```javascript
export const options = {
  stages: [
    { duration: '2m', target: 100 },  // Ramp up to 100 VUs over 2 minutes
    { duration: '5m', target: 100 },  // Hold at 100 VUs for 5 minutes
    { duration: '2m', target: 0   },  // Ramp down to 0 VUs over 2 minutes
  ],
};
```

### Thresholds

Thresholds are **pass/fail criteria** defined as code. The test fails if any threshold is breached.

```javascript
export const options = {
  thresholds: {
    'http_req_duration': ['p(95)<500'],   // 95% of requests must complete < 500ms
    'http_req_failed': ['rate<0.01'],     // Error rate must be < 1%
    'http_reqs': ['rate>100'],            // Throughput must be > 100 req/s
  },
};
```

### Metrics

K6 tracks these **built-in metrics** automatically:

| Metric | Type | Description |
|---|---|---|
| `http_reqs` | Counter | Total number of HTTP requests |
| `http_req_duration` | Trend | Total time for request (send + wait + receive) |
| `http_req_waiting` | Trend | Time waiting for server response (TTFB) |
| `http_req_connecting` | Trend | TCP connection time |
| `http_req_tls_handshaking` | Trend | TLS handshake time |
| `http_req_sending` | Trend | Time sending data to server |
| `http_req_receiving` | Trend | Time receiving data from server |
| `http_req_failed` | Rate | Fraction of failed requests |
| `vus` | Gauge | Current active VUs |
| `vus_max` | Gauge | Max VUs allocated |
| `iterations` | Counter | Total iterations completed |
| `iteration_duration` | Trend | Time to complete one full iteration |
| `data_sent` | Counter | Total bytes sent |
| `data_received` | Counter | Total bytes received |

**Metric Types:**
- **Counter** – Cumulative sum (e.g., total requests)
- **Gauge** – Current value (e.g., active VUs)
- **Rate** – Fraction of values that are true (e.g., error rate)
- **Trend** – Statistical distribution (p50, p90, p95, p99, min, max, avg)

> **Engineer Insight:** In interviews, always reference `p(95)` and `p(99)` for latency — not just average. Averages hide outliers that kill user experience.

---

## 3. Installation & Setup

### Linux (Debian/Ubuntu)

```bash
sudo gpg -k
sudo gpg --no-default-keyring \
  --keyring /usr/share/keyrings/k6-archive-keyring.gpg \
  --keyserver hkp://keyserver.ubuntu.com:80 \
  --recv-keys C5AD17C747E3415A3642D57D77C6C491D6AC1D69

echo "deb [signed-by=/usr/share/keyrings/k6-archive-keyring.gpg] \
  https://dl.k6.io/deb stable main" | sudo tee /etc/apt/sources.list.d/k6.list

sudo apt-get update
sudo apt-get install k6
```

### macOS (Homebrew)

```bash
brew install k6
```

### Windows (Chocolatey)

```powershell
choco install k6
```

### Windows (Winget)

```powershell
winget install k6 --source winget
```

### Docker

```bash
docker run --rm -i grafana/k6 run - <script.js
```

### Verify Installation

```bash
k6 version
# k6 v0.52.0 (go1.22.4, linux/amd64)
```

### Running Your First Script

```bash
# Run a test
k6 run script.js

# Run with specific VUs and duration (override script options)
k6 run --vus 10 --duration 30s script.js

# Run with environment variables
k6 run -e BASE_URL=https://api.example.com script.js

# Output results to JSON
k6 run --out json=results.json script.js

# Output to InfluxDB (Grafana stack)
k6 run --out influxdb=http://localhost:8086/k6 script.js
```

---

## 4. Basic Script Structure

K6 scripts have **4 lifecycle stages**:

```
┌─────────────────────────────────────────────────────┐
│  INIT STAGE       (runs once per VU, before test)   │
│  setup()          (runs once before all VUs start)  │
│  default()        (runs repeatedly during test)     │
│  teardown()       (runs once after all VUs finish)  │
└─────────────────────────────────────────────────────┘
```

### Full Lifecycle Example

```javascript
// ============================================================
// INIT STAGE — runs once per VU at startup
// Use: imports, shared config, file reads, options definition
// ============================================================
import http from 'k6/http';
import { sleep, check } from 'k6';
import { SharedArray } from 'k6/data';

export const options = {
  stages: [
    { duration: '1m', target: 50 },
    { duration: '3m', target: 50 },
    { duration: '1m', target: 0  },
  ],
  thresholds: {
    'http_req_duration': ['p(95)<400'],
    'http_req_failed':   ['rate<0.01'],
  },
};

// Load data in init stage (SharedArray is efficient — loads once)
const users = new SharedArray('users', function () {
  return JSON.parse(open('./data/users.json'));
});

// ============================================================
// SETUP — runs ONCE before the test, returns data to default()
// Use: auth tokens, DB seeding, test environment preparation
// ============================================================
export function setup() {
  const loginRes = http.post('https://api.example.com/auth/login', JSON.stringify({
    username: 'admin',
    password: 'secret123',
  }), { headers: { 'Content-Type': 'application/json' } });

  const token = loginRes.json('token');
  console.log(`Setup complete. Token acquired: ${token.substring(0, 10)}...`);

  return { authToken: token }; // passed to default() and teardown()
}

// ============================================================
// DEFAULT FUNCTION — the main test logic, runs per VU per iteration
// ============================================================
export default function (data) {
  const headers = {
    'Authorization': `Bearer ${data.authToken}`,
    'Content-Type':  'application/json',
  };

  const user = users[Math.floor(Math.random() * users.length)];

  const res = http.get(`https://api.example.com/users/${user.id}`, { headers });

  check(res, {
    'status is 200':          (r) => r.status === 200,
    'response time < 500ms':  (r) => r.timings.duration < 500,
    'has user data':          (r) => r.json('id') !== undefined,
  });

  sleep(1); // Think time between iterations — always add this!
}

// ============================================================
// TEARDOWN — runs ONCE after test, receives setup() return value
// Use: cleanup, logout, delete test data
// ============================================================
export function teardown(data) {
  http.post('https://api.example.com/auth/logout', null, {
    headers: { 'Authorization': `Bearer ${data.authToken}` },
  });
  console.log('Teardown complete. Session invalidated.');
}
```

> **Critical Interview Point:** `setup()` and `teardown()` each run **once** regardless of VU count. The `default` function runs **per VU per iteration**. Data returned from `setup()` is **read-only** in `default()` — it's serialized via JSON.

---

## 5. Writing Test Scripts

### HTTP GET Request

```javascript
import http from 'k6/http';
import { check } from 'k6';

export default function () {
  // Simple GET
  const res = http.get('https://api.example.com/products');

  // With query params
  const resWithParams = http.get('https://api.example.com/products', {
    params: {
      category: 'electronics',
      limit: 10,
      page: 1,
    },
  });

  check(res, {
    'status 200':         (r) => r.status === 200,
    'body not empty':     (r) => r.body.length > 0,
    'content-type JSON':  (r) => r.headers['Content-Type'].includes('application/json'),
  });

  console.log(`Duration: ${res.timings.duration}ms`);
}
```

### HTTP POST Request

```javascript
import http from 'k6/http';
import { check } from 'k6';

export default function () {
  const payload = JSON.stringify({
    name:     'Test Product',
    price:    99.99,
    category: 'electronics',
    stock:    100,
  });

  const headers = { 'Content-Type': 'application/json' };

  const res = http.post('https://api.example.com/products', payload, { headers });

  check(res, {
    'created successfully': (r) => r.status === 201,
    'returns product id':   (r) => r.json('id') !== undefined,
  });

  // Extract created ID for use in subsequent requests
  const productId = res.json('id');
  console.log(`Created product: ${productId}`);
}
```

### PUT / PATCH / DELETE

```javascript
import http from 'k6/http';

export default function () {
  const headers = { 'Content-Type': 'application/json' };

  // PUT (full update)
  http.put('https://api.example.com/products/1',
    JSON.stringify({ name: 'Updated Product', price: 79.99 }), { headers });

  // PATCH (partial update)
  http.patch('https://api.example.com/products/1',
    JSON.stringify({ price: 89.99 }), { headers });

  // DELETE
  const delRes = http.del('https://api.example.com/products/1');
  check(delRes, { 'deleted': (r) => r.status === 204 });
}
```

### Headers and Params

```javascript
import http from 'k6/http';

export default function () {
  const params = {
    headers: {
      'Authorization':  'Bearer eyJhbGciOiJIUzI1NiJ9...',
      'Content-Type':   'application/json',
      'Accept':         'application/json',
      'X-Request-ID':   `req-${Date.now()}`,
      'X-Correlation-ID': `corr-${__VU}-${__ITER}`, // VU and iteration number
    },
    tags: { name: 'GetUserProfile' }, // Custom tag for grouping metrics
    timeout: '5s',
  };

  const res = http.get('https://api.example.com/profile', params);
}
```

### Authentication Handling

**Bearer Token (JWT)**
```javascript
import http from 'k6/http';

export function setup() {
  const res = http.post('https://api.example.com/auth/token', JSON.stringify({
    client_id:     'my-app',
    client_secret: 'secret',
    grant_type:    'client_credentials',
  }), { headers: { 'Content-Type': 'application/json' } });

  return { token: res.json('access_token') };
}

export default function (data) {
  http.get('https://api.example.com/secure', {
    headers: { 'Authorization': `Bearer ${data.token}` },
  });
}
```

**Basic Auth**
```javascript
import http from 'k6/http';
import encoding from 'k6/encoding';

export default function () {
  const credentials = encoding.b64encode('username:password');
  http.get('https://api.example.com/admin', {
    headers: { 'Authorization': `Basic ${credentials}` },
  });

  // Alternatively, use the built-in shorthand:
  http.get('https://username:password@api.example.com/admin');
}
```

**API Key**
```javascript
import http from 'k6/http';

const API_KEY = __ENV.API_KEY; // Pass via: k6 run -e API_KEY=your_key script.js

export default function () {
  http.get('https://api.example.com/data', {
    headers: { 'X-API-Key': API_KEY },
  });
}
```

### Dynamic Data (Parameterization)

**From JSON file**
```javascript
import { SharedArray } from 'k6/data';

// SharedArray: loaded ONCE, shared across all VUs — memory-efficient
const testData = new SharedArray('test-data', function () {
  return JSON.parse(open('./data/users.json'));
  // users.json: [{"id":1,"email":"user1@test.com","password":"pass1"}, ...]
});

export default function () {
  const user = testData[Math.floor(Math.random() * testData.length)];
  // OR cycle through: testData[__ITER % testData.length]

  http.post('https://api.example.com/login', JSON.stringify({
    email:    user.email,
    password: user.password,
  }));
}
```

**From CSV file**
```javascript
import { SharedArray } from 'k6/data';
import papaparse from 'https://jslib.k6.io/papaparse/5.1.1/index.js';

const csvData = new SharedArray('csv-users', function () {
  return papaparse.parse(open('./data/users.csv'), { header: true }).data;
  // CSV headers: id,email,password
});

export default function () {
  const record = csvData[__VU % csvData.length]; // Round-robin per VU
  console.log(`VU ${__VU} using: ${record.email}`);
}
```

**Random / Generated Data**
```javascript
import { uuidv4 } from 'https://jslib.k6.io/k6-utils/1.4.0/index.js';
import { randomIntBetween, randomItem } from 'https://jslib.k6.io/k6-utils/1.4.0/index.js';

export default function () {
  const payload = {
    id:       uuidv4(),
    age:      randomIntBetween(18, 65),
    country:  randomItem(['IN', 'US', 'UK', 'AU']),
    amount:   randomIntBetween(100, 10000),
  };

  http.post('https://api.example.com/orders', JSON.stringify(payload), {
    headers: { 'Content-Type': 'application/json' },
  });
}
```

---

## 6. Load Testing Types

### 1. Smoke Test

**Purpose:** Verify the script works and the system handles minimal load without errors.

```javascript
export const options = {
  vus:      2,
  duration: '1m',
  thresholds: {
    'http_req_failed':   ['rate==0'],     // Zero errors allowed
    'http_req_duration': ['p(99)<1000'],  // 99% under 1 second
  },
};
```

> Run before every full test. If smoke fails, don't waste time on load tests.

---

### 2. Load Test

**Purpose:** Test expected normal and peak load; validate SLOs.

```javascript
export const options = {
  stages: [
    { duration: '5m',  target: 100 },  // Ramp to expected load
    { duration: '10m', target: 100 },  // Hold at expected load
    { duration: '5m',  target: 200 },  // Ramp to peak load
    { duration: '10m', target: 200 },  // Hold at peak
    { duration: '5m',  target: 0   },  // Ramp down
  ],
  thresholds: {
    'http_req_duration': ['p(95)<500', 'p(99)<1000'],
    'http_req_failed':   ['rate<0.01'],
  },
};
```

---

### 3. Stress Test

**Purpose:** Find the system's breaking point; identify max capacity.

```javascript
export const options = {
  stages: [
    { duration: '2m', target: 100  },
    { duration: '5m', target: 100  },
    { duration: '2m', target: 300  },
    { duration: '5m', target: 300  },
    { duration: '2m', target: 500  },
    { duration: '5m', target: 500  },  // Breaking point zone
    { duration: '2m', target: 1000 },  // Push beyond
    { duration: '5m', target: 0    },
  ],
};
```

> **What to watch:** Where do errors start appearing? At what VU count does p(95) latency spike? That's your max capacity.

---

### 4. Spike Test

**Purpose:** Simulate sudden surge in traffic (flash sale, viral event, DDoS patterns).

```javascript
export const options = {
  stages: [
    { duration: '1m', target: 10   },  // Baseline
    { duration: '30s', target: 1000 }, // Sudden spike!
    { duration: '3m', target: 1000 },  // Stay at spike
    { duration: '30s', target: 10  },  // Drop back
    { duration: '3m', target: 10   },  // Recovery observation
    { duration: '30s', target: 0   },
  ],
};
```

> **What to watch:** Recovery time after the spike. Can autoscaling handle it? Are circuit breakers triggering?

---

### 5. Soak Test (Endurance Test)

**Purpose:** Detect memory leaks, connection pool exhaustion, gradual performance degradation over time.

```javascript
export const options = {
  stages: [
    { duration: '5m',  target: 100 },  // Ramp up
    { duration: '8h',  target: 100 },  // Hold for extended period
    { duration: '5m',  target: 0   },  // Ramp down
  ],
  thresholds: {
    'http_req_duration': ['p(95)<500'],
    'http_req_failed':   ['rate<0.01'],
  },
};
```

> **What to watch:** Does p(95) drift upward over 8 hours? If it starts at 200ms and reaches 800ms after 4 hours — memory leak or connection leak.

---

### Test Type Summary

| Test Type | VUs | Duration | Goal |
|---|---|---|---|
| Smoke | 1–5 | 1–5 min | Script validation |
| Load | Expected peak | 30–60 min | SLO validation |
| Stress | Beyond peak | 30–60 min | Breaking point |
| Spike | Sudden 10x | 5–30 min | Recovery behavior |
| Soak | Moderate | 4–24 hours | Memory/leak detection |

---

## 7. Advanced Features

### Checks and Assertions

Checks do **not** stop the test — they record pass/fail rates. Unlike assertions in unit tests, a failed check doesn't abort the VU.

```javascript
import { check } from 'k6';

const res = http.post('https://api.example.com/orders', payload, { headers });

const checkResults = check(res, {
  'status 201':            (r) => r.status === 201,
  'has order id':          (r) => r.json('orderId') !== undefined,
  'response time OK':      (r) => r.timings.duration < 600,
  'correct content-type':  (r) => r.headers['Content-Type'].includes('application/json'),
  'no error message':      (r) => !r.json('error'),
});

if (!checkResults) {
  console.error(`Check failed! Status: ${res.status}, Body: ${res.body}`);
}
```

> To **fail the test on check failure**, use thresholds on `checks` metric:
```javascript
thresholds: {
  'checks': ['rate>0.99'], // 99% of checks must pass
}
```

### Thresholds for Pass/Fail

```javascript
export const options = {
  thresholds: {
    // Trend metrics (use p(), avg, min, max)
    'http_req_duration':               ['p(95)<500', 'p(99)<1000', 'avg<300'],

    // Rate metrics
    'http_req_failed':                 ['rate<0.01'],
    'checks':                          ['rate>0.99'],

    // Counter metrics
    'http_reqs':                       ['count>1000'],

    // Tag-based thresholds (specific endpoint SLOs)
    'http_req_duration{name:Login}':   ['p(95)<300'],
    'http_req_duration{name:Checkout}':['p(95)<800'],

    // Abort test early if threshold breaches
    'http_req_duration': [{
      threshold: 'p(99)<2000',
      abortOnFail: true,      // Stop test if breached
      delayAbortEval: '1m',   // Wait 1 min before evaluating
    }],
  },
};
```

### Custom Metrics

```javascript
import { Counter, Gauge, Rate, Trend } from 'k6/metrics';

// Define custom metrics
const checkoutErrors    = new Counter('checkout_errors');
const activeCheckouts   = new Gauge('active_checkouts');
const checkoutSuccRate  = new Rate('checkout_success_rate');
const checkoutDuration  = new Trend('checkout_duration', true); // true = time metric

export default function () {
  activeCheckouts.add(1);

  const start = Date.now();
  const res = http.post('https://api.example.com/checkout', payload);
  const duration = Date.now() - start;

  checkoutDuration.add(duration);

  if (res.status === 200) {
    checkoutSuccRate.add(1);
  } else {
    checkoutSuccRate.add(0);
    checkoutErrors.add(1);
    console.error(`Checkout failed: ${res.status}`);
  }

  activeCheckouts.add(-1);
}

// Use in thresholds
export const options = {
  thresholds: {
    'checkout_errors':        ['count<10'],
    'checkout_success_rate':  ['rate>0.95'],
    'checkout_duration':      ['p(95)<1000'],
  },
};
```

### Data Parameterization (CSV/JSON)

**JSON with SharedArray (recommended)**
```javascript
import { SharedArray } from 'k6/data';

// Loads once, shared across all VUs — extremely memory efficient
const products = new SharedArray('products', () =>
  JSON.parse(open('./data/products.json'))
);

export default function () {
  // Different VUs test different products concurrently
  const product = products[__VU % products.length];

  http.get(`https://api.example.com/products/${product.id}`);
}
```

**CSV Parameterization**
```javascript
import papaparse from 'https://jslib.k6.io/papaparse/5.1.1/index.js';
import { SharedArray } from 'k6/data';

const csvUsers = new SharedArray('csv', () =>
  papaparse.parse(open('./data/test_users.csv'), {
    header: true,
    skipEmptyLines: true,
  }).data
);

export default function () {
  const user = csvUsers[(__VU - 1 + __ITER) % csvUsers.length];
  console.log(`Testing with: ${user.email}`);
}
```

### Correlation Handling

Correlation extracts dynamic values (tokens, IDs, session keys) from responses to use in subsequent requests.

```javascript
import http from 'k6/http';
import { check } from 'k6';

export default function () {
  // Step 1: Login and extract token (correlation)
  const loginRes = http.post('https://api.example.com/auth/login', JSON.stringify({
    email:    'user@example.com',
    password: 'password123',
  }), { headers: { 'Content-Type': 'application/json' } });

  check(loginRes, { 'login success': (r) => r.status === 200 });

  // Extract via JSON path
  const token = loginRes.json('data.access_token');
  const userId = loginRes.json('data.user.id');

  // Step 2: Use extracted values in next request
  const profileRes = http.get(`https://api.example.com/users/${userId}`, {
    headers: { 'Authorization': `Bearer ${token}` },
  });

  // Step 3: Create order, extract order ID
  const orderRes = http.post('https://api.example.com/orders', JSON.stringify({
    userId:    userId,
    productId: 'PROD-001',
    quantity:  2,
  }), {
    headers: {
      'Authorization': `Bearer ${token}`,
      'Content-Type':  'application/json',
    },
  });

  const orderId = orderRes.json('orderId');

  // Step 4: Poll order status using correlated orderId
  http.get(`https://api.example.com/orders/${orderId}/status`, {
    headers: { 'Authorization': `Bearer ${token}` },
  });
}
```

**Extract with Regex (HTML forms, CSRF tokens)**
```javascript
const res = http.get('https://example.com/login');
const csrfToken = res.html().find('input[name="_csrf"]').attr('value');

http.post('https://example.com/login', {
  username:  'user',
  password:  'pass',
  _csrf:     csrfToken, // Correlated CSRF token
});
```

---

## 8. Performance Optimization Insights

### How to Analyze Results

**K6 Console Output — Key Sections:**
```
✓ status 200         ────────────────────────── 99.8% ✓ / 0.2% ✗
✓ response time OK   ────────────────────────── 98.1% ✓ / 1.9% ✗

http_req_duration............: avg=243ms  min=45ms   med=210ms   max=4.2s
                               p(90)=380ms p(95)=512ms p(99)=1.8s
http_req_failed..............: 0.18% ✓ 18 / ✗ 9982
http_reqs....................: 10000  167.3/s

iteration_duration...........: avg=1.24s  min=1.04s  med=1.21s  max=5.2s
vus..........................: 100 min=97   max=100
```

**What to look for:**
- `p(95)` vs your SLO — the most common KPI
- `p(99)` vs `p(50)` gap — large gap = high tail latency (outlier requests suffering)
- `http_req_failed` rate — anything above 0.1% needs investigation
- `http_req_waiting` vs `http_req_duration` — if waiting >> duration, server is slow
- `http_req_connecting` spikes — TCP connection pool exhaustion

### Bottleneck Identification

```
Response Time Breakdown:
┌─────────────────────────────────────────────────┐
│ http_req_connecting   ↑HIGH  → Connection pool  │
│ http_req_tls_handshaking ↑HIGH → TLS overhead   │
│ http_req_waiting      ↑HIGH  → Server slowness  │
│ http_req_receiving    ↑HIGH  → Large payload    │
└─────────────────────────────────────────────────┘
```

| Symptom | Likely Cause | Fix |
|---|---|---|
| High `http_req_connecting` | Too many new TCP connections | Enable keep-alive, increase server connection pool |
| High `http_req_waiting` (TTFB) | Server CPU/DB bottleneck | Profile backend, add caching, scale horizontally |
| High `http_req_receiving` | Large response payloads | Compression (gzip), pagination, field filtering |
| Errors only at high VUs | Thread/connection pool exhaustion | Tune server pool size |
| Gradual latency drift in soak | Memory leak | Heap profiling, GC tuning |
| Spiky p(99) | GC pauses or lock contention | Application-level profiling |

### Best Practices

**Script Design:**
- Always add `sleep(1)` or realistic think time — no think time = DDoS simulation, not load test
- Use `SharedArray` for test data — never load files inside `default()` 
- Tag requests (`tags: { name: 'Login' }`) for granular threshold tracking
- Use `__ENV` for environment-specific configs, never hardcode URLs
- Group related requests with `group()` for logical organization

**Test Execution:**
- Always run smoke test first
- Run from cloud/external network to avoid testing your own infra's bandwidth
- Warm up the system before measuring (ramp period)
- Monitor server-side metrics in parallel (CPU, memory, GC, DB connections)
- Test at least 3 runs to eliminate variance

**Result Analysis:**
- Never report average — always use percentiles (p95, p99)
- Compare baseline vs current (regression detection)
- Correlate test results with APM data (Datadog, New Relic, Dynatrace)
- Define SLOs before the test, not after

```javascript
// Good: Tag requests for granular analysis
http.get(url, { tags: { name: 'ProductDetail', flow: 'Browse' } });

// Good: Group related steps
import { group } from 'k6';

export default function () {
  group('User Login Flow', () => {
    const res = http.post('/auth/login', credentials);
    check(res, { 'logged in': (r) => r.status === 200 });
  });

  group('Product Browse Flow', () => {
    http.get('/products');
    http.get('/products/123');
  });
}
```

---

## 9. K6 + Real-World Case Study

### Scenario: E-Commerce Platform — Black Friday Load Test

**Context:** An e-commerce platform expects 10x normal traffic during Black Friday sale. Normal load: 500 concurrent users. Expected peak: 5000 concurrent users. Target: 99.9% uptime, p(95) < 800ms for all critical flows.

**Critical User Flows:**
1. Browse Products (50% of traffic)
2. User Login (20%)
3. Add to Cart (20%)
4. Checkout (10%)

### Complete Test Script

```javascript
import http from 'k6/http';
import { check, group, sleep } from 'k6';
import { Counter, Rate, Trend } from 'k6/metrics';
import { SharedArray } from 'k6/data';
import { uuidv4 } from 'https://jslib.k6.io/k6-utils/1.4.0/index.js';

// ─── Custom Metrics ───────────────────────────────────────
const checkoutSuccessRate = new Rate('checkout_success_rate');
const checkoutDuration    = new Trend('checkout_duration_ms', true);
const cartErrors          = new Counter('cart_errors');

// ─── Test Data ────────────────────────────────────────────
const users = new SharedArray('users', () =>
  JSON.parse(open('./data/users.json'))
);

const products = new SharedArray('products', () =>
  JSON.parse(open('./data/products.json'))
);

// ─── Config ───────────────────────────────────────────────
const BASE_URL = __ENV.BASE_URL || 'https://api.shop.example.com';

// ─── Load Profile: Simulate Black Friday Surge ────────────
export const options = {
  scenarios: {
    browse_products: {
      executor:           'ramping-vus',
      startVUs:           0,
      stages: [
        { duration: '5m',  target: 2500 }, // 50% of 5000
        { duration: '20m', target: 2500 },
        { duration: '5m',  target: 0    },
      ],
      exec: 'browseProducts',
    },
    user_login: {
      executor: 'ramping-vus',
      startVUs: 0,
      stages: [
        { duration: '5m',  target: 1000 }, // 20% of 5000
        { duration: '20m', target: 1000 },
        { duration: '5m',  target: 0    },
      ],
      exec: 'userLogin',
    },
    checkout_flow: {
      executor: 'ramping-vus',
      startVUs: 0,
      stages: [
        { duration: '5m',  target: 500 }, // 10% of 5000
        { duration: '20m', target: 500 },
        { duration: '5m',  target: 0   },
      ],
      exec: 'checkoutFlow',
    },
  },

  thresholds: {
    // Global SLOs
    'http_req_duration':                     ['p(95)<800', 'p(99)<2000'],
    'http_req_failed':                       ['rate<0.001'], // 0.1% max errors

    // Flow-specific SLOs
    'http_req_duration{name:ProductList}':   ['p(95)<500'],
    'http_req_duration{name:Login}':         ['p(95)<300'],
    'http_req_duration{name:Checkout}':      ['p(95)<1500'],

    // Business metrics
    'checkout_success_rate':                 ['rate>0.99'],
    'cart_errors':                           ['count<50'],
  },
};

// ─── Setup: System Health Check ───────────────────────────
export function setup() {
  const healthRes = http.get(`${BASE_URL}/health`);
  if (healthRes.status !== 200) {
    throw new Error(`System not healthy! Status: ${healthRes.status}`);
  }
  console.log('✅ System health check passed. Starting test...');
}

// ─── Scenario 1: Browse Products (no auth needed) ─────────
export function browseProducts() {
  group('Browse Products', () => {
    const listRes = http.get(`${BASE_URL}/products?page=1&limit=20`, {
      tags: { name: 'ProductList' },
    });

    check(listRes, {
      'product list 200':    (r) => r.status === 200,
      'has products':        (r) => r.json('data.items').length > 0,
    });

    if (listRes.status === 200) {
      const items   = listRes.json('data.items');
      const product = items[Math.floor(Math.random() * items.length)];

      const detailRes = http.get(`${BASE_URL}/products/${product.id}`, {
        tags: { name: 'ProductDetail' },
      });

      check(detailRes, {
        'product detail 200': (r) => r.status === 200,
        'has price':          (r) => r.json('price') > 0,
      });
    }
  });

  sleep(2 + Math.random() * 3); // 2–5 seconds think time
}

// ─── Scenario 2: User Login ────────────────────────────────
export function userLogin() {
  const user = users[__VU % users.length];

  group('Login Flow', () => {
    const loginRes = http.post(`${BASE_URL}/auth/login`, JSON.stringify({
      email:    user.email,
      password: user.password,
    }), {
      headers: { 'Content-Type': 'application/json' },
      tags: { name: 'Login' },
    });

    check(loginRes, {
      'login 200':    (r) => r.status === 200,
      'has token':    (r) => r.json('token') !== null,
    });

    if (loginRes.status === 200) {
      const token = loginRes.json('token');

      const profileRes = http.get(`${BASE_URL}/profile`, {
        headers: { 'Authorization': `Bearer ${token}` },
        tags: { name: 'Profile' },
      });

      check(profileRes, { 'profile loaded': (r) => r.status === 200 });
    }
  });

  sleep(1 + Math.random() * 2);
}

// ─── Scenario 3: Full Checkout Flow ───────────────────────
export function checkoutFlow() {
  const user    = users[__VU % users.length];
  const product = products[Math.floor(Math.random() * products.length)];
  const headers = { 'Content-Type': 'application/json' };

  group('Checkout Flow', () => {
    // Login
    const loginRes = http.post(`${BASE_URL}/auth/login`,
      JSON.stringify({ email: user.email, password: user.password }),
      { headers, tags: { name: 'Login' } }
    );

    if (loginRes.status !== 200) return;

    const token   = loginRes.json('token');
    const authHdr = { ...headers, 'Authorization': `Bearer ${token}` };

    sleep(1);

    // Add to cart
    const cartRes = http.post(`${BASE_URL}/cart/items`, JSON.stringify({
      productId: product.id,
      quantity:  1,
    }), { headers: authHdr, tags: { name: 'AddToCart' } });

    if (!check(cartRes, { 'cart add 201': (r) => r.status === 201 })) {
      cartErrors.add(1);
      return;
    }

    sleep(2);

    // Checkout
    const checkoutStart = Date.now();
    const checkoutRes = http.post(`${BASE_URL}/orders/checkout`, JSON.stringify({
      cartId:        cartRes.json('cartId'),
      paymentMethod: 'card',
      addressId:     user.addressId,
    }), { headers: authHdr, tags: { name: 'Checkout' } });

    checkoutDuration.add(Date.now() - checkoutStart);

    const success = check(checkoutRes, {
      'checkout 200':    (r) => r.status === 200,
      'order created':   (r) => r.json('orderId') !== undefined,
    });

    checkoutSuccessRate.add(success);
  });

  sleep(3 + Math.random() * 2);
}

// ─── Teardown ─────────────────────────────────────────────
export function teardown() {
  console.log('✅ Test complete. Check Grafana dashboard for results.');
}
```

### Results Interpretation

**Scenario Results (Simulated):**
```
Scenarios:           browse_products, user_login, checkout_flow
Duration:            30m
Total Requests:      1,245,680
Failed Requests:     1,246 (0.1%)

http_req_duration:
  avg=312ms   p(50)=245ms   p(90)=580ms   p(95)=890ms ❌ SLO BREACHED
  p(99)=2.3s  max=8.5s

checkout_success_rate: 97.8% ❌ (target: 99%)
checkout_duration_ms:  p(95)=1.9s ❌ (target: 1.5s)
cart_errors:           23 ✅
```

### Issues Found & Fixes

| Issue | Finding | Fix |
|---|---|---|
| **p(95) latency breach** | Checkout API p(95) = 1.9s | DB query missing index on `orders.userId` |
| **Checkout success rate drop** | 2.2% checkout failures at peak | Payment service connection pool exhausted (max 50, needed 200) |
| **Latency spikes** | p(99) = 8.5s during spike | GC pauses in JVM service; tuned `-Xmx` and GC strategy |
| **Cart errors at peak** | 23 cart errors above 3000 VUs | Redis cart store had connection timeout at high concurrency |

**After fixes — re-run results:**
```
http_req_duration:   p(95)=620ms ✅   p(99)=1.4s ✅
checkout_success_rate: 99.3% ✅
checkout_duration_ms:  p(95)=1.2s ✅
```

---

## 10. CI/CD Integration

### GitHub Actions

```yaml
# .github/workflows/performance-test.yml
name: K6 Performance Tests

on:
  push:
    branches: [main, develop]
  pull_request:
    branches: [main]
  schedule:
    - cron: '0 2 * * *'  # Daily at 2 AM

jobs:
  performance-test:
    runs-on: ubuntu-latest

    steps:
      - name: Checkout code
        uses: actions/checkout@v4

      - name: Install K6
        run: |
          sudo gpg --no-default-keyring \
            --keyring /usr/share/keyrings/k6-archive-keyring.gpg \
            --keyserver hkp://keyserver.ubuntu.com:80 \
            --recv-keys C5AD17C747E3415A3642D57D77C6C491D6AC1D69
          echo "deb [signed-by=/usr/share/keyrings/k6-archive-keyring.gpg] \
            https://dl.k6.io/deb stable main" \
            | sudo tee /etc/apt/sources.list.d/k6.list
          sudo apt-get update && sudo apt-get install k6

      - name: Run Smoke Test
        run: k6 run tests/smoke-test.js
        env:
          BASE_URL: ${{ secrets.STAGING_URL }}
          API_KEY:  ${{ secrets.API_KEY }}

      - name: Run Load Test
        run: k6 run --out json=results/load-test.json tests/load-test.js
        env:
          BASE_URL: ${{ secrets.STAGING_URL }}

      - name: Upload Results
        uses: actions/upload-artifact@v4
        if: always()
        with:
          name: k6-results
          path: results/

      - name: Send results to Grafana Cloud
        run: |
          k6 run \
            --out cloud \
            tests/load-test.js
        env:
          K6_CLOUD_TOKEN: ${{ secrets.K6_CLOUD_TOKEN }}
          K6_CLOUD_PROJECT_ID: ${{ secrets.K6_CLOUD_PROJECT_ID }}
```

### Jenkins Pipeline

```groovy
// Jenkinsfile
pipeline {
    agent any

    environment {
        BASE_URL    = credentials('staging-api-url')
        API_KEY     = credentials('api-key')
        K6_VERSION  = '0.52.0'
    }

    stages {
        stage('Install K6') {
            steps {
                sh '''
                    wget -q https://github.com/grafana/k6/releases/download/v${K6_VERSION}/k6-v${K6_VERSION}-linux-amd64.tar.gz
                    tar -xzf k6-v${K6_VERSION}-linux-amd64.tar.gz
                    sudo mv k6-v${K6_VERSION}-linux-amd64/k6 /usr/local/bin/
                '''
            }
        }

        stage('Smoke Test') {
            steps {
                sh 'k6 run tests/smoke-test.js'
            }
        }

        stage('Load Test') {
            steps {
                sh '''
                    k6 run \
                      --out json=results/load-test-${BUILD_NUMBER}.json \
                      tests/load-test.js
                '''
            }
            post {
                always {
                    archiveArtifacts artifacts: 'results/*.json'
                    publishHTML([
                        reportDir:   'results',
                        reportFiles: 'report.html',
                        reportName:  'K6 Performance Report'
                    ])
                }
            }
        }
    }

    post {
        failure {
            emailext (
                subject: "Performance Test FAILED - Build ${BUILD_NUMBER}",
                body:    "K6 load test failed. Check results: ${BUILD_URL}",
                to:      'sre-team@company.com'
            )
        }
    }
}
```

### Docker Compose for Local CI Simulation

```yaml
# docker-compose.yml
version: '3.8'

services:
  influxdb:
    image: influxdb:1.8
    ports: ['8086:8086']
    environment:
      - INFLUXDB_DB=k6

  grafana:
    image: grafana/grafana:latest
    ports: ['3000:3000']
    environment:
      - GF_AUTH_ANONYMOUS_ENABLED=true
      - GF_AUTH_ANONYMOUS_ORG_ROLE=Admin
    volumes:
      - ./grafana/provisioning:/etc/grafana/provisioning

  k6:
    image: grafana/k6:latest
    volumes:
      - ./tests:/scripts
      - ./data:/data
    environment:
      - BASE_URL=http://app:8080
    command: run --out influxdb=http://influxdb:8086/k6 /scripts/load-test.js
    depends_on: [influxdb]
```

```bash
# Run full monitoring stack
docker-compose up -d influxdb grafana
docker-compose run k6

# Access Grafana: http://localhost:3000
# Import K6 dashboard: Grafana ID 2587
```

> **Engineer Insight:** In CI, always use `--exit-on-running` for scheduled tests and set `abortOnFail: true` on thresholds to give clear pass/fail signals to the pipeline.

---

## 11. Common Interview Questions

### Conceptual Questions

**Q1: What is the difference between K6 and JMeter? When would you choose K6?**

> K6 is a code-first, developer-friendly tool with low resource usage (Go runtime, ~20MB RAM per 100 VUs vs JMeter's JVM overhead). K6 scripts are plain JavaScript, easy to version control and review. Choose K6 for modern microservices, CI/CD pipelines, and when the team is developer-heavy. Choose JMeter for legacy enterprise systems, teams requiring a GUI, or when JDBC/LDAP protocol testing is needed.

---

**Q2: What is the difference between `check()` and `threshold`?**

> `check()` is an in-test assertion that records pass/fail metrics per iteration — it doesn't stop the test. A `threshold` is a post-run (or real-time) pass/fail criterion that determines the exit code of the test. You use checks to observe, and thresholds to enforce SLOs. A failed check won't fail your CI pipeline unless you add `thresholds: { 'checks': ['rate>0.99'] }`.

---

**Q3: Explain the K6 lifecycle stages and their execution context.**

> K6 has 4 lifecycle stages: (1) **Init** — runs once per VU, used for imports and configuration; (2) **setup()** — runs once before any VU starts, used for auth/test data preparation, returns a data object; (3) **default()** — runs per VU per iteration, receives setup data as read-only; (4) **teardown()** — runs once after all VUs finish, used for cleanup. The key distinction is that setup/teardown run in their own VU context and don't count toward test metrics.

---

**Q4: What is `SharedArray` and why should you use it?**

> `SharedArray` loads data once in the init context and shares it across all VUs via a read-only, memory-mapped structure. Without it, if you use `JSON.parse(open(...))` inside `default()`, each VU would load its own copy — 1000 VUs × 10MB file = 10GB RAM. `SharedArray` ensures one copy in memory regardless of VU count, critical for large parameterization datasets.

---

**Q5: What is the difference between `p(95)` and average response time? Why do SREs prefer percentiles?**

> Average can be misleading — a few very fast requests can mask many slow ones. `p(95)` means 95% of users experience a response time at or below this value. It's a better SLO metric because it captures tail latency that affects real users. If p(50) = 200ms but p(99) = 5s, your average might be 250ms but 1% of users (potentially thousands) have terrible experiences. SLEs and SLOs are always defined in percentiles.

---

### Scenario-Based Questions

**Q6: Your load test shows p(95) < 500ms at 100 VUs but spikes to 3s at 500 VUs. What's causing this and how do you investigate?**

> This suggests a scalability bottleneck. Investigation steps: (1) Break down response time components (`http_req_waiting` vs `http_req_connecting`) — high `waiting` points to server-side bottleneck; (2) Check if errors correlate with latency increase (connection pool exhaustion); (3) Tag requests by endpoint and find which endpoint degrades first; (4) Correlate with server metrics — CPU, memory, DB connection count, thread pool utilization; (5) Common causes: thread pool too small, DB connection pool exhausted, missing index causing full table scan, GC pauses, or single-threaded code path. Fix based on finding: increase pool sizes, add DB indexes, optimize queries, or scale horizontally.

---

**Q7: You need to test a login API that returns a CSRF token which must be used in subsequent requests. How do you handle this in K6?**

> This is a correlation problem. In the `default()` function: (1) Make a GET request to the login page; (2) Extract the CSRF token from the response using `res.html().find('input[name="_csrf"]').attr('value')` or regex; (3) Include the extracted token in the POST request body or header. This simulates how a real browser would handle stateful, CSRF-protected forms. The extracted value persists within the VU's scope for that iteration.

---

**Q8: How would you integrate K6 into a GitHub Actions CI pipeline and ensure it fails the build on performance regression?**

> Define thresholds in the script with `abortOnFail: true` for critical ones. In GitHub Actions, run k6 as a step — K6 returns exit code 1 if any threshold is breached, which automatically fails the CI job. Store baseline results and compare p(95) against the previous run using a custom comparison script. Use `--out json` to export results and archive them as artifacts. Add `k6 cloud` integration for hosted results history and trend charts.

---

**Q9: During a soak test (8 hours), response time starts at 200ms and gradually increases to 1.5s. What's happening?**

> This pattern is classic **memory leak or resource exhaustion**. Investigation: (1) Monitor JVM heap or process memory over time — if it grows without plateauing, memory leak; (2) Check DB connection pool — if connections aren't being released, pool fills up causing queuing; (3) Check for growing in-memory caches without eviction; (4) Look for file descriptor leaks; (5) Analyze GC logs — increasing GC pause times correlate with response time drift. Fix: heap profiling with VisualVM/YourKit, review connection pool `maxLifetime` settings, implement proper resource cleanup.

---

**Q10: What are executors in K6 and when would you use `constant-arrival-rate` vs `ramping-vus`?**

> Executors control how VUs and iterations are scheduled. `ramping-vus` controls the number of concurrent users — good for simulating user-based load. `constant-arrival-rate` controls the **rate of iterations per second** regardless of response time — good for simulating realistic RPS targets (e.g., "the system must handle 1000 requests/second"). If your API slows down with `ramping-vus`, throughput drops; with `constant-arrival-rate`, VUs increase automatically to maintain the target rate, giving a more realistic production simulation for rate-sensitive SLOs.

---

**Q11: How do you handle test data management in K6 at scale?**

> Use `SharedArray` for all test data files — loaded once, shared across VUs. For VU-specific isolation (each VU needs different credentials), use `csvData[(__VU - 1) % csvData.length]`. For iteration uniqueness, combine VU and iteration: `data[(__VU * 100 + __ITER) % data.length]`. For sensitive data, use `__ENV` variables passed at runtime — never hardcode in scripts. For very large datasets, consider generating data dynamically with UUIDs or sequence numbers.

---

**Q12: What is the `k6/execution` module and how is it useful?**

> `k6/execution` provides runtime metadata about the current test execution. It lets you access `execution.scenario.name`, `execution.vu.idInTest`, `execution.instance.vusActive` etc. This is useful for: (1) Routing VUs to different test paths based on their ID; (2) Logging with VU context; (3) Building canary-style scenarios where only VU 1 does setup validation. Example: `import exec from 'k6/execution'; const vuId = exec.vu.idInTest;`

---

**Q13: Explain how you would test a WebSocket-based real-time chat application with K6.**

```javascript
import ws from 'k6/ws';
import { check } from 'k6';

export default function () {
  const url  = 'wss://chat.example.com/socket';
  const params = { headers: { 'Authorization': `Bearer ${token}` } };

  const res = ws.connect(url, params, function (socket) {
    socket.on('open',    () => socket.send(JSON.stringify({ type: 'join', room: 'general' })));
    socket.on('message', (data) => {
      check(JSON.parse(data), { 'valid message format': (m) => m.type !== undefined });
    });
    socket.on('error',   (e) => console.error(`WS Error: ${e}`));

    socket.setTimeout(() => socket.close(), 30000); // Hold connection 30s
  });

  check(res, { 'status 101 (upgrade)': (r) => r.status === 101 });
}
```

---

**Q14: What is the difference between `http_req_duration` and `iteration_duration`?**

> `http_req_duration` measures only the time for a single HTTP request (send + wait + receive). `iteration_duration` measures the time for one complete execution of the `default()` function, including all HTTP requests, `sleep()` calls, data processing, and any logic. For SLO reporting, use `http_req_duration` per endpoint. For understanding overall user journey timing (end-to-end), use `iteration_duration`. If `iteration_duration` >> sum of all `http_req_duration`, your test has excessive sleep or slow JS logic.

---

**Q15: How do you run different test scenarios concurrently in K6?**

> Use the `scenarios` option to define multiple named executors running simultaneously:
```javascript
export const options = {
  scenarios: {
    read_heavy:  { executor: 'ramping-vus', exec: 'readScenario',  ... },
    write_heavy: { executor: 'ramping-vus', exec: 'writeScenario', ... },
    admin_ops:   { executor: 'constant-vus', vus: 5, exec: 'adminScenario', duration: '10m' },
  },
};
```
Each scenario runs independently, calling its designated `exec` function. This is how you simulate realistic mixed workloads instead of a single endpoint hammering.

---

**Q16: What would you investigate if K6 shows very low error rate but your APM shows DB timeout errors?**

> K6 only measures what the server returns to the client. If the application catches the DB timeout internally and returns a 200 OK with degraded/empty data, K6 won't flag it as an error. This is a "silent failure." Solutions: (1) Add content checks — verify response body contains expected data, not just status code; (2) Check for error flags in JSON response (`r.json('error') !== null`); (3) Add custom metrics that track partial/degraded responses; (4) Correlate K6 timestamps with APM traces to find the gap.

---

**Q17: How do you prevent K6 from triggering WAF/rate-limiting during tests?**

> (1) Add `sleep()` with realistic think time between requests; (2) Ramp up gradually — don't start with full load immediately; (3) Use realistic user agents in headers; (4) Randomize request patterns with parameterization; (5) Coordinate with the security team to whitelist the test runner's IP; (6) Use distributed execution (K6 Cloud or multiple runners) to spread load across IPs; (7) Add `X-Load-Test: true` header and configure WAF to allow it.

---

**Q18: What is the `handleSummary()` function in K6?**

> `handleSummary()` allows you to customize the end-of-test summary output — generate custom HTML reports, send metrics to Slack/PagerDuty, or write to files.
```javascript
import { textSummary } from 'https://jslib.k6.io/k6-summary/0.0.2/index.js';

export function handleSummary(data) {
  return {
    'results/summary.json': JSON.stringify(data),
    'results/report.html':  generateHtmlReport(data), // custom function
    stdout: textSummary(data, { indent: ' ', enableColors: true }),
  };
}
```

---

## 12. Hands-on Mini Project

### Build a Load Test for a Public REST API (JSONPlaceholder)

**Objective:** Load test `https://jsonplaceholder.typicode.com` simulating CRUD operations. Define SLOs, run all test types, and analyze results.

**Project Structure:**
```
k6-project/
├── tests/
│   ├── smoke-test.js
│   ├── load-test.js
│   └── stress-test.js
├── scripts/
│   └── full-test.js
├── data/
│   └── users.json
├── results/
└── README.md
```

**Step 1: Create test data**
```json
// data/users.json
[
  { "id": 1, "name": "Alice Johnson", "email": "alice@example.com" },
  { "id": 2, "name": "Bob Smith",    "email": "bob@example.com"   },
  { "id": 3, "name": "Carol White",  "email": "carol@example.com" }
]
```

**Step 2: Smoke Test**
```javascript
// tests/smoke-test.js
import http from 'k6/http';
import { check, sleep } from 'k6';

export const options = {
  vus: 2, duration: '1m',
  thresholds: {
    'http_req_failed':   ['rate==0'],
    'http_req_duration': ['p(99)<2000'],
  },
};

export default function () {
  const res = http.get('https://jsonplaceholder.typicode.com/posts/1');
  check(res, {
    'status 200': (r) => r.status === 200,
    'has title':  (r) => r.json('title').length > 0,
  });
  sleep(1);
}
```

**Step 3: Full CRUD Load Test**
```javascript
// scripts/full-test.js
import http from 'k6/http';
import { check, group, sleep } from 'k6';
import { SharedArray } from 'k6/data';
import { Counter } from 'k6/metrics';

const BASE  = 'https://jsonplaceholder.typicode.com';
const users = new SharedArray('u', () => JSON.parse(open('../data/users.json')));

const crudErrors = new Counter('crud_errors');

export const options = {
  stages: [
    { duration: '1m', target: 20  },
    { duration: '3m', target: 20  },
    { duration: '1m', target: 50  },
    { duration: '3m', target: 50  },
    { duration: '1m', target: 0   },
  ],
  thresholds: {
    'http_req_duration': ['p(95)<600', 'p(99)<1500'],
    'http_req_failed':   ['rate<0.02'],
    'crud_errors':       ['count<10'],
  },
};

export default function () {
  const user = users[__VU % users.length];
  const hdrs = { 'Content-Type': 'application/json' };

  group('GET Posts', () => {
    const r = http.get(`${BASE}/posts?userId=${user.id}`, { tags: { name: 'GetPosts' } });
    if (!check(r, { 'get posts 200': (x) => x.status === 200 })) crudErrors.add(1);
  });

  sleep(0.5);

  group('GET Single Post', () => {
    const postId = Math.floor(Math.random() * 100) + 1;
    const r = http.get(`${BASE}/posts/${postId}`, { tags: { name: 'GetPost' } });
    check(r, { 'single post 200': (x) => x.status === 200 });
  });

  sleep(0.5);

  group('POST Create', () => {
    const r = http.post(`${BASE}/posts`, JSON.stringify({
      title:  `Load Test Post by ${user.name}`,
      body:   'Generated by K6 performance test',
      userId: user.id,
    }), { headers: hdrs, tags: { name: 'CreatePost' } });

    if (!check(r, { 'create 201': (x) => x.status === 201 })) crudErrors.add(1);
  });

  sleep(1);

  group('PUT Update', () => {
    const r = http.put(`${BASE}/posts/1`, JSON.stringify({
      id:     1,
      title:  'Updated title',
      body:   'Updated body',
      userId: user.id,
    }), { headers: hdrs, tags: { name: 'UpdatePost' } });

    check(r, { 'update 200': (x) => x.status === 200 });
  });

  sleep(1);
}
```

**Step 4: Run Tests**
```bash
# Smoke first
k6 run tests/smoke-test.js

# Load test with JSON output
k6 run --out json=results/load-$(date +%Y%m%d_%H%M).json scripts/full-test.js

# Stress test
k6 run tests/stress-test.js

# With Grafana/InfluxDB
docker-compose up -d
k6 run --out influxdb=http://localhost:8086/k6 scripts/full-test.js
```

**Step 5: Analyze Results**

Look for:
- Which endpoint has the highest p(95)?
- At which VU count do errors appear?
- Is `http_req_waiting` high (server-side issue)?
- Compare `p(50)` vs `p(99)` gap — small gap = consistent performance

---

## 13. Cheat Sheet

### CLI Commands

```bash
# Basic run
k6 run script.js

# Override VUs and duration
k6 run --vus 50 --duration 2m script.js

# Set environment variable
k6 run -e BASE_URL=https://api.staging.com script.js

# Output formats
k6 run --out json=results.json script.js
k6 run --out csv=results.csv script.js
k6 run --out influxdb=http://localhost:8086/k6 script.js
k6 run --out cloud script.js                     # K6 Cloud

# Quiet mode (no progress bar)
k6 run --quiet script.js

# Verbose logging
k6 run --verbose script.js

# Log HTTP requests
k6 run --http-debug script.js
k6 run --http-debug=full script.js               # With bodies

# Multiple outputs
k6 run --out json=r.json --out influxdb=http://localhost:8086/k6 script.js

# Archive (bundle script + dependencies)
k6 archive script.js -o archive.tar
k6 run archive.tar

# Convert HAR to K6 script
k6 convert recording.har -o script.js
```

### Key Code Snippets

```javascript
// ── Imports ─────────────────────────────────────────────
import http                    from 'k6/http';
import { check, sleep, group } from 'k6';
import { SharedArray }         from 'k6/data';
import { Counter, Rate, Trend, Gauge } from 'k6/metrics';
import exec                    from 'k6/execution';

// ── Options Quick Reference ──────────────────────────────
export const options = {
  vus: 10, duration: '30s',                        // Simple
  stages: [                                          // Ramp
    { duration: '1m', target: 100 },
    { duration: '5m', target: 100 },
    { duration: '1m', target: 0   },
  ],
  thresholds: {
    'http_req_duration': ['p(95)<500'],
    'http_req_failed':   ['rate<0.01'],
  },
};

// ── HTTP Methods ─────────────────────────────────────────
const get    = http.get(url, params);
const post   = http.post(url, body, params);
const put    = http.put(url, body, params);
const patch  = http.patch(url, body, params);
const del    = http.del(url, null, params);

// ── Request Params Template ──────────────────────────────
const params = {
  headers: { 'Content-Type': 'application/json', 'Authorization': `Bearer ${token}` },
  tags:    { name: 'MyEndpoint', flow: 'checkout' },
  timeout: '10s',
};

// ── Checks ───────────────────────────────────────────────
check(res, {
  'status 200':         (r) => r.status === 200,
  'body has id':        (r) => r.json('id') !== undefined,
  'latency < 500ms':    (r) => r.timings.duration < 500,
  'has auth header':    (r) => r.headers['X-Auth'] !== undefined,
});

// ── Custom Metrics ───────────────────────────────────────
const myCounter = new Counter('my_counter');
const myRate    = new Rate('my_rate');
const myTrend   = new Trend('my_trend', true);  // true = time-based
const myGauge   = new Gauge('my_gauge');

myCounter.add(1);
myRate.add(true);       // true = success, false = failure
myTrend.add(duration);
myGauge.add(current);

// ── SharedArray ──────────────────────────────────────────
const data = new SharedArray('name', () => JSON.parse(open('./file.json')));
const item = data[__VU % data.length];   // Round-robin
const item2 = data[Math.floor(Math.random() * data.length)]; // Random

// ── VU / Iteration Info ──────────────────────────────────
console.log(__VU);    // Current VU ID (1-based)
console.log(__ITER);  // Current iteration number (0-based)
console.log(__ENV.MY_VAR);  // Environment variable

// ── Execution Context ────────────────────────────────────
import exec from 'k6/execution';
exec.vu.idInTest;         // Unique VU ID in test
exec.scenario.name;       // Current scenario name
exec.instance.vusActive;  // Currently active VUs

// ── Group ────────────────────────────────────────────────
group('My Flow', () => {
  http.get('/step1');
  http.post('/step2', payload);
});

// ── Response Properties ──────────────────────────────────
res.status            // HTTP status code
res.body              // Response body (string)
res.json()            // Parse body as JSON
res.json('data.id')   // JSONPath extraction
res.headers           // Response headers
res.timings.duration  // Total request time (ms)
res.timings.waiting   // TTFB (ms)
res.timings.connecting// TCP connect time (ms)
res.html()            // Parse as HTML (jQuery-like)

// ── Threshold Operators ──────────────────────────────────
// p(N)  — Nth percentile
// avg   — Average
// min   — Minimum
// max   — Maximum
// rate  — For Rate metrics
// count — For Counter metrics
// value — For Gauge metrics
// 'p(95)<500'    — p95 must be below 500ms
// 'rate<0.01'    — Less than 1% failures
// 'count>1000'   — At least 1000 occurrences

// ── HandleSummary ────────────────────────────────────────
export function handleSummary(data) {
  return {
    'summary.json': JSON.stringify(data),
    stdout: textSummary(data, { indent: ' ', enableColors: true }),
  };
}
```

### Threshold Quick Reference

```javascript
thresholds: {
  // Common SLO patterns
  'http_req_duration':              ['p(95)<500', 'p(99)<1000'],
  'http_req_failed':                ['rate<0.01'],       // < 1% errors
  'http_reqs':                      ['rate>100'],         // > 100 RPS
  'checks':                         ['rate>0.99'],        // > 99% pass
  'http_req_duration{name:Login}':  ['p(95)<300'],        // Tagged endpoint
  'my_custom_rate':                 ['rate>0.95'],

  // With abort
  'http_req_duration': [{
    threshold:      'p(99)<2000',
    abortOnFail:    true,
    delayAbortEval: '30s',
  }],
}
```

---

*Document Version: 1.0 | Last Updated: June 2026*
*Targeted for Performance Testing Engineer / SRE roles — 10-20 LPA*
