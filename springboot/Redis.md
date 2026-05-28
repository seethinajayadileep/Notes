# 🚀 Spring Boot with Redis — Complete Beginner to Advanced Guide

> Written by a Senior Backend Engineer for developers who want to learn Redis deeply with Spring Boot — practically, not just theoretically.

---

## 📚 Table of Contents

1. [Introduction](#1-introduction)
2. [Redis Core Concepts](#2-redis-core-concepts)
3. [Redis Architecture](#3-redis-architecture)
4. [Spring Boot Redis Setup](#4-spring-boot-redis-setup)
5. [application.yml Configuration](#5-applicationyml-configuration)
6. [RedisTemplate in Spring Boot](#6-redistemplate-in-spring-boot)
7. [Basic Redis CRUD Operations](#7-basic-redis-crud-operations)
8. [Redis Cache in Spring Boot](#8-redis-cache-in-spring-boot)
9. [Redis List Example](#9-redis-list-example)
10. [Real Project Example: Detection Service](#10-real-project-example-detection-service)
11. [Redis Repository Approach](#11-redis-repository-approach)
12. [Running Redis Locally](#12-running-redis-locally)
13. [Running Redis with Docker](#13-running-redis-with-docker)
14. [Common Redis Commands](#14-common-redis-commands)
15. [Common Errors and Fixes](#15-common-errors-and-fixes)
16. [Best Practices](#16-best-practices)
17. [Interview Questions](#17-interview-questions)
18. [Final Mini Project](#18-final-mini-project)

---

## 1. Introduction

### What is Redis?

Redis stands for **Remote Dictionary Server**. It is an open-source, in-memory data store that works as a key-value database. Think of it as a super-fast notebook where your application can write something and read it back almost instantly.

> **Simple Analogy:** Imagine you are a librarian. A normal database is like going to a library, finding the shelf, finding the book, opening the page, and reading it. Redis is like keeping your most-used books right on your desk — instant access.

### Why Redis is Used in Backend / Microservices

- To **speed up repeated database queries** by caching results
- To **manage user sessions** without hitting the database every request
- To **rate-limit API calls** (e.g., allow 100 requests per minute per user)
- To **share data between microservices** without tight coupling
- To **store temporary data** like OTPs, tokens, recent activity
- To **implement real-time features** like live leaderboards, pub/sub messaging

### Redis as an In-Memory Database

Redis stores all data **in RAM (memory)**, not on disk. This is why it is extremely fast.

- RAM read speed: ~100 nanoseconds
- SSD read speed: ~16 microseconds (160x slower)
- HDD read speed: ~4 milliseconds (40,000x slower)

This makes Redis ideal for data you need to access again and again very quickly.

### Redis vs Normal Database

| Feature | Redis | Normal Database (MySQL/PostgreSQL) |
|---|---|---|
| Storage | RAM (memory) | Disk |
| Speed | Microseconds | Milliseconds |
| Data persistence | Optional | Default |
| Best for | Cache, sessions, queues | Permanent business data |
| Data size | Limited by RAM | Can be terabytes |
| Query support | Key-based | SQL queries |
| Relationships | Not supported | Full support |

**When to use what:**
- Use **MySQL/PostgreSQL** for your main business data (users, orders, products)
- Use **Redis** for caching that data so you don't query the DB every single time

### Redis vs Cache

People often confuse Redis with cache. Here is the truth:

- **Cache** is a concept — a temporary fast storage layer
- **Redis** is a tool — one of many ways to implement cache

Redis can be used as:
1. A pure in-memory cache
2. A persistent database (with AOF/RDB)
3. A message broker (Pub/Sub)
4. A queue (using Lists)

So Redis is much more than just a cache.

### Real-Time Examples of Redis Usage

| Use Case | Example |
|---|---|
| Caching | Store product details for 10 minutes so you don't hit DB every request |
| Session management | Store user login session with 30-minute TTL |
| OTP storage | Store a 6-digit OTP with 5-minute expiry |
| Rate limiting | Count API calls per user per minute |
| Leaderboard | Track top 10 players using Sorted Sets |
| Recent activity | Show last 5 viewed products using Redis List |
| Pub/Sub messaging | Notify all connected services when an event happens |
| Shopping cart | Store cart items temporarily before checkout |

---

## 2. Redis Core Concepts

### Key

A key is simply a **unique identifier** for your data in Redis. It is always a string.

```
"user:1001:profile"
"product:55:details"
"otp:9876543210"
"recent_checks:42"
```

**Best practice:** Use meaningful, structured key names like `{entity}:{id}:{field}`.

### Value

A value is the **data stored against a key**. It can be a string, JSON, number, list, set, hash, or sorted set.

```
Key:   "user:1001:name"
Value: "Rahul Sharma"

Key:   "product:55:details"
Value: {"id":55,"name":"iPhone","price":79999}
```

### TTL (Time to Live)

TTL is the **expiry time** of a key. After TTL expires, Redis automatically deletes the key.

```
SET otp:9876543210 "483920" EX 300
# This OTP will auto-delete after 300 seconds (5 minutes)
```

This is extremely useful for:
- OTPs (expire in 5 minutes)
- Sessions (expire in 30 minutes)
- Cache data (expire in 10 minutes)

### Cache

Cache is a temporary storage layer that holds copies of frequently accessed data so your application doesn't need to fetch it from the slower database every time.

```
Without cache:   Browser → API → Database (every request)
With cache:      Browser → API → Redis (if exists) → Database (only if not in Redis)
```

### In-Memory Storage

All Redis data lives in server RAM. When your Spring Boot app calls `redisTemplate.opsForValue().get("key")`, Redis reads directly from memory — no disk I/O.

### Redis Data Types

#### String

The simplest type. Stores text, numbers, or JSON as a single value.

```
SET name "Rahul"
GET name
→ "Rahul"

SET counter 10
INCR counter
→ 11
```

**Use for:** User names, OTPs, counters, simple JSON strings

#### List

An ordered list of strings. You can push to the front or back.

```
LPUSH tasks "task1"
LPUSH tasks "task2"
LRANGE tasks 0 -1
→ ["task2", "task1"]
```

**Use for:** Recent activity, job queues, chat messages, last N records

#### Set

An unordered collection of **unique** strings.

```
SADD tags "java"
SADD tags "spring"
SADD tags "java"   # duplicate, ignored
SMEMBERS tags
→ {"java", "spring"}
```

**Use for:** Unique visitors, user permissions, tags

#### Hash

A map of field-value pairs, like a mini object inside Redis.

```
HSET user:1001 name "Rahul" age "28" city "Delhi"
HGET user:1001 name
→ "Rahul"
HGETALL user:1001
→ {name: "Rahul", age: "28", city: "Delhi"}
```

**Use for:** User profiles, product details, shopping cart items

#### Sorted Set

Like a Set but each member has a **score** for ordering.

```
ZADD leaderboard 1500 "PlayerA"
ZADD leaderboard 2200 "PlayerB"
ZADD leaderboard 1800 "PlayerC"
ZRANGE leaderboard 0 -1 WITHSCORES
→ PlayerA:1500, PlayerC:1800, PlayerB:2200
```

**Use for:** Leaderboards, rankings, priority queues

#### Pub/Sub

A messaging pattern where publishers send messages to channels and subscribers receive them.

```
# Subscriber
SUBSCRIBE news-channel

# Publisher
PUBLISH news-channel "Server X is down"
```

**Use for:** Real-time notifications, event broadcasting between services

### Persistence

Redis offers two ways to persist data to disk:

- **RDB (Redis Database):** Takes a snapshot at intervals (like a backup)
- **AOF (Append Only File):** Logs every write operation

By default, Redis stores in memory only. Persistence must be configured explicitly.

### Eviction Policy

When Redis runs out of memory, it decides what to delete using an eviction policy.

| Policy | Behavior |
|---|---|
| `noeviction` | Returns error when memory is full |
| `allkeys-lru` | Removes least recently used keys |
| `volatile-lru` | Removes least recently used keys with TTL |
| `allkeys-random` | Removes random keys |
| `volatile-ttl` | Removes keys with shortest TTL first |

> **Tip:** For a cache setup, use `allkeys-lru` so Redis automatically removes old cached data when memory is full.

---

## 3. Redis Architecture

### How Spring Boot Connects to Redis

```
Spring Boot Application
        │
        │  (uses)
        ▼
  RedisTemplate / @Cacheable
        │
        │  (TCP connection via Lettuce or Jedis client)
        ▼
   Redis Server (localhost:6379)
        │
        │  (stores in)
        ▼
     RAM Memory
```

Spring Boot connects to Redis using a **client library**:
- **Lettuce** (default in Spring Boot 2+) — non-blocking, async
- **Jedis** — older, blocking, simpler

### How Data is Stored as Key-Value Pairs

```
Redis Memory (simplified view):
┌────────────────────────────────────────┐
│  KEY                   VALUE           │
│  ─────────────────── │─────────────── │
│  user:1001:name      │ "Rahul"        │
│  product:55:details  │ "{json...}"    │
│  otp:9876543210      │ "483920"       │
│  recent_checks:42    │ [list of json] │
└────────────────────────────────────────┘
```

### How TTL Works

```
Time 0s   → SET otp:123 "489201" EX 300
Time 100s → GET otp:123  →  "489201"  (still alive)
Time 300s → GET otp:123  →  (nil)     (auto deleted!)
```

Redis runs a background thread that continuously checks for expired keys and removes them.

### How Redis Improves Performance

```
Without Redis (100 users request same product):
┌──────────────────────────────────────────────┐
│  Request 1  →  DB Query  (50ms)              │
│  Request 2  →  DB Query  (50ms)              │
│  ...                                         │
│  Request 100 → DB Query  (50ms)              │
│  Total DB calls: 100, Total time: 5000ms     │
└──────────────────────────────────────────────┘

With Redis (100 users request same product):
┌──────────────────────────────────────────────┐
│  Request 1  →  DB Query (50ms) → Store Redis │
│  Request 2  →  Redis Hit (1ms) ✓             │
│  ...                                         │
│  Request 100 → Redis Hit (1ms) ✓             │
│  Total DB calls: 1, Total time: ~150ms       │
└──────────────────────────────────────────────┘
```

---

## 4. Spring Boot Redis Setup

### Project Folder Structure

```
src/
└── main/
    ├── java/
    │   └── com/
    │       └── example/
    │           └── redis/
    │               ├── RedisApplication.java
    │               ├── config/
    │               │   └── RedisConfig.java
    │               ├── controller/
    │               │   ├── RedisController.java
    │               │   └── ProductController.java
    │               ├── service/
    │               │   ├── RedisService.java
    │               │   └── ProductService.java
    │               ├── model/
    │               │   ├── Product.java
    │               │   └── CheckResultEvent.java
    │               └── dto/
    │                   └── ProductDTO.java
    └── resources/
        └── application.yml
```

### Maven Dependencies (`pom.xml`)

```xml
<?xml version="1.0" encoding="UTF-8"?>
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0
             https://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>

    <parent>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-parent</artifactId>
        <version>3.2.0</version>
        <relativePath/>
    </parent>

    <groupId>com.example</groupId>
    <artifactId>spring-boot-redis</artifactId>
    <version>0.0.1-SNAPSHOT</version>
    <name>spring-boot-redis</name>

    <properties>
        <java.version>17</java.version>
    </properties>

    <dependencies>

        <!-- Spring Boot Web: For REST APIs -->
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-web</artifactId>
        </dependency>

        <!-- Spring Data Redis: Core Redis support -->
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-data-redis</artifactId>
        </dependency>

        <!-- Lettuce (included by default): Redis client -->
        <!-- No need to add separately, spring-boot-starter-data-redis includes it -->

        <!-- Jackson: For JSON serialization of objects in Redis -->
        <dependency>
            <groupId>com.fasterxml.jackson.core</groupId>
            <artifactId>jackson-databind</artifactId>
        </dependency>

        <!-- Lombok: Reduces boilerplate code (getters, setters, constructors) -->
        <dependency>
            <groupId>org.projectlombok</groupId>
            <artifactId>lombok</artifactId>
            <optional>true</optional>
        </dependency>

        <!-- Spring Boot Test -->
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-test</artifactId>
            <scope>test</scope>
        </dependency>

    </dependencies>

    <build>
        <plugins>
            <plugin>
                <groupId>org.springframework.boot</groupId>
                <artifactId>spring-boot-maven-plugin</artifactId>
                <configuration>
                    <excludes>
                        <exclude>
                            <groupId>org.projectlombok</groupId>
                            <artifactId>lombok</artifactId>
                        </exclude>
                    </excludes>
                </configuration>
            </plugin>
        </plugins>
    </build>

</project>
```

**What each dependency does:**

| Dependency | Purpose |
|---|---|
| `spring-boot-starter-web` | Adds REST API support (Spring MVC, embedded Tomcat) |
| `spring-boot-starter-data-redis` | Core Redis integration (RedisTemplate, @Cacheable) |
| `jackson-databind` | Converts Java objects ↔ JSON for Redis storage |
| `lombok` | Auto-generates getters, setters, constructors |

---

## 5. application.yml Configuration

**File location:** `src/main/resources/application.yml`

```yaml
spring:
  application:
    name: spring-boot-redis-demo

  data:
    redis:
      # Redis server hostname or IP address
      # Use 'localhost' for local, or your Docker container name
      host: localhost

      # Redis default port is 6379 — do not change unless customized
      port: 6379

      # Password if Redis is secured (leave empty if no password)
      # password: yourRedisPassword

      # Connection timeout in milliseconds
      # How long to wait when trying to connect to Redis
      timeout: 2000ms

      # Redis database index (Redis has 16 databases: 0 to 15)
      # Use 0 for default, separate databases for different environments
      database: 0

      lettuce:
        pool:
          # Minimum idle connections in the pool
          min-idle: 2
          # Maximum idle connections in the pool
          max-idle: 10
          # Maximum total connections
          max-active: 20
          # Wait time to get a connection from pool
          max-wait: 1000ms

  cache:
    # Tells Spring to use Redis as caching provider
    type: redis
    redis:
      # Default TTL for all caches (10 minutes)
      time-to-live: 600000
      # Use key prefix to avoid collision between cache names
      use-key-prefix: true
      # Allows storing null values (set false to avoid caching nulls)
      cache-null-values: false

# Logging for debugging Redis operations
logging:
  level:
    org.springframework.data.redis: DEBUG
```

**Line-by-line explanation:**

| Property | Explanation |
|---|---|
| `host` | Where Redis server is running. `localhost` = same machine |
| `port` | Redis default port. Change only if you used a custom port |
| `password` | Leave commented if Redis has no auth. Uncomment and set for secured Redis |
| `timeout` | If Redis doesn't respond in 2 seconds, throw a connection error |
| `database` | Redis has 16 logical databases (0–15). Use different ones per environment |
| `lettuce.pool.*` | Controls connection pooling — keeps connections warm for performance |
| `cache.type` | Tells Spring Boot to use Redis as the cache backend |
| `time-to-live` | All cached data expires in 600,000ms = 10 minutes by default |
| `use-key-prefix` | Adds cache name as prefix to keys, avoids collision between caches |
| `cache-null-values` | `false` = don't cache null responses (recommended) |

---

## 6. RedisTemplate in Spring Boot

### What is RedisTemplate?

`RedisTemplate` is Spring's main class for interacting with Redis. It provides methods for all Redis data types and handles low-level connection management.

Think of it like `JdbcTemplate` for SQL — it wraps the connection complexity so you just call simple methods.

### What is StringRedisTemplate?

`StringRedisTemplate` is a pre-configured version of `RedisTemplate` where both key and value are `String`. Useful when you only store simple string values.

### Why Serializers Are Important

When Java stores objects into Redis, it must **convert them to bytes**. When reading back, it must convert bytes back to Java objects. This conversion is called **serialization**.

By default, Spring uses Java's native serializer, which produces unreadable binary. We configure **JSON serialization** so the data is readable in Redis CLI.

### RedisConfig.java

**File location:** `src/main/java/com/example/redis/config/RedisConfig.java`

```java
package com.example.redis.config;

import com.fasterxml.jackson.annotation.JsonTypeInfo;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.SerializationFeature;
import com.fasterxml.jackson.databind.jsontype.impl.LaissezFaireSubTypeValidator;
import com.fasterxml.jackson.datatype.jsr310.JavaTimeModule;
import org.springframework.cache.CacheManager;
import org.springframework.cache.annotation.EnableCaching;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.data.redis.cache.RedisCacheConfiguration;
import org.springframework.data.redis.cache.RedisCacheManager;
import org.springframework.data.redis.connection.RedisConnectionFactory;
import org.springframework.data.redis.core.RedisTemplate;
import org.springframework.data.redis.serializer.GenericJackson2JsonRedisSerializer;
import org.springframework.data.redis.serializer.RedisSerializationContext;
import org.springframework.data.redis.serializer.StringRedisSerializer;

import java.time.Duration;

@Configuration      // Marks this as a Spring configuration class
@EnableCaching      // Activates Spring's caching support (@Cacheable, @CachePut, @CacheEvict)
public class RedisConfig {

    /**
     * Creates a RedisTemplate bean for storing any Object type as JSON.
     * Keys are stored as String, values are stored as JSON.
     *
     * @param connectionFactory Auto-injected by Spring using application.yml properties
     */
    @Bean
    public RedisTemplate<String, Object> redisTemplate(RedisConnectionFactory connectionFactory) {

        RedisTemplate<String, Object> template = new RedisTemplate<>();

        // Set the connection factory (Lettuce connection using application.yml config)
        template.setConnectionFactory(connectionFactory);

        // KEY serializer: Store keys as plain readable strings
        // Example: "product:55:details" stored exactly as that string
        template.setKeySerializer(new StringRedisSerializer());

        // VALUE serializer: Store values as JSON
        // Example: Product object stored as {"id":55,"name":"iPhone","price":79999}
        template.setValueSerializer(new GenericJackson2JsonRedisSerializer(objectMapper()));

        // HASH KEY serializer: For Redis Hash data type
        template.setHashKeySerializer(new StringRedisSerializer());

        // HASH VALUE serializer: For Redis Hash values
        template.setHashValueSerializer(new GenericJackson2JsonRedisSerializer(objectMapper()));

        // Apply all configurations
        template.afterPropertiesSet();

        return template;
    }

    /**
     * Configure CacheManager to use Redis with JSON serialization.
     * This is what powers @Cacheable, @CachePut, @CacheEvict annotations.
     */
    @Bean
    public CacheManager cacheManager(RedisConnectionFactory connectionFactory) {

        RedisCacheConfiguration cacheConfig = RedisCacheConfiguration.defaultCacheConfig()
                // Default TTL for all caches: 10 minutes
                .entryTtl(Duration.ofMinutes(10))
                // Serialize keys as strings
                .serializeKeysWith(
                        RedisSerializationContext.SerializationPair
                                .fromSerializer(new StringRedisSerializer())
                )
                // Serialize values as JSON
                .serializeValuesWith(
                        RedisSerializationContext.SerializationPair
                                .fromSerializer(new GenericJackson2JsonRedisSerializer(objectMapper()))
                )
                // Do not cache null values
                .disableCachingNullValues();

        return RedisCacheManager.builder(connectionFactory)
                .cacheDefaults(cacheConfig)
                .build();
    }

    /**
     * ObjectMapper configured for Redis serialization.
     * Includes type information so deserialization works correctly.
     */
    @Bean
    public ObjectMapper objectMapper() {
        ObjectMapper mapper = new ObjectMapper();

        // Support Java 8 date/time types
        mapper.registerModule(new JavaTimeModule());
        mapper.disable(SerializationFeature.WRITE_DATES_AS_TIMESTAMPS);

        // Store type info in JSON so Spring knows which class to deserialize into
        mapper.activateDefaultTyping(
                LaissezFaireSubTypeValidator.instance,
                ObjectMapper.DefaultTyping.NON_FINAL,
                JsonTypeInfo.As.PROPERTY
        );

        return mapper;
    }
}
```

**Summary:**

| Component | Purpose |
|---|---|
| `RedisTemplate<String, Object>` | Generic template for storing any Java object |
| `StringRedisSerializer` (key) | Keys are stored as plain strings — human readable |
| `GenericJackson2JsonRedisSerializer` (value) | Values stored as JSON — human readable in Redis CLI |
| `CacheManager` | Wires Spring's cache annotations to Redis |
| `ObjectMapper` | Configured to handle Java 8 dates and type info |

---

## 7. Basic Redis CRUD Operations

### RedisService.java

**File location:** `src/main/java/com/example/redis/service/RedisService.java`

```java
package com.example.redis.service;

import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.data.redis.core.RedisTemplate;
import org.springframework.stereotype.Service;

import java.util.concurrent.TimeUnit;

@Service
@RequiredArgsConstructor    // Lombok: generates constructor for final fields
@Slf4j                      // Lombok: generates logger
public class RedisService {

    // RedisTemplate injected from RedisConfig
    private final RedisTemplate<String, Object> redisTemplate;

    /**
     * Save a key-value pair in Redis without TTL (persists until manually deleted)
     */
    public void save(String key, Object value) {
        redisTemplate.opsForValue().set(key, value);
        log.info("Saved to Redis: key={}, value={}", key, value);
    }

    /**
     * Save a key-value pair with TTL (auto-expires after specified seconds)
     *
     * Example: save("otp:9876543210", "483920", 300) → expires in 5 minutes
     */
    public void saveWithTTL(String key, Object value, long ttlSeconds) {
        redisTemplate.opsForValue().set(key, value, ttlSeconds, TimeUnit.SECONDS);
        log.info("Saved to Redis with TTL={}s: key={}, value={}", ttlSeconds, key, value);
    }

    /**
     * Retrieve a value by key
     * Returns null if key doesn't exist or has expired
     */
    public Object get(String key) {
        Object value = redisTemplate.opsForValue().get(key);
        log.info("Retrieved from Redis: key={}, value={}", key, value);
        return value;
    }

    /**
     * Update a value (same as save — Redis will overwrite existing value)
     */
    public void update(String key, Object newValue) {
        redisTemplate.opsForValue().set(key, newValue);
        log.info("Updated Redis key={} with new value={}", key, newValue);
    }

    /**
     * Delete a key from Redis
     */
    public void delete(String key) {
        redisTemplate.delete(key);
        log.info("Deleted from Redis: key={}", key);
    }

    /**
     * Check if a key exists in Redis
     */
    public boolean exists(String key) {
        Boolean exists = redisTemplate.hasKey(key);
        return Boolean.TRUE.equals(exists);
    }

    /**
     * Get remaining TTL of a key in seconds
     * Returns -1 if key has no TTL (persistent)
     * Returns -2 if key doesn't exist
     */
    public long getTTL(String key) {
        Long ttl = redisTemplate.getExpire(key, TimeUnit.SECONDS);
        return ttl != null ? ttl : -2;
    }

    /**
     * Set TTL on an already existing key
     */
    public void setTTL(String key, long ttlSeconds) {
        redisTemplate.expire(key, ttlSeconds, TimeUnit.SECONDS);
        log.info("Set TTL={}s on key={}", ttlSeconds, key);
    }
}
```

### RedisController.java

**File location:** `src/main/java/com/example/redis/controller/RedisController.java`

```java
package com.example.redis.controller;

import lombok.RequiredArgsConstructor;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import com.example.redis.service.RedisService;

import java.util.Map;

@RestController
@RequestMapping("/redis")
@RequiredArgsConstructor
public class RedisController {

    private final RedisService redisService;

    /**
     * POST /redis/save
     * Body: { "key": "user:1001:name", "value": "Rahul", "ttl": 300 }
     *
     * Saves key-value to Redis. If ttl > 0, the key auto-expires.
     */
    @PostMapping("/save")
    public ResponseEntity<String> save(@RequestBody Map<String, Object> request) {
        String key = (String) request.get("key");
        Object value = request.get("value");
        Object ttlObj = request.get("ttl");

        if (ttlObj != null) {
            long ttl = Long.parseLong(ttlObj.toString());
            redisService.saveWithTTL(key, value, ttl);
            return ResponseEntity.ok("Saved with TTL=" + ttl + "s: " + key);
        } else {
            redisService.save(key, value);
            return ResponseEntity.ok("Saved: " + key);
        }
    }

    /**
     * GET /redis/{key}
     * Returns the value stored at the given key.
     * Returns 404 if key not found or expired.
     */
    @GetMapping("/{key}")
    public ResponseEntity<Object> get(@PathVariable String key) {
        Object value = redisService.get(key);
        if (value == null) {
            return ResponseEntity.notFound().build();
        }
        return ResponseEntity.ok(value);
    }

    /**
     * DELETE /redis/{key}
     * Deletes the given key from Redis.
     */
    @DeleteMapping("/{key}")
    public ResponseEntity<String> delete(@PathVariable String key) {
        redisService.delete(key);
        return ResponseEntity.ok("Deleted: " + key);
    }

    /**
     * GET /redis/ttl/{key}
     * Returns remaining TTL in seconds.
     */
    @GetMapping("/ttl/{key}")
    public ResponseEntity<String> getTTL(@PathVariable String key) {
        long ttl = redisService.getTTL(key);
        return ResponseEntity.ok("TTL for '" + key + "': " + ttl + " seconds");
    }

    /**
     * GET /redis/exists/{key}
     * Returns true/false whether the key exists.
     */
    @GetMapping("/exists/{key}")
    public ResponseEntity<Boolean> exists(@PathVariable String key) {
        return ResponseEntity.ok(redisService.exists(key));
    }
}
```

**Test with curl:**

```bash
# Save without TTL
curl -X POST http://localhost:8080/redis/save \
  -H "Content-Type: application/json" \
  -d '{"key":"user:1001:name","value":"Rahul"}'

# Save with TTL (expires in 60 seconds)
curl -X POST http://localhost:8080/redis/save \
  -H "Content-Type: application/json" \
  -d '{"key":"otp:9876543210","value":"483920","ttl":300}'

# Get value
curl http://localhost:8080/redis/user:1001:name

# Delete key
curl -X DELETE http://localhost:8080/redis/user:1001:name

# Check TTL
curl http://localhost:8080/redis/ttl/otp:9876543210

# Check if exists
curl http://localhost:8080/redis/exists/user:1001:name
```

---

## 8. Redis Cache in Spring Boot

### What is Caching?

Caching means storing a copy of frequently accessed data in a fast storage layer (Redis) so that repeated requests are served from Redis instead of querying the database every time.

```
First request:
Browser → API → Check Redis → MISS → Query DB → Store in Redis → Return Response

Subsequent requests (within TTL):
Browser → API → Check Redis → HIT → Return Response  (no DB call!)
```

### Why Caching is Useful

- Reduces database load significantly
- Makes API responses much faster
- Improves scalability — your DB can handle more users

### Spring Cache Annotations

#### `@EnableCaching`
Enable this on your main class or config class. Without this, all cache annotations are ignored.

```java
@EnableCaching  // Already added in RedisConfig.java
```

#### `@Cacheable`
Used on **read methods**. On first call it queries the database and stores result in Redis. On subsequent calls, it directly returns from Redis without touching the method.

```java
@Cacheable(value = "products", key = "#productId")
public Product getProduct(Long productId) {
    // This code runs ONLY on cache MISS
    // On cache HIT, Spring skips this method entirely and returns cached value
    return productRepository.findById(productId).orElseThrow();
}
```

**Redis key generated:** `products::55` (cache name + "::" + key)

#### `@CachePut`
Always executes the method AND updates the cache. Use this for **update operations**.

```java
@CachePut(value = "products", key = "#product.id")
public Product updateProduct(Product product) {
    // Always runs, always updates cache
    return productRepository.save(product);
}
```

#### `@CacheEvict`
Removes data from cache. Use this for **delete operations**.

```java
@CacheEvict(value = "products", key = "#productId")
public void deleteProduct(Long productId) {
    // Removes "products::55" from Redis after deletion
    productRepository.deleteById(productId);
}

// To clear entire cache:
@CacheEvict(value = "products", allEntries = true)
public void clearAllProductCache() { ... }
```

### Product.java (Model)

**File location:** `src/main/java/com/example/redis/model/Product.java`

```java
package com.example.redis.model;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.io.Serializable;

// Serializable is required when storing in Redis
@Data
@Builder
@NoArgsConstructor
@AllArgsConstructor
public class Product implements Serializable {

    private Long id;
    private String name;
    private String description;
    private Double price;
    private Integer stockQuantity;
    private String category;
}
```

### ProductService.java

**File location:** `src/main/java/com/example/redis/service/ProductService.java`

```java
package com.example.redis.service;

import com.example.redis.model.Product;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.cache.annotation.CacheEvict;
import org.springframework.cache.annotation.CachePut;
import org.springframework.cache.annotation.Cacheable;
import org.springframework.stereotype.Service;

import java.util.HashMap;
import java.util.Map;

@Service
@RequiredArgsConstructor
@Slf4j
public class ProductService {

    // Simulated in-memory "database" for this example
    // In real project: inject ProductRepository (JPA)
    private final Map<Long, Product> productDB = new HashMap<>(Map.of(
            1L, Product.builder().id(1L).name("iPhone 15").price(79999.0).category("Mobile").build(),
            2L, Product.builder().id(2L).name("MacBook Pro").price(149999.0).category("Laptop").build(),
            3L, Product.builder().id(3L).name("AirPods Pro").price(24999.0).category("Audio").build()
    ));

    /**
     * @Cacheable: Check Redis first.
     * If cache MISS → execute method → store result in Redis → return
     * If cache HIT → skip method entirely → return from Redis
     *
     * Redis key: "products::1" (where 1 is productId)
     */
    @Cacheable(value = "products", key = "#productId")
    public Product getProduct(Long productId) {
        log.info(">>> CACHE MISS: Fetching product {} from DB", productId);
        // Simulate slow DB call
        simulateSlowDB();
        return productDB.get(productId);
    }

    /**
     * @CachePut: Always executes AND updates cache.
     * Use for create/update operations.
     */
    @CachePut(value = "products", key = "#product.id")
    public Product saveProduct(Product product) {
        log.info("Saving product to DB and updating cache: {}", product.getId());
        productDB.put(product.getId(), product);
        return product;
    }

    /**
     * @CacheEvict: Remove from cache after deletion.
     * Next call to getProduct() will go to DB again.
     */
    @CacheEvict(value = "products", key = "#productId")
    public void deleteProduct(Long productId) {
        log.info("Deleting product {} from DB and evicting from cache", productId);
        productDB.remove(productId);
    }

    /**
     * Evict ALL entries from "products" cache.
     */
    @CacheEvict(value = "products", allEntries = true)
    public void clearAllCache() {
        log.info("Cleared all product cache");
    }

    private void simulateSlowDB() {
        try {
            Thread.sleep(500); // Simulate 500ms DB call
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}
```

### ProductController.java

**File location:** `src/main/java/com/example/redis/controller/ProductController.java`

```java
package com.example.redis.controller;

import com.example.redis.model.Product;
import com.example.redis.service.ProductService;
import lombok.RequiredArgsConstructor;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/products")
@RequiredArgsConstructor
public class ProductController {

    private final ProductService productService;

    /**
     * GET /products/{id}
     * First call: ~500ms (DB hit)
     * Subsequent calls: <5ms (Redis hit)
     */
    @GetMapping("/{id}")
    public ResponseEntity<Product> getProduct(@PathVariable Long id) {
        Product product = productService.getProduct(id);
        if (product == null) return ResponseEntity.notFound().build();
        return ResponseEntity.ok(product);
    }

    /**
     * POST /products
     * Saves and caches the product
     */
    @PostMapping
    public ResponseEntity<Product> saveProduct(@RequestBody Product product) {
        return ResponseEntity.ok(productService.saveProduct(product));
    }

    /**
     * DELETE /products/{id}
     * Deletes and evicts from cache
     */
    @DeleteMapping("/{id}")
    public ResponseEntity<Void> deleteProduct(@PathVariable Long id) {
        productService.deleteProduct(id);
        return ResponseEntity.noContent().build();
    }

    /**
     * DELETE /products/cache/clear
     * Clears entire product cache
     */
    @DeleteMapping("/cache/clear")
    public ResponseEntity<String> clearCache() {
        productService.clearAllCache();
        return ResponseEntity.ok("Product cache cleared");
    }
}
```

**Test caching behavior:**

```bash
# First call — slow (500ms, DB hit)
curl http://localhost:8080/products/1

# Second call — fast (<5ms, Redis hit)
curl http://localhost:8080/products/1

# In console logs, you will see:
# First call:  ">>> CACHE MISS: Fetching product 1 from DB"
# Second call: (nothing logged — method skipped entirely!)
```

---

## 9. Redis List Example

### The Problem We Are Solving

A monitoring service checks if a web service is UP every minute. We want to keep the **last 3 check results** for each service so we can detect patterns (e.g., 3 consecutive failures = CRITICAL).

### Key Design

```
Key format:  recent_checks:{serviceId}
Value type:  Redis List (JSON strings)
Max size:    3 entries (trim older ones)
TTL:         5 minutes (auto-cleanup if service stops sending)
```

### CheckResultEvent.java

**File location:** `src/main/java/com/example/redis/model/CheckResultEvent.java`

```java
package com.example.redis.model;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.io.Serializable;

@Data
@Builder
@NoArgsConstructor
@AllArgsConstructor
public class CheckResultEvent implements Serializable {

    private Long serviceId;
    private String serviceName;
    private String url;
    private boolean success;
    private int statusCode;
    private long responseTimeMs;
    private String checkedAt;
}
```

### RecentChecksService.java

**File location:** `src/main/java/com/example/redis/service/RecentChecksService.java`

```java
package com.example.redis.service;

import com.example.redis.model.CheckResultEvent;
import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.data.redis.core.RedisTemplate;
import org.springframework.stereotype.Service;

import java.util.Collections;
import java.util.List;
import java.util.concurrent.TimeUnit;
import java.util.stream.Collectors;

@Service
@RequiredArgsConstructor
@Slf4j
public class RecentChecksService {

    private final RedisTemplate<String, Object> redisTemplate;
    private final ObjectMapper objectMapper;

    // Constants
    private static final String KEY_PREFIX = "recent_checks:";
    private static final int MAX_RESULTS = 3;
    private static final long TTL_MINUTES = 5;

    /**
     * Pushes a new check result to the left of the Redis list.
     * Trims the list to keep only the last MAX_RESULTS entries.
     * Resets TTL every time a new result is added.
     *
     * Flow:
     *   LPUSH recent_checks:42 "{...json...}"
     *   LTRIM recent_checks:42 0 2  → keeps only 3 entries
     *   EXPIRE recent_checks:42 300 → reset 5 min TTL
     */
    public void pushCheckResult(CheckResultEvent event) {
        String key = KEY_PREFIX + event.getServiceId();
        try {
            String json = objectMapper.writeValueAsString(event);

            // Push new result to front of list (most recent first)
            redisTemplate.opsForList().leftPush(key, json);

            // Trim to keep only last 3 results
            // Index 0 = most recent, Index 2 = oldest
            redisTemplate.opsForList().trim(key, 0, MAX_RESULTS - 1);

            // Reset TTL — if no new checks in 5 minutes, auto-cleanup
            redisTemplate.expire(key, TTL_MINUTES, TimeUnit.MINUTES);

            log.info("Pushed check result for serviceId={}: success={}", event.getServiceId(), event.isSuccess());

        } catch (JsonProcessingException e) {
            log.error("Failed to serialize CheckResultEvent for serviceId={}", event.getServiceId(), e);
        }
    }

    /**
     * Returns the last MAX_RESULTS check results for the given serviceId.
     * Most recent result is at index 0.
     */
    public List<CheckResultEvent> getRecentChecks(Long serviceId) {
        String key = KEY_PREFIX + serviceId;

        // LRANGE key 0 2 → returns up to 3 entries
        List<Object> rawList = redisTemplate.opsForList().range(key, 0, MAX_RESULTS - 1);

        if (rawList == null || rawList.isEmpty()) {
            log.info("No recent checks found for serviceId={}", serviceId);
            return Collections.emptyList();
        }

        return rawList.stream()
                .map(item -> {
                    try {
                        return objectMapper.readValue(item.toString(), CheckResultEvent.class);
                    } catch (JsonProcessingException e) {
                        log.error("Failed to deserialize check result", e);
                        return null;
                    }
                })
                .filter(item -> item != null)
                .collect(Collectors.toList());
    }

    /**
     * Returns the count of recent check results stored for this service.
     */
    public long getCheckCount(Long serviceId) {
        String key = KEY_PREFIX + serviceId;
        Long size = redisTemplate.opsForList().size(key);
        return size != null ? size : 0;
    }

    /**
     * Deletes all recent checks for a service.
     */
    public void clearChecks(Long serviceId) {
        String key = KEY_PREFIX + serviceId;
        redisTemplate.delete(key);
        log.info("Cleared recent checks for serviceId={}", serviceId);
    }
}
```

---

## 10. Real Project Example: Detection Service

### Architecture Overview

```
Kafka Topic: check.results
        │
        │ (consumes CheckResultEvent)
        ▼
┌─────────────────────┐
│  Detection Service  │
│  (Spring Boot)      │
└─────────┬───────────┘
          │
          │ (stores last 3 results per service)
          ▼
┌─────────────────────┐
│       Redis         │
│  recent_checks:{id} │
│  [result3,          │
│   result2,          │
│   result1]          │
└─────────┬───────────┘
          │
          │ (reads 3 results + applies rules)
          ▼
┌─────────────────────┐
│    Rule Engine      │
└─────────┬───────────┘
          │
          │ (creates/resolves incidents)
          ▼
┌─────────────────────┐
│  Incident Service   │
└─────────────────────┘
```

### Detection Rules

| Condition | Severity | Action |
|---|---|---|
| All 3 checks failed | CRITICAL | Create downtime incident |
| Avg responseTimeMs > 5000 | CRITICAL | Create slow response incident |
| Avg responseTimeMs > 2000 | HIGH | Create slow response incident |
| All 3 checks succeeded | — | Auto-resolve open incidents |

### DetectionService.java

**File location:** `src/main/java/com/example/redis/service/DetectionService.java`

```java
package com.example.redis.service;

import com.example.redis.model.CheckResultEvent;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
@RequiredArgsConstructor
@Slf4j
public class DetectionService {

    private final RecentChecksService recentChecksService;

    /**
     * Called when a new CheckResultEvent arrives (e.g., from Kafka consumer).
     * 1. Stores the result in Redis
     * 2. Reads last 3 results
     * 3. Applies detection rules
     */
    public void processCheckResult(CheckResultEvent event) {
        log.info("Processing check result for service: {} | success={} | responseTime={}ms",
                event.getServiceName(), event.isSuccess(), event.getResponseTimeMs());

        // Step 1: Store in Redis (keeps last 3, resets TTL)
        recentChecksService.pushCheckResult(event);

        // Step 2: Read last 3 results
        List<CheckResultEvent> recentChecks = recentChecksService.getRecentChecks(event.getServiceId());

        // Step 3: Only apply rules when we have exactly 3 results
        if (recentChecks.size() < 3) {
            log.info("Not enough data yet for serviceId={} ({} results). Waiting for 3.",
                    event.getServiceId(), recentChecks.size());
            return;
        }

        applyRules(event.getServiceId(), event.getServiceName(), recentChecks);
    }

    /**
     * Applies detection rules on the last 3 check results.
     */
    private void applyRules(Long serviceId, String serviceName, List<CheckResultEvent> checks) {

        boolean allFailed = checks.stream().noneMatch(CheckResultEvent::isSuccess);
        boolean allSucceeded = checks.stream().allMatch(CheckResultEvent::isSuccess);

        double avgResponseTime = checks.stream()
                .mapToLong(CheckResultEvent::getResponseTimeMs)
                .average()
                .orElse(0.0);

        log.info("Rule evaluation for {} | allFailed={} | allSucceeded={} | avgResponseTime={}ms",
                serviceName, allFailed, allSucceeded, avgResponseTime);

        if (allFailed) {
            log.error("CRITICAL: All 3 checks failed for {} (serviceId={}). Triggering CRITICAL DOWNTIME incident.",
                    serviceName, serviceId);
            // In real project: incidentService.createIncident(serviceId, "CRITICAL", "DOWNTIME");
            notifyIncident(serviceId, serviceName, "CRITICAL", "DOWNTIME",
                    "All 3 consecutive health checks failed.");

        } else if (avgResponseTime > 5000) {
            log.error("CRITICAL: Avg response time {}ms exceeds 5000ms for {} (serviceId={}).",
                    avgResponseTime, serviceName, serviceId);
            notifyIncident(serviceId, serviceName, "CRITICAL", "SLOW_RESPONSE",
                    "Average response time is " + avgResponseTime + "ms (>5000ms threshold).");

        } else if (avgResponseTime > 2000) {
            log.warn("HIGH: Avg response time {}ms exceeds 2000ms for {} (serviceId={}).",
                    avgResponseTime, serviceName, serviceId);
            notifyIncident(serviceId, serviceName, "HIGH", "SLOW_RESPONSE",
                    "Average response time is " + avgResponseTime + "ms (>2000ms threshold).");

        } else if (allSucceeded) {
            log.info("All 3 checks PASSED for {} (serviceId={}). Auto-resolving any open incidents.",
                    serviceName, serviceId);
            // In real project: incidentService.resolveIncident(serviceId);
            resolveIncident(serviceId, serviceName);
        } else {
            log.info("No rule triggered for {} — partial failures or normal response time.", serviceName);
        }
    }

    private void notifyIncident(Long serviceId, String serviceName, String severity, String type, String reason) {
        // Replace this with actual HTTP call to Incident Service or Kafka message
        log.info(">>> INCIDENT ALERT | serviceId={} | service={} | severity={} | type={} | reason={}",
                serviceId, serviceName, severity, type, reason);
    }

    private void resolveIncident(Long serviceId, String serviceName) {
        log.info(">>> AUTO-RESOLVE | serviceId={} | service={}", serviceId, serviceName);
    }
}
```

### DetectionController.java (for testing without Kafka)

**File location:** `src/main/java/com/example/redis/controller/DetectionController.java`

```java
package com.example.redis.controller;

import com.example.redis.model.CheckResultEvent;
import com.example.redis.service.DetectionService;
import com.example.redis.service.RecentChecksService;
import lombok.RequiredArgsConstructor;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/detection")
@RequiredArgsConstructor
public class DetectionController {

    private final DetectionService detectionService;
    private final RecentChecksService recentChecksService;

    /**
     * POST /detection/process
     * Simulates receiving a CheckResultEvent (as if from Kafka)
     */
    @PostMapping("/process")
    public ResponseEntity<String> processEvent(@RequestBody CheckResultEvent event) {
        detectionService.processCheckResult(event);
        return ResponseEntity.ok("Processed check result for serviceId=" + event.getServiceId());
    }

    /**
     * GET /detection/recent/{serviceId}
     * Returns last 3 check results from Redis
     */
    @GetMapping("/recent/{serviceId}")
    public ResponseEntity<List<CheckResultEvent>> getRecentChecks(@PathVariable Long serviceId) {
        List<CheckResultEvent> checks = recentChecksService.getRecentChecks(serviceId);
        return ResponseEntity.ok(checks);
    }
}
```

**Test the detection service:**

```bash
# Simulate 3 consecutive failures
curl -X POST http://localhost:8080/detection/process \
  -H "Content-Type: application/json" \
  -d '{"serviceId":42,"serviceName":"PaymentService","url":"https://pay.example.com","success":false,"statusCode":500,"responseTimeMs":100,"checkedAt":"2024-01-01T10:00:00"}'

curl -X POST http://localhost:8080/detection/process \
  -H "Content-Type: application/json" \
  -d '{"serviceId":42,"serviceName":"PaymentService","url":"https://pay.example.com","success":false,"statusCode":500,"responseTimeMs":120,"checkedAt":"2024-01-01T10:01:00"}'

curl -X POST http://localhost:8080/detection/process \
  -H "Content-Type: application/json" \
  -d '{"serviceId":42,"serviceName":"PaymentService","url":"https://pay.example.com","success":false,"statusCode":500,"responseTimeMs":110,"checkedAt":"2024-01-01T10:02:00"}'

# After 3rd call, you should see in logs:
# CRITICAL: All 3 checks failed for PaymentService

# Check recent results in Redis
curl http://localhost:8080/detection/recent/42
```

---

## 11. Redis Repository Approach

### What is @RedisHash?

`@RedisHash` is Spring Data Redis's way to map a Java class to a Redis Hash. It works similarly to `@Entity` for JPA — each object is stored as a Hash in Redis with a structured key.

### RedisTemplate vs Redis Repository

| Feature | RedisTemplate | Redis Repository (@RedisHash) |
|---|---|---|
| Control | Full control over keys and types | Abstracted (Spring manages keys) |
| Flexibility | Any Redis data type (List, Set, Hash, etc.) | Only Redis Hash |
| Complexity | More code | Less code (like JPA) |
| TTL control | Manual | Via `@TimeToLive` annotation |
| Best for | Custom operations, multiple data types | Simple CRUD on entity objects |

### When to Use Each

- Use **RedisTemplate** when: you need full control, custom key formats, Lists, Sets, Sorted Sets, or complex operations
- Use **Redis Repository** when: you want simple CRUD on a single entity, and it feels natural like JPA

### UserSession.java (RedisHash Entity)

**File location:** `src/main/java/com/example/redis/model/UserSession.java`

```java
package com.example.redis.model;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;
import org.springframework.data.annotation.Id;
import org.springframework.data.redis.core.RedisHash;
import org.springframework.data.redis.core.TimeToLive;

import java.io.Serializable;

/**
 * @RedisHash("user_sessions") — stores data as Redis Hash under key "user_sessions:{id}"
 * Example key: "user_sessions:session-abc-123"
 */
@RedisHash("user_sessions")
@Data
@Builder
@NoArgsConstructor
@AllArgsConstructor
public class UserSession implements Serializable {

    @Id
    private String sessionId;       // Redis key suffix: "user_sessions:session-abc-123"

    private Long userId;
    private String email;
    private String role;
    private String loginTime;
    private String ipAddress;

    @TimeToLive
    private Long ttlSeconds;        // Auto-expire this session after N seconds
}
```

### UserSessionRepository.java

**File location:** `src/main/java/com/example/redis/repository/UserSessionRepository.java`

```java
package com.example.redis.repository;

import com.example.redis.model.UserSession;
import org.springframework.data.repository.CrudRepository;
import org.springframework.stereotype.Repository;

/**
 * Spring Data Redis repository for UserSession.
 * Provides: save(), findById(), existsById(), delete(), findAll()
 * No SQL needed — works just like JpaRepository!
 */
@Repository
public interface UserSessionRepository extends CrudRepository<UserSession, String> {
    // Spring generates implementation automatically
}
```

### UserSessionService.java

**File location:** `src/main/java/com/example/redis/service/UserSessionService.java`

```java
package com.example.redis.service;

import com.example.redis.model.UserSession;
import com.example.redis.repository.UserSessionRepository;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;

import java.util.Optional;
import java.util.UUID;

@Service
@RequiredArgsConstructor
@Slf4j
public class UserSessionService {

    private final UserSessionRepository sessionRepository;

    /**
     * Create a new session for a user (e.g., after login)
     * TTL: 1800 seconds = 30 minutes
     */
    public UserSession createSession(Long userId, String email, String role) {
        UserSession session = UserSession.builder()
                .sessionId(UUID.randomUUID().toString())
                .userId(userId)
                .email(email)
                .role(role)
                .loginTime(java.time.LocalDateTime.now().toString())
                .ttlSeconds(1800L)  // Session expires in 30 minutes
                .build();

        UserSession saved = sessionRepository.save(session);
        log.info("Created session {} for userId={}", saved.getSessionId(), userId);
        return saved;
    }

    /**
     * Get session by sessionId
     */
    public Optional<UserSession> getSession(String sessionId) {
        return sessionRepository.findById(sessionId);
    }

    /**
     * Invalidate (delete) a session — used on logout
     */
    public void invalidateSession(String sessionId) {
        sessionRepository.deleteById(sessionId);
        log.info("Invalidated session: {}", sessionId);
    }

    /**
     * Check if a session is valid
     */
    public boolean isSessionValid(String sessionId) {
        return sessionRepository.existsById(sessionId);
    }
}
```

---

## 12. Running Redis Locally

### Install on macOS (Homebrew)

```bash
# Install Homebrew if not already installed
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install Redis
brew install redis

# Start Redis as a background service
brew services start redis

# Check if Redis is running
brew services list
# Should show redis with status: started

# OR start Redis manually (runs in foreground)
redis-server
```

### Install on Ubuntu/Debian Linux

```bash
# Update package list
sudo apt update

# Install Redis
sudo apt install redis-server -y

# Start Redis service
sudo systemctl start redis-server

# Enable auto-start on boot
sudo systemctl enable redis-server

# Check status
sudo systemctl status redis-server
```

### Connect Using redis-cli

```bash
# Connect to local Redis
redis-cli

# Now you're in Redis CLI prompt: 127.0.0.1:6379>

# Test connection
PING
# → PONG (Redis is alive!)

# Set a key manually
SET mykey "Hello Redis"

# Get the value
GET mykey
# → "Hello Redis"

# Set key with TTL (expires in 60 seconds)
SET otp:test "123456" EX 60

# Check TTL remaining
TTL otp:test
# → 58 (seconds remaining)

# Delete a key
DEL mykey

# Check all keys
KEYS *

# Exit redis-cli
EXIT
```

---

## 13. Running Redis with Docker

### Basic Commands

```bash
# Pull latest Redis image from Docker Hub
docker pull redis:latest

# Run Redis container (no password)
docker run --name my-redis -p 6379:6379 -d redis:latest

# Explanation:
# --name my-redis     → Container name
# -p 6379:6379        → Map host port 6379 to container port 6379
# -d                  → Run in detached (background) mode
# redis:latest        → Use latest Redis image

# Run Redis with a password
docker run --name my-redis-secure \
  -p 6379:6379 \
  -d redis:latest \
  redis-server --requirepass "myStrongPassword123"

# Run Redis with data persistence (mount a volume)
docker run --name my-redis-persistent \
  -p 6379:6379 \
  -v redis-data:/data \
  -d redis:latest

# Connect using redis-cli inside the Docker container
docker exec -it my-redis redis-cli

# Connect with password
docker exec -it my-redis-secure redis-cli -a myStrongPassword123

# Check if container is running
docker ps

# View Redis logs
docker logs my-redis

# Stop the container
docker stop my-redis

# Start the container again
docker start my-redis

# Remove the container
docker rm my-redis

# Remove container and its data volume
docker rm -v my-redis
```

### Docker Compose (Recommended for Projects)

**File location:** `docker-compose.yml` (root of project)

```yaml
version: '3.8'

services:
  redis:
    image: redis:7-alpine
    container_name: spring-redis
    ports:
      - "6379:6379"
    command: redis-server --requirepass mypassword --save 60 1 --loglevel warning
    volumes:
      - redis_data:/data
    restart: unless-stopped
    healthcheck:
      test: ["CMD", "redis-cli", "-a", "mypassword", "ping"]
      interval: 10s
      timeout: 5s
      retries: 3

volumes:
  redis_data:
```

```bash
# Start with Docker Compose
docker-compose up -d

# Stop
docker-compose down

# Connect
docker exec -it spring-redis redis-cli -a mypassword
```

---

## 14. Common Redis Commands

### Full Command Reference

| Command | Syntax | Example | Description |
|---|---|---|---|
| `SET` | `SET key value [EX seconds]` | `SET name "Rahul" EX 300` | Store a string value with optional TTL |
| `GET` | `GET key` | `GET name` | Retrieve value by key |
| `DEL` | `DEL key [key ...]` | `DEL name session:1` | Delete one or more keys |
| `EXISTS` | `EXISTS key` | `EXISTS name` | Returns 1 if exists, 0 if not |
| `EXPIRE` | `EXPIRE key seconds` | `EXPIRE name 600` | Set TTL on existing key |
| `TTL` | `TTL key` | `TTL name` | Get remaining TTL in seconds (-1=no TTL, -2=not found) |
| `KEYS` | `KEYS pattern` | `KEYS user:*` | List all keys matching pattern |
| `LPUSH` | `LPUSH key value` | `LPUSH tasks "task1"` | Push to left (front) of list |
| `RPUSH` | `RPUSH key value` | `RPUSH tasks "task1"` | Push to right (back) of list |
| `LRANGE` | `LRANGE key start stop` | `LRANGE tasks 0 2` | Get list elements from index |
| `LTRIM` | `LTRIM key start stop` | `LTRIM tasks 0 2` | Keep only elements in range |
| `LLEN` | `LLEN key` | `LLEN tasks` | Get list length |
| `HSET` | `HSET key field value` | `HSET user:1 name "Rahul"` | Set hash field |
| `HGET` | `HGET key field` | `HGET user:1 name` | Get one hash field |
| `HGETALL` | `HGETALL key` | `HGETALL user:1` | Get all hash fields and values |
| `HDEL` | `HDEL key field` | `HDEL user:1 age` | Delete a hash field |
| `SADD` | `SADD key member` | `SADD tags "java"` | Add member to set |
| `SMEMBERS` | `SMEMBERS key` | `SMEMBERS tags` | Get all set members |
| `ZADD` | `ZADD key score member` | `ZADD board 1500 "PlayerA"` | Add to sorted set with score |
| `ZRANGE` | `ZRANGE key start stop` | `ZRANGE board 0 -1` | Get sorted set members by rank |
| `INCR` | `INCR key` | `INCR counter` | Increment integer value by 1 |
| `DECR` | `DECR key` | `DECR counter` | Decrement integer value by 1 |
| `FLUSHDB` | `FLUSHDB` | `FLUSHDB` | Delete ALL keys in current database (⚠️ destructive!) |
| `FLUSHALL` | `FLUSHALL` | `FLUSHALL` | Delete ALL keys in ALL databases (⚠️ very destructive!) |
| `INFO` | `INFO [section]` | `INFO memory` | Server info/stats |
| `DBSIZE` | `DBSIZE` | `DBSIZE` | Count of keys in DB |

---

## 15. Common Errors and Fixes

### Error 1: Connection Refused / Unable to Connect to localhost:6379

```
Error: io.lettuce.core.RedisConnectionException: Unable to connect to localhost:6379
```

**Cause:** Redis server is not running.

**Fix:**

```bash
# Check if Redis is running
redis-cli ping
# If you see "Could not connect to Redis at localhost:6379" → Redis is down

# Start Redis (Mac)
brew services start redis

# Start Redis (Linux)
sudo systemctl start redis-server

# Start Redis (Docker)
docker start my-redis

# Verify
redis-cli ping  # Should return: PONG
```

### Error 2: Serialization Error

```
Error: org.springframework.data.redis.serializer.SerializationException:
       Could not read JSON: Cannot deserialize value of type `...`
```

**Cause:** Object stored with one class version, but code changed or wrong serializer used.

**Fix:**

```java
// In RedisConfig.java, make sure you use GenericJackson2JsonRedisSerializer
template.setValueSerializer(new GenericJackson2JsonRedisSerializer(objectMapper()));

// Ensure your model class implements Serializable
public class Product implements Serializable { ... }

// If data is corrupted in Redis, flush and re-cache:
// redis-cli FLUSHDB
```

### Error 3: Wrong Redis Password

```
Error: WRONGPASS invalid username-password pair
```

**Fix:**

```yaml
# application.yml
spring:
  data:
    redis:
      password: yourCorrectPassword  # Make sure this matches Redis config
```

```bash
# Verify password in redis-cli
redis-cli -a yourCorrectPassword ping
```

### Error 4: Data Not Visible in Redis CLI

**Cause:** Data stored with Java serializer (binary) — not readable as plain text.

**Fix:** Configure `GenericJackson2JsonRedisSerializer` as shown in `RedisConfig.java`. After that, data will be readable in `redis-cli`.

### Error 5: TTL Not Working

**Cause:** TTL not set when saving, or key was overwritten without TTL.

**Fix:**

```java
// Always use this for data that should expire
redisTemplate.opsForValue().set(key, value, 300, TimeUnit.SECONDS);

// If key already exists without TTL, set it manually:
redisTemplate.expire(key, 300, TimeUnit.SECONDS);
```

### Error 6: Cache Not Updating (@CachePut not working)

**Cause:** Cache key mismatch between `@Cacheable` and `@CachePut`.

**Fix:** Ensure both annotations use the same `value` and `key` expression.

```java
// Both must match exactly:
@Cacheable(value = "products", key = "#productId")
public Product get(Long productId) { ... }

@CachePut(value = "products", key = "#product.id")  // ✅ matches
public Product update(Product product) { ... }
```

### Error 7: @Cacheable Method Not Being Skipped

**Cause:** `@EnableCaching` is missing, or calling the method from within the same class (self-invocation bypasses Spring proxy).

**Fix:**

```java
// 1. Add @EnableCaching to RedisConfig or main class
@EnableCaching
@Configuration
public class RedisConfig { ... }

// 2. Never call a cached method from the same class — call it via injected service
// WRONG (self-invocation):
this.getProduct(id);   // @Cacheable is ignored

// CORRECT (via proxy):
productService.getProduct(id);  // @Cacheable works
```

### Error 8: Redis Server Not Started

```
Error: Could not connect to Redis at 127.0.0.1:6379: Connection refused
```

**Fix:**

```bash
redis-server   # Start manually in terminal
# OR
brew services start redis   # Mac
sudo systemctl start redis  # Linux
```

### Error 9: Docker Redis Port Issue

```
Error: Bind for 0.0.0.0:6379 failed: port is already allocated
```

**Cause:** Another Redis instance (or another process) is using port 6379.

**Fix:**

```bash
# Check what's using port 6379
lsof -i :6379

# Option 1: Stop existing Redis
brew services stop redis

# Option 2: Use a different port for Docker
docker run --name my-redis -p 6380:6379 -d redis:latest
# Then update application.yml to use port 6380
```

---

## 16. Best Practices

### Key Naming Convention

```
✅ Good:   "user:1001:profile"       → entity:id:field
✅ Good:   "product:55:details"
✅ Good:   "session:abc-123"
✅ Good:   "recent_checks:42"
✅ Good:   "otp:9876543210"

❌ Bad:    "data"
❌ Bad:    "user1001"
❌ Bad:    "temp"
```

Use `{entity}:{id}:{field}` format. This prevents key collisions and makes debugging easy.

### Always Set TTL for Temporary Data

```java
// ✅ For cache data — always set TTL
redisTemplate.opsForValue().set("product:55", product, 600, TimeUnit.SECONDS);

// ❌ Without TTL — lives forever, wastes memory
redisTemplate.opsForValue().set("product:55", product);
```

### Do Not Store Huge Objects

```java
// ❌ Bad: Storing a list of 10,000 products
redisTemplate.opsForValue().set("all_products", allProducts);  // Could be MBs!

// ✅ Good: Store individual products by ID
redisTemplate.opsForValue().set("product:55", singleProduct, 600, TimeUnit.SECONDS);
```

### Use Separate Key Prefixes Per Feature

```
Cache layer:          products::55
Session layer:        session:abc-123
OTP layer:            otp:9876543210
Rate limit layer:     rate_limit:userId:endpoint
Recent checks layer:  recent_checks:42
```

### Use JSON Serialization Carefully

Always configure `GenericJackson2JsonRedisSerializer` so data is human-readable in Redis CLI. Never use Java default serialization (stores binary garbage).

### Avoid Caching Frequently Changing Data Without Eviction Strategy

If a product's price changes every 5 minutes, don't cache it for 10 minutes without a `@CacheEvict` or `@CachePut` mechanism.

### Use Redis For Its Strengths

| Use Redis for | Don't use Redis for |
|---|---|
| Caching DB query results | Primary storage of important business data |
| User sessions | Complex relational queries |
| Rate limiting | Long-term data that must survive restarts |
| Queues and pub/sub | Large files or binary data |
| Sliding windows | Transactions requiring ACID guarantees |
| Recent activity | Reporting and analytics queries |

### Monitor Redis Memory

```bash
# In redis-cli
INFO memory

# Key fields:
# used_memory_human: current memory usage
# maxmemory_human: configured max (0 = no limit)
# mem_fragmentation_ratio: ideally 1.0-1.5
```

---

## 17. Interview Questions

### Q1. What is Redis?

Redis (Remote Dictionary Server) is an open-source, in-memory key-value data store. It stores data in RAM for ultra-fast read/write operations. It supports multiple data types: String, List, Set, Hash, Sorted Set, and more.

---

### Q2. Why is Redis so fast?

Redis stores everything in **RAM** instead of disk. RAM access time is ~100 nanoseconds vs ~4 milliseconds for HDD. Additionally, Redis uses a **single-threaded event loop** (no context switching) and **simple data structures** that are optimized for speed.

---

### Q3. Redis vs Normal Database (MySQL/PostgreSQL)

| | Redis | MySQL |
|---|---|---|
| Storage | RAM | Disk |
| Speed | Microseconds | Milliseconds |
| Data size | Limited by RAM | Virtually unlimited |
| Persistence | Optional | Default |
| Query language | Key-based | SQL |
| Use case | Cache, sessions | Business data |

---

### Q4. Redis vs Cache

Cache is a concept (temporary fast storage). Redis is a tool that can implement a cache. Redis is also a database, queue, and message broker — it's much more than just a cache.

---

### Q5. What is TTL?

TTL (Time to Live) is the expiry duration set on a Redis key. After TTL expires, Redis automatically deletes the key. Example: `SET otp:123 "483920" EX 300` → key deletes after 300 seconds.

---

### Q6. What is RedisTemplate?

`RedisTemplate<K, V>` is Spring's main class for Redis operations. It provides methods like `opsForValue()`, `opsForList()`, `opsForHash()`, `opsForSet()`, `opsForZSet()` for all Redis data types.

---

### Q7. What is StringRedisTemplate?

A specialized `RedisTemplate<String, String>` pre-configured to use `StringRedisSerializer` for both key and value. Use it when you only deal with plain string values.

---

### Q8. What is @Cacheable?

`@Cacheable` marks a method so its return value is cached. On first call, the method executes and result is stored in Redis. On subsequent calls with the same key, Spring returns the cached value without calling the method.

---

### Q9. What is @CacheEvict?

`@CacheEvict` removes a specific entry (or all entries) from the cache. Used on delete/update methods to ensure stale data is cleared from Redis.

---

### Q10. What are Redis data types?

| Type | Use case |
|---|---|
| String | Simple values, counters, OTPs, JSON |
| List | Queues, recent N items, chat messages |
| Set | Unique tags, permissions, visited pages |
| Hash | Object/entity storage (like a row) |
| Sorted Set | Leaderboards, ranked data |
| Pub/Sub | Real-time event broadcasting |

---

### Q11. What is a Redis List?

A Redis List is an ordered collection of strings. Supports `LPUSH` (push front), `RPUSH` (push back), `LRANGE` (read range), `LTRIM` (trim to size). Useful for queues, recent activity, and last-N records.

---

### Q12. What is a Redis Hash?

A Redis Hash is a field-value map stored under one key. Like a small object: `HSET user:1 name "Rahul" age "28"`. You can get individual fields with `HGET` or everything with `HGETALL`.

---

### Q13. What is eviction policy?

When Redis runs out of memory, the eviction policy decides what to delete. Common policies:
- `allkeys-lru`: Remove least recently used keys (best for cache)
- `volatile-lru`: Remove LRU keys that have a TTL
- `noeviction`: Return error (never delete)

---

### Q14. What happens if Redis goes down?

- **Without persistence:** All cached data is lost. Application falls back to DB queries — slower but functional.
- **With RDB/AOF persistence:** Data can be restored on restart.
- Best practice: Treat Redis as a cache that can be rebuilt from the DB. Don't store data that can't be recovered.

---

### Q15. How does Redis help in microservices?

- **Shared cache:** Multiple services can read the same cached data
- **Session sharing:** User sessions accessible by any service instance
- **Rate limiting:** Centralized API call counting
- **Pub/Sub:** Event broadcasting between services
- **Distributed locks:** Coordinate actions across service instances

---

### Q16. Redis vs Kafka

| | Redis Pub/Sub | Kafka |
|---|---|---|
| Persistence | No (messages lost if no subscriber) | Yes (messages stored on disk) |
| Replay | Not possible | Supported |
| Throughput | Very high | Very high |
| Use case | Real-time notifications | Event streaming, event sourcing |
| Complexity | Simple | Complex |

**Rule of thumb:** Use Redis Pub/Sub for fire-and-forget notifications. Use Kafka when you need durable, replayable event streams.

---

### Q17. When NOT to use Redis?

- When data must survive restarts and loss is unacceptable
- For complex queries (joins, aggregations)
- When the data size exceeds available RAM
- For long-term storage or audit logs
- When you need ACID transactions across multiple operations

---

### Q18. What is the difference between LPUSH and RPUSH?

- `LPUSH`: Pushes to the **left (front/head)** of the list
- `RPUSH`: Pushes to the **right (back/tail)** of the list

For recent-activity patterns, use `LPUSH` + `LTRIM` to always keep newest items at index 0.

---

### Q19. How does @Cacheable know which method to skip?

Spring uses **AOP (Aspect Oriented Programming)** and creates a proxy around your service. When the method is called, the proxy checks Redis first. If the cache key exists, it returns the cached value without invoking the actual method.

---

### Q20. What is the difference between cache miss and cache hit?

- **Cache hit:** The requested key is found in Redis → data returned directly from Redis (fast)
- **Cache miss:** Key not found in Redis (doesn't exist or expired) → method executes, DB is queried, result stored in Redis

---

### Q21. Can Redis store complex Java objects?

Yes, by configuring `GenericJackson2JsonRedisSerializer`. Java objects are converted to JSON before storing and converted back to Java on retrieval.

---

### Q22. What is the difference between RedisTemplate and Redis Repository?

- **RedisTemplate:** Low-level, gives full control over all Redis operations and data types
- **Redis Repository (@RedisHash):** High-level abstraction for simple CRUD, works like JPA but stores data as Redis Hash

---

### Q23. What is Redis persistence?

Redis offers two persistence options:
- **RDB (Snapshot):** Saves a snapshot of data to disk at intervals. Compact but may lose recent data.
- **AOF (Append Only File):** Logs every write operation. More durable but slower and larger.
Can be used together for best of both.

---

### Q24. What is a Redis Sorted Set? Give an example.

A Sorted Set stores unique members each with a floating-point score. Members are always sorted by score.

```
ZADD leaderboard 1500 "Alice"
ZADD leaderboard 2200 "Bob"
ZRANGE leaderboard 0 -1 WITHSCORES
→ Alice:1500, Bob:2200
```

Use for leaderboards, priority queues, time-based windows.

---

### Q25. How do you implement rate limiting with Redis?

```java
// Allow max 5 requests per minute per user
String key = "rate:userId:" + userId;
Long count = redisTemplate.opsForValue().increment(key);

if (count == 1) {
    // First request — set 60-second window
    redisTemplate.expire(key, 60, TimeUnit.SECONDS);
}

if (count > 5) {
    throw new RuntimeException("Rate limit exceeded. Try again in 1 minute.");
}
```

---

## 18. Final Mini Project

This mini project combines everything learned. It includes CRUD APIs, TTL support, and the recent-checks feature.

### Project Structure

```
src/
└── main/
    ├── java/
    │   └── com/example/redis/
    │       ├── RedisApplication.java
    │       ├── config/
    │       │   └── RedisConfig.java           ← (already shown above)
    │       ├── controller/
    │       │   ├── RedisController.java        ← (already shown above)
    │       │   ├── ProductController.java      ← (already shown above)
    │       │   └── DetectionController.java    ← (already shown above)
    │       ├── service/
    │       │   ├── RedisService.java           ← (already shown above)
    │       │   ├── ProductService.java         ← (already shown above)
    │       │   ├── RecentChecksService.java    ← (already shown above)
    │       │   └── DetectionService.java       ← (already shown above)
    │       └── model/
    │           ├── Product.java                ← (already shown above)
    │           └── CheckResultEvent.java       ← (already shown above)
    └── resources/
        └── application.yml                    ← (already shown above)
```

### RedisApplication.java (Main Class)

**File location:** `src/main/java/com/example/redis/RedisApplication.java`

```java
package com.example.redis;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
public class RedisApplication {
    public static void main(String[] args) {
        SpringApplication.run(RedisApplication.class, args);
    }
}
```

### All Available API Endpoints

| Method | Endpoint | Description |
|---|---|---|
| `POST` | `/redis/save` | Save key-value (with optional TTL) |
| `GET` | `/redis/{key}` | Get value by key |
| `DELETE` | `/redis/{key}` | Delete key |
| `GET` | `/redis/ttl/{key}` | Get remaining TTL |
| `GET` | `/redis/exists/{key}` | Check if key exists |
| `GET` | `/products/{id}` | Get product (cached) |
| `POST` | `/products` | Save product (updates cache) |
| `DELETE` | `/products/{id}` | Delete product (evicts cache) |
| `DELETE` | `/products/cache/clear` | Clear all product cache |
| `POST` | `/detection/process` | Simulate check result event |
| `GET` | `/detection/recent/{serviceId}` | Get last 3 check results |

### Complete End-to-End Test Script

```bash
#!/bin/bash
BASE_URL="http://localhost:8080"

echo "=== 1. Save a key-value pair ==="
curl -s -X POST $BASE_URL/redis/save \
  -H "Content-Type: application/json" \
  -d '{"key":"user:1001:name","value":"Rahul Sharma"}' && echo

echo ""
echo "=== 2. Save with TTL (expires in 60s) ==="
curl -s -X POST $BASE_URL/redis/save \
  -H "Content-Type: application/json" \
  -d '{"key":"otp:9876543210","value":"483920","ttl":60}' && echo

echo ""
echo "=== 3. Get the value ==="
curl -s $BASE_URL/redis/user:1001:name && echo

echo ""
echo "=== 4. Check TTL ==="
curl -s $BASE_URL/redis/ttl/otp:9876543210 && echo

echo ""
echo "=== 5. Check if key exists ==="
curl -s $BASE_URL/redis/exists/user:1001:name && echo

echo ""
echo "=== 6. Get product (first call - DB hit, slow ~500ms) ==="
time curl -s $BASE_URL/products/1 | python3 -m json.tool

echo ""
echo "=== 7. Get product (second call - Redis hit, fast <5ms) ==="
time curl -s $BASE_URL/products/1 | python3 -m json.tool

echo ""
echo "=== 8. Push check results for service 42 ==="
for i in 1 2 3; do
  curl -s -X POST $BASE_URL/detection/process \
    -H "Content-Type: application/json" \
    -d "{\"serviceId\":42,\"serviceName\":\"PaymentService\",\"url\":\"https://pay.example.com\",\"success\":false,\"statusCode\":500,\"responseTimeMs\":$((100 * i)),\"checkedAt\":\"2024-01-01T10:0${i}:00\"}"
  echo " (check $i pushed)"
done

echo ""
echo "=== 9. Get last 3 check results from Redis ==="
curl -s $BASE_URL/detection/recent/42 | python3 -m json.tool

echo ""
echo "=== 10. Delete a key ==="
curl -s -X DELETE $BASE_URL/redis/user:1001:name && echo

echo ""
echo "=== Done! ==="
```

---

## 🎯 Quick Cheat Sheet

```
# Spring Annotations:
@EnableCaching     → Enable caching in the application
@Cacheable         → Read from cache; execute method only on miss
@CachePut          → Always execute + update cache
@CacheEvict        → Remove from cache

# RedisTemplate Operations:
opsForValue()      → String operations (get, set, increment)
opsForList()       → List operations (lpush, rpush, lrange, ltrim)
opsForHash()       → Hash operations (hset, hget, hgetall)
opsForSet()        → Set operations (sadd, smembers)
opsForZSet()       → Sorted Set operations (zadd, zrange)

# Redis CLI Quick Commands:
PING               → Test connection
SET key val EX 300 → Set with 5-min TTL
GET key            → Read value
DEL key            → Delete key
TTL key            → Check expiry
KEYS *             → List all keys
FLUSHDB            → Clear all keys (⚠️ dangerous!)
```

---

> 📌 **Remember:** Redis is a tool, not a solution to every problem. Use it where speed matters and data loss is acceptable. Always back your Redis cache with a persistent database for critical business data.

---

*Notes authored for learning, revision, and direct project use. Happy coding! 🚀*
