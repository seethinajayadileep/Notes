# Spring Boot Big Project Folder Structure and File Organization

> **A complete beginner-friendly guide for organizing a production-level Spring Boot project**

---

## Table of Contents

1. [Introduction](#1-introduction)
2. [Recommended Big Spring Boot Folder Structure](#2-recommended-big-spring-boot-folder-structure)
3. [Main Application Class](#3-main-application-class)
4. [controller Folder](#4-controller-folder)
5. [service Folder](#5-service-folder)
6. [service/impl Folder](#6-serviceimpl-folder)
7. [repository Folder](#7-repository-folder)
8. [entity Folder](#8-entity-folder)
9. [dto Folder](#9-dto-folder)
10. [dto/request Folder](#10-dtorequest-folder)
11. [dto/response Folder](#11-dtoresponse-folder)
12. [mapper Folder](#12-mapper-folder)
13. [exception Folder](#13-exception-folder)
14. [config Folder](#14-config-folder)
15. [security Folder](#15-security-folder)
16. [client Folder](#16-client-folder)
17. [kafka Folder](#17-kafka-folder)
18. [redis Folder](#18-redis-folder)
19. [scheduler Folder](#19-scheduler-folder)
20. [validation Folder](#20-validation-folder)
21. [constant Folder](#21-constant-folder)
22. [util Folder](#22-util-folder)
23. [resources Folder](#23-resources-folder)
24. [test Folder](#24-test-folder)
25. [Layer Flow Explanation](#25-layer-flow-explanation)
26. [Example: User Module](#26-example-user-module-folder-arrangement)
27. [Example: Product Module](#27-example-product-module-folder-arrangement)
28. [Example: Monitoring Project](#28-example-monitoring-project-folder-arrangement)
29. [Package-by-Layer vs Package-by-Feature](#29-package-by-layer-vs-package-by-feature)
30. [Best Practices](#30-best-practices)
31. [Common Mistakes](#31-common-mistakes)
32. [Naming Conventions](#32-naming-conventions)
33. [Final Recommended Structure](#33-final-recommended-structure)
34. [Interview Questions](#34-interview-questions)

---

## 1. Introduction

### Why Folder Structure Matters in Big Spring Boot Projects

When you start learning Spring Boot, you often create small projects with just a few files. But in real companies, a project can have hundreds or even thousands of Java files. If all these files are placed randomly without any structure, the project becomes very hard to work with.

A good folder structure is like a clean filing system. Every file has a fixed place. Every team member knows exactly where to look. Every new feature can be added without breaking other parts of the project.

### Problems Caused by Poor File Organization

When a Spring Boot project has no proper structure, these problems happen:

- **Hard to find files** — A developer searches for a file but cannot find it because it is placed in a random folder
- **Duplicate code** — Two developers write the same logic because they could not find the existing one
- **Hard to fix bugs** — A bug in one class causes changes in many unrelated places
- **Slow onboarding** — A new team member takes weeks just to understand where things are
- **Merge conflicts** — Multiple developers edit the same file because there is no clear separation of work
- **Tight coupling** — Business logic, database logic, and API logic all mixed in one class
- **Hard to write tests** — When everything is mixed together, testing one thing requires setting up everything else

### How Proper Structure Helps

| Benefit | Explanation |
|---|---|
| **Scalability** | New features can be added in the correct folder without touching existing code |
| **Debugging** | When something breaks, you know exactly which layer caused it |
| **Testing** | Each layer can be tested independently |
| **Teamwork** | Frontend team, backend team, and DevOps team all understand the layout |
| **Code Review** | Reviewers quickly find what changed and why |
| **Maintainability** | Code written today is easy to understand after 6 months |

### Small Project vs Big Project Structure

**Small Project (3–5 files):**
```
MyApp/
├── MyAppApplication.java
├── UserController.java
├── User.java
└── UserRepository.java
```

This works for practice. But in production, you have 50+ features, 200+ classes, and multiple developers.

**Big Project (production-level):**
```
MyApp/
├── controller/
├── service/
├── service/impl/
├── repository/
├── entity/
├── dto/
├── mapper/
├── exception/
├── config/
├── security/
├── kafka/
├── redis/
└── util/
```

Every folder has a clear purpose. Every class has one responsibility. This is what real companies use.

---

## 2. Recommended Big Spring Boot Folder Structure

Here is the complete folder structure for a production-level Spring Boot project:

```
spring-boot-big-project/
├── src/
│   ├── main/
│   │   ├── java/
│   │   │   └── com/company/project/
│   │   │       ├── ProjectApplication.java          ← Main entry point
│   │   │       │
│   │   │       ├── config/                          ← All configuration classes
│   │   │       │   ├── SecurityConfig.java
│   │   │       │   ├── KafkaConfig.java
│   │   │       │   ├── RedisConfig.java
│   │   │       │   ├── SwaggerConfig.java
│   │   │       │   └── CorsConfig.java
│   │   │       │
│   │   │       ├── controller/                      ← REST API endpoints
│   │   │       │   ├── UserController.java
│   │   │       │   ├── ProductController.java
│   │   │       │   └── AuthController.java
│   │   │       │
│   │   │       ├── service/                         ← Business logic interfaces
│   │   │       │   ├── UserService.java
│   │   │       │   └── ProductService.java
│   │   │       │
│   │   │       ├── service/impl/                    ← Business logic implementations
│   │   │       │   ├── UserServiceImpl.java
│   │   │       │   └── ProductServiceImpl.java
│   │   │       │
│   │   │       ├── repository/                      ← Database access layer
│   │   │       │   ├── UserRepository.java
│   │   │       │   └── ProductRepository.java
│   │   │       │
│   │   │       ├── entity/                          ← JPA entity classes (database tables)
│   │   │       │   ├── User.java
│   │   │       │   └── Product.java
│   │   │       │
│   │   │       ├── dto/                             ← Data Transfer Objects
│   │   │       │   ├── request/                     ← Incoming data from client
│   │   │       │   │   ├── CreateUserRequest.java
│   │   │       │   │   ├── LoginRequest.java
│   │   │       │   │   └── CreateProductRequest.java
│   │   │       │   └── response/                    ← Outgoing data to client
│   │   │       │       ├── UserResponse.java
│   │   │       │       ├── LoginResponse.java
│   │   │       │       └── ProductResponse.java
│   │   │       │
│   │   │       ├── mapper/                          ← Entity ↔ DTO conversion
│   │   │       │   ├── UserMapper.java
│   │   │       │   └── ProductMapper.java
│   │   │       │
│   │   │       ├── exception/                       ← Custom exceptions and error handling
│   │   │       │   ├── GlobalExceptionHandler.java
│   │   │       │   ├── ResourceNotFoundException.java
│   │   │       │   ├── BadRequestException.java
│   │   │       │   └── UnauthorizedException.java
│   │   │       │
│   │   │       ├── security/                        ← JWT and security logic
│   │   │       │   ├── JwtFilter.java
│   │   │       │   ├── JwtService.java
│   │   │       │   └── CustomUserDetailsService.java
│   │   │       │
│   │   │       ├── client/                          ← External API / microservice callers
│   │   │       │   ├── PaymentClient.java
│   │   │       │   └── NotificationClient.java
│   │   │       │
│   │   │       ├── kafka/                           ← Kafka producer, consumer, events
│   │   │       │   ├── producer/
│   │   │       │   │   └── CheckResultProducer.java
│   │   │       │   ├── consumer/
│   │   │       │   │   └── CheckResultConsumer.java
│   │   │       │   └── event/
│   │   │       │       └── CheckResultEvent.java
│   │   │       │
│   │   │       ├── redis/                           ← Redis cache logic
│   │   │       │   └── RecentCheckCacheService.java
│   │   │       │
│   │   │       ├── scheduler/                       ← Scheduled jobs
│   │   │       │   ├── MonitoringJob.java
│   │   │       │   └── CleanupJob.java
│   │   │       │
│   │   │       ├── validation/                      ← Custom validation annotations
│   │   │       │   ├── ValidPassword.java
│   │   │       │   └── UniqueEmailValidator.java
│   │   │       │
│   │   │       ├── constant/                        ← Constants and fixed values
│   │   │       │   ├── AppConstants.java
│   │   │       │   ├── KafkaTopicConstants.java
│   │   │       │   └── RedisKeyConstants.java
│   │   │       │
│   │   │       └── util/                            ← Utility/helper classes
│   │   │           ├── DateUtil.java
│   │   │           └── TokenUtil.java
│   │   │
│   │   └── resources/
│   │       ├── application.yml                      ← Main configuration
│   │       ├── application-dev.yml                  ← Dev environment config
│   │       ├── application-prod.yml                 ← Production environment config
│   │       ├── static/                              ← Static assets (if needed)
│   │       ├── templates/                           ← Thymeleaf templates (if needed)
│   │       └── db/
│   │           └── migration/                       ← Flyway SQL migration files
│   │               ├── V1__create_user_table.sql
│   │               └── V2__create_product_table.sql
│   │
│   └── test/
│       └── java/
│           └── com/company/project/
│               ├── controller/
│               │   └── UserControllerTest.java
│               ├── service/
│               │   └── UserServiceTest.java
│               ├── repository/
│               │   └── UserRepositoryTest.java
│               └── integration/
│                   └── UserIntegrationTest.java
│
├── pom.xml                                          ← Maven dependencies
├── Dockerfile                                       ← Docker build instructions
├── docker-compose.yml                               ← Local dev environment setup
├── README.md                                        ← Project documentation
└── .gitignore                                       ← Files to exclude from Git
```

### What Each Folder Does (Quick Summary)

| Folder | Purpose |
|---|---|
| `controller/` | Receives HTTP requests, sends HTTP responses |
| `service/` | Contains interfaces for business logic |
| `service/impl/` | Contains actual implementation of business logic |
| `repository/` | Talks to the database |
| `entity/` | Represents database tables as Java classes |
| `dto/request/` | Represents data coming from the client |
| `dto/response/` | Represents data going back to the client |
| `mapper/` | Converts between entity and DTO |
| `exception/` | Custom error classes and global error handler |
| `config/` | Spring configuration classes |
| `security/` | JWT, authentication, authorization |
| `client/` | Calls external services or other microservices |
| `kafka/` | Kafka producer, consumer, and event classes |
| `redis/` | Redis caching logic |
| `scheduler/` | Scheduled tasks that run automatically |
| `validation/` | Custom validation annotations |
| `constant/` | Fixed values like topic names and key names |
| `util/` | General helper methods |

---

## 3. Main Application Class

### File: `ProjectApplication.java`

```java
package com.company.project;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
public class ProjectApplication {

    public static void main(String[] args) {
        SpringApplication.run(ProjectApplication.class, args);
    }
}
```

### Why It Must Stay in the Root Package

The `@SpringBootApplication` annotation does three things at once:
- `@Configuration` — marks this class as a configuration class
- `@EnableAutoConfiguration` — enables Spring Boot's auto-configuration
- `@ComponentScan` — scans all packages below the current package for Spring beans

**This is why the application class must be in the root package (`com.company.project`).** When it is in the root package, Spring automatically scans all sub-packages like `controller`, `service`, `repository`, etc.

### Package Scanning Explained

```
com.company.project                  ← @SpringBootApplication here
│
├── controller/UserController.java   ← Scanned automatically ✅
├── service/UserService.java         ← Scanned automatically ✅
├── repository/UserRepository.java   ← Scanned automatically ✅
└── entity/User.java                 ← Scanned automatically ✅
```

### Common Mistake

```
com.company.project.controller
└── ProjectApplication.java          ← WRONG! ❌

com.company.project.service
└── UserService.java                  ← NOT scanned ❌
```

If you put `ProjectApplication.java` inside the `controller` folder, Spring will only scan the `controller` package and completely miss `service`, `repository`, and other packages.

**Rule: Always keep the main application class in the root package.**

---

## 4. controller Folder

### What Controller Classes Do

Controller classes handle HTTP requests from the client (browser, Postman, mobile app, etc.) and send back HTTP responses. They are the entry point of your application.

### What Should Be Inside Controller

- `@RestController` or `@Controller` annotation
- `@RequestMapping`, `@GetMapping`, `@PostMapping`, `@PutMapping`, `@DeleteMapping` annotations
- Method that receives request, calls service, returns response
- Request validation using `@Valid`
- Path variable and request parameter extraction

### What Should NOT Be Inside Controller

- Business logic (calculations, rules, decisions)
- Database queries
- Kafka or Redis code
- Exception handling logic (use `@RestControllerAdvice` instead)
- Direct entity exposure (use DTO instead)

### Example Controller Files

- `UserController.java` — handles `/api/users` endpoints
- `ProductController.java` — handles `/api/products` endpoints
- `AuthController.java` — handles `/api/auth/login`, `/api/auth/register`

### Sample Controller Code

```java
package com.company.project.controller;

import com.company.project.dto.request.CreateUserRequest;
import com.company.project.dto.response.UserResponse;
import com.company.project.service.UserService;
import jakarta.validation.Valid;
import lombok.RequiredArgsConstructor;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/api/users")
@RequiredArgsConstructor
public class UserController {

    private final UserService userService;

    // GET /api/users → Get all users
    @GetMapping
    public ResponseEntity<List<UserResponse>> getAllUsers() {
        return ResponseEntity.ok(userService.getAllUsers());
    }

    // GET /api/users/{id} → Get one user by ID
    @GetMapping("/{id}")
    public ResponseEntity<UserResponse> getUserById(@PathVariable Long id) {
        return ResponseEntity.ok(userService.getUserById(id));
    }

    // POST /api/users → Create a new user
    @PostMapping
    public ResponseEntity<UserResponse> createUser(@Valid @RequestBody CreateUserRequest request) {
        UserResponse response = userService.createUser(request);
        return ResponseEntity.status(HttpStatus.CREATED).body(response);
    }

    // PUT /api/users/{id} → Update a user
    @PutMapping("/{id}")
    public ResponseEntity<UserResponse> updateUser(
            @PathVariable Long id,
            @Valid @RequestBody CreateUserRequest request) {
        return ResponseEntity.ok(userService.updateUser(id, request));
    }

    // DELETE /api/users/{id} → Delete a user
    @DeleteMapping("/{id}")
    public ResponseEntity<Void> deleteUser(@PathVariable Long id) {
        userService.deleteUser(id);
        return ResponseEntity.noContent().build();
    }
}
```

**Key points:**
- Controller is thin — no business logic
- Calls `userService` for everything
- Returns `ResponseEntity` with proper status codes
- Uses `@Valid` to trigger request validation

---

## 5. service Folder

### What the Service Layer Means

The service layer contains the **business logic** of your application. Business logic means the rules and calculations that your application must perform. For example: "A user cannot register with an email that already exists" — this rule belongs in the service layer.

### Why We Create Service Interfaces

In the `service` folder, we keep **interfaces only** (not implementations). The reason:

- It allows **loose coupling** — the controller only knows about the interface, not the implementation
- It makes **unit testing** easier — you can create a fake (mock) implementation during tests
- It follows the **Dependency Inversion Principle** — depend on abstractions, not on concrete classes
- It allows **multiple implementations** if needed in the future

### Example Service Files

- `UserService.java` — interface for user-related business logic
- `ProductService.java` — interface for product-related business logic

### Sample Service Interface Code

```java
package com.company.project.service;

import com.company.project.dto.request.CreateUserRequest;
import com.company.project.dto.response.UserResponse;

import java.util.List;

public interface UserService {

    List<UserResponse> getAllUsers();

    UserResponse getUserById(Long id);

    UserResponse createUser(CreateUserRequest request);

    UserResponse updateUser(Long id, CreateUserRequest request);

    void deleteUser(Long id);
}
```

**Key points:**
- Only method declarations, no logic
- Takes request DTOs as input
- Returns response DTOs as output
- Never takes entities or exposes entities

---

## 6. service/impl Folder

### What Implementation Classes Are

The `service/impl` folder contains the **actual implementation** of the service interfaces. This is where real business logic is written. The class implements the interface defined in `service/`.

### Why We Keep Implementations Separately

- Keeps the `service/` folder clean with only contracts (interfaces)
- Easy to swap implementations — for example, replace `UserServiceImpl` with `MockUserServiceImpl` during tests
- Follows Single Responsibility Principle
- Makes the codebase easier to navigate

### Sample Service Implementation Code

```java
package com.company.project.service.impl;

import com.company.project.dto.request.CreateUserRequest;
import com.company.project.dto.response.UserResponse;
import com.company.project.entity.User;
import com.company.project.exception.ResourceNotFoundException;
import com.company.project.mapper.UserMapper;
import com.company.project.repository.UserRepository;
import com.company.project.service.UserService;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;
import java.util.stream.Collectors;

@Service
@RequiredArgsConstructor
@Slf4j
public class UserServiceImpl implements UserService {

    private final UserRepository userRepository;
    private final UserMapper userMapper;

    @Override
    public List<UserResponse> getAllUsers() {
        log.info("Fetching all users");
        return userRepository.findAll()
                .stream()
                .map(userMapper::toResponse)
                .collect(Collectors.toList());
    }

    @Override
    public UserResponse getUserById(Long id) {
        log.info("Fetching user with id: {}", id);
        User user = userRepository.findById(id)
                .orElseThrow(() -> new ResourceNotFoundException("User not found with id: " + id));
        return userMapper.toResponse(user);
    }

    @Override
    @Transactional
    public UserResponse createUser(CreateUserRequest request) {
        log.info("Creating new user with email: {}", request.getEmail());
        User user = userMapper.toEntity(request);
        User savedUser = userRepository.save(user);
        return userMapper.toResponse(savedUser);
    }

    @Override
    @Transactional
    public UserResponse updateUser(Long id, CreateUserRequest request) {
        User user = userRepository.findById(id)
                .orElseThrow(() -> new ResourceNotFoundException("User not found with id: " + id));
        user.setName(request.getName());
        user.setEmail(request.getEmail());
        return userMapper.toResponse(userRepository.save(user));
    }

    @Override
    @Transactional
    public void deleteUser(Long id) {
        User user = userRepository.findById(id)
                .orElseThrow(() -> new ResourceNotFoundException("User not found with id: " + id));
        userRepository.delete(user);
    }
}
```

**Key points:**
- `@Service` — registers this class as a Spring bean
- `implements UserService` — connects it to the interface
- Uses `UserRepository`, `UserMapper` via constructor injection (`@RequiredArgsConstructor`)
- Uses `@Transactional` for database write operations
- Uses `@Slf4j` for logging
- Throws custom exceptions instead of raw exceptions

---

## 7. repository Folder

### What the Repository Layer Does

The repository layer is responsible for all **database operations**. It talks directly to the database to save, find, update, and delete records. In Spring Boot, we use Spring Data JPA which provides a lot of functionality without writing SQL.

### How It Connects to the Database

- Repositories extend `JpaRepository<Entity, ID>` interface
- Spring Data JPA auto-generates the SQL at runtime
- You can also write custom queries using `@Query` or method name conventions

### JpaRepository Explanation

```
JpaRepository<User, Long>
             ↑      ↑
         Entity   Primary Key Type
```

`JpaRepository` provides these methods for free:
- `findAll()` — get all records
- `findById(id)` — get one record by ID
- `save(entity)` — insert or update
- `deleteById(id)` — delete by ID
- `count()` — count records
- `existsById(id)` — check if record exists

### Sample Repository Code

```java
package com.company.project.repository;

import com.company.project.entity.User;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;
import org.springframework.stereotype.Repository;

import java.util.List;
import java.util.Optional;

@Repository
public interface UserRepository extends JpaRepository<User, Long> {

    // Spring Data JPA auto-creates SQL from method name
    Optional<User> findByEmail(String email);

    boolean existsByEmail(String email);

    List<User> findByActiveTrue();

    // Custom JPQL query
    @Query("SELECT u FROM User u WHERE u.name LIKE %:name%")
    List<User> searchByName(@Param("name") String name);

    // Native SQL query
    @Query(value = "SELECT * FROM users WHERE created_at > NOW() - INTERVAL '7 days'",
           nativeQuery = true)
    List<User> findRecentUsers();
}
```

**Key points:**
- It is an interface, not a class
- Extends `JpaRepository` — gets 20+ methods for free
- Custom finders follow naming conventions: `findBy`, `existsBy`, `countBy`
- Complex queries use `@Query` with JPQL or native SQL

---

## 8. entity Folder

### What Entity Classes Are

An entity class is a Java class that maps to a **database table**. Every field in the class maps to a column in the table. When you save an entity object, Spring JPA converts it to a SQL INSERT or UPDATE statement.

### Common JPA Annotations

| Annotation | Meaning |
|---|---|
| `@Entity` | Marks this class as a JPA entity (database table) |
| `@Table(name = "users")` | Specifies the exact table name in the database |
| `@Id` | Marks the primary key field |
| `@GeneratedValue` | Auto-generates the primary key value |
| `@Column` | Customizes a column (name, nullable, unique, length) |
| `@ManyToOne` | Many rows of this table relate to one row of another |
| `@OneToMany` | One row of this table relates to many rows of another |
| `@CreationTimestamp` | Auto-sets the field when the record is created |
| `@UpdateTimestamp` | Auto-sets the field when the record is updated |

### Sample Entity Code

```java
package com.company.project.entity;

import jakarta.persistence.*;
import lombok.*;
import org.hibernate.annotations.CreationTimestamp;
import org.hibernate.annotations.UpdateTimestamp;

import java.time.LocalDateTime;
import java.util.List;

@Entity
@Table(name = "users")
@Getter
@Setter
@NoArgsConstructor
@AllArgsConstructor
@Builder
public class User {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(name = "name", nullable = false, length = 100)
    private String name;

    @Column(name = "email", nullable = false, unique = true)
    private String email;

    @Column(name = "password", nullable = false)
    private String password;

    @Column(name = "active")
    private boolean active = true;

    // One user can have many orders
    @OneToMany(mappedBy = "user", cascade = CascadeType.ALL)
    private List<Order> orders;

    @CreationTimestamp
    @Column(name = "created_at", updatable = false)
    private LocalDateTime createdAt;

    @UpdateTimestamp
    @Column(name = "updated_at")
    private LocalDateTime updatedAt;
}
```

**Key points:**
- Entity class should only represent database structure
- Do not put business logic in entity classes
- Use Lombok annotations to avoid boilerplate code
- Always use `@Column` for clarity even when column name matches field name

---

## 9. dto Folder

### What DTO Means

DTO stands for **Data Transfer Object**. It is a simple Java class used to carry data between layers — specifically between the controller and the client (browser, Postman, mobile app).

### Why We Should Not Expose Entity Directly in API

Imagine your `User` entity has a `password` field. If you return the entity directly in your REST API response, the password is exposed to the client. This is a serious security problem.

Also, the entity structure might change because of database changes. If you expose the entity directly, every database change breaks the API contract with the client.

**DTOs solve both problems:**
- You control exactly which fields to expose
- Entity changes do not break the API automatically

### Difference Between Request DTO and Response DTO

| Request DTO | Response DTO |
|---|---|
| Data coming **from** the client | Data going **to** the client |
| Contains fields client sends in request body | Contains fields client receives back |
| Has validation annotations (`@NotBlank`, `@Email`) | Does not need validation |
| Example: `CreateUserRequest`, `LoginRequest` | Example: `UserResponse`, `LoginResponse` |

### Common DTO Examples

| DTO Class | Purpose |
|---|---|
| `CreateUserRequest` | Client sends this when creating a user |
| `LoginRequest` | Client sends this when logging in |
| `UserResponse` | Server sends this with user details |
| `LoginResponse` | Server sends this with JWT token |
| `CreateProductRequest` | Client sends this when creating a product |
| `ProductResponse` | Server sends this with product details |

---

## 10. dto/request Folder

### What Request DTOs Are

Request DTOs represent the **data that comes from the client** (frontend, Postman, mobile app). When a client sends a POST or PUT request, the body of that request is mapped into a request DTO.

### How Validation Annotations Work

When you add `@Valid` in the controller method, Spring automatically validates the request DTO before calling the service. If validation fails, Spring returns a 400 Bad Request response.

### Common Validation Annotations

| Annotation | Purpose |
|---|---|
| `@NotBlank` | Field must not be null or empty |
| `@NotNull` | Field must not be null |
| `@Email` | Must be a valid email format |
| `@Size(min, max)` | String must be within the size range |
| `@Min(value)` | Number must be >= value |
| `@Max(value)` | Number must be <= value |
| `@Pattern(regexp)` | Must match the regular expression |

### Sample Request DTO Code

```java
package com.company.project.dto.request;

import jakarta.validation.constraints.*;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@NoArgsConstructor
@AllArgsConstructor
@Builder
public class CreateUserRequest {

    @NotBlank(message = "Name is required")
    @Size(min = 2, max = 100, message = "Name must be between 2 and 100 characters")
    private String name;

    @NotBlank(message = "Email is required")
    @Email(message = "Please provide a valid email address")
    private String email;

    @NotBlank(message = "Password is required")
    @Size(min = 8, max = 50, message = "Password must be between 8 and 50 characters")
    private String password;

    @NotNull(message = "Phone number is required")
    @Pattern(regexp = "^[+]?[0-9]{10,13}$", message = "Please provide a valid phone number")
    private String phoneNumber;
}
```

```java
package com.company.project.dto.request;

import jakarta.validation.constraints.Email;
import jakarta.validation.constraints.NotBlank;
import lombok.Data;

@Data
public class LoginRequest {

    @NotBlank(message = "Email is required")
    @Email(message = "Please provide a valid email")
    private String email;

    @NotBlank(message = "Password is required")
    private String password;
}
```

---

## 11. dto/response Folder

### What Response DTOs Are

Response DTOs represent the **data that your API sends back** to the client. They define exactly what fields the client will see in the response.

### Why Response DTO Should Not Expose Sensitive Fields

- Never include `password` in a response DTO
- Never include internal IDs like `internalAuditId` unless needed by the client
- Include only what the client needs
- This also reduces the size of the response

### Sample Response DTO Code

```java
package com.company.project.dto.response;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.time.LocalDateTime;

@Data
@NoArgsConstructor
@AllArgsConstructor
@Builder
public class UserResponse {

    private Long id;
    private String name;
    private String email;
    private String phoneNumber;
    private boolean active;
    private LocalDateTime createdAt;
    // Notice: password is NOT here — never expose password
}
```

```java
package com.company.project.dto.response;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@NoArgsConstructor
@AllArgsConstructor
@Builder
public class LoginResponse {

    private String accessToken;
    private String tokenType = "Bearer";
    private Long expiresIn;        // Token validity in seconds
    private String userEmail;
    private String userName;
}
```

---

## 12. mapper Folder

### Why Mapper Is Used

A mapper converts between two different object types. In Spring Boot projects, we convert:
- `Entity → Response DTO` (when reading from database and sending to client)
- `Request DTO → Entity` (when client sends data and we need to save to database)

Without a mapper, you would repeat the same copy-paste code everywhere.

### Manual Mapper vs MapStruct

| Approach | Description | When to Use |
|---|---|---|
| **Manual Mapper** | You write the conversion code yourself | Small projects, full control needed |
| **MapStruct** | A library that auto-generates mapper code at compile time | Large projects, reduces boilerplate |

### Sample Manual Mapper Code

```java
package com.company.project.mapper;

import com.company.project.dto.request.CreateUserRequest;
import com.company.project.dto.response.UserResponse;
import com.company.project.entity.User;
import org.springframework.stereotype.Component;

@Component
public class UserMapper {

    // Convert Entity → Response DTO
    public UserResponse toResponse(User user) {
        if (user == null) return null;

        return UserResponse.builder()
                .id(user.getId())
                .name(user.getName())
                .email(user.getEmail())
                .active(user.isActive())
                .createdAt(user.getCreatedAt())
                .build();
        // Note: password is NOT included
    }

    // Convert Request DTO → Entity
    public User toEntity(CreateUserRequest request) {
        if (request == null) return null;

        return User.builder()
                .name(request.getName())
                .email(request.getEmail())
                .password(request.getPassword()) // Will be encoded in service
                .active(true)
                .build();
        // Note: id and createdAt are NOT set — JPA handles these
    }
}
```

### MapStruct Example (for reference)

```java
// With MapStruct library — much less code
@Mapper(componentModel = "spring")
public interface UserMapper {

    UserResponse toResponse(User user);

    @Mapping(target = "id", ignore = true)
    @Mapping(target = "createdAt", ignore = true)
    User toEntity(CreateUserRequest request);
}
```

---

## 13. exception Folder

### Why Custom Exceptions Are Important

Without custom exceptions, your application throws generic errors like `NullPointerException` or `RuntimeException` to the client. This is bad because:
- The client sees internal Java error details (security risk)
- The client cannot understand what went wrong
- Every error returns 500 Internal Server Error (not meaningful)

Custom exceptions let you return clear, meaningful error messages with proper HTTP status codes.

### GlobalExceptionHandler

`@RestControllerAdvice` creates a global exception handler that catches exceptions from any controller and returns a proper JSON error response.

### Sample Exception Code

```java
// Custom exception class
package com.company.project.exception;

import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.ResponseStatus;

@ResponseStatus(HttpStatus.NOT_FOUND)
public class ResourceNotFoundException extends RuntimeException {

    public ResourceNotFoundException(String message) {
        super(message);
    }
}
```

```java
// Bad request exception
package com.company.project.exception;

import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.ResponseStatus;

@ResponseStatus(HttpStatus.BAD_REQUEST)
public class BadRequestException extends RuntimeException {

    public BadRequestException(String message) {
        super(message);
    }
}
```

```java
// Error response DTO
package com.company.project.exception;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import java.time.LocalDateTime;

@Data
@AllArgsConstructor
@Builder
public class ErrorResponse {
    private int status;
    private String error;
    private String message;
    private LocalDateTime timestamp;
}
```

```java
// Global exception handler
package com.company.project.exception;

import lombok.extern.slf4j.Slf4j;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.validation.FieldError;
import org.springframework.web.bind.MethodArgumentNotValidException;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.RestControllerAdvice;

import java.time.LocalDateTime;
import java.util.HashMap;
import java.util.Map;

@RestControllerAdvice
@Slf4j
public class GlobalExceptionHandler {

    // Handle 404 - Resource not found
    @ExceptionHandler(ResourceNotFoundException.class)
    public ResponseEntity<ErrorResponse> handleResourceNotFound(ResourceNotFoundException ex) {
        log.error("Resource not found: {}", ex.getMessage());
        ErrorResponse error = ErrorResponse.builder()
                .status(404)
                .error("Not Found")
                .message(ex.getMessage())
                .timestamp(LocalDateTime.now())
                .build();
        return ResponseEntity.status(HttpStatus.NOT_FOUND).body(error);
    }

    // Handle 400 - Validation errors
    @ExceptionHandler(MethodArgumentNotValidException.class)
    public ResponseEntity<Map<String, String>> handleValidationErrors(
            MethodArgumentNotValidException ex) {
        Map<String, String> errors = new HashMap<>();
        ex.getBindingResult().getAllErrors().forEach(error -> {
            String field = ((FieldError) error).getField();
            String message = error.getDefaultMessage();
            errors.put(field, message);
        });
        return ResponseEntity.status(HttpStatus.BAD_REQUEST).body(errors);
    }

    // Handle 500 - Generic unexpected errors
    @ExceptionHandler(Exception.class)
    public ResponseEntity<ErrorResponse> handleGenericException(Exception ex) {
        log.error("Unexpected error: ", ex);
        ErrorResponse error = ErrorResponse.builder()
                .status(500)
                .error("Internal Server Error")
                .message("Something went wrong. Please try again later.")
                .timestamp(LocalDateTime.now())
                .build();
        return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).body(error);
    }
}
```

---

## 14. config Folder

### What Configuration Classes Are

Configuration classes are Java classes annotated with `@Configuration`. They define beans, settings, and infrastructure setup that Spring needs to run. Instead of putting configuration in `application.yml` alone, complex configuration goes into Java config classes.

### When to Create a Config Class

Create a config class when you need to:
- Define custom beans
- Set up security rules
- Configure third-party libraries (Kafka, Redis, Swagger, etc.)
- Set CORS policies
- Configure HTTP clients

### Configuration Files in the `config/` Folder

| Config File | Purpose |
|---|---|
| `SecurityConfig.java` | Defines security rules, JWT setup, allowed URLs |
| `KafkaConfig.java` | Sets up Kafka producer and consumer factories |
| `RedisConfig.java` | Configures Redis connection and template |
| `SwaggerConfig.java` | Sets up Swagger/OpenAPI documentation |
| `RestTemplateConfig.java` | Configures `RestTemplate` bean for HTTP calls |
| `WebClientConfig.java` | Configures `WebClient` bean for reactive HTTP calls |
| `CorsConfig.java` | Configures Cross-Origin Resource Sharing |

### Sample Config Code

```java
package com.company.project.config;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.client.RestTemplate;
import org.springframework.web.cors.CorsConfiguration;
import org.springframework.web.cors.UrlBasedCorsConfigurationSource;
import org.springframework.web.filter.CorsFilter;

import java.util.List;

@Configuration
public class AppConfig {

    @Bean
    public RestTemplate restTemplate() {
        return new RestTemplate();
    }

    @Bean
    public CorsFilter corsFilter() {
        CorsConfiguration config = new CorsConfiguration();
        config.setAllowedOrigins(List.of("http://localhost:3000", "https://yourfrontend.com"));
        config.setAllowedMethods(List.of("GET", "POST", "PUT", "DELETE", "OPTIONS"));
        config.setAllowedHeaders(List.of("*"));
        config.setAllowCredentials(true);

        UrlBasedCorsConfigurationSource source = new UrlBasedCorsConfigurationSource();
        source.registerCorsConfiguration("/**", config);
        return new CorsFilter(source);
    }
}
```

---

## 15. security Folder

### What Security-Related Files Should Be Here

The `security/` folder contains all classes related to authentication and authorization. Specifically JWT (JSON Web Token) handling, Spring Security filters, and user details loading.

### Files and Their Responsibilities

| File | Responsibility |
|---|---|
| `JwtService.java` | Generate JWT token, extract claims, validate token |
| `JwtFilter.java` | Intercept every request, read JWT from header, set authentication |
| `CustomUserDetailsService.java` | Load user from database by username/email for authentication |
| `SecurityConfig.java` (also in config/) | Define which URLs are public and which require authentication |

### Example File Descriptions

```java
// JwtService.java
// - generateToken(username) → creates and signs JWT
// - extractUsername(token) → reads username from JWT
// - isTokenValid(token, userDetails) → checks if token is valid and not expired

// JwtFilter.java (extends OncePerRequestFilter)
// - Runs before every request
// - Reads "Authorization: Bearer <token>" header
// - Validates JWT and sets SecurityContext

// CustomUserDetailsService.java (implements UserDetailsService)
// - loadUserByUsername(email) method
// - Loads User from UserRepository by email
// - Returns UserDetails object with roles

// SecurityConfig.java
// - @EnableWebSecurity
// - Defines which endpoints are public: /api/auth/**, /actuator/health
// - Defines which endpoints need JWT: /api/**
// - Sets up password encoder (BCryptPasswordEncoder)
// - Registers JwtFilter
```

---

## 16. client Folder

### What Client Classes Are

Client classes are used when your service needs to **call another service or API**. In microservice architecture, different services talk to each other over HTTP. The `client/` folder holds all the code that makes these outgoing calls.

### Three Ways to Call External APIs

| Approach | Description | When to Use |
|---|---|---|
| **FeignClient** | Declarative HTTP client — define an interface and Feign generates the code | Microservices calling each other (recommended) |
| **RestTemplate** | Older Spring HTTP client — synchronous | Simple use cases, legacy code |
| **WebClient** | Reactive HTTP client — non-blocking | High performance, reactive applications |

### Sample Client Code (FeignClient)

```java
package com.company.project.client;

import com.company.project.dto.response.PaymentResponse;
import org.springframework.cloud.openfeign.FeignClient;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;

// name = service name in Eureka/Kubernetes
// url = fallback URL if no service discovery
@FeignClient(name = "payment-service", url = "${payment.service.url}")
public interface PaymentClient {

    @PostMapping("/api/payments/process")
    PaymentResponse processPayment(@RequestBody PaymentRequest request);

    @GetMapping("/api/payments/{id}")
    PaymentResponse getPaymentById(@PathVariable String id);
}
```

```java
// NotificationClient.java — sends notifications via another microservice
@FeignClient(name = "notification-service", url = "${notification.service.url}")
public interface NotificationClient {

    @PostMapping("/api/notifications/send")
    void sendNotification(@RequestBody NotificationRequest request);
}
```

**Usage in service:**
```java
@Service
@RequiredArgsConstructor
public class OrderServiceImpl implements OrderService {

    private final PaymentClient paymentClient;
    private final NotificationClient notificationClient;

    public void processOrder(Order order) {
        // Call payment service
        PaymentResponse payment = paymentClient.processPayment(buildPaymentRequest(order));
        // Call notification service
        notificationClient.sendNotification(buildNotification(order));
    }
}
```

---

## 17. kafka Folder

### How to Organize Kafka Files

Kafka files are split into three sub-folders:

```
kafka/
├── producer/     ← Classes that SEND messages to Kafka
├── consumer/     ← Classes that RECEIVE messages from Kafka
└── event/        ← Event data classes (like DTOs for Kafka messages)
```

### kafka/producer — CheckResultProducer Example

```java
package com.company.project.kafka.producer;

import com.company.project.constant.KafkaTopicConstants;
import com.company.project.kafka.event.CheckResultEvent;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.kafka.core.KafkaTemplate;
import org.springframework.stereotype.Service;

@Service
@RequiredArgsConstructor
@Slf4j
public class CheckResultProducer {

    private final KafkaTemplate<String, CheckResultEvent> kafkaTemplate;

    public void sendCheckResult(CheckResultEvent event) {
        log.info("Sending check result event for service: {}", event.getServiceId());
        kafkaTemplate.send(KafkaTopicConstants.CHECK_RESULT_TOPIC, event.getServiceId(), event);
    }
}
```

### kafka/consumer — CheckResultConsumer Example

```java
package com.company.project.kafka.consumer;

import com.company.project.kafka.event.CheckResultEvent;
import com.company.project.service.DetectionService;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.kafka.annotation.KafkaListener;
import org.springframework.stereotype.Component;

@Component
@RequiredArgsConstructor
@Slf4j
public class CheckResultConsumer {

    private final DetectionService detectionService;

    @KafkaListener(
        topics = "${kafka.topics.check-result}",
        groupId = "${spring.kafka.consumer.group-id}"
    )
    public void consume(CheckResultEvent event) {
        log.info("Received check result for service: {}", event.getServiceId());
        detectionService.processCheckResult(event);
    }
}
```

### kafka/event — CheckResultEvent Example

```java
package com.company.project.kafka.event;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.time.LocalDateTime;

@Data
@NoArgsConstructor
@AllArgsConstructor
@Builder
public class CheckResultEvent {

    private String serviceId;
    private String serviceName;
    private String status;           // UP, DOWN, DEGRADED
    private Long responseTimeMs;
    private LocalDateTime checkedAt;
    private String errorMessage;
}
```

---

## 18. redis Folder

### Where to Keep Redis Cache Logic

All Redis-related caching logic lives in the `redis/` folder. This keeps cache code separate from business logic.

### Sample Redis Cache Service

```java
package com.company.project.redis;

import com.company.project.constant.RedisKeyConstants;
import com.company.project.kafka.event.CheckResultEvent;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.data.redis.core.RedisTemplate;
import org.springframework.stereotype.Service;

import java.time.Duration;
import java.util.List;

@Service
@RequiredArgsConstructor
@Slf4j
public class RecentCheckCacheService {

    private final RedisTemplate<String, Object> redisTemplate;

    private static final int MAX_RECENT_CHECKS = 100;
    private static final Duration CACHE_TTL = Duration.ofHours(24);

    // Save a check result to Redis list
    public void saveCheckResult(CheckResultEvent event) {
        String key = RedisKeyConstants.RECENT_CHECKS_PREFIX + event.getServiceId();
        log.info("Saving check result to Redis with key: {}", key);

        redisTemplate.opsForList().leftPush(key, event);
        redisTemplate.opsForList().trim(key, 0, MAX_RECENT_CHECKS - 1);
        redisTemplate.expire(key, CACHE_TTL);
    }

    // Get recent check results from Redis
    public List<Object> getRecentChecks(String serviceId) {
        String key = RedisKeyConstants.RECENT_CHECKS_PREFIX + serviceId;
        return redisTemplate.opsForList().range(key, 0, -1);
    }

    // Check if a value exists in Redis
    public boolean hasRecentFailures(String serviceId) {
        String key = RedisKeyConstants.FAILURE_FLAG_PREFIX + serviceId;
        return Boolean.TRUE.equals(redisTemplate.hasKey(key));
    }
}
```

### Redis Key Naming Convention

```java
// RedisKeyConstants.java
package com.company.project.constant;

public final class RedisKeyConstants {

    private RedisKeyConstants() {}

    public static final String RECENT_CHECKS_PREFIX = "monitoring:checks:";
    public static final String FAILURE_FLAG_PREFIX  = "monitoring:failure:";
    public static final String USER_SESSION_PREFIX  = "session:user:";
    public static final String RATE_LIMIT_PREFIX    = "ratelimit:";
}
```

**Good Redis key format:** `service-name:entity:identifier`  
Example: `monitoring:checks:service-123`, `session:user:456`

---

## 19. scheduler Folder

### What Scheduler Classes Are

Schedulers are classes that **run automatically at a fixed time or interval** without being triggered by an HTTP request. They are useful for background tasks.

### When to Use @Scheduled

- Running a health check every 30 seconds
- Generating daily reports at midnight
- Cleaning up old records every week
- Sending reminder emails every morning

### Sample Scheduler Code

```java
package com.company.project.scheduler;

import com.company.project.service.MonitoringService;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.stereotype.Component;

@Component
@RequiredArgsConstructor
@Slf4j
public class MonitoringJob {

    private final MonitoringService monitoringService;

    // Run every 30 seconds
    @Scheduled(fixedDelay = 30000)
    public void runHealthChecks() {
        log.info("Running scheduled health check job");
        monitoringService.checkAllServices();
    }

    // Run every day at midnight
    @Scheduled(cron = "0 0 0 * * *")
    public void generateDailyReport() {
        log.info("Generating daily monitoring report");
        monitoringService.generateDailyReport();
    }
}
```

```java
package com.company.project.scheduler;

import lombok.extern.slf4j.Slf4j;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.stereotype.Component;

@Component
@Slf4j
public class CleanupJob {

    // Run every Sunday at 2 AM
    @Scheduled(cron = "0 0 2 * * SUN")
    public void cleanupOldLogs() {
        log.info("Running weekly log cleanup job");
        // delete logs older than 30 days
    }
}
```

**Note:** Add `@EnableScheduling` to your main application class or a config class to activate schedulers.

---

## 20. validation Folder

### Custom Validation Annotations

Spring provides built-in validators like `@NotBlank`, `@Email`, `@Size`. But sometimes you need custom validation rules — for example, checking if a password is strong enough, or checking if an email is already registered.

The `validation/` folder holds these custom validators.

### Sample Custom Validation Code

```java
// Step 1: Create the annotation
package com.company.project.validation;

import jakarta.validation.Constraint;
import jakarta.validation.Payload;
import java.lang.annotation.*;

@Documented
@Constraint(validatedBy = PasswordValidator.class)
@Target({ElementType.FIELD})
@Retention(RetentionPolicy.RUNTIME)
public @interface ValidPassword {
    String message() default "Password must contain uppercase, lowercase, digit, and special character";
    Class<?>[] groups() default {};
    Class<? extends Payload>[] payload() default {};
}
```

```java
// Step 2: Create the validator
package com.company.project.validation;

import jakarta.validation.ConstraintValidator;
import jakarta.validation.ConstraintValidatorContext;
import java.util.regex.Pattern;

public class PasswordValidator implements ConstraintValidator<ValidPassword, String> {

    private static final String PASSWORD_PATTERN =
        "^(?=.*[0-9])(?=.*[a-z])(?=.*[A-Z])(?=.*[@#$%^&+=!])(?=\\S+$).{8,}$";

    @Override
    public boolean isValid(String password, ConstraintValidatorContext context) {
        if (password == null) return false;
        return Pattern.matches(PASSWORD_PATTERN, password);
    }
}
```

```java
// Step 3: Use the custom annotation in request DTO
public class CreateUserRequest {

    @ValidPassword
    private String password;
}
```

---

## 21. constant Folder

### What Constants Are

Constants are fixed values that do not change. Instead of writing `"check-result-topic"` in ten different places in your code, define it once as a constant and use the constant everywhere. This way, if the value ever changes, you update it in only one place.

### Sample Constants Code

```java
package com.company.project.constant;

public final class AppConstants {

    private AppConstants() {} // Prevent instantiation

    public static final int MAX_RETRY_COUNT    = 3;
    public static final int DEFAULT_PAGE_SIZE  = 20;
    public static final int MAX_PAGE_SIZE      = 100;
    public static final String DEFAULT_SORT_BY = "createdAt";
}
```

```java
package com.company.project.constant;

public final class KafkaTopicConstants {

    private KafkaTopicConstants() {}

    public static final String CHECK_RESULT_TOPIC    = "monitoring.check.result";
    public static final String INCIDENT_CREATED_TOPIC = "monitoring.incident.created";
    public static final String ALERT_TOPIC           = "monitoring.alert";
}
```

```java
package com.company.project.constant;

public final class SecurityConstants {

    private SecurityConstants() {}

    public static final String TOKEN_PREFIX     = "Bearer ";
    public static final String HEADER_STRING    = "Authorization";
    public static final long JWT_EXPIRATION_MS  = 86400000L; // 24 hours
    public static final String[] PUBLIC_URLS    = {
        "/api/auth/**",
        "/actuator/health",
        "/swagger-ui/**",
        "/v3/api-docs/**"
    };
}
```

---

## 22. util Folder

### What Utility Classes Are

Utility classes contain general-purpose **helper methods** that can be reused across the application. They are usually `static` methods.

### When to Use util

- Date formatting and parsing
- String manipulation
- File operations
- Token generation/parsing

### When NOT to Use util

- Business logic — that belongs in service
- Database operations — that belongs in repository
- API-specific logic — that belongs in controller

Too many util classes is a sign that business logic is being put in the wrong place.

### Sample Utility Code

```java
package com.company.project.util;

import java.time.LocalDateTime;
import java.time.ZoneId;
import java.time.format.DateTimeFormatter;

public final class DateUtil {

    private DateUtil() {}

    private static final DateTimeFormatter FORMATTER =
        DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");

    public static String format(LocalDateTime dateTime) {
        if (dateTime == null) return null;
        return dateTime.format(FORMATTER);
    }

    public static LocalDateTime now() {
        return LocalDateTime.now(ZoneId.of("UTC"));
    }

    public static boolean isExpired(LocalDateTime expiresAt) {
        return LocalDateTime.now().isAfter(expiresAt);
    }
}
```

---

## 23. resources Folder

### application.yml — Main Configuration

```yaml
spring:
  application:
    name: my-spring-boot-app
  profiles:
    active: dev   # Change to 'prod' in production

server:
  port: 8080
```

### application-dev.yml — Development Environment

```yaml
spring:
  datasource:
    url: jdbc:postgresql://localhost:5432/mydb_dev
    username: devuser
    password: devpassword

  redis:
    host: localhost
    port: 6379

  kafka:
    bootstrap-servers: localhost:9092

logging:
  level:
    com.company.project: DEBUG
```

### application-prod.yml — Production Environment

```yaml
spring:
  datasource:
    url: ${DATABASE_URL}       # Read from environment variable
    username: ${DB_USERNAME}
    password: ${DB_PASSWORD}

  redis:
    host: ${REDIS_HOST}
    port: ${REDIS_PORT}

  kafka:
    bootstrap-servers: ${KAFKA_BROKERS}

logging:
  level:
    com.company.project: INFO  # Less logging in production
```

### db/migration — Flyway Migration Files

```
db/migration/
├── V1__create_users_table.sql
├── V2__create_products_table.sql
├── V3__add_active_column_to_users.sql
└── V4__create_orders_table.sql
```

Flyway runs these files **in order** when the application starts. Once a file runs, Flyway never runs it again. This keeps your database schema in sync with your code.

```sql
-- V1__create_users_table.sql
CREATE TABLE users (
    id         BIGSERIAL PRIMARY KEY,
    name       VARCHAR(100)        NOT NULL,
    email      VARCHAR(255) UNIQUE NOT NULL,
    password   VARCHAR(255)        NOT NULL,
    active     BOOLEAN DEFAULT TRUE,
    created_at TIMESTAMP DEFAULT NOW(),
    updated_at TIMESTAMP DEFAULT NOW()
);
```

---

## 24. test Folder

### How to Arrange Test Files

Test files follow the **exact same package structure** as the main source files. This makes it easy to find the test for any class.

```
test/java/com/company/project/
├── controller/
│   └── UserControllerTest.java      ← Tests for UserController
├── service/
│   └── UserServiceTest.java         ← Tests for UserServiceImpl
├── repository/
│   └── UserRepositoryTest.java      ← Tests for UserRepository
└── integration/
    └── UserIntegrationTest.java     ← Full end-to-end tests
```

### Unit Test vs Integration Test

| Unit Test | Integration Test |
|---|---|
| Tests one class in isolation | Tests multiple layers together |
| Uses mocks for dependencies | Uses real database, real beans |
| Very fast to run | Slower to run |
| Example: `UserServiceTest` | Example: `UserIntegrationTest` |

### Sample Service Unit Test

```java
package com.company.project.service;

import com.company.project.dto.request.CreateUserRequest;
import com.company.project.dto.response.UserResponse;
import com.company.project.entity.User;
import com.company.project.exception.ResourceNotFoundException;
import com.company.project.mapper.UserMapper;
import com.company.project.repository.UserRepository;
import com.company.project.service.impl.UserServiceImpl;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.junit.jupiter.MockitoExtension;

import java.util.Optional;

import static org.assertj.core.api.Assertions.assertThat;
import static org.assertj.core.api.Assertions.assertThatThrownBy;
import static org.mockito.Mockito.*;

@ExtendWith(MockitoExtension.class)
class UserServiceTest {

    @Mock
    private UserRepository userRepository;

    @Mock
    private UserMapper userMapper;

    @InjectMocks
    private UserServiceImpl userService;

    @Test
    void shouldReturnUserWhenFound() {
        // Arrange
        User user = User.builder().id(1L).name("Alice").email("alice@example.com").build();
        UserResponse expectedResponse = UserResponse.builder().id(1L).name("Alice").build();

        when(userRepository.findById(1L)).thenReturn(Optional.of(user));
        when(userMapper.toResponse(user)).thenReturn(expectedResponse);

        // Act
        UserResponse actualResponse = userService.getUserById(1L);

        // Assert
        assertThat(actualResponse.getName()).isEqualTo("Alice");
        verify(userRepository, times(1)).findById(1L);
    }

    @Test
    void shouldThrowExceptionWhenUserNotFound() {
        when(userRepository.findById(99L)).thenReturn(Optional.empty());

        assertThatThrownBy(() -> userService.getUserById(99L))
                .isInstanceOf(ResourceNotFoundException.class)
                .hasMessageContaining("User not found");
    }
}
```

---

## 25. Layer Flow Explanation

### Basic Flow: Controller → Service → Repository → Database

```
Client (Browser / Postman / Mobile App)
        |
        | HTTP Request (POST /api/users)
        ↓
+------------------+
|   Controller     |  → Receives request, validates input, calls service
+------------------+
        |
        | calls userService.createUser(request)
        ↓
+------------------+
|   Service        |  → Business logic, rules, calculations
+------------------+
        |
        | calls userRepository.save(entity)
        ↓
+------------------+
|   Repository     |  → Builds and executes SQL query
+------------------+
        |
        | SQL INSERT INTO users ...
        ↓
+------------------+
|   Database       |  → PostgreSQL / MySQL stores the data
+------------------+
        |
        | Returns saved record
        ↑ (Response flows back up through all layers)
```

### Kafka Flow: Controller → Service → Kafka Producer → Kafka Topic

```
Controller
    |
    ↓
Service (business logic)
    |
    ↓
CheckResultProducer.sendCheckResult(event)
    |
    ↓
Kafka Topic: "monitoring.check.result"
    |
    ↓  (Different microservice or same service)
CheckResultConsumer.consume(event)
    |
    ↓
Service (process the consumed event)
```

### Detection Flow: Consumer → Service → Redis → Rule Engine → External Client

```
Kafka Consumer (receives check result)
    |
    ↓
DetectionService.processCheckResult(event)
    |
    ├── Save to Redis (RecentCheckCacheService)
    |
    ├── RuleEngineService.evaluate(recentChecks)
    |       |
    |       └── Is there an incident? YES/NO
    |
    └── If incident detected → IncidentClient.createIncident(incident)
                                    |
                                    ↓
                              Other Microservice
                              (Incident Service)
```

### External API Call Flow: Controller → Service → Client → Other Microservice

```
Controller
    |
    ↓
Service
    |
    ↓
PaymentClient.processPayment(request)    [FeignClient]
    |
    | HTTP POST → payment-service/api/payments/process
    ↓
Payment Microservice
    |
    ↓
Returns PaymentResponse
    |
    ↑  Back to Service → Back to Controller → Back to Client
```

---

## 26. Example: User Module Folder Arrangement

Here is how all files for a complete User module are organized:

```
com/company/project/
│
├── controller/
│   └── UserController.java
│
├── service/
│   └── UserService.java            ← Interface
│
├── service/impl/
│   └── UserServiceImpl.java        ← Implementation
│
├── repository/
│   └── UserRepository.java
│
├── entity/
│   └── User.java
│
├── dto/
│   ├── request/
│   │   ├── CreateUserRequest.java
│   │   └── UpdateUserRequest.java
│   └── response/
│       └── UserResponse.java
│
└── mapper/
    └── UserMapper.java
```

### Each File Explained

| File | What It Does |
|---|---|
| `UserController` | Handles `/api/users` HTTP requests |
| `UserService` | Interface declaring what operations user module supports |
| `UserServiceImpl` | Actual business logic — validates, calls repository, uses mapper |
| `UserRepository` | Connects to `users` database table |
| `User` | Java class that represents the `users` table |
| `CreateUserRequest` | Data the client sends when creating a user |
| `UserResponse` | Data your API sends back about a user (no password) |
| `UserMapper` | Converts `User` entity to `UserResponse` and back |

---

## 27. Example: Product Module Folder Arrangement

```
com/company/project/
│
├── controller/
│   └── ProductController.java
│
├── service/
│   └── ProductService.java
│
├── service/impl/
│   └── ProductServiceImpl.java
│
├── repository/
│   └── ProductRepository.java
│
├── entity/
│   └── Product.java
│
├── dto/
│   ├── request/
│   │   └── CreateProductRequest.java
│   └── response/
│       └── ProductResponse.java
│
└── mapper/
    └── ProductMapper.java
```

### Product Entity

```java
@Entity
@Table(name = "products")
@Getter @Setter @Builder @NoArgsConstructor @AllArgsConstructor
public class Product {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(nullable = false)
    private String name;

    @Column(nullable = false)
    private String description;

    @Column(nullable = false)
    private BigDecimal price;

    @Column(nullable = false)
    private Integer stock;

    @ManyToOne
    @JoinColumn(name = "category_id")
    private Category category;

    @CreationTimestamp
    private LocalDateTime createdAt;
}
```

---

## 28. Example: Monitoring Project Folder Arrangement

This is a real-world example of a monitoring system with two microservices.

### Monitoring Service

```
monitoring-service/
└── com/company/monitoring/
    │
    ├── entity/
    │   ├── MonitoredService.java       ← Represents a service being monitored
    │   └── MonitoringLog.java          ← One log entry per health check
    │
    ├── repository/
    │   ├── MonitoredServiceRepository.java
    │   └── MonitoringLogRepository.java
    │
    ├── service/
    │   └── MonitoringService.java       ← Interface
    │
    ├── service/impl/
    │   └── MonitoringServiceImpl.java   ← Runs health checks, saves logs
    │
    ├── scheduler/
    │   └── MonitoringJob.java           ← @Scheduled → calls MonitoringService every 30s
    │
    └── kafka/
        ├── producer/
        │   └── CheckResultProducer.java  ← Sends CheckResultEvent to Kafka
        └── event/
            └── CheckResultEvent.java     ← Event data class
```

### Detection Service

```
detection-service/
└── com/company/detection/
    │
    ├── service/
    │   ├── DetectionService.java        ← Interface
    │   ├── RuleEngineService.java       ← Interface
    │   └── impl/
    │       ├── DetectionServiceImpl.java    ← Processes check results
    │       └── RuleEngineServiceImpl.java   ← Evaluates failure rules
    │
    ├── redis/
    │   └── RecentCheckCacheService.java ← Stores recent checks in Redis
    │
    ├── client/
    │   └── IncidentClient.java          ← FeignClient → calls Incident Service
    │
    └── kafka/
        └── consumer/
            └── CheckResultConsumer.java ← @KafkaListener → receives events
```

### How the Two Services Work Together

```
Monitoring Service:
[MonitoringJob] → [MonitoringServiceImpl] → checks URL
                                          → saves MonitoringLog to DB
                                          → [CheckResultProducer] → Kafka

Detection Service:
Kafka → [CheckResultConsumer] → [DetectionServiceImpl]
                                        → [RecentCheckCacheService] (Redis)
                                        → [RuleEngineServiceImpl]
                                        → if incident: [IncidentClient] → Incident Service
```

---

## 29. Package-by-Layer vs Package-by-Feature

### Package-by-Layer

All classes of the same type are in the same package:

```
com/company/project/
├── controller/
│   ├── UserController.java
│   ├── ProductController.java
│   └── OrderController.java
├── service/
│   ├── UserService.java
│   ├── ProductService.java
│   └── OrderService.java
├── repository/
│   ├── UserRepository.java
│   ├── ProductRepository.java
│   └── OrderRepository.java
└── entity/
    ├── User.java
    ├── Product.java
    └── Order.java
```

### Package-by-Feature

All classes related to one feature are in the same package:

```
com/company/project/
├── user/
│   ├── UserController.java
│   ├── UserService.java
│   ├── UserServiceImpl.java
│   ├── UserRepository.java
│   └── User.java
├── product/
│   ├── ProductController.java
│   ├── ProductService.java
│   └── ...
└── order/
    ├── OrderController.java
    └── ...
```

### Comparison Table

| Aspect | Package-by-Layer | Package-by-Feature |
|---|---|---|
| **Navigation** | Must jump between packages to work on one feature | All related files are in one place |
| **Scalability** | Gets messy with many features | Scales well with many features |
| **Teamwork** | Multiple people can conflict in same package | Each team works in their own feature package |
| **Visibility** | Easy to see all controllers or all services | Easy to see all files for one feature |
| **Testing** | Tests mirror the layer structure | Tests are co-located with features |

### When to Use Each

| Project Size | Recommended Approach |
|---|---|
| **Small (1–5 features)** | Package-by-layer — simple and familiar |
| **Medium (5–15 features)** | Package-by-layer with sub-packages inside features |
| **Large (15+ features)** | Package-by-feature — much easier to navigate |
| **Microservices** | Package-by-feature — each service has clear boundaries |

---

## 30. Best Practices

### Controller Layer

- **Keep controller thin** — controller should have maximum 5–10 lines per method
- Call service methods directly; do not write logic in controller
- Always use `@Valid` for request validation
- Always return `ResponseEntity` with proper HTTP status

### Service Layer

- **Keep business logic inside service** — not in controller, not in repository
- Use service interfaces, not concrete classes, in controller
- Use `@Transactional` for methods that write to the database
- Log important business events using `@Slf4j`

### Data Transfer

- **Never expose entity directly** in API response
- Always use DTOs for both request and response
- Use mapper to convert between entity and DTO
- Keep request and response DTOs in separate sub-packages

### Code Organization

- **Use meaningful package names** — `kafka/producer`, `kafka/consumer`, `kafka/event`
- **Keep config classes separate** in the `config/` folder
- **Centralize exception handling** in `GlobalExceptionHandler`
- **Keep Kafka, Redis, Scheduler code in separate folders** — do not put them in service classes directly

### Avoiding Problems

- **Avoid huge service classes** — if a service class has 500+ lines, split it into smaller services
- **Avoid circular dependencies** — Service A calling Service B which calls Service A
- **Write tests that mirror the package structure** — test files in the same package as the class being tested

---

## 31. Common Mistakes

### Mistake 1: Writing All Code in Controller

```java
// ❌ WRONG - business logic in controller
@PostMapping("/users")
public ResponseEntity<User> createUser(@RequestBody User user) {
    if (userRepository.existsByEmail(user.getEmail())) {
        throw new RuntimeException("Email already exists");
    }
    user.setPassword(passwordEncoder.encode(user.getPassword()));
    return ResponseEntity.ok(userRepository.save(user));
}

// ✅ CORRECT - controller calls service
@PostMapping("/users")
public ResponseEntity<UserResponse> createUser(@Valid @RequestBody CreateUserRequest request) {
    return ResponseEntity.status(HttpStatus.CREATED).body(userService.createUser(request));
}
```

### Mistake 2: Exposing Entity Directly

```java
// ❌ WRONG - returns entity (password exposed!)
public ResponseEntity<User> getUser(@PathVariable Long id) {
    return ResponseEntity.ok(userRepository.findById(id).get());
}

// ✅ CORRECT - returns response DTO
public ResponseEntity<UserResponse> getUser(@PathVariable Long id) {
    return ResponseEntity.ok(userService.getUserById(id));
}
```

### Mistake 3: No Exception Handler

```java
// ❌ WRONG - client gets 500 with Java stack trace
User user = userRepository.findById(id)
        .orElseThrow(() -> new RuntimeException("Not found")); // Exposes internal error

// ✅ CORRECT - client gets 404 with clear message
User user = userRepository.findById(id)
        .orElseThrow(() -> new ResourceNotFoundException("User not found with id: " + id));
// GlobalExceptionHandler catches this and returns proper 404 JSON
```

### Mistake 4: Hardcoding Topic Names and Redis Keys

```java
// ❌ WRONG - hardcoded strings scattered everywhere
kafkaTemplate.send("monitoring.check.result", event);
redisTemplate.get("monitoring:checks:" + serviceId);

// ✅ CORRECT - use constants
kafkaTemplate.send(KafkaTopicConstants.CHECK_RESULT_TOPIC, event);
redisTemplate.get(RedisKeyConstants.RECENT_CHECKS_PREFIX + serviceId);
```

### Mistake 5: Putting Business Logic in Repository

```java
// ❌ WRONG - business calculation in repository
@Query("SELECT u FROM User u WHERE u.age > 18 AND u.verified = true AND u.subscription = 'PREMIUM'")
List<User> findEligibleForDiscount(); // Too much business logic in query

// ✅ CORRECT - simple query in repository, business rule in service
List<User> findByAgeGreaterThan(int age);
// Service: filter and apply business rules
```

### Other Common Mistakes

- Keeping all files in one package (no structure)
- Mixing entity and DTO — using the same class for both
- Creating too many util classes instead of putting logic in service
- Not using Spring profiles — same config for dev and prod
- Bad package naming like `helpers/`, `managers/`, `processors/`

---

## 32. Naming Conventions

### Good Naming

| Class Type | Good Name | Why |
|---|---|---|
| Controller | `UserController` | Clear — handles user-related HTTP endpoints |
| Service Interface | `UserService` | Clear — defines user business operations |
| Service Impl | `UserServiceImpl` | Standard convention for implementation classes |
| Repository | `UserRepository` | Clear — accesses user database table |
| Mapper | `UserMapper` | Clear — converts user entity/DTO |
| Entity | `User` | Same as table name (singular) |
| Request DTO | `CreateUserRequest` | Verb + Entity + Request pattern |
| Response DTO | `UserResponse` | Entity + Response pattern |
| Exception | `UserNotFoundException` | Entity + Not + Found + Exception |
| Config | `SecurityConfig`, `KafkaConfig` | Topic + Config pattern |
| Scheduler | `MonitoringJob`, `CleanupJob` | Topic + Job pattern |
| Kafka Producer | `CheckResultProducer` | Event + Producer |
| Kafka Consumer | `CheckResultConsumer` | Event + Consumer |
| Kafka Event | `CheckResultEvent` | Topic/Action + Event |
| Redis Service | `RecentCheckCacheService` | Data + Cache + Service |

### Bad Naming — Avoid These

| Bad Name | Problem |
|---|---|
| `UserLogic` | Unclear — logic for what? |
| `UserManager` | Too generic — manager of what? |
| `UserData` | Too vague — what kind of data? |
| `CommonService` | Has no clear domain — what does it do? |
| `Helper` | Means nothing — what does it help with? |
| `ProcessUser` | Verb as class name — wrong convention |
| `UserInfo` | Unclear — is it entity, DTO, or something else? |
| `Utils` | Too broad — split into specific util classes |

---

## 33. Final Recommended Structure

Here is the final production-grade structure for a Spring Boot microservice using REST API, PostgreSQL, Redis, Kafka, Feign Client, Scheduler, and JWT Security:

```
my-microservice/
├── src/
│   ├── main/
│   │   ├── java/
│   │   │   └── com/company/service/
│   │   │       │
│   │   │       ├── MyServiceApplication.java
│   │   │       │
│   │   │       ├── config/
│   │   │       │   ├── SecurityConfig.java        ← JWT security rules
│   │   │       │   ├── KafkaConfig.java           ← Producer/consumer factory
│   │   │       │   ├── RedisConfig.java           ← RedisTemplate bean
│   │   │       │   ├── FeignConfig.java           ← Feign error decoder
│   │   │       │   ├── SwaggerConfig.java         ← API documentation
│   │   │       │   └── SchedulerConfig.java       ← @EnableScheduling
│   │   │       │
│   │   │       ├── controller/
│   │   │       │   └── [Feature]Controller.java
│   │   │       │
│   │   │       ├── service/
│   │   │       │   └── [Feature]Service.java      ← Interface only
│   │   │       │
│   │   │       ├── service/impl/
│   │   │       │   └── [Feature]ServiceImpl.java  ← @Service implementation
│   │   │       │
│   │   │       ├── repository/
│   │   │       │   └── [Feature]Repository.java   ← JpaRepository
│   │   │       │
│   │   │       ├── entity/
│   │   │       │   └── [Feature].java             ← @Entity, @Table
│   │   │       │
│   │   │       ├── dto/
│   │   │       │   ├── request/
│   │   │       │   │   └── Create[Feature]Request.java
│   │   │       │   └── response/
│   │   │       │       └── [Feature]Response.java
│   │   │       │
│   │   │       ├── mapper/
│   │   │       │   └── [Feature]Mapper.java
│   │   │       │
│   │   │       ├── exception/
│   │   │       │   ├── GlobalExceptionHandler.java
│   │   │       │   ├── ResourceNotFoundException.java
│   │   │       │   ├── BadRequestException.java
│   │   │       │   └── ErrorResponse.java
│   │   │       │
│   │   │       ├── security/
│   │   │       │   ├── JwtService.java
│   │   │       │   ├── JwtFilter.java
│   │   │       │   └── CustomUserDetailsService.java
│   │   │       │
│   │   │       ├── client/
│   │   │       │   ├── PaymentClient.java         ← @FeignClient
│   │   │       │   └── NotificationClient.java
│   │   │       │
│   │   │       ├── kafka/
│   │   │       │   ├── producer/
│   │   │       │   │   └── [Feature]Producer.java
│   │   │       │   ├── consumer/
│   │   │       │   │   └── [Feature]Consumer.java
│   │   │       │   └── event/
│   │   │       │       └── [Feature]Event.java
│   │   │       │
│   │   │       ├── redis/
│   │   │       │   └── [Feature]CacheService.java
│   │   │       │
│   │   │       ├── scheduler/
│   │   │       │   └── [Feature]Job.java
│   │   │       │
│   │   │       ├── validation/
│   │   │       │   ├── ValidPassword.java
│   │   │       │   └── PasswordValidator.java
│   │   │       │
│   │   │       ├── constant/
│   │   │       │   ├── AppConstants.java
│   │   │       │   ├── KafkaTopicConstants.java
│   │   │       │   ├── RedisKeyConstants.java
│   │   │       │   └── SecurityConstants.java
│   │   │       │
│   │   │       └── util/
│   │   │           ├── DateUtil.java
│   │   │           └── TokenUtil.java
│   │   │
│   │   └── resources/
│   │       ├── application.yml
│   │       ├── application-dev.yml
│   │       ├── application-prod.yml
│   │       └── db/migration/
│   │           ├── V1__init_schema.sql
│   │           └── V2__add_indexes.sql
│   │
│   └── test/
│       └── java/com/company/service/
│           ├── controller/
│           ├── service/
│           ├── repository/
│           └── integration/
│
├── pom.xml
├── Dockerfile
├── docker-compose.yml
├── README.md
└── .gitignore
```

---

## 34. Interview Questions

### Section A: Project Structure Questions

**Q1. Why is it important to keep `ProjectApplication.java` in the root package?**

`@SpringBootApplication` uses `@ComponentScan` which scans all sub-packages of the package where the main class is located. If you put the main class in `controller/` package, Spring will not scan `service/` or `repository/` packages and those beans will not be found, causing application startup failure.

---

**Q2. What is the difference between the service folder and service/impl folder?**

The `service/` folder contains **interfaces** that define what operations are available. The `service/impl/` folder contains **implementation classes** annotated with `@Service` that contain the actual business logic. Keeping them separate allows loose coupling and easier testing with mock implementations.

---

**Q3. Why should we not write business logic in the controller?**

Controllers should be thin — they only handle HTTP concerns (receive request, return response). Business logic in controllers causes: tight coupling between HTTP layer and business rules, difficulty in unit testing, code duplication when same logic is needed from different endpoints, and violation of Single Responsibility Principle.

---

**Q4. Why should we use DTOs instead of exposing entities directly?**

Entities are tied to the database structure. Exposing them directly can leak sensitive fields (like `password`), expose internal IDs, and break the API contract when the database schema changes. DTOs let you control exactly what data is exposed and are independent of database changes.

---

**Q5. What is the difference between a request DTO and a response DTO?**

A **request DTO** represents data coming from the client (POST/PUT body). It has validation annotations like `@NotBlank`, `@Email`. A **response DTO** represents data sent back to the client. It has no validation annotations and must not include sensitive fields like passwords.

---

### Section B: Layer and Bean Questions

**Q6. What does `@RestController` do? How is it different from `@Controller`?**

`@RestController` = `@Controller` + `@ResponseBody`. It means every method in the class automatically converts its return value to JSON. `@Controller` alone is used when returning view names (Thymeleaf/JSP), and you need `@ResponseBody` on individual methods for JSON output.

---

**Q7. What does `@Service` annotation do?**

`@Service` marks a class as a Spring-managed bean that contains business logic. It is a specialization of `@Component`. Spring scans and registers it in the application context. It also enables proxy creation for `@Transactional` to work correctly.

---

**Q8. What does `@Repository` annotation do?**

`@Repository` marks a class as a Spring-managed bean for database operations. It also enables Spring's exception translation — JDBC exceptions are automatically converted into Spring's `DataAccessException` hierarchy, which is easier to handle.

---

**Q9. What does `@Transactional` mean and where should you use it?**

`@Transactional` wraps a method in a database transaction. If the method succeeds, changes are committed. If an exception occurs, all changes are rolled back. Use it on service methods that perform write operations (create, update, delete). Do not use it on read-only methods without `readOnly = true`.

---

**Q10. What is `JpaRepository` and what does it provide?**

`JpaRepository<Entity, ID>` is a Spring Data interface that provides built-in methods for CRUD operations: `findAll()`, `findById()`, `save()`, `deleteById()`, `count()`, `existsById()`, and more. You extend this interface and Spring auto-generates the implementation at runtime.

---

### Section C: DTO and Mapper Questions

**Q11. What is the purpose of a Mapper class?**

A Mapper converts between entity and DTO. It avoids repeating copy-paste code for field assignments in multiple places. It keeps entity-to-DTO conversion logic in one place. If the entity changes, only the mapper needs to be updated.

---

**Q12. What is MapStruct? How is it different from a manual mapper?**

MapStruct is a compile-time code generator. You define a mapper interface with annotations, and MapStruct generates the implementation during compilation. It is faster than reflection-based mappers and produces clean, readable code. A manual mapper is a `@Component` class where you write the conversion code yourself.

---

**Q13. Can the same class be used as both entity and DTO?**

Technically yes, but it is a bad practice. Entity classes are tied to database columns and JPA annotations. DTO classes are tied to API contracts. Mixing them means database changes break the API and API changes affect the database. Always keep them separate.

---

### Section D: Exception Handling Questions

**Q14. What is `@RestControllerAdvice` and how does it work?**

`@RestControllerAdvice` creates a global exception handler that intercepts exceptions thrown by any controller in the application. It combines `@ControllerAdvice` and `@ResponseBody`. Methods inside it annotated with `@ExceptionHandler` handle specific exception types and return proper JSON error responses.

---

**Q15. What HTTP status code should `ResourceNotFoundException` return?**

`ResourceNotFoundException` should return **404 Not Found**. This tells the client that the requested resource (user, product, etc.) does not exist. Use `@ResponseStatus(HttpStatus.NOT_FOUND)` on the exception class or return `ResponseEntity.status(404)` in the handler.

---

**Q16. What happens when `@Valid` fails in a controller? Who handles it?**

When `@Valid` fails, Spring throws `MethodArgumentNotValidException`. The `GlobalExceptionHandler` should have an `@ExceptionHandler(MethodArgumentNotValidException.class)` method that catches this, extracts field-level validation errors, and returns a 400 Bad Request response with a map of field names to error messages.

---

### Section E: Config and Security Questions

**Q17. What is the purpose of the `config/` folder? Give examples of what goes there.**

The `config/` folder holds Spring configuration classes annotated with `@Configuration`. Examples: `SecurityConfig` (security rules), `KafkaConfig` (producer/consumer setup), `RedisConfig` (connection and template setup), `SwaggerConfig` (API documentation), `CorsConfig` (cross-origin settings).

---

**Q18. What does `SecurityConfig` do?**

`SecurityConfig` defines Spring Security rules: which URLs are public (no authentication needed), which URLs require authentication, what authentication mechanism to use (JWT), which password encoder to use (`BCryptPasswordEncoder`), and which filters to apply (like `JwtFilter`).

---

**Q19. What is a JWT Filter and where should it be placed?**

A JWT filter (`JwtFilter`) extends `OncePerRequestFilter`. It runs before every HTTP request, reads the `Authorization: Bearer <token>` header, validates the JWT, and sets the `SecurityContext` with the user's authentication. It should be placed in the `security/` folder and registered in `SecurityConfig`.

---

### Section F: Kafka Questions

**Q20. How do you organize Kafka-related files in a Spring Boot project?**

Kafka files are organized into three sub-folders inside `kafka/`:
- `kafka/producer/` — classes that send messages to Kafka topics
- `kafka/consumer/` — classes annotated with `@KafkaListener` that receive messages
- `kafka/event/` — data classes representing Kafka message payloads (like DTOs for Kafka)

---

**Q21. Where should Kafka topic names be defined?**

Kafka topic names should be defined as constants in `KafkaTopicConstants.java` inside the `constant/` folder. Never hardcode strings like `"monitoring.check.result"` in multiple places. Use the constant everywhere so that changing the topic name requires only one change.

---

**Q22. What class sends a Kafka message and what class receives it?**

A **Producer** class (e.g., `CheckResultProducer`) uses `KafkaTemplate.send()` to publish messages. A **Consumer** class (e.g., `CheckResultConsumer`) uses `@KafkaListener` annotation on a method to receive and process messages from a topic.

---

### Section G: Redis Questions

**Q23. Where should Redis caching logic be placed?**

Redis caching logic should be placed in the `redis/` folder. Create a service class like `RecentCheckCacheService` that uses `RedisTemplate` to interact with Redis. Do not put Redis code directly in business service classes — keep it isolated in the `redis/` folder.

---

**Q24. What is a good Redis key naming convention?**

Use a hierarchical format: `service-name:entity:identifier`. For example: `monitoring:checks:service-123`, `session:user:456`, `ratelimit:api:/api/users:192.168.1.1`. This makes keys meaningful, avoids collisions, and makes it easy to scan keys by prefix. Always define key patterns as constants.

---

### Section H: General Architecture Questions

**Q25. What is the difference between Package-by-Layer and Package-by-Feature? When should you use each?**

**Package-by-Layer** groups files by their type (all controllers together, all services together). Simple and familiar, but gets hard to navigate as features grow. Best for small projects.

**Package-by-Feature** groups all files for one feature together (user module, product module). Much easier to navigate in large projects. Each team can work on their own feature package without conflicts. Best for medium to large projects and microservices.

---

**Q26. Why should Scheduler classes be in a separate `scheduler/` folder?**

Schedulers run on background threads triggered by time, not by HTTP requests. Keeping them in a separate folder makes it immediately clear that these are automated jobs, not API endpoints. It prevents mixing scheduled job logic with service business logic and makes it easy to find all background jobs in one place.

---

**Q27. What is a FeignClient and where should it be placed?**

A `FeignClient` is a declarative HTTP client from Spring Cloud that allows a microservice to call another microservice by defining just an interface with annotations. It should be placed in the `client/` folder. Examples: `PaymentClient`, `NotificationClient`, `IncidentClient`. The actual HTTP calls are generated by Feign at runtime.

---

**Q28. What are the common mistakes in Spring Boot project structure?**

The most common mistakes are: writing all code in the controller, exposing entities directly in APIs, mixing business logic and repository logic, not using a global exception handler, hardcoding strings like topic names and Redis keys, not using Spring profiles for environment-specific config, putting the main application class in the wrong package, and creating too many util classes instead of proper service classes.

---

**Q29. Why is it important to use `application-dev.yml` and `application-prod.yml` separately?**

Different environments have different database URLs, credentials, Kafka brokers, Redis hosts, and logging levels. Using separate profile files ensures that development settings never accidentally go to production (e.g., debug-level logging filling up production disk), and production credentials are never checked into Git if they are stored as environment variables in the prod profile.

---

*This README was written for beginner to intermediate Spring Boot developers who want to understand how real production projects are structured. Apply these patterns consistently and your project will remain clean, testable, and maintainable as it grows.*
