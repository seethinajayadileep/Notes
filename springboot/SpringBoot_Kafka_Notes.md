# 🚀 Spring Boot with Apache Kafka — Complete Beginner-Friendly Notes

> **Written by:** Senior Java Backend Engineer & Technical Mentor
> **Purpose:** Learning, Revision, and Project Implementation
> **Level:** Beginner → Intermediate

---

## 📚 Table of Contents

| # | Section |
|---|---------|
| 1 | [Introduction to Apache Kafka](#1-introduction-to-apache-kafka) |
| 2 | [Kafka Core Concepts](#2-kafka-core-concepts) |
| 3 | [Kafka Architecture](#3-kafka-architecture) |
| 4 | [Spring Boot Kafka Setup](#4-spring-boot-kafka-setup) |
| 5 | [application.yml Configuration](#5-applicationyml-configuration) |
| 6 | [Kafka Producer in Spring Boot](#6-kafka-producer-in-spring-boot) |
| 7 | [Kafka Consumer in Spring Boot](#7-kafka-consumer-in-spring-boot) |
| 8 | [Sending JSON Objects through Kafka](#8-sending-json-objects-through-kafka) |
| 9 | [Real Project Example](#9-real-project-example-monitoring--detection-service) |
| 10 | [Kafka Topic Creation](#10-kafka-topic-creation) |
| 11 | [Running Kafka Locally](#11-running-kafka-locally) |
| 12 | [Common Errors and Fixes](#12-common-errors-and-fixes) |
| 13 | [Best Practices](#13-best-practices) |
| 14 | [Interview Questions](#14-interview-questions) |
| 15 | [Final Mini Project](#15-final-mini-project) |

---

## 1. Introduction to Apache Kafka

### 🔷 What is Apache Kafka?

Apache Kafka is an **open-source distributed event streaming platform** originally built by LinkedIn and later donated to the Apache Software Foundation.

Think of Kafka like a **giant post office** or a **message bulletin board**:

- One service writes (publishes) a message to a board → **Producer**
- Other services read (consume) those messages from the board → **Consumer**
- The board itself is called a → **Topic**

> **Simple Analogy (Telugu context):** Imagine a WhatsApp group. One person posts a message (Producer). Everyone in the group reads it (Consumer). The group itself is the Topic. Even if you're offline, you'll see the message when you come back — Kafka works the same way!

```
Normal WhatsApp Group = Kafka
┌─────────────────────────────────────┐
│  WhatsApp Group = Topic             │
│  Person who sends msg = Producer    │
│  Person who reads msg = Consumer    │
│  Message stays in group = Kafka     │
│  stores message on disk             │
└─────────────────────────────────────┘
```

---

### 🔷 Why Kafka is Used in Backend / Microservices

In modern microservices architecture, multiple services need to communicate. Kafka solves several critical problems:

| Problem | Without Kafka | With Kafka |
|---------|--------------|------------|
| Service A needs to notify B, C, D | Direct REST calls to each — tight coupling | Publish one message; B, C, D consume independently |
| Service B is temporarily down | REST call fails, data is lost | Kafka stores message; B reads it when it comes back up |
| High traffic — 1 million events/sec | REST endpoints get overwhelmed | Kafka handles millions of messages/sec easily |
| Audit / event history needed | Hard to track what happened | Kafka retains all events as a log |
| Real-time data processing | Hard to do synchronously | Natural fit for Kafka's streaming model |

**Why teams choose Kafka:**
- **Decoupling** — Services don't need to know about each other
- **Durability** — Messages are written to disk, not lost if a consumer crashes
- **Scalability** — Horizontally scalable by adding more partitions/brokers
- **Replay** — You can re-read old messages (great for debugging)
- **High Throughput** — Handles millions of messages per second

---

### 🔷 Real-Time Examples of Kafka Usage

| Company / Use Case | How They Use Kafka |
|--------------------|--------------------|
| **LinkedIn** | Activity tracking (who viewed your profile, job recommendations) |
| **Uber** | Real-time trip tracking, surge pricing calculation |
| **Netflix** | User activity events, recommendations engine |
| **Swiggy / Zomato** | Order placed → notify restaurant → notify delivery partner |
| **Banking Apps** | Transaction events → fraud detection → notification service |
| **Your Monitoring App** | URL check result → detection service → incident creation |

**Real Example from your project:**
```
URL Monitor checks https://myapi.com every 60 seconds
    ↓
Publishes CheckResultEvent to Kafka topic: check.results
    ↓
Detection Service reads the event
    ↓
If 3 consecutive failures → Create Incident
```

---

### 🔷 Kafka vs Normal REST API Communication

| Feature | REST API (Synchronous) | Kafka (Asynchronous) |
|---------|------------------------|----------------------|
| **Communication Style** | Request → Wait → Response | Fire and Forget (Publish → done) |
| **Coupling** | Tight — caller must know callee's URL | Loose — producer doesn't know consumers |
| **If receiver is down** | Request fails immediately | Message waits in Kafka until receiver comes back |
| **Speed** | Slower under heavy load | Very fast, handles millions/sec |
| **Message History** | No history kept | Kafka retains messages (configurable) |
| **Multiple receivers** | Must call each one manually | All consumers get the message automatically |
| **Use case** | CRUD operations, queries | Events, notifications, data pipelines |
| **Error handling** | Complex retry logic needed | Built-in retry + Dead Letter Topic |

> **When to use REST:** User logs in, fetches their profile → use REST.
> **When to use Kafka:** Order placed → notify warehouse + send email + update analytics → use Kafka.

---

## 2. Kafka Core Concepts

Understanding these 10 concepts will give you 80% of Kafka knowledge. Learn them well!

---

### 🔷 1. Producer

A **Producer** is any application or service that **sends (publishes) messages to a Kafka topic**.

```
Producer = The sender
```

**Real Example:** Your Monitoring Service checks a URL and sends the result to Kafka.

```java
// Producer sends a message
kafkaTemplate.send("check.results", checkResultEvent);
//                  ↑ topic name    ↑ the message/event
```

> **Tenglish:** Producer ante message ni Kafka lo pampinchi service. "I checked the URL and here's the result" ani cheppíntundi Kafka ki.

---

### 🔷 2. Consumer

A **Consumer** is any application or service that **reads (consumes) messages from a Kafka topic**.

```
Consumer = The receiver / listener
```

**Real Example:** Your Detection Service reads check results from Kafka to decide if an incident should be created.

```java
@KafkaListener(topics = "check.results", groupId = "detection-group")
public void consume(CheckResultEvent event) {
    // process the event
}
```

> **Tenglish:** Consumer ante Kafka lo unna messages ni chaduvutundi. "Ee result vachindi, idi analyze cheyyadam" ani chestundi.

---

### 🔷 3. Topic

A **Topic** is a **named category or feed** where messages are stored and organized.

```
Topic = A named mailbox / folder / WhatsApp group
```

Think of it like a database table — but for messages. Each topic stores messages in an ordered, immutable log.

| Topic Name | What goes in it |
|-----------|----------------|
| `check.results` | URL check result events |
| `order.placed` | Order placed events |
| `user.registered` | New user registration events |
| `payment.processed` | Payment completion events |

**Rules:**
- Topic names should be descriptive (use dot notation: `service.action`)
- Multiple producers can write to same topic
- Multiple consumers can read from same topic

> **Tenglish:** Topic ante oka folder laanti. "check.results" folder lo monitoring service messages vesthundi, detection service chaduvutundi.

---

### 🔷 4. Partition

A **Partition** is a way to **split a topic into multiple ordered segments** for parallelism and scalability.

```
Topic with 3 Partitions:
┌─────────────────────────────────────────────┐
│ Topic: check.results                         │
│                                             │
│  Partition 0: [msg1] [msg4] [msg7] ...      │
│  Partition 1: [msg2] [msg5] [msg8] ...      │
│  Partition 2: [msg3] [msg6] [msg9] ...      │
└─────────────────────────────────────────────┘
```

**Why partitions?**
- Allow **parallel processing** — different consumers read different partitions simultaneously
- Enable **horizontal scaling** — more partitions = more throughput
- Messages within a partition are **strictly ordered**
- Messages across partitions have no guaranteed order

**How messages are assigned to partitions:**
- If a **key** is provided → same key always goes to same partition (ordering guaranteed)
- If **no key** → messages are round-robined across partitions

> **Tenglish:** Partition ante oka topic ni chinna chinna pieces ga cheyyadam. Oka restaurant lo 3 counters unte — 3 partitions. Each counter ni separately serve cheyyadam = parallel processing.

---

### 🔷 5. Offset

An **Offset** is a **unique sequential ID** assigned to each message within a partition.

```
Partition 0:
┌────┬────┬────┬────┬────┐
│ 0  │ 1  │ 2  │ 3  │ 4  │  ← Offsets
└────┴────┴────┴────┴────┘
  ↑
  Consumer last read offset = 2
  (Will next read offset 3)
```

**Key facts about offsets:**
- Offsets start at **0** and increment by 1
- Kafka tracks what offset each consumer group has read up to (called **committed offset**)
- Offsets are **per partition** — each partition has its own offset sequence
- If a consumer crashes, it resumes from its last committed offset

> **Tenglish:** Offset ante oka bookmark laanti. "Nenu message number 5 varaku chadivanu, next time 6 nundi start cheyyi" ani Kafka ki cheptundi consumer.

---

### 🔷 6. Consumer Group

A **Consumer Group** is a **group of consumers that together consume a topic**, where each partition is consumed by only one consumer in the group at a time.

```
Topic: check.results (3 partitions)
Consumer Group: detection-group

┌──────────────────────────────────────────────┐
│  Partition 0  →  Consumer A (detection-1)    │
│  Partition 1  →  Consumer B (detection-2)    │
│  Partition 2  →  Consumer C (detection-3)    │
└──────────────────────────────────────────────┘
All 3 consumers share the load — each reads 1 partition
```

**Rules:**
- If consumers in group < partitions → one consumer reads multiple partitions
- If consumers in group = partitions → perfect 1:1 assignment (ideal)
- If consumers in group > partitions → extra consumers sit idle
- Different groups each get a **complete copy** of all messages

**Same groupId vs Different groupId:**

| Scenario | What Happens |
|----------|-------------|
| 3 consumers, same `groupId` | Messages are **split** among them (load balanced) |
| 3 consumers, different `groupId` | Each consumer gets **all** messages (broadcast) |

> **Tenglish:** Same group lo unte messages share chestaru. Different group lo unte — andaru same messages chaduvutaru. Zomato order ki — restaurant + delivery partner different groups lo untaru, ibbayindi message same order ki cheptundi.

---

### 🔷 7. Broker

A **Broker** is a **Kafka server** that stores messages and serves clients (producers/consumers).

```
Kafka Cluster with 3 Brokers:
┌──────────┐  ┌──────────┐  ┌──────────┐
│ Broker 1 │  │ Broker 2 │  │ Broker 3 │
│ (Leader) │  │(Follower)│  │(Follower)│
│ Port 9092│  │ Port 9093│  │ Port 9094│
└──────────┘  └──────────┘  └──────────┘
```

**Key facts:**
- Each broker has a unique **broker ID**
- Brokers store topic partitions
- One broker is the **leader** for a partition; others are **followers** (replicas)
- Producers and consumers talk to the leader broker for a partition

> **Tenglish:** Broker ante Kafka server. Oka broker down ayina, inko broker leader avutundi. So data loss undi kaadu!

---

### 🔷 8. Cluster

A **Cluster** is a **group of Kafka brokers** working together.

```
Kafka Cluster
┌─────────────────────────────────────┐
│  Broker 1  │  Broker 2  │ Broker 3  │
│            │            │           │
│ Partition0 │ Partition1 │Partition2 │
│ (Leader)   │ (Leader)   │(Leader)   │
│ Partition1 │ Partition2 │Partition0 │
│ (Replica)  │ (Replica)  │(Replica)  │
└─────────────────────────────────────┘
```

- In production, you typically run **3 or more brokers** for fault tolerance
- For local development, **1 broker** is enough

---

### 🔷 9. Zookeeper vs KRaft Mode

**Zookeeper (Old way — before Kafka 2.8):**
- Kafka used Apache Zookeeper to manage cluster metadata (who is leader, broker list, etc.)
- Required running a separate Zookeeper process alongside Kafka
- More complexity, more things to manage

**KRaft Mode (New way — Kafka 2.8+ / default in Kafka 3.x):**
- Kafka manages its own metadata using a built-in **Raft consensus protocol** (KRaft = Kafka + Raft)
- No Zookeeper needed!
- Simpler setup, better performance, easier to manage

```
Old Setup:                    New Setup (KRaft):
┌──────────┐                  ┌──────────────────────┐
│Zookeeper │                  │  Kafka Broker        │
│(separate)│                  │  (manages its own    │
└────┬─────┘                  │   metadata via KRaft)│
     │                        └──────────────────────┘
┌────┴─────┐
│  Kafka   │
│  Broker  │
└──────────┘
```

> **Recommendation:** Use **KRaft mode** for local development and new projects. It's simpler!

---

### 🔷 10. Serialization and Deserialization

Kafka sends messages as **bytes** (raw binary data) over the network. So:
- **Serialization** = Converting Java object → bytes (before sending to Kafka)
- **Deserialization** = Converting bytes → Java object (after receiving from Kafka)

```
Producer Side:
CheckResultEvent (Java object)
    → Serializer (JsonSerializer)
    → {"serviceId": 1, "url": "...", ...}  (bytes sent to Kafka)

Consumer Side:
{"serviceId": 1, "url": "...", ...}  (bytes received from Kafka)
    → Deserializer (JsonDeserializer)
    → CheckResultEvent (Java object)
```

**Common Serializers in Spring Kafka:**

| Data Type | Serializer | Deserializer |
|-----------|-----------|--------------|
| `String` | `StringSerializer` | `StringDeserializer` |
| `Integer` | `IntegerSerializer` | `IntegerDeserializer` |
| `JSON Object` | `JsonSerializer` | `JsonDeserializer` |

> **Tenglish:** Serialization ante Java object ni bytes ga maarchodam (Kafka ki pampinchataniki). Deserialization ante aa bytes ni again Java object ga maarchodam (Consumer read chesappudu).

---

## 3. Kafka Architecture

### 🔷 How Producer Sends a Message to Topic

```
Step-by-step flow:

1. Producer creates a message (ProducerRecord)
2. Serializer converts it to bytes
3. Partitioner decides which partition to send to
   - If key provided → hash(key) % numPartitions
   - If no key → round-robin
4. Message goes to the Leader Broker of that partition
5. Leader writes it to its local log
6. Followers (replicas) copy the message
7. Leader sends ACK back to Producer
8. Producer considers send successful

┌──────────┐     ┌─────────────────────────────────────┐
│ Producer │────►│  Topic: check.results                │
│          │     │                                      │
│ Serialize│     │  Partition 0: [0][1][2][3]...        │
│ Partition│────►│  Partition 1: [0][1][2]...           │
│   Route  │     │  Partition 2: [0][1]...              │
└──────────┘     └─────────────────────────────────────┘
```

---

### 🔷 How Consumer Reads Messages from Topic

```
Step-by-step flow:

1. Consumer subscribes to a topic with a groupId
2. Kafka assigns partitions to consumers in the group
3. Consumer polls for new messages (continuous loop)
4. Kafka returns messages from last committed offset
5. Consumer processes the messages
6. Consumer commits the offset back to Kafka
7. Loop repeats

┌─────────────────────────────────┐     ┌──────────┐
│ Topic: check.results            │     │ Consumer │
│                                 │     │ Group:   │
│ Partition 0: [0][1][2][3]...   │────►│ detection│
│ Partition 1: [0][1][2]...      │────►│ -group   │
│ Partition 2: [0][1]...         │────►│          │
└─────────────────────────────────┘     │ Offset:  │
                                        │ committed│
                                        └──────────┘
```

---

### 🔷 How Partitions Help in Scalability

```
WITHOUT partitions (1 partition):
┌─────────────────────────────────────────────┐
│ Topic: orders (1 partition)                 │
│ [msg1][msg2][msg3]...[msg1000000]           │
│                                             │
│ Only 1 consumer can read at a time          │
│ → Bottleneck! Slow!                         │
└─────────────────────────────────────────────┘

WITH partitions (3 partitions):
┌─────────────────────────────────────────────┐
│ Topic: orders (3 partitions)                │
│ Partition 0: [msg1][msg4][msg7]...          │──► Consumer A
│ Partition 1: [msg2][msg5][msg8]...          │──► Consumer B
│ Partition 2: [msg3][msg6][msg9]...          │──► Consumer C
│                                             │
│ 3 consumers read in PARALLEL → 3x faster!  │
└─────────────────────────────────────────────┘
```

---

### 🔷 How Consumer Groups Work

```
Scenario: Topic has 3 partitions, Group has 3 consumers
                 ┌─────────────────────┐
                 │  Topic: check.results│
                 │  (3 partitions)     │
                 └──┬──────┬──────┬───┘
                    │      │      │
                    P0     P1     P2
                    │      │      │
              ┌─────▼──────▼──────▼────┐
              │   Consumer Group:      │
              │   detection-group      │
              │                        │
              │  [Consumer A] ← P0    │
              │  [Consumer B] ← P1    │
              │  [Consumer C] ← P2    │
              └────────────────────────┘
Each consumer handles exactly one partition.
This is optimal load balancing!

---

If you have 2 consumers but 3 partitions:
  Consumer A ← P0, P2  (handles two partitions)
  Consumer B ← P1      (handles one partition)

If you have 4 consumers but 3 partitions:
  Consumer A ← P0
  Consumer B ← P1
  Consumer C ← P2
  Consumer D ← IDLE (no partition assigned — wasted resource!)
```

---

### 🔷 Two Different Consumer Groups = Complete Independence

```
Topic: check.results

Group 1: detection-group          Group 2: analytics-group
┌──────────────────────┐          ┌──────────────────────┐
│ Consumer A reads P0  │          │ Consumer X reads P0  │
│ Consumer B reads P1  │          │ Consumer Y reads P1  │
│ Consumer C reads P2  │          │ Consumer Z reads P2  │
└──────────────────────┘          └──────────────────────┘

Both groups receive ALL messages independently.
detection-group creates incidents.
analytics-group stores data for reports.
SAME Kafka topic serves both use cases!
```

---

## 4. Spring Boot Kafka Setup

### 🔷 Project Structure

```
my-kafka-app/
├── src/
│   └── main/
│       ├── java/
│       │   └── com/example/kafka/
│       │       ├── KafkaApplication.java          ← Main class
│       │       ├── config/
│       │       │   └── KafkaTopicConfig.java      ← Topic bean config
│       │       ├── producer/
│       │       │   ├── ProducerService.java        ← Kafka send logic
│       │       │   └── ProducerController.java     ← REST endpoint
│       │       ├── consumer/
│       │       │   └── ConsumerService.java        ← @KafkaListener
│       │       └── dto/
│       │           └── CheckResultEvent.java       ← Event DTO
│       └── resources/
│           └── application.yml                    ← Kafka config
└── pom.xml                                        ← Dependencies
```

---

### 🔷 Required Maven Dependencies (pom.xml)

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
    <artifactId>kafka-demo</artifactId>
    <version>0.0.1-SNAPSHOT</version>
    <name>kafka-demo</name>
    <description>Spring Boot Kafka Demo</description>

    <properties>
        <java.version>17</java.version>
    </properties>

    <dependencies>

        <!-- ✅ Spring Boot Web — for REST controllers -->
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-web</artifactId>
        </dependency>

        <!-- ✅ Spring Kafka — the main Kafka integration library -->
        <!-- Includes KafkaTemplate, @KafkaListener, KafkaAdmin, etc. -->
        <dependency>
            <groupId>org.springframework.kafka</groupId>
            <artifactId>spring-kafka</artifactId>
        </dependency>

        <!-- ✅ Lombok — reduces boilerplate (getters, setters, constructors) -->
        <!-- @Data, @Builder, @Slf4j annotations from Lombok -->
        <dependency>
            <groupId>org.projectlombok</groupId>
            <artifactId>lombok</artifactId>
            <optional>true</optional>
        </dependency>

        <!-- ✅ Jackson — for JSON serialization/deserialization -->
        <!-- Usually included transitively, but add explicitly for safety -->
        <dependency>
            <groupId>com.fasterxml.jackson.core</groupId>
            <artifactId>jackson-databind</artifactId>
        </dependency>

        <!-- ✅ Test dependencies -->
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-test</artifactId>
            <scope>test</scope>
        </dependency>

        <dependency>
            <groupId>org.springframework.kafka</groupId>
            <artifactId>spring-kafka-test</artifactId>
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

| Dependency | Why We Need It |
|-----------|---------------|
| `spring-boot-starter-web` | Enables REST controllers (`@RestController`, `@GetMapping`) |
| `spring-kafka` | Core Kafka integration — `KafkaTemplate`, `@KafkaListener` |
| `lombok` | Removes boilerplate — no need to write getters/setters manually |
| `jackson-databind` | Converts Java objects ↔ JSON strings (needed for JSON Kafka messages) |
| `spring-kafka-test` | Provides `EmbeddedKafka` for unit testing |

---

## 5. application.yml Configuration

### 🔷 Complete application.yml with Explanations

**File location:** `src/main/resources/application.yml`

```yaml
spring:
  application:
    name: kafka-demo                    # Your app name

  kafka:
    # ──────────────────────────────────────────────
    # BOOTSTRAP SERVER
    # ──────────────────────────────────────────────
    bootstrap-servers: localhost:9092
    # ↑ The address of your Kafka broker(s)
    # localhost:9092 = running on your own machine, port 9092
    # For multiple brokers: localhost:9092,localhost:9093,localhost:9094
    # In production (AWS MSK): broker1.kafka.aws.com:9092,broker2.kafka.aws.com:9092

    # ──────────────────────────────────────────────
    # PRODUCER CONFIGURATION
    # ──────────────────────────────────────────────
    producer:
      key-serializer: org.apache.kafka.common.serialization.StringSerializer
      # ↑ How to serialize the MESSAGE KEY to bytes
      # Key is optional but useful for partition routing and ordering
      # StringSerializer = converts String key to bytes

      value-serializer: org.springframework.kafka.support.serializer.JsonSerializer
      # ↑ How to serialize the MESSAGE VALUE (your actual data) to bytes
      # JsonSerializer = converts any Java object to JSON bytes
      # For simple String messages, use StringSerializer instead

      acks: all
      # ↑ Acknowledgement mode:
      # acks=0  → Producer doesn't wait for any ack (fastest, but risky — data loss possible)
      # acks=1  → Wait for leader broker to write (balanced)
      # acks=all → Wait for leader + ALL replicas to write (slowest, but safest)
      # Use 'all' for production

      retries: 3
      # ↑ How many times to retry if send fails
      # Automatically retries up to 3 times before throwing error

    # ──────────────────────────────────────────────
    # CONSUMER CONFIGURATION
    # ──────────────────────────────────────────────
    consumer:
      group-id: my-consumer-group
      # ↑ The Consumer Group ID
      # All consumers with this same group-id share the topic partitions
      # Change this per service (detection-group, analytics-group, etc.)

      auto-offset-reset: earliest
      # ↑ What to do when a consumer joins and there's no committed offset:
      # earliest → start reading from the VERY FIRST message in the topic
      # latest   → start reading only NEW messages (ignore old ones)
      # none     → throw exception if no offset found
      # Use 'earliest' in development, 'latest' in production usually

      key-deserializer: org.apache.kafka.common.serialization.StringDeserializer
      # ↑ How to deserialize the message key bytes back to String

      value-deserializer: org.springframework.kafka.support.serializer.JsonDeserializer
      # ↑ How to deserialize message value bytes back to Java object
      # JsonDeserializer converts JSON bytes → Java object

      properties:
        spring.json.trusted.packages: "*"
        # ↑ IMPORTANT for JsonDeserializer!
        # Tells Kafka which Java packages are trusted for deserialization
        # "*" means trust ALL packages (fine for dev)
        # In production, specify exact packages: "com.example.dto,com.example.events"

        spring.json.type.mapping: checkResult:com.example.kafka.dto.CheckResultEvent
        # ↑ Maps JSON type header to Java class
        # Format: "alias:fully.qualified.ClassName"
        # Useful when producer and consumer are in different services
        # (class names might differ across services)

# ──────────────────────────────────────────────
# LOGGING CONFIGURATION
# ──────────────────────────────────────────────
logging:
  level:
    org.apache.kafka: WARN
    # ↑ Reduce Kafka's own verbose logging
    # Change to DEBUG to see detailed Kafka internals
    com.example.kafka: DEBUG
    # ↑ Show debug logs for your own code
```

---

### 🔷 application.yml for String-only Messages (Simpler Version)

If you're just sending plain `String` messages (not JSON objects), use this simpler config:

```yaml
spring:
  kafka:
    bootstrap-servers: localhost:9092

    producer:
      key-serializer: org.apache.kafka.common.serialization.StringSerializer
      value-serializer: org.apache.kafka.common.serialization.StringSerializer

    consumer:
      group-id: my-consumer-group
      auto-offset-reset: earliest
      key-deserializer: org.apache.kafka.common.serialization.StringDeserializer
      value-deserializer: org.apache.kafka.common.serialization.StringDeserializer
```

> **Rule of thumb:** Start with String serializers. Once working, upgrade to JsonSerializer for objects.


---

## 6. Kafka Producer in Spring Boot

### 🔷 Project File Location

```
src/main/java/com/example/kafka/
├── producer/
│   ├── ProducerService.java       ← Put this here
│   └── ProducerController.java    ← Put this here
```

---

### 🔷 What is KafkaTemplate?

`KafkaTemplate<K, V>` is the **main class Spring provides for sending messages to Kafka**.

- It's similar to `JdbcTemplate` (for database) or `RestTemplate` (for HTTP)
- Spring auto-configures it based on your `application.yml`
- You just `@Autowired` it and call `.send()`

```
KafkaTemplate
    ↓ wraps
Kafka Producer (low-level Java client)
    ↓ sends to
Kafka Broker → Topic → Partition
```

---

### 🔷 Step 1: Main Application Class

**File:** `src/main/java/com/example/kafka/KafkaApplication.java`

```java
package com.example.kafka;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
public class KafkaApplication {
    public static void main(String[] args) {
        SpringApplication.run(KafkaApplication.class, args);
    }
}
```

---

### 🔷 Step 2: Producer Service

**File:** `src/main/java/com/example/kafka/producer/ProducerService.java`

```java
package com.example.kafka.producer;

import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.kafka.core.KafkaTemplate;
import org.springframework.kafka.support.SendResult;
import org.springframework.stereotype.Service;

import java.util.concurrent.CompletableFuture;

@Service                        // Marks this as a Spring Service bean
@RequiredArgsConstructor        // Lombok: generates constructor with final fields
@Slf4j                          // Lombok: creates logger → log.info(), log.error()
public class ProducerService {

    // KafkaTemplate<Key Type, Value Type>
    // Key = String (message key, used for partitioning)
    // Value = String (the actual message content)
    private final KafkaTemplate<String, String> kafkaTemplate;

    // Topic name as a constant — easy to change in one place
    private static final String TOPIC = "my-topic";

    /**
     * Sends a plain String message to the Kafka topic.
     *
     * kafkaTemplate.send() returns a CompletableFuture.
     * We attach callbacks to handle success and failure.
     */
    public void sendMessage(String message) {
        log.info("Sending message to topic [{}]: {}", TOPIC, message);

        // send(topicName, messageValue)
        // You can also use: send(topicName, key, messageValue) for key-based partitioning
        CompletableFuture<SendResult<String, String>> future =
                kafkaTemplate.send(TOPIC, message);

        // ✅ Success callback — runs when Kafka confirms the message was received
        future.thenAccept(result -> {
            log.info("Message sent successfully! Topic: {}, Partition: {}, Offset: {}",
                    result.getRecordMetadata().topic(),
                    result.getRecordMetadata().partition(),
                    result.getRecordMetadata().offset()
            );
        });

        // ❌ Failure callback — runs if the send fails (broker down, network issue, etc.)
        future.exceptionally(ex -> {
            log.error("Failed to send message to topic [{}]: {}", TOPIC, ex.getMessage());
            return null;
        });
    }

    /**
     * Sends a message with an explicit KEY.
     * Messages with the same key ALWAYS go to the same partition.
     * This guarantees ordering for messages with the same key.
     */
    public void sendMessageWithKey(String key, String message) {
        log.info("Sending keyed message to topic [{}], key=[{}]: {}", TOPIC, key, message);

        // send(topicName, key, value)
        kafkaTemplate.send(TOPIC, key, message);
    }
}
```

---

### 🔷 Step 3: REST Controller

**File:** `src/main/java/com/example/kafka/producer/ProducerController.java`

```java
package com.example.kafka.producer;

import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/api/kafka")
@RequiredArgsConstructor
@Slf4j
public class ProducerController {

    // Inject ProducerService — business logic stays in service, not here
    private final ProducerService producerService;

    /**
     * POST /api/kafka/publish?message=hello
     *
     * Example curl:
     * curl -X POST "http://localhost:8080/api/kafka/publish?message=HelloKafka"
     */
    @PostMapping("/publish")
    public ResponseEntity<String> publishMessage(@RequestParam String message) {
        log.info("Received publish request: {}", message);

        producerService.sendMessage(message);

        return ResponseEntity.ok("Message published successfully: " + message);
    }

    /**
     * POST /api/kafka/publish-keyed?key=service-1&message=hello
     *
     * Example curl:
     * curl -X POST "http://localhost:8080/api/kafka/publish-keyed?key=svc1&message=Hello"
     */
    @PostMapping("/publish-keyed")
    public ResponseEntity<String> publishKeyedMessage(
            @RequestParam String key,
            @RequestParam String message) {

        producerService.sendMessageWithKey(key, message);

        return ResponseEntity.ok("Keyed message published. Key: " + key);
    }
}
```

---

### 🔷 How `send()` Works — Explained

```java
kafkaTemplate.send("my-topic", "Hello Kafka");
//             ↑ topic name    ↑ message value

// Under the hood:
// 1. JsonSerializer (or StringSerializer) converts "Hello Kafka" to bytes
// 2. Partitioner decides which partition to send to
// 3. Message is batched (for performance)
// 4. Sent to the leader broker of that partition
// 5. Broker writes it to disk
// 6. ACK returned (if acks=all, waits for replicas too)
// 7. CompletableFuture resolves (thenAccept callback fires)
```

**Overloads of `send()`:**

```java
// Option 1: Just topic + value
kafkaTemplate.send("my-topic", "Hello");

// Option 2: Topic + key + value
kafkaTemplate.send("my-topic", "service-1", "Hello");

// Option 3: Full ProducerRecord (advanced)
ProducerRecord<String, String> record = new ProducerRecord<>(
    "my-topic",     // topic
    0,              // specific partition (optional)
    "service-1",    // key
    "Hello"         // value
);
kafkaTemplate.send(record);
```

> **Tenglish:** `kafkaTemplate.send()` ante oka courier parcel pampinche laanti. Topic = courier address, message = parcel content. Kafka receipt (offset) ichi confirm chestundi.

---

## 7. Kafka Consumer in Spring Boot

### 🔷 Project File Location

```
src/main/java/com/example/kafka/
└── consumer/
    └── ConsumerService.java    ← Put this here
```

---

### 🔷 Consumer Service using @KafkaListener

**File:** `src/main/java/com/example/kafka/consumer/ConsumerService.java`

```java
package com.example.kafka.consumer;

import lombok.extern.slf4j.Slf4j;
import org.apache.kafka.clients.consumer.ConsumerRecord;
import org.springframework.kafka.annotation.KafkaListener;
import org.springframework.stereotype.Service;

@Service
@Slf4j
public class ConsumerService {

    /**
     * @KafkaListener — The magic annotation!
     *
     * topics    = which topic to listen to (can be multiple: {"topic1", "topic2"})
     * groupId   = the consumer group this consumer belongs to
     *
     * Spring automatically:
     * 1. Creates a Kafka consumer thread
     * 2. Subscribes it to the topic
     * 3. Continuously polls for new messages
     * 4. Calls this method for each new message
     * 5. Commits the offset after method returns successfully
     */
    @KafkaListener(topics = "my-topic", groupId = "my-consumer-group")
    public void consumeMessage(String message) {
        // 'message' is automatically deserialized using your configured deserializer
        log.info("✅ Received message from topic [my-topic]: {}", message);

        // Put your business logic here
        processMessage(message);
    }

    /**
     * Advanced: Consume with full metadata using ConsumerRecord
     * Useful when you need partition number, offset, timestamp, key, etc.
     */
    @KafkaListener(topics = "my-topic", groupId = "my-consumer-group-advanced")
    public void consumeWithMetadata(ConsumerRecord<String, String> record) {
        log.info("📦 Received message:");
        log.info("   Topic     : {}", record.topic());
        log.info("   Partition : {}", record.partition());
        log.info("   Offset    : {}", record.offset());
        log.info("   Key       : {}", record.key());
        log.info("   Value     : {}", record.value());
        log.info("   Timestamp : {}", record.timestamp());
    }

    /**
     * Listen to multiple topics at once
     */
    @KafkaListener(topics = {"topic-A", "topic-B"}, groupId = "multi-topic-group")
    public void consumeMultipleTopics(String message) {
        log.info("Received from multi-topic listener: {}", message);
    }

    private void processMessage(String message) {
        // Your actual business logic here
        log.debug("Processing: {}", message);
    }
}
```

---

### 🔷 What @KafkaListener Does

```
@KafkaListener creates a background thread that:

Application starts
    ↓
Spring finds @KafkaListener annotation
    ↓
Creates MessageListenerContainer
    ↓
Container spawns a thread for this listener
    ↓
Thread connects to Kafka broker
    ↓
Thread subscribes to topic "my-topic" with groupId "my-consumer-group"
    ↓
Thread enters infinite poll loop:
    → Polls Kafka every 5 seconds (default)
    → Gets new messages
    → Calls your method for each message
    → Commits offset if method succeeds
    → If method throws exception → does NOT commit offset → retries
```

---

### 🔷 What groupId Means

```yaml
# In application.yml
consumer:
  group-id: my-consumer-group
```

Or override per listener:
```java
@KafkaListener(topics = "my-topic", groupId = "specific-group")
```

**groupId controls how messages are shared:**

```
Topic: my-topic (3 partitions)
100 messages total

Scenario A: 3 consumers, SAME groupId = "group-A"
┌─────────────────────────────────────────────────────┐
│  Consumer 1 (group-A) reads Partition 0 → 34 msgs  │
│  Consumer 2 (group-A) reads Partition 1 → 33 msgs  │
│  Consumer 3 (group-A) reads Partition 2 → 33 msgs  │
│  Total = 100 msgs processed (each msg processed 1x) │
└─────────────────────────────────────────────────────┘

Scenario B: 2 consumers, DIFFERENT groupIds
┌─────────────────────────────────────────────────────┐
│  Consumer 1 (group-A) reads ALL 3 partitions → 100 msgs │
│  Consumer 2 (group-B) reads ALL 3 partitions → 100 msgs │
│  Total = 200 msgs processed (each msg processed 2x) │
└─────────────────────────────────────────────────────┘
```

**Real-world use case for different groupIds:**
```
Kafka topic: order.placed

group: email-service      → sends order confirmation email
group: inventory-service  → decrements stock
group: analytics-service  → updates dashboard metrics

All three get every order event. Each handles it differently.
```

> **Tenglish:**
> - Same groupId = Team work — partition cheppukununtaru, load share chestaru
> - Different groupId = Each person full message chaduvutadu — like different departments seeing same notice

---

### 🔷 What Happens if Consumer is Down?

```
Timeline:
10:00 AM — Consumer reads offset 0–49 (50 messages), commits offset 50
10:30 AM — Consumer crashes (service down)
10:30–11:00 AM — Producer keeps publishing → offsets 50–200 accumulate in Kafka
11:00 AM — Consumer restarts
11:00 AM — Consumer asks Kafka: "What's my last committed offset?"
           Kafka says: "50"
           Consumer starts reading from offset 50
           → Consumer catches up on ALL 150 missed messages!

This is called: Consumer Lag
```

This is why Kafka is powerful — **messages are never lost** as long as retention period hasn't expired.

---

## 8. Sending JSON Objects through Kafka

### 🔷 Project File Location

```
src/main/java/com/example/kafka/
├── dto/
│   └── CheckResultEvent.java     ← Event DTO here
├── producer/
│   ├── EventProducerService.java  ← JSON producer here
│   └── EventProducerController.java
└── consumer/
    └── EventConsumerService.java  ← JSON consumer here
```

---

### 🔷 Step 1: Create the Event DTO

**File:** `src/main/java/com/example/kafka/dto/CheckResultEvent.java`

```java
package com.example.kafka.dto;

import com.fasterxml.jackson.annotation.JsonFormat;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * CheckResultEvent — Data Transfer Object for URL check results.
 *
 * This object is serialized to JSON by the producer
 * and deserialized back by the consumer.
 *
 * Lombok annotations explained:
 * @Data           → generates getters, setters, toString, equals, hashCode
 * @Builder        → enables builder pattern: CheckResultEvent.builder().serviceId(1L).build()
 * @NoArgsConstructor → generates no-arg constructor (REQUIRED by Jackson for deserialization)
 * @AllArgsConstructor → generates all-args constructor (used by @Builder)
 */
@Data
@Builder
@NoArgsConstructor
@AllArgsConstructor
public class CheckResultEvent {

    private Long serviceId;        // ID of the monitored service
    private String serviceName;    // e.g., "Payment API"
    private String url;            // e.g., "https://api.payment.com/health"
    private boolean success;       // true = HTTP 2xx, false = timeout/error
    private int statusCode;        // HTTP status code: 200, 503, 0 (timeout), etc.
    private long responseTimeMs;   // How long the request took in milliseconds
    private String checkedAt;      // ISO timestamp: "2024-01-15T10:30:00Z"
}
```

---

### 🔷 Step 2: application.yml for JSON

Update your `application.yml` to use JSON serializers:

```yaml
spring:
  kafka:
    bootstrap-servers: localhost:9092

    producer:
      key-serializer: org.apache.kafka.common.serialization.StringSerializer
      value-serializer: org.springframework.kafka.support.serializer.JsonSerializer
      # ↑ Converts Java object → JSON bytes

    consumer:
      group-id: detection-group
      auto-offset-reset: earliest
      key-deserializer: org.apache.kafka.common.serialization.StringDeserializer
      value-deserializer: org.springframework.kafka.support.serializer.JsonDeserializer
      # ↑ Converts JSON bytes → Java object

      properties:
        spring.json.trusted.packages: "com.example.kafka.dto"
        # ↑ Only trust our own DTO package (security best practice)
        # Use "*" if producer and consumer are in different services with different package names
```

---

### 🔷 Step 3: JSON Producer Service

**File:** `src/main/java/com/example/kafka/producer/EventProducerService.java`

```java
package com.example.kafka.producer;

import com.example.kafka.dto.CheckResultEvent;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.kafka.core.KafkaTemplate;
import org.springframework.stereotype.Service;

@Service
@RequiredArgsConstructor
@Slf4j
public class EventProducerService {

    // KafkaTemplate<String, CheckResultEvent>
    // Key type = String
    // Value type = CheckResultEvent (will be serialized to JSON automatically)
    private final KafkaTemplate<String, CheckResultEvent> kafkaTemplate;

    private static final String TOPIC = "check.results";

    /**
     * Publishes a CheckResultEvent to the check.results topic.
     * The JsonSerializer converts the object to JSON bytes automatically.
     *
     * Example JSON sent to Kafka:
     * {
     *   "serviceId": 1,
     *   "serviceName": "Payment API",
     *   "url": "https://api.payment.com/health",
     *   "success": false,
     *   "statusCode": 503,
     *   "responseTimeMs": 4532,
     *   "checkedAt": "2024-01-15T10:30:00Z"
     * }
     */
    public void publishCheckResult(CheckResultEvent event) {
        // Using serviceId as the key ensures all events for the same service
        // go to the same partition (preserving order per service)
        String key = String.valueOf(event.getServiceId());

        log.info("Publishing CheckResultEvent for service [{}] - success={}, statusCode={}",
                event.getServiceName(), event.isSuccess(), event.getStatusCode());

        kafkaTemplate.send(TOPIC, key, event);
    }
}
```

---

### 🔷 Step 4: REST Controller to Trigger Event

**File:** `src/main/java/com/example/kafka/producer/EventProducerController.java`

```java
package com.example.kafka.producer;

import com.example.kafka.dto.CheckResultEvent;
import lombok.RequiredArgsConstructor;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.time.Instant;

@RestController
@RequestMapping("/api/events")
@RequiredArgsConstructor
public class EventProducerController {

    private final EventProducerService eventProducerService;

    /**
     * POST /api/events/check-result
     *
     * Accepts a CheckResultEvent JSON body and publishes to Kafka.
     *
     * Example curl:
     * curl -X POST http://localhost:8080/api/events/check-result \
     *   -H "Content-Type: application/json" \
     *   -d '{
     *     "serviceId": 1,
     *     "serviceName": "Payment API",
     *     "url": "https://api.payment.com/health",
     *     "success": false,
     *     "statusCode": 503,
     *     "responseTimeMs": 4500,
     *     "checkedAt": "2024-01-15T10:30:00Z"
     *   }'
     */
    @PostMapping("/check-result")
    public ResponseEntity<String> publishCheckResult(@RequestBody CheckResultEvent event) {
        // Set timestamp if not provided
        if (event.getCheckedAt() == null) {
            event.setCheckedAt(Instant.now().toString());
        }

        eventProducerService.publishCheckResult(event);
        return ResponseEntity.ok("CheckResultEvent published for service: " + event.getServiceName());
    }

    /**
     * POST /api/events/simulate-failure/{serviceId}
     *
     * Simulates a failed check — useful for testing incident creation.
     */
    @PostMapping("/simulate-failure/{serviceId}")
    public ResponseEntity<String> simulateFailure(@PathVariable Long serviceId) {
        CheckResultEvent event = CheckResultEvent.builder()
                .serviceId(serviceId)
                .serviceName("Test Service " + serviceId)
                .url("https://example.com/health")
                .success(false)
                .statusCode(503)
                .responseTimeMs(5000L)
                .checkedAt(Instant.now().toString())
                .build();

        eventProducerService.publishCheckResult(event);
        return ResponseEntity.ok("Simulated failure published for service: " + serviceId);
    }
}
```

---

### 🔷 Step 5: JSON Consumer Service

**File:** `src/main/java/com/example/kafka/consumer/EventConsumerService.java`

```java
package com.example.kafka.consumer;

import com.example.kafka.dto.CheckResultEvent;
import lombok.extern.slf4j.Slf4j;
import org.springframework.kafka.annotation.KafkaListener;
import org.springframework.stereotype.Service;

@Service
@Slf4j
public class EventConsumerService {

    /**
     * Listens to the check.results topic.
     * Spring + JsonDeserializer automatically converts JSON bytes → CheckResultEvent.
     *
     * The parameter type MUST match what was published:
     * Producer sends: CheckResultEvent
     * Consumer receives: CheckResultEvent  ← Same type
     */
    @KafkaListener(
        topics = "check.results",
        groupId = "detection-group",
        containerFactory = "kafkaListenerContainerFactory"
        // ↑ containerFactory is auto-configured, you usually don't need to specify it
        // unless you have multiple custom container factories
    )
    public void consumeCheckResult(CheckResultEvent event) {
        log.info("📨 Received CheckResultEvent:");
        log.info("   Service   : {} (ID: {})", event.getServiceName(), event.getServiceId());
        log.info("   URL       : {}", event.getUrl());
        log.info("   Success   : {}", event.isSuccess());
        log.info("   Status    : {}", event.getStatusCode());
        log.info("   Response  : {}ms", event.getResponseTimeMs());
        log.info("   Checked At: {}", event.getCheckedAt());

        // Route to appropriate handler
        if (event.isSuccess()) {
            handleSuccessResult(event);
        } else {
            handleFailureResult(event);
        }
    }

    private void handleSuccessResult(CheckResultEvent event) {
        log.info("✅ Service [{}] is healthy", event.getServiceName());
        // Check if there are 3 consecutive successes → auto-resolve incident
    }

    private void handleFailureResult(CheckResultEvent event) {
        log.warn("❌ Service [{}] FAILED! Status: {}, Time: {}ms",
                event.getServiceName(), event.getStatusCode(), event.getResponseTimeMs());
        // Check if there are 3 consecutive failures → create incident
    }
}
```

---

### 🔷 JSON Flow Visualization

```
Producer Side (EventProducerService):
CheckResultEvent {
  serviceId=1,
  serviceName="Payment API",
  success=false,
  statusCode=503
}
        ↓ JsonSerializer
{
  "serviceId": 1,
  "serviceName": "Payment API",
  "success": false,
  "statusCode": 503,
  ...
}  (JSON bytes written to Kafka)

─────────────────────────── Kafka Topic: check.results ───────────────────────────

Consumer Side (EventConsumerService):
{
  "serviceId": 1,
  "serviceName": "Payment API",
  "success": false,
  "statusCode": 503,
  ...
}  (JSON bytes read from Kafka)
        ↓ JsonDeserializer
CheckResultEvent {
  serviceId=1,
  serviceName="Payment API",
  success=false,
  statusCode=503
}
```


---

## 9. Real Project Example: Monitoring + Detection Service

### 🔷 Architecture Overview

This is your actual project use case. Let's map it completely.

```
┌─────────────────────────────────────────────────────────────────────┐
│                        SYSTEM ARCHITECTURE                          │
│                                                                     │
│  ┌───────────────────┐                                              │
│  │  Monitoring       │  Every 60 seconds:                          │
│  │  Service          │  → Checks URL via HTTP                      │
│  │                   │  → Creates CheckResultEvent                  │
│  │  @Scheduled       │  → Publishes to Kafka                        │
│  │  (every 60s)      │                                              │
│  └────────┬──────────┘                                              │
│           │ publishes                                               │
│           ▼                                                         │
│  ┌───────────────────┐                                              │
│  │  Kafka Topic      │                                              │
│  │  check.results    │  Stores all check result events              │
│  │  (3 partitions)   │  Partitioned by serviceId (key)              │
│  └────────┬──────────┘                                              │
│           │ consumes                                                │
│           ▼                                                         │
│  ┌───────────────────┐                                              │
│  │  Detection        │  On each event:                             │
│  │  Service          │  → Gets last 3 results for this service     │
│  │                   │  → All 3 failed? → Create Incident          │
│  │  @KafkaListener   │  → All 3 success? → Resolve Incident        │
│  └────────┬──────────┘                                              │
│           │ calls                                                   │
│           ▼                                                         │
│  ┌───────────────────┐                                              │
│  │  Incident         │  Creates / Resolves incidents                │
│  │  Service          │  Sends alerts (email, Slack, PagerDuty)     │
│  └───────────────────┘                                              │
└─────────────────────────────────────────────────────────────────────┘
```

---

### 🔷 Monitoring Service Code

**File:** `monitoring-service/src/main/java/com/monitor/scheduler/UrlCheckerScheduler.java`

```java
package com.monitor.scheduler;

import com.monitor.dto.CheckResultEvent;
import com.monitor.producer.CheckResultProducer;
import com.monitor.repository.MonitoredServiceRepository;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.stereotype.Component;
import org.springframework.web.client.RestTemplate;

import java.time.Instant;

@Component
@RequiredArgsConstructor
@Slf4j
public class UrlCheckerScheduler {

    private final MonitoredServiceRepository serviceRepo;
    private final CheckResultProducer checkResultProducer;
    private final RestTemplate restTemplate;

    /**
     * Runs every 60 seconds.
     * For each monitored service, performs an HTTP GET and publishes the result.
     */
    @Scheduled(fixedDelay = 60_000)  // 60 seconds in milliseconds
    public void checkAllUrls() {
        log.info("⏰ Starting URL check cycle...");

        serviceRepo.findAllActive().forEach(service -> {
            CheckResultEvent event = performCheck(service.getId(),
                    service.getName(), service.getUrl());
            checkResultProducer.publish(event);
        });
    }

    private CheckResultEvent performCheck(Long serviceId, String serviceName, String url) {
        long startTime = System.currentTimeMillis();

        try {
            // Perform the HTTP GET request
            var response = restTemplate.getForEntity(url, String.class);
            long responseTime = System.currentTimeMillis() - startTime;

            boolean isSuccess = response.getStatusCode().is2xxSuccessful();

            return CheckResultEvent.builder()
                    .serviceId(serviceId)
                    .serviceName(serviceName)
                    .url(url)
                    .success(isSuccess)
                    .statusCode(response.getStatusCode().value())
                    .responseTimeMs(responseTime)
                    .checkedAt(Instant.now().toString())
                    .build();

        } catch (Exception ex) {
            long responseTime = System.currentTimeMillis() - startTime;
            log.warn("Check FAILED for [{}]: {}", url, ex.getMessage());

            return CheckResultEvent.builder()
                    .serviceId(serviceId)
                    .serviceName(serviceName)
                    .url(url)
                    .success(false)
                    .statusCode(0)  // 0 = could not connect
                    .responseTimeMs(responseTime)
                    .checkedAt(Instant.now().toString())
                    .build();
        }
    }
}
```

---

### 🔷 Detection Service Code

**File:** `detection-service/src/main/java/com/detect/consumer/DetectionConsumer.java`

```java
package com.detect.consumer;

import com.detect.dto.CheckResultEvent;
import com.detect.service.IncidentService;
import com.detect.store.ResultStore;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.kafka.annotation.KafkaListener;
import org.springframework.stereotype.Component;

import java.util.List;

@Component
@RequiredArgsConstructor
@Slf4j
public class DetectionConsumer {

    private final ResultStore resultStore;        // Stores recent results in memory or Redis
    private final IncidentService incidentService; // Creates/resolves incidents

    @KafkaListener(topics = "check.results", groupId = "detection-group")
    public void onCheckResult(CheckResultEvent event) {
        log.info("🔍 Processing check result for service [{}]: success={}",
                event.getServiceName(), event.isSuccess());

        // Store this result (keep only last N results per service)
        resultStore.add(event.getServiceId(), event);

        // Get the last 3 results for this service
        List<CheckResultEvent> recentResults = resultStore.getRecent(event.getServiceId(), 3);

        // Only evaluate when we have at least 3 results
        if (recentResults.size() < 3) {
            log.info("Not enough data yet for service [{}]. Have {}/3 results",
                    event.getServiceName(), recentResults.size());
            return;
        }

        // Check if all 3 consecutive results are failures
        boolean allFailed = recentResults.stream().noneMatch(CheckResultEvent::isSuccess);

        // Check if all 3 consecutive results are successes
        boolean allSucceeded = recentResults.stream().allMatch(CheckResultEvent::isSuccess);

        if (allFailed) {
            log.warn("🚨 Service [{}] failed 3 consecutive times! Creating incident...",
                    event.getServiceName());
            incidentService.createIncident(event);

        } else if (allSucceeded) {
            log.info("✅ Service [{}] recovered (3 consecutive successes). Resolving incident...",
                    event.getServiceName());
            incidentService.resolveIncident(event.getServiceId());
        }
    }
}
```

---

### 🔷 Decision Logic Visualization

```
Event Stream for Service "Payment API" (serviceId=1):

Time →  10:00   10:01   10:02   10:03   10:04   10:05
        FAIL    FAIL    FAIL    SUCCESS SUCCESS SUCCESS

At 10:02: Last 3 = [FAIL, FAIL, FAIL]
          allFailed = true
          → 🚨 CREATE INCIDENT

At 10:05: Last 3 = [SUCCESS, SUCCESS, SUCCESS]
          allSucceeded = true
          → ✅ RESOLVE INCIDENT (auto-resolve)
```

---

## 10. Kafka Topic Creation

### 🔷 Method 1: CLI (Command Line)

```bash
# Create topic manually
bin/kafka-topics.sh \
  --create \
  --topic check.results \
  --bootstrap-server localhost:9092 \
  --partitions 3 \
  --replication-factor 1

# Arguments explained:
# --topic check.results     → Name of the topic
# --partitions 3            → Split into 3 partitions (for parallel consumption)
# --replication-factor 1    → Keep 1 copy of data (use 3 in production!)
#                             replication-factor cannot exceed number of brokers
#                             (1 broker locally → max replication-factor = 1)
```

---

### 🔷 Method 2: Spring Boot NewTopic Bean (Recommended)

This is the **recommended approach** — topic gets created automatically when app starts.

**File:** `src/main/java/com/example/kafka/config/KafkaTopicConfig.java`

```java
package com.example.kafka.config;

import org.apache.kafka.clients.admin.NewTopic;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.kafka.config.TopicBuilder;

@Configuration
public class KafkaTopicConfig {

    /**
     * Defines the "check.results" topic.
     * Spring Boot auto-creates this topic on startup if it doesn't exist.
     * If it already exists, Spring checks but does NOT recreate it.
     *
     * TopicBuilder is a fluent API from spring-kafka — cleaner than new NewTopic(...)
     */
    @Bean
    public NewTopic checkResultsTopic() {
        return TopicBuilder
                .name("check.results")          // Topic name
                .partitions(3)                  // Number of partitions
                .replicas(1)                    // Replication factor (use 3 in prod)
                .build();
    }

    /**
     * You can define multiple topics in the same config class.
     * Just add more @Bean methods.
     */
    @Bean
    public NewTopic incidentsTopic() {
        return TopicBuilder
                .name("incidents")
                .partitions(1)
                .replicas(1)
                .build();
    }

    /**
     * Dead Letter Topic — where failed messages land.
     * Naming convention: original-topic-name.DLT
     */
    @Bean
    public NewTopic checkResultsDlt() {
        return TopicBuilder
                .name("check.results.DLT")
                .partitions(1)
                .replicas(1)
                .build();
    }
}
```

**Why use `NewTopic` bean instead of CLI?**

| CLI | NewTopic Bean |
|-----|--------------|
| Must remember to run CLI command | Auto-created on app startup |
| Easy to forget in new environment | Works in all environments automatically |
| Manual step in deployment | Fully automated |
| Need Kafka access to run | Handled by Spring admin client |

---

### 🔷 Partitions & Replication Factor Guide

| Setting | Dev (Local) | Staging | Production |
|---------|------------|---------|-----------|
| `partitions` | 1–3 | 3–6 | 6–12+ (based on throughput) |
| `replication-factor` | 1 | 2–3 | 3 (minimum) |
| `brokers` | 1 | 2–3 | 3–5+ |

> **Rule:** `replication-factor` must be ≤ number of brokers in the cluster.


---

## 11. Running Kafka Locally

### 🔷 Option A: KRaft Mode (Recommended — No Zookeeper)

**Step 1: Download Kafka**

```bash
# Download Kafka 3.7.x (or latest)
wget https://downloads.apache.org/kafka/3.7.0/kafka_2.13-3.7.0.tgz

# Extract it
tar -xzf kafka_2.13-3.7.0.tgz

# Enter the directory
cd kafka_2.13-3.7.0
```

**Step 2: Generate a Cluster UUID**

```bash
# Generate a unique ID for your Kafka cluster (one-time setup)
KAFKA_CLUSTER_ID="$(bin/kafka-storage.sh random-uuid)"
echo "Cluster UUID: $KAFKA_CLUSTER_ID"
```

**Step 3: Format Storage**

```bash
# Format the log directory with the cluster UUID (one-time setup)
bin/kafka-storage.sh format \
  -t $KAFKA_CLUSTER_ID \
  -c config/kraft/server.properties

# Expected output:
# Formatting /tmp/kraft-combined-logs with metadata.version ...
```

**Step 4: Start Kafka in KRaft Mode**

```bash
# Start Kafka (runs in foreground — keep terminal open)
bin/kafka-server-start.sh config/kraft/server.properties

# To run in background:
bin/kafka-server-start.sh -daemon config/kraft/server.properties

# Verify it started (look for this line in logs):
# [KafkaServer id=1] started
```

---

### 🔷 Option B: Docker (Easiest!)

**docker-compose.yml**

```yaml
version: '3'
services:
  kafka:
    image: confluentinc/cp-kafka:7.6.0
    hostname: kafka
    ports:
      - "9092:9092"
    environment:
      KAFKA_NODE_ID: 1
      KAFKA_LISTENER_SECURITY_PROTOCOL_MAP: CONTROLLER:PLAINTEXT,PLAINTEXT:PLAINTEXT
      KAFKA_ADVERTISED_LISTENERS: PLAINTEXT://localhost:9092
      KAFKA_LISTENERS: PLAINTEXT://0.0.0.0:9092,CONTROLLER://localhost:9093
      KAFKA_INTER_BROKER_LISTENER_NAME: PLAINTEXT
      KAFKA_CONTROLLER_LISTENER_NAMES: CONTROLLER
      KAFKA_CONTROLLER_QUORUM_VOTERS: 1@localhost:9093
      KAFKA_PROCESS_ROLES: broker,controller
      KAFKA_OFFSETS_TOPIC_REPLICATION_FACTOR: 1
      KAFKA_AUTO_CREATE_TOPICS_ENABLE: "true"
      CLUSTER_ID: "MkU3OEVBNTcwNTJENDM2Qk"
```

```bash
# Start Kafka with Docker
docker-compose up -d

# Check if running
docker-compose ps

# Stop Kafka
docker-compose down
```

---

### 🔷 Useful Kafka CLI Commands

```bash
# ─────────────────────────────────────────
# TOPIC MANAGEMENT
# ─────────────────────────────────────────

# List all topics
bin/kafka-topics.sh --list --bootstrap-server localhost:9092

# Create a topic
bin/kafka-topics.sh --create \
  --topic check.results \
  --bootstrap-server localhost:9092 \
  --partitions 3 \
  --replication-factor 1

# Describe a topic (see partitions, replication, leaders)
bin/kafka-topics.sh --describe \
  --topic check.results \
  --bootstrap-server localhost:9092

# Delete a topic
bin/kafka-topics.sh --delete \
  --topic check.results \
  --bootstrap-server localhost:9092


# ─────────────────────────────────────────
# PRODUCER — Send test messages from terminal
# ─────────────────────────────────────────

# Start a console producer (type messages, press Enter to send)
bin/kafka-console-producer.sh \
  --topic check.results \
  --bootstrap-server localhost:9092

# Type messages:
# > Hello from terminal!
# > This is message 2
# Press Ctrl+C to stop


# ─────────────────────────────────────────
# CONSUMER — Read messages from terminal
# ─────────────────────────────────────────

# Read NEW messages only (from now onwards)
bin/kafka-console-consumer.sh \
  --topic check.results \
  --bootstrap-server localhost:9092

# Read ALL messages (from the very beginning)
bin/kafka-console-consumer.sh \
  --topic check.results \
  --from-beginning \
  --bootstrap-server localhost:9092

# Read with key displayed
bin/kafka-console-consumer.sh \
  --topic check.results \
  --from-beginning \
  --property print.key=true \
  --property key.separator=" => " \
  --bootstrap-server localhost:9092


# ─────────────────────────────────────────
# CONSUMER GROUPS
# ─────────────────────────────────────────

# List consumer groups
bin/kafka-consumer-groups.sh \
  --list \
  --bootstrap-server localhost:9092

# Describe consumer group (shows lag, offset, partition assignment)
bin/kafka-consumer-groups.sh \
  --describe \
  --group detection-group \
  --bootstrap-server localhost:9092

# Reset offset for a consumer group (useful for replaying events)
bin/kafka-consumer-groups.sh \
  --reset-offsets \
  --to-earliest \
  --topic check.results \
  --group detection-group \
  --execute \
  --bootstrap-server localhost:9092
```

---

## 12. Common Errors and Fixes

### ❌ Error 1: KafkaTemplate Bean Not Found

**Error:**
```
Parameter 0 of constructor required a bean of type 
'org.springframework.kafka.core.KafkaTemplate' that could not be found.
```

**Cause:** `spring-kafka` dependency is missing, or `bootstrap-servers` is not configured.

**Fix:**
```xml
<!-- Add to pom.xml -->
<dependency>
    <groupId>org.springframework.kafka</groupId>
    <artifactId>spring-kafka</artifactId>
</dependency>
```

```yaml
# Add to application.yml
spring:
  kafka:
    bootstrap-servers: localhost:9092
```

---

### ❌ Error 2: Connection Refused localhost:9092

**Error:**
```
org.apache.kafka.common.errors.TimeoutException: 
Failed to update metadata after 60000 ms.
Connection refused: localhost/127.0.0.1:9092
```

**Cause:** Kafka server is not running.

**Fix:**
```bash
# Check if Kafka is running
ps aux | grep kafka

# Start Kafka
bin/kafka-server-start.sh config/kraft/server.properties

# Or with Docker
docker-compose up -d

# Verify port is open
nc -zv localhost 9092
```

---

### ❌ Error 3: Topic Does Not Exist

**Error:**
```
WARN [Consumer clientId=...] Error while fetching metadata...
LEADER_NOT_AVAILABLE for partition check.results-0
```

**Cause:** Topic hasn't been created yet.

**Fix:**
```bash
# Create the topic manually
bin/kafka-topics.sh --create \
  --topic check.results \
  --bootstrap-server localhost:9092 \
  --partitions 3 \
  --replication-factor 1
```

Or use the `NewTopic` bean in Spring Boot:
```yaml
# application.yml — enable auto topic creation
spring:
  kafka:
    admin:
      auto-create: true
```

---

### ❌ Error 4: Deserialization Error

**Error:**
```
org.springframework.kafka.listener.ListenerExecutionFailedException:
Caused by: org.apache.kafka.common.errors.SerializationException:
Can't deserialize data from topic [check.results]
```

**Cause:** Producer sent JSON but consumer is using `StringDeserializer`, or trusted packages not configured.

**Fix:**
```yaml
spring:
  kafka:
    consumer:
      value-deserializer: org.springframework.kafka.support.serializer.JsonDeserializer
      properties:
        spring.json.trusted.packages: "*"
        # Or be specific:
        # spring.json.trusted.packages: "com.example.kafka.dto"
```

Also ensure the DTO class has a **no-arg constructor** (Lombok `@NoArgsConstructor` handles this):
```java
@Data
@NoArgsConstructor   // ← REQUIRED for Jackson deserialization
@AllArgsConstructor
public class CheckResultEvent { ... }
```

---

### ❌ Error 5: Consumer Not Receiving Messages

**Symptoms:** Producer sends messages, consumer is running but no messages appear.

**Common causes and fixes:**

```bash
# Check 1: Is consumer in same group as another consumer that's reading?
# Check consumer group lag:
bin/kafka-consumer-groups.sh \
  --describe \
  --group detection-group \
  --bootstrap-server localhost:9092

# Check 2: Is consumer reading from a different partition?
# Check 3: Did consumer miss messages due to auto-offset-reset: latest?
```

```yaml
# Fix: Change to 'earliest' to read from beginning
spring:
  kafka:
    consumer:
      auto-offset-reset: earliest
```

```java
// Check 4: Is @KafkaListener annotation present and correct?
@KafkaListener(
    topics = "check.results",   // ← Must match EXACTLY the producer's topic name
    groupId = "detection-group" // ← Must be set
)
public void consume(CheckResultEvent event) { ... }
```

---

### ❌ Error 6: Wrong groupId Issue

**Symptom:** Consumer is getting only some messages, not all of them.

**Cause:** Multiple instances of your app are running with the same groupId — messages are being split between instances (which is correct behavior for load balancing, but confusing in dev).

**Fix:**
```bash
# Check how many consumers are in the group
bin/kafka-consumer-groups.sh \
  --describe \
  --group detection-group \
  --bootstrap-server localhost:9092

# Kill duplicate consumers, or run only one instance during development
```

---

### ❌ Error 7: Kafka Server Not Started / Already Running

**Error on start:**
```
ERROR [KafkaServer id=1] Fatal error during KafkaServer startup.
java.io.IOException: Can't lock file: /tmp/kraft-combined-logs/.lock
```

**Cause:** Kafka is already running, or previous process didn't clean up.

**Fix:**
```bash
# Kill existing Kafka processes
pkill -f kafka

# Or find and kill specific process
ps aux | grep kafka
kill -9 <PID>

# Clear the lock file
rm /tmp/kraft-combined-logs/.lock

# Restart
bin/kafka-server-start.sh config/kraft/server.properties
```

---

### ❌ Error 8: No Readable meta.properties Found

**Error:**
```
ERROR Exiting Kafka due to fatal exception during startup
kafka.common.InconsistentClusterIdException: 
The Cluster ID ... doesn't match stored clusterId ... 
in meta.properties.
```

**Cause:** You formatted storage with one cluster UUID, but logs directory still has old metadata from a different UUID.

**Fix:**
```bash
# Delete the old log directory (loses all data — only do in dev!)
rm -rf /tmp/kraft-combined-logs

# Re-format storage with new UUID
KAFKA_CLUSTER_ID="$(bin/kafka-storage.sh random-uuid)"
bin/kafka-storage.sh format \
  -t $KAFKA_CLUSTER_ID \
  -c config/kraft/server.properties

# Start fresh
bin/kafka-server-start.sh config/kraft/server.properties
```

---

## 13. Best Practices

### ✅ 1. Use Meaningful, Consistent Topic Names

```
❌ Bad:  "topic1", "data", "messages", "kafka-topic"
✅ Good: "order.placed", "payment.completed", "check.results", "user.registered"

Convention: <domain>.<event-name>
Examples:
  monitoring.check.results
  inventory.stock.updated
  notification.email.sent
```

---

### ✅ 2. Always Use DTO/Event Classes for JSON Messages

```java
// ❌ Bad — sending raw JSON string (error-prone, hard to maintain)
kafkaTemplate.send("check.results", "{\"serviceId\":1,\"success\":false}");

// ✅ Good — using a proper DTO class
CheckResultEvent event = CheckResultEvent.builder()
    .serviceId(1L)
    .success(false)
    .build();
kafkaTemplate.send("check.results", event);
// JsonSerializer handles the conversion automatically
```

---

### ✅ 3. Never Put Business Logic Inside Controller

```java
// ❌ Bad — business logic in controller
@PostMapping("/publish")
public ResponseEntity<String> publish(@RequestBody CheckResultEvent event) {
    // WRONG: processing in controller
    if (event.getStatusCode() == 503) {
        kafkaTemplate.send("check.results", event);
    }
    return ResponseEntity.ok("done");
}

// ✅ Good — controller just delegates to service
@PostMapping("/publish")
public ResponseEntity<String> publish(@RequestBody CheckResultEvent event) {
    monitoringService.processAndPublish(event);
    return ResponseEntity.ok("done");
}
// Business logic lives in MonitoringService
```

---

### ✅ 4. Use Retry Handling

```java
@KafkaListener(topics = "check.results", groupId = "detection-group")
@RetryableTopic(
    attempts = "3",                            // Retry up to 3 times
    backoff = @Backoff(delay = 1000, multiplier = 2.0),
    // Retry delays: 1s, 2s, 4s
    dltTopicSuffix = ".DLT"
    // After all retries fail, send to check.results.DLT
)
public void consume(CheckResultEvent event) {
    // If this throws an exception, Spring retries automatically
    detectionService.process(event);
}
```

---

### ✅ 5. Use Dead Letter Topic (DLT)

```java
// When consumer fails after all retries, message goes to DLT
// Create a separate listener for DLT to handle/alert/log failed messages

@KafkaListener(topics = "check.results.DLT", groupId = "dlt-handler-group")
public void handleDeadLetter(CheckResultEvent event) {
    log.error("💀 Message in DLT — could not process after retries: {}", event);
    // Save to database for manual review
    // Send alert to engineering team
    deadLetterRepository.save(toEntity(event));
}
```

---

### ✅ 6. Use Proper Logging

```java
// ❌ Bad
System.out.println("Got message: " + event);

// ✅ Good
@Slf4j  // Lombok annotation
public class ConsumerService {

    @KafkaListener(...)
    public void consume(CheckResultEvent event) {
        log.info("Received check result for service [{}]: success={}",
                 event.getServiceName(), event.isSuccess());
        // log.info uses {} placeholders — no string concatenation (performance)
        // log.debug for verbose info
        // log.warn for non-critical issues
        // log.error for failures
    }
}
```

---

### ✅ 7. Keep Producer and Consumer Configs Clean

```java
// ❌ Bad — hardcoding topic names everywhere
kafkaTemplate.send("check.results", event);  // in 5 different places
```

```java
// ✅ Good — use constants class
public class KafkaTopics {
    public static final String CHECK_RESULTS = "check.results";
    public static final String CHECK_RESULTS_DLT = "check.results.DLT";
    public static final String INCIDENTS = "incidents";

    private KafkaTopics() {} // Prevent instantiation
}

// Usage:
kafkaTemplate.send(KafkaTopics.CHECK_RESULTS, event);
```

---

### ✅ 8. Use Idempotency Where Needed

Idempotency = sending the same message multiple times has the same effect as sending once.

```java
// Problem: Network retry might cause duplicate messages
// Solution: Use idempotent producer

// application.yml
spring:
  kafka:
    producer:
      properties:
        enable.idempotence: true   # Prevents duplicate messages from producer
        max.in.flight.requests.per.connection: 5

// On consumer side: use a processed-message cache
@KafkaListener(topics = "check.results", groupId = "detection-group")
public void consume(CheckResultEvent event) {
    String messageId = event.getServiceId() + "_" + event.getCheckedAt();

    // Check if already processed (use Redis or in-memory cache)
    if (processedMessageCache.contains(messageId)) {
        log.info("Duplicate message ignored: {}", messageId);
        return;
    }

    processedMessageCache.add(messageId);
    detectionService.process(event);
}
```


---

## 14. Interview Questions

### 🎯 Beginner Level (Q1–Q10)

---

**Q1. What is Apache Kafka?**

> Apache Kafka is an open-source **distributed event streaming platform** used for high-performance, real-time data pipelines and event-driven systems. It stores messages as an ordered, fault-tolerant log and allows multiple producers to publish and multiple consumers to subscribe.
>
> **Simple answer:** Kafka is a messaging system that lets services communicate asynchronously by publishing and consuming events from named "topics."

---

**Q2. What is a Topic in Kafka?**

> A **Topic** is a named category or channel where messages are written and read. It's like a queue or a folder with a name. Producers write to a topic; consumers read from it.
>
> Example: `check.results`, `order.placed`, `user.registered`

---

**Q3. What is a Partition?**

> A **Partition** is a subdivision of a topic. A topic can have multiple partitions, which allows **parallel processing**. Each partition is an ordered, immutable log of messages. Messages within a partition are strictly ordered by offset.
>
> **Real example:** Topic `check.results` with 3 partitions → 3 consumers can read simultaneously → 3x throughput.

---

**Q4. What is an Offset?**

> An **Offset** is a unique sequential number assigned to each message within a partition. It starts at 0 and increases by 1. Kafka uses offsets to track which messages a consumer group has already read.
>
> **Analogy:** Like a page number in a book. Kafka remembers "you read up to page 50" so next time you start from page 51.

---

**Q5. What is a Consumer Group?**

> A **Consumer Group** is a group of consumers identified by a `groupId`. When multiple consumers share the same groupId, Kafka distributes partitions among them (load balancing). When consumers have different groupIds, each group receives all messages independently.
>
> **Same groupId:** Load balancing (each message processed by one consumer)
> **Different groupId:** Broadcast (each consumer group processes all messages)

---

**Q6. What is a Kafka Broker?**

> A **Broker** is a single Kafka server. It stores topic partitions and serves read/write requests from producers and consumers. Multiple brokers form a Kafka **Cluster**. One broker acts as the **leader** for each partition.

---

**Q7. What is a Producer in Kafka?**

> A **Producer** is a client application that publishes (sends) messages to a Kafka topic. In Spring Boot, `KafkaTemplate` is the producer abstraction. You call `kafkaTemplate.send(topic, message)` to publish.

---

**Q8. What is a Consumer in Kafka?**

> A **Consumer** is a client application that subscribes to (reads) messages from a Kafka topic. In Spring Boot, the `@KafkaListener` annotation marks a method as a consumer. It continuously polls Kafka and processes messages.

---

**Q9. What is a Kafka Cluster?**

> A **Kafka Cluster** is a group of Kafka brokers working together. Clusters provide fault tolerance (if one broker fails, others take over), scalability (add more brokers = more capacity), and high availability.

---

**Q10. What is KRaft mode?**

> **KRaft** (Kafka + Raft) is Kafka's built-in metadata management system introduced in Kafka 2.8. It eliminates the need for Apache Zookeeper. Kafka now manages its own cluster metadata using the Raft consensus algorithm, making setup simpler and performance better.

---

### 🎯 Intermediate Level (Q11–Q20)

---

**Q11. What is KafkaTemplate in Spring Boot?**

> `KafkaTemplate<K, V>` is the primary Spring abstraction for sending messages to Kafka. It wraps the underlying Kafka producer client and provides convenience methods like `send(topic, value)` and `send(topic, key, value)`. It's auto-configured by Spring Boot based on `application.yml` settings.

---

**Q12. What does @KafkaListener do?**

> `@KafkaListener` marks a method as a Kafka message consumer. Spring creates a `MessageListenerContainer` that runs a background thread to continuously poll the specified topic. When messages arrive, Spring deserializes them and invokes the annotated method. Offset is committed after the method returns successfully.

---

**Q13. What happens if a consumer is down?**

> Kafka retains messages on disk (for the configured retention period, default 7 days). When the consumer comes back online, it reads from its **last committed offset**, processing all messages it missed during the downtime. This is called catching up on **consumer lag**. No messages are lost.

---

**Q14. How does Kafka ensure message ordering?**

> Kafka guarantees ordering **within a partition** only. If you need all messages for a specific entity (e.g., all events for serviceId=1) to be ordered, use that entity's ID as the **message key**. Kafka routes all messages with the same key to the same partition, ensuring they are always processed in order.

---

**Q15. What is a Replication Factor?**

> **Replication factor** is the number of copies of each partition's data across brokers.
> - `replication-factor=1` → Only 1 copy. If that broker dies, data is lost.
> - `replication-factor=3` → 3 copies across 3 brokers. Can survive 2 broker failures.
> - **Production recommendation:** Use replication-factor=3 minimum.

---

**Q16. What is a Dead Letter Topic (DLT)?**

> A **Dead Letter Topic** is a separate Kafka topic where messages are sent when a consumer fails to process them after all retry attempts. Instead of losing the message, it lands in the DLT for manual review, alerting, or reprocessing. Convention: `original-topic.DLT`.
>
> Example: `check.results.DLT` gets messages that `check.results` consumers couldn't handle.

---

**Q17. What is auto.offset.reset?**

> `auto.offset.reset` tells the consumer what to do when there's no committed offset for its group (first time connecting, or offset expired):
> - `earliest` → Start from the very first message in the topic
> - `latest` → Start only from new messages (ignore old ones)
> - `none` → Throw an exception

---

**Q18. Difference between Kafka and RabbitMQ?**

| Feature | Kafka | RabbitMQ |
|---------|-------|----------|
| **Type** | Event streaming / log | Traditional message queue |
| **Message retention** | Stored on disk (days/weeks) | Deleted after consumption |
| **Throughput** | Millions of messages/sec | Thousands/sec |
| **Consumer model** | Pull-based (consumer polls) | Push-based (broker pushes) |
| **Message replay** | Yes — re-read from any offset | No — once consumed, gone |
| **Ordering** | Guaranteed within partition | Queue-level ordering |
| **Use case** | Event sourcing, data pipelines | Task queues, RPC patterns |
| **Complexity** | Higher setup complexity | Simpler for basic use cases |

---

**Q19. Kafka vs REST API — When to use which?**

| Use Case | Use REST | Use Kafka |
|----------|---------|---------|
| Get user profile | ✅ | ❌ |
| User login | ✅ | ❌ |
| Order placed → notify 5 services | ❌ | ✅ |
| Real-time analytics pipeline | ❌ | ✅ |
| File upload | ✅ | ❌ |
| Audit log of all events | ❌ | ✅ |
| Microservice-to-microservice event | ❌ | ✅ |
| Simple CRUD query | ✅ | ❌ |

---

**Q20. How does Kafka handle scalability?**

> Kafka scales through:
> 1. **Partitions** — More partitions → more parallelism → higher throughput
> 2. **Brokers** — Add more Kafka broker servers to the cluster → distributes storage and traffic
> 3. **Consumer Groups** — Add more consumer instances → faster processing
> 4. **Horizontal scaling** — No single point of bottleneck; everything distributes

---

### 🎯 Advanced Level (Q21–Q25)

---

**Q21. What is the difference between at-most-once, at-least-once, and exactly-once delivery?**

| Delivery Mode | What It Means | Risk |
|---------------|--------------|------|
| **At-most-once** | Message sent once; may be lost | Data loss possible |
| **At-least-once** | Message retried if failed; may be duplicated | Duplicates possible |
| **Exactly-once** | Message processed exactly once, no duplicates | Hardest to implement |

> Spring Kafka default is **at-least-once**. Use idempotent producers + transactional consumers for exactly-once.

---

**Q22. What is Consumer Lag?**

> **Consumer Lag** is the difference between the latest offset in a partition and the consumer's current committed offset. High lag means the consumer is falling behind the producer.
>
> ```
> Latest offset in partition: 1000
> Consumer's committed offset: 750
> Consumer Lag = 1000 - 750 = 250 messages behind
> ```
>
> Monitor lag using:
> ```bash
> bin/kafka-consumer-groups.sh --describe --group detection-group --bootstrap-server localhost:9092
> ```

---

**Q23. How do you handle Kafka message deserialization errors?**

> Use an `ErrorHandlingDeserializer` to catch and handle bad messages gracefully:
>
> ```yaml
> spring:
>   kafka:
>     consumer:
>       value-deserializer: org.springframework.kafka.support.serializer.ErrorHandlingDeserializer
>       properties:
>         spring.deserializer.value.delegate.class: org.springframework.kafka.support.serializer.JsonDeserializer
>         spring.json.trusted.packages: "*"
> ```
>
> This prevents one bad message from crashing your entire consumer and blocking all subsequent messages.

---

**Q24. What is the Kafka Producer Acknowledgement (acks) setting?**

> The `acks` setting controls when the producer considers a message "sent":
>
> | Value | Behavior | Risk |
> |-------|----------|------|
> | `0` | Don't wait for any ack (fire and forget) | High risk of loss |
> | `1` | Wait for leader broker to write | Medium risk (if leader fails before replication) |
> | `all` or `-1` | Wait for leader + all replicas | No data loss (safest) |
>
> Production recommendation: `acks=all` with `min.insync.replicas=2`.

---

**Q25. What is a Kafka Key and why is it important?**

> A **message key** is an optional attribute you can attach to a Kafka message. Keys serve two purposes:
>
> 1. **Partitioning** — Messages with the same key always go to the same partition (Kafka uses hash(key) % numPartitions)
> 2. **Ordering** — Since same-key messages go to the same partition, and partitions are ordered, you get ordering guarantees per key
>
> ```java
> // Without key — message goes to random partition (no ordering)
> kafkaTemplate.send("check.results", event);
>
> // With key — all events for serviceId=1 go to same partition (ordered)
> kafkaTemplate.send("check.results", String.valueOf(event.getServiceId()), event);
> ```
>
> **Real example:** All check results for `serviceId=42` go to Partition 0. Detection service reads them in order — critical for determining consecutive failures!


---

## 15. Final Mini Project

A complete, working Spring Boot Kafka project from scratch — Step by step.

---

### 🔷 Phase 1: String Message Producer & Consumer

#### Complete Project Structure

```
kafka-mini-project/
├── pom.xml
└── src/main/
    ├── java/com/example/kafka/
    │   ├── KafkaMiniApplication.java
    │   ├── config/
    │   │   └── KafkaTopicConfig.java
    │   ├── producer/
    │   │   ├── MessageProducerService.java
    │   │   └── MessageController.java
    │   └── consumer/
    │       └── MessageConsumerService.java
    └── resources/
        └── application.yml
```

---

#### File 1: KafkaMiniApplication.java

```java
package com.example.kafka;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
public class KafkaMiniApplication {
    public static void main(String[] args) {
        SpringApplication.run(KafkaMiniApplication.class, args);
    }
}
```

---

#### File 2: application.yml

```yaml
spring:
  application:
    name: kafka-mini-project

  kafka:
    bootstrap-servers: localhost:9092

    producer:
      key-serializer: org.apache.kafka.common.serialization.StringSerializer
      value-serializer: org.apache.kafka.common.serialization.StringSerializer

    consumer:
      group-id: mini-project-group
      auto-offset-reset: earliest
      key-deserializer: org.apache.kafka.common.serialization.StringDeserializer
      value-deserializer: org.apache.kafka.common.serialization.StringDeserializer

server:
  port: 8080

logging:
  level:
    com.example.kafka: DEBUG
```

---

#### File 3: KafkaTopicConfig.java

```java
package com.example.kafka.config;

import org.apache.kafka.clients.admin.NewTopic;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.kafka.config.TopicBuilder;

@Configuration
public class KafkaTopicConfig {

    @Bean
    public NewTopic myTopic() {
        return TopicBuilder
                .name("my-topic")
                .partitions(3)
                .replicas(1)
                .build();
    }
}
```

---

#### File 4: MessageProducerService.java

```java
package com.example.kafka.producer;

import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.kafka.core.KafkaTemplate;
import org.springframework.stereotype.Service;

@Service
@RequiredArgsConstructor
@Slf4j
public class MessageProducerService {

    private final KafkaTemplate<String, String> kafkaTemplate;

    public void sendMessage(String message) {
        log.info("📤 Sending: {}", message);
        kafkaTemplate.send("my-topic", message)
                .thenAccept(result ->
                    log.info("✅ Sent to partition {}, offset {}",
                        result.getRecordMetadata().partition(),
                        result.getRecordMetadata().offset())
                )
                .exceptionally(ex -> {
                    log.error("❌ Failed: {}", ex.getMessage());
                    return null;
                });
    }
}
```

---

#### File 5: MessageController.java

```java
package com.example.kafka.producer;

import lombok.RequiredArgsConstructor;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/api")
@RequiredArgsConstructor
public class MessageController {

    private final MessageProducerService producerService;

    /**
     * POST /api/publish?message=YourMessage
     *
     * Test with:
     * curl -X POST "http://localhost:8080/api/publish?message=HelloKafka"
     */
    @PostMapping("/publish")
    public ResponseEntity<String> publish(@RequestParam String message) {
        producerService.sendMessage(message);
        return ResponseEntity.ok("Published: " + message);
    }
}
```

---

#### File 6: MessageConsumerService.java

```java
package com.example.kafka.consumer;

import lombok.extern.slf4j.Slf4j;
import org.springframework.kafka.annotation.KafkaListener;
import org.springframework.stereotype.Service;

@Service
@Slf4j
public class MessageConsumerService {

    @KafkaListener(topics = "my-topic", groupId = "mini-project-group")
    public void consume(String message) {
        log.info("📨 Received: {}", message);
        // Your processing logic here
    }
}
```

---

#### Testing Phase 1

```bash
# 1. Start Kafka (if not running)
bin/kafka-server-start.sh config/kraft/server.properties

# 2. Run your Spring Boot app
mvn spring-boot:run

# 3. Send a message via REST
curl -X POST "http://localhost:8080/api/publish?message=HelloKafka"

# Expected console output:
# 📤 Sending: HelloKafka
# ✅ Sent to partition 1, offset 0
# 📨 Received: HelloKafka
```

---

### 🔷 Phase 2: Upgrade to Send CheckResultEvent JSON

Now we upgrade from plain String messages to structured JSON events.

#### Changes Needed:

1. Update `application.yml` serializers to JSON
2. Add `CheckResultEvent` DTO
3. Update producer to use `KafkaTemplate<String, CheckResultEvent>`
4. Update consumer method signature to receive `CheckResultEvent`
5. Add `@NoArgsConstructor` to DTO for Jackson

---

#### Updated application.yml (JSON version)

```yaml
spring:
  application:
    name: kafka-mini-project-json

  kafka:
    bootstrap-servers: localhost:9092

    producer:
      key-serializer: org.apache.kafka.common.serialization.StringSerializer
      value-serializer: org.springframework.kafka.support.serializer.JsonSerializer

    consumer:
      group-id: mini-project-json-group
      auto-offset-reset: earliest
      key-deserializer: org.apache.kafka.common.serialization.StringDeserializer
      value-deserializer: org.springframework.kafka.support.serializer.JsonDeserializer
      properties:
        spring.json.trusted.packages: "com.example.kafka.dto"

server:
  port: 8080
```

---

#### CheckResultEvent.java (DTO)

```java
package com.example.kafka.dto;

import lombok.*;

@Data
@Builder
@NoArgsConstructor      // REQUIRED for JSON deserialization
@AllArgsConstructor
public class CheckResultEvent {
    private Long serviceId;
    private String serviceName;
    private String url;
    private boolean success;
    private int statusCode;
    private long responseTimeMs;
    private String checkedAt;
}
```

---

#### Updated KafkaTopicConfig.java

```java
package com.example.kafka.config;

import org.apache.kafka.clients.admin.NewTopic;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.kafka.config.TopicBuilder;

@Configuration
public class KafkaTopicConfig {

    @Bean
    public NewTopic checkResultsTopic() {
        return TopicBuilder
                .name("check.results")
                .partitions(3)
                .replicas(1)
                .build();
    }
}
```

---

#### Updated Producer Service

```java
package com.example.kafka.producer;

import com.example.kafka.dto.CheckResultEvent;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.kafka.core.KafkaTemplate;
import org.springframework.stereotype.Service;

import java.time.Instant;

@Service
@RequiredArgsConstructor
@Slf4j
public class EventProducerService {

    private final KafkaTemplate<String, CheckResultEvent> kafkaTemplate;

    public void publishEvent(CheckResultEvent event) {
        log.info("📤 Publishing CheckResultEvent for service [{}]", event.getServiceName());

        // Use serviceId as key for ordered partitioning
        kafkaTemplate.send("check.results",
                String.valueOf(event.getServiceId()),
                event);

        log.info("✅ Event published");
    }
}
```

---

#### Updated REST Controller

```java
package com.example.kafka.producer;

import com.example.kafka.dto.CheckResultEvent;
import lombok.RequiredArgsConstructor;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.time.Instant;

@RestController
@RequestMapping("/api")
@RequiredArgsConstructor
public class EventController {

    private final EventProducerService producerService;

    /**
     * POST /api/publish
     *
     * Test with:
     * curl -X POST http://localhost:8080/api/publish \
     *   -H "Content-Type: application/json" \
     *   -d '{
     *         "serviceId": 1,
     *         "serviceName": "Payment API",
     *         "url": "https://api.payment.com/health",
     *         "success": false,
     *         "statusCode": 503,
     *         "responseTimeMs": 4500,
     *         "checkedAt": "2024-01-15T10:30:00Z"
     *       }'
     */
    @PostMapping("/publish")
    public ResponseEntity<String> publish(@RequestBody CheckResultEvent event) {
        if (event.getCheckedAt() == null) {
            event.setCheckedAt(Instant.now().toString());
        }
        producerService.publishEvent(event);
        return ResponseEntity.ok("CheckResultEvent published for: " + event.getServiceName());
    }

    /**
     * POST /api/publish/simulate?serviceId=1&success=false
     * Quick simulation endpoint for testing
     */
    @PostMapping("/publish/simulate")
    public ResponseEntity<String> simulate(
            @RequestParam Long serviceId,
            @RequestParam(defaultValue = "false") boolean success) {

        CheckResultEvent event = CheckResultEvent.builder()
                .serviceId(serviceId)
                .serviceName("Simulated Service " + serviceId)
                .url("https://example.com/health")
                .success(success)
                .statusCode(success ? 200 : 503)
                .responseTimeMs(success ? 120L : 5000L)
                .checkedAt(Instant.now().toString())
                .build();

        producerService.publishEvent(event);

        return ResponseEntity.ok("Simulated " + (success ? "SUCCESS" : "FAILURE")
                + " for serviceId=" + serviceId);
    }
}
```

---

#### Updated Consumer Service

```java
package com.example.kafka.consumer;

import com.example.kafka.dto.CheckResultEvent;
import lombok.extern.slf4j.Slf4j;
import org.springframework.kafka.annotation.KafkaListener;
import org.springframework.stereotype.Service;

@Service
@Slf4j
public class EventConsumerService {

    @KafkaListener(topics = "check.results", groupId = "mini-project-json-group")
    public void consume(CheckResultEvent event) {
        log.info("📨 Received CheckResultEvent:");
        log.info("   Service    : {} (ID: {})", event.getServiceName(), event.getServiceId());
        log.info("   URL        : {}", event.getUrl());
        log.info("   Success    : {}", event.isSuccess());
        log.info("   Status Code: {}", event.getStatusCode());
        log.info("   Response   : {}ms", event.getResponseTimeMs());
        log.info("   Checked At : {}", event.getCheckedAt());

        if (!event.isSuccess()) {
            log.warn("🚨 ALERT: Service [{}] FAILED with status {}!",
                    event.getServiceName(), event.getStatusCode());
        }
    }
}
```

---

#### Testing Phase 2

```bash
# 1. Start Kafka
bin/kafka-server-start.sh config/kraft/server.properties

# 2. Run Spring Boot app
mvn spring-boot:run

# 3. Simulate a failure
curl -X POST "http://localhost:8080/api/publish/simulate?serviceId=1&success=false"

# Expected output in console:
# 📤 Publishing CheckResultEvent for service [Simulated Service 1]
# ✅ Event published
# 📨 Received CheckResultEvent:
#    Service    : Simulated Service 1 (ID: 1)
#    URL        : https://example.com/health
#    Success    : false
#    Status Code: 503
#    Response   : 5000ms
#    Checked At : 2024-01-15T10:30:00Z
# 🚨 ALERT: Service [Simulated Service 1] FAILED with status 503!

# 4. Simulate a recovery
curl -X POST "http://localhost:8080/api/publish/simulate?serviceId=1&success=true"

# 5. Send via full JSON body
curl -X POST http://localhost:8080/api/publish \
  -H "Content-Type: application/json" \
  -d '{
    "serviceId": 42,
    "serviceName": "Payment Gateway",
    "url": "https://payment.example.com/health",
    "success": false,
    "statusCode": 503,
    "responseTimeMs": 6000,
    "checkedAt": "2024-01-15T10:30:00Z"
  }'
```

---

### 🔷 Final Project: What You Built

```
┌─────────────────────────────────────────────────────────────────┐
│                   WHAT YOU BUILT                                │
│                                                                 │
│  REST API                                                       │
│  POST /api/publish           ← Accepts JSON or query param      │
│  POST /api/publish/simulate  ← Quick test endpoint              │
│         │                                                       │
│         ▼                                                       │
│  EventProducerService                                           │
│  KafkaTemplate.send("check.results", serviceId, event)         │
│         │                                                       │
│         ▼                                                       │
│  Kafka Topic: check.results (3 partitions)                      │
│  Messages partitioned by serviceId (ordering guaranteed)        │
│         │                                                       │
│         ▼                                                       │
│  EventConsumerService (@KafkaListener)                          │
│  Receives CheckResultEvent (auto-deserialized from JSON)        │
│  Logs result, flags failures                                    │
└─────────────────────────────────────────────────────────────────┘
```

---

## 📋 Quick Reference Card

### Kafka Commands Cheat Sheet

```bash
# Start Kafka (KRaft)
bin/kafka-server-start.sh config/kraft/server.properties

# List topics
bin/kafka-topics.sh --list --bootstrap-server localhost:9092

# Create topic
bin/kafka-topics.sh --create --topic my-topic --bootstrap-server localhost:9092 --partitions 3 --replication-factor 1

# Console Producer
bin/kafka-console-producer.sh --topic my-topic --bootstrap-server localhost:9092

# Console Consumer (from beginning)
bin/kafka-console-consumer.sh --topic my-topic --from-beginning --bootstrap-server localhost:9092

# Consumer Group Lag
bin/kafka-consumer-groups.sh --describe --group my-group --bootstrap-server localhost:9092
```

---

### Spring Boot Kafka Annotations

| Annotation | Usage |
|-----------|-------|
| `@KafkaListener` | Marks a method as a Kafka message consumer |
| `@EnableKafka` | Enables Kafka listener infrastructure (auto-added by Spring Boot) |
| `@RetryableTopic` | Enables automatic retry + DLT for a listener |
| `@KafkaHandler` | For class-level `@KafkaListener` with multiple message types |

---

### Key Classes

| Class | Purpose |
|-------|---------|
| `KafkaTemplate<K, V>` | Send messages (producer) |
| `@KafkaListener` | Receive messages (consumer) |
| `NewTopic` | Define/create topics as Spring beans |
| `TopicBuilder` | Fluent builder for `NewTopic` |
| `ConsumerRecord<K, V>` | Full message with metadata (topic, partition, offset, key, value) |
| `JsonSerializer` | Serialize Java objects → JSON bytes |
| `JsonDeserializer` | Deserialize JSON bytes → Java objects |

---

### application.yml Quick Reference

```yaml
spring:
  kafka:
    bootstrap-servers: localhost:9092    # Kafka broker address
    producer:
      key-serializer: StringSerializer   # How to encode the key
      value-serializer: JsonSerializer   # How to encode the value
      acks: all                          # Wait for all replicas
      retries: 3                         # Retry failed sends 3 times
    consumer:
      group-id: my-group                 # Consumer group name
      auto-offset-reset: earliest        # Start from beginning if no offset
      key-deserializer: StringDeserializer
      value-deserializer: JsonDeserializer
      properties:
        spring.json.trusted.packages: "*"  # Trust all packages for deserialization
```

---

## 🎓 Learning Path Summary

```
Week 1: Basics
├── Understand Kafka concepts (Producer, Consumer, Topic, Partition, Offset)
├── Run Kafka locally (KRaft mode or Docker)
├── Build Phase 1 mini project (String messages)
└── Test with curl + console consumer

Week 2: Intermediate
├── Upgrade to JSON events (CheckResultEvent)
├── Create proper topic with NewTopic bean
├── Understand Consumer Groups and partitioning
└── Implement proper logging and error handling

Week 3: Advanced
├── Implement @RetryableTopic + Dead Letter Topic
├── Add idempotency handling
├── Connect to your actual Monitoring/Detection service
├── Monitor consumer lag
└── Practice interview questions
```

---

> **Built with ❤️ for learning by a Senior Java Backend Engineer**
>
> **Remember:** The best way to learn Kafka is to run it locally and experiment. Break things, fix them, and understand why they broke. That's how real engineers learn!
>
> **Tenglish closing note:** "Kafka ante chala kastam ga untundi ani anipistundi, kani oka sari hands-on chestey chala simple ga artham avutundi. Oka step씩 cover cheyyi — concepts → local setup → string producer → JSON producer → consumer groups. Meeru cheyagalaru! 💪"

