# Kotlin Complete Notes

> *Interview-ready | Android + Backend | Beginner → Advanced*

---

## Table of Contents
1. [What is Kotlin?](#1-what-is-kotlin)
2. [Kotlin Setup](#2-kotlin-setup)
3. [Variables in Kotlin](#3-variables-in-kotlin)
4. [Data Types](#4-data-types)
5. [Operators](#5-operators)
6. [Conditions](#6-conditions)
7. [Loops](#7-loops)
8. [Functions](#8-functions)
9. [Null Safety](#9-null-safety)
10. [Strings](#10-strings)
11. [Arrays and Collections](#11-arrays-and-collections)
12. [Classes and Objects](#12-classes-and-objects)
13. [Object-Oriented Programming](#13-object-oriented-programming)
14. [Inheritance](#14-inheritance)
15. [Abstract Class and Interface](#15-abstract-class-and-interface)
16. [Data Class](#16-data-class)
17. [Sealed Class](#17-sealed-class)
18. [Enum Class](#18-enum-class)
19. [Object Keyword](#19-object-keyword)
20. [Extension Functions](#20-extension-functions)
21. [Lambda and Higher-Order Functions](#21-lambda-and-higher-order-functions)
22. [Scope Functions](#22-scope-functions)
23. [Collection Functions](#23-collection-functions)
24. [Exception Handling](#24-exception-handling)
25. [Coroutines](#25-coroutines)
26. [Coroutine Dispatchers](#26-coroutine-dispatchers)
27. [Flow](#27-flow)
28. [Kotlin in Android Development](#28-kotlin-in-android-development)
29. [Kotlin in Backend Development](#29-kotlin-in-backend-development)
30. [Kotlin Interview Questions](#30-kotlin-interview-questions)
31. [Common Kotlin Mistakes](#31-common-kotlin-mistakes)
32. [Practical Coding Tasks](#32-practical-coding-tasks)
33. [Kotlin Roadmap](#33-kotlin-roadmap)
34. [Final Revision Notes](#34-final-revision-notes)

---

## 1. What is Kotlin?

Kotlin is a **modern, statically-typed programming language** created by JetBrains (the same people who made IntelliJ IDEA). It runs on the JVM (Java Virtual Machine), meaning it can do everything Java does — but with far less code and way more safety.

Think of Kotlin as "Java, but cleaned up by someone who actually cares."

### Why Kotlin is Used
- Less boilerplate — you write less, achieve more
- Built-in null safety — no more NullPointerException surprises
- Concise and readable code
- 100% interoperable with Java (you can mix both in the same project)
- First-class support for coroutines (async programming made easy)

### Where Kotlin is Used
- **Android development** — Google officially recommends Kotlin over Java
- **Backend development** — with Spring Boot or Ktor
- **Multiplatform** — share code between Android, iOS, and web (Kotlin Multiplatform)
- **Scripting** — automation, build scripts (Gradle uses Kotlin DSL)

### Kotlin for Android
Google made Kotlin the **preferred language for Android** in 2019. Most modern Android libraries (Jetpack, Compose, Retrofit, etc.) are written with Kotlin in mind.

### Kotlin for Backend
Kotlin works seamlessly with **Spring Boot** (the most popular Java backend framework). You get Spring's power + Kotlin's clean syntax. **Ktor** is a pure-Kotlin lightweight framework as an alternative.

### Kotlin vs Java

| Feature | Kotlin | Java |
|---|---|---|
| Null Safety | Built-in | Manual (error-prone) |
| Boilerplate | Very low | High |
| Data classes | 1 line | 50+ lines |
| Coroutines | Built-in | Needs libraries |
| Lambdas | Clean syntax | Verbose |
| Default args | Yes | No |
| Extension functions | Yes | No |
| Interoperability | 100% with Java | — |

### Advantages of Kotlin
- Fewer bugs due to null safety
- More readable code
- Faster development
- Modern language features (sealed classes, data classes, etc.)
- Great IDE support (IntelliJ, Android Studio)

---

## 2. Kotlin Setup

### Kotlin in IntelliJ IDEA
1. Download IntelliJ IDEA (Community edition is free): [jetbrains.com/idea](https://www.jetbrains.com/idea/)
2. Create a new project → Select **Kotlin** → **JVM | IDEA**
3. Create a `.kt` file and start coding

### Kotlin in Android Studio
Android Studio comes with Kotlin support built-in.
1. Create a new Android project
2. Select **Kotlin** as the language
3. Android Studio sets everything up automatically

### Kotlin File Structure
- Kotlin files have a `.kt` extension
- You don't need to match file name with class name (unlike Java)
- You can put multiple classes, functions, and variables in a single file

### The `main` Function
This is the entry point of any Kotlin program — just like `public static void main` in Java, but much cleaner.

```kotlin
fun main() {
    println("Hello Kotlin")
}
```

> `fun` = function  
> `println` = print with newline  
> No semicolons needed!

---

## 3. Variables in Kotlin

Kotlin has two ways to declare variables: `val` and `var`.

### `val` — Immutable (read-only)
Think of it like a **constant**. Once assigned, you can't reassign it.

```kotlin
val name = "Rahul"
name = "Amit" // ERROR: Val cannot be reassigned
```

### `var` — Mutable
You can reassign it whenever you want.

```kotlin
var age = 25
age = 26 // Works fine
```

### Difference Between `val` and `var`

| | `val` | `var` |
|---|---|---|
| Reassignable? | No | Yes |
| Like Java's | `final` | regular variable |
| Best for | Constants, results | Counters, changing state |

### Type Inference
Kotlin is smart — it figures out the type automatically.

```kotlin
val name = "Kotlin"   // Kotlin infers: String
val age = 25          // Kotlin infers: Int
val price = 99.99     // Kotlin infers: Double
```

You can also explicitly declare the type:

```kotlin
val name: String = "Kotlin"
val age: Int = 25
```

### Best Practices
- **Prefer `val` over `var`** — immutable code is safer and easier to debug
- Use `var` only when you genuinely need to change the value
- Let Kotlin infer the type unless it helps readability to be explicit

> 💡 **Interview Tip:** "val doesn't mean the object is immutable — it means the reference can't be reassigned. A `val` list can still have items added to it if it's a MutableList."

---

## 4. Data Types

Kotlin has the same basic types as Java, but all types in Kotlin are objects (no primitive types visible to you).

### Numeric Types

```kotlin
val myInt: Int = 100
val myLong: Long = 100L
val myFloat: Float = 10.5f
val myDouble: Double = 10.5
```

| Type | Size | Range |
|---|---|---|
| `Int` | 32-bit | -2 billion to 2 billion |
| `Long` | 64-bit | Very large numbers |
| `Float` | 32-bit | Decimal (less precise) |
| `Double` | 64-bit | Decimal (more precise) |

### Boolean

```kotlin
val isLoggedIn: Boolean = true
val isEmpty: Boolean = false
```

### Char

```kotlin
val letter: Char = 'A'  // Single quotes for Char
```

### String

```kotlin
val greeting: String = "Hello Kotlin"  // Double quotes for String
```

### Nullable Types
In Kotlin, a variable **cannot hold null by default**. To allow null, add `?` to the type.

```kotlin
val name: String = null      // ERROR
val name: String? = null     // OK — nullable String
```

> 💡 **Interview Tip:** "What is the difference between `String` and `String?`?"  
> `String` = never null. `String?` = can be null. This is the foundation of Kotlin's null safety.

---

## 5. Operators

### Arithmetic Operators

```kotlin
val a = 10
val b = 3

println(a + b)   // 13
println(a - b)   // 7
println(a * b)   // 30
println(a / b)   // 3 (integer division)
println(a % b)   // 1 (remainder/modulo)
```

### Comparison Operators

```kotlin
println(a > b)   // true
println(a < b)   // false
println(a >= b)  // true
println(a <= b)  // false
println(a == b)  // false
println(a != b)  // true
```

### Logical Operators

```kotlin
val x = true
val y = false

println(x && y)   // AND → false
println(x || y)   // OR → true
println(!x)       // NOT → false
```

### Assignment Operators

```kotlin
var n = 10
n += 5   // n = 15
n -= 3   // n = 12
n *= 2   // n = 24
n /= 4   // n = 6
```

### Safe Call Operator `?.`
Used with nullable variables. If the variable is null, it returns null instead of crashing.

```kotlin
val name: String? = null
println(name?.length)   // prints null — no crash
```

### Elvis Operator `?:`
"If left side is null, use the right side as default."

```kotlin
val name: String? = null
val length = name?.length ?: 0   // length = 0
```

### Not-null Assertion `!!`
Tells Kotlin: "I promise this isn't null — trust me."

```kotlin
val name: String? = "Kotlin"
println(name!!.length)   // Works if name is not null
```

### ⚠️ Why `!!` is Risky
If the variable IS null and you use `!!`, you get a `NullPointerException` — the exact thing Kotlin is designed to prevent.

```kotlin
val name: String? = null
println(name!!.length)   // CRASH: KotlinNullPointerException
```

**Rule:** Only use `!!` when you are 100% certain the value will never be null. Prefer `?.` and `?:` instead.

---

## 6. Conditions

### Basic `if`

```kotlin
val age = 20

if (age >= 18) {
    println("Adult")
} else {
    println("Minor")
}
```

### `if` as an Expression
In Kotlin, `if` returns a value — you can use it like a ternary operator.

```kotlin
val age = 20
val status = if (age >= 18) "Adult" else "Minor"
println(status)  // Adult
```

No need for Java's `? :` ternary — `if` itself is an expression!

### `when` — Kotlin's `switch`
`when` is way more powerful than Java's `switch`.

```kotlin
val day = 3

when (day) {
    1 -> println("Monday")
    2 -> println("Tuesday")
    3 -> println("Wednesday")
    4, 5 -> println("Thursday or Friday")
    else -> println("Weekend")
}
```

### `when` as an Expression

```kotlin
val grade = 85
val result = when {
    grade >= 90 -> "A"
    grade >= 75 -> "B"
    grade >= 60 -> "C"
    else -> "Fail"
}
println(result)  // B
```

### `when` vs Java `switch`

| Feature | `when` (Kotlin) | `switch` (Java) |
|---|---|---|
| Returns value | Yes | No |
| Multiple values per case | Yes (`1, 2 ->`) | No |
| Range checks | Yes | No |
| No `break` needed | Yes | No (needs break) |
| Works without argument | Yes | No |

---

## 7. Loops

### `for` Loop with Range

```kotlin
for (i in 1..5) {
    println(i)   // 1 2 3 4 5
}
```

### `for` Loop — Exclusive Range

```kotlin
for (i in 1 until 5) {
    println(i)   // 1 2 3 4 (excludes 5)
}
```

### `for` Loop — Step

```kotlin
for (i in 1..10 step 2) {
    println(i)   // 1 3 5 7 9
}
```

### `for` Loop — Reverse

```kotlin
for (i in 5 downTo 1) {
    println(i)   // 5 4 3 2 1
}
```

### `for` Loop — Over a List

```kotlin
val fruits = listOf("Apple", "Banana", "Cherry")
for (fruit in fruits) {
    println(fruit)
}
```

### `while` Loop

```kotlin
var count = 1
while (count <= 5) {
    println(count)
    count++
}
```

### `do-while` Loop
Runs at least once, even if condition is false.

```kotlin
var n = 10
do {
    println(n)
    n++
} while (n < 5)
// Prints 10 once, then stops because n < 5 is false
```

### `break` and `continue`

```kotlin
for (i in 1..10) {
    if (i == 5) break      // stops the loop at 5
    if (i % 2 == 0) continue  // skips even numbers
    println(i)
}
// Output: 1 3
```

---

## 8. Functions

### Basic Function

```kotlin
fun greet(name: String): String {
    return "Hello, $name!"
}

println(greet("Kotlin"))  // Hello, Kotlin!
```

### Function with No Return (`Unit`)
`Unit` is like `void` in Java. It means "returns nothing useful."

```kotlin
fun printMessage(msg: String): Unit {
    println(msg)
}

// Unit is optional to write — this is the same:
fun printMessage(msg: String) {
    println(msg)
}
```

### Default Arguments
You can give parameters default values.

```kotlin
fun greet(name: String = "World") {
    println("Hello, $name!")
}

greet()           // Hello, World!
greet("Kotlin")   // Hello, Kotlin!
```

### Named Arguments
You can pass arguments by name — great for clarity.

```kotlin
fun createUser(name: String, age: Int, city: String) {
    println("$name, $age, $city")
}

createUser(city = "Delhi", name = "Rahul", age = 25)
```

### Single Expression Function
If your function has just one expression, use `=`.

```kotlin
fun square(n: Int) = n * n
fun add(a: Int, b: Int) = a + b
```

> 💡 **Interview Tip:** "What is a single expression function?" — It's a function where the body is a single expression, written with `=` instead of `{}`. Kotlin infers the return type.

---

## 9. Null Safety

This is one of Kotlin's **most important features**. Worth understanding deeply.

### The Problem with Null
In Java, any variable can be null. Accessing a null variable causes a `NullPointerException` (NPE) — the most common runtime crash.

```java
// Java
String name = null;
System.out.println(name.length()); // CRASH: NullPointerException
```

### Kotlin's Solution
Kotlin makes null safety a **compile-time guarantee**.

```kotlin
var name: String = "Kotlin"    // Cannot be null
var nickname: String? = null   // Can be null (nullable type)
```

### Safe Call Operator `?.`
If the object is null, skip the call and return null instead of crashing.

```kotlin
val name: String? = null
println(name?.length)   // prints: null (no crash)

val name2: String? = "Kotlin"
println(name2?.length)  // prints: 6
```

### Elvis Operator `?:`
Provide a fallback value if the result is null.

```kotlin
val name: String? = null
val length = name?.length ?: 0
println(length)  // 0
```

Read it as: "Give me `name?.length`, OR if that's null, give me `0`."

### Not-null Assertion `!!`
Force Kotlin to treat a nullable as non-null. **Dangerous!**

```kotlin
val name: String? = "Kotlin"
println(name!!.length)  // Works — but risky
```

### `let` with Null Safety
Execute a block only if the value is not null.

```kotlin
val name: String? = "Kotlin"
name?.let {
    println("Name is: $it")  // Only runs if name is not null
}
```

### Common Mistakes

```kotlin
// WRONG — using !! without checking
val user: User? = getUser()
user!!.profile.name  // Crash if user is null

// RIGHT — use ?. and ?:
val name = user?.profile?.name ?: "Unknown"
```

### Interview Questions on Null Safety
- **Q: What is the difference between `String` and `String?`?**  
  A: `String` is non-nullable (can never be null). `String?` is nullable (can hold null).

- **Q: What does `?.` do?**  
  A: Safe call operator — returns null if the receiver is null instead of throwing NPE.

- **Q: What does `?:` do?**  
  A: Elvis operator — returns the right-hand value if the left-hand value is null.

- **Q: Why should you avoid `!!`?**  
  A: It bypasses null safety and can cause `KotlinNullPointerException` at runtime.

---

## 10. Strings

### String Templates
Embed variables or expressions directly in strings using `$`.

```kotlin
val name = "Kotlin"
val version = 2.0

println("Language: $name")          // Language: Kotlin
println("Version: ${version + 0.1}") // Version: 2.1
```

### Multiline Strings
Use triple quotes `"""` for multiline strings.

```kotlin
val message = """
    Hello,
    Welcome to Kotlin.
    Have fun!
""".trimIndent()

println(message)
```

### Common String Functions

```kotlin
val str = "Hello Kotlin"

println(str.length)           // 12
println(str.uppercase())      // HELLO KOTLIN
println(str.lowercase())      // hello kotlin
println(str.contains("Kotlin"))  // true
println(str.replace("Kotlin", "World"))  // Hello World
println(str.split(" "))       // [Hello, Kotlin]
println(str.trim())           // removes leading/trailing spaces
println(str.startsWith("Hello"))  // true
println(str.endsWith("Kotlin"))   // true
println(str.substring(6))     // Kotlin
println(str.isEmpty())        // false
println(str.isNotEmpty())     // true
```

### String Comparison

```kotlin
val a = "Kotlin"
val b = "kotlin"

println(a == b)                     // false (case-sensitive)
println(a.equals(b, ignoreCase = true))  // true
```

> In Kotlin, `==` checks structural equality (content), not reference equality. Use `===` for reference equality.

---

## 11. Arrays and Collections

### Array

```kotlin
val numbers = arrayOf(1, 2, 3, 4, 5)
println(numbers[0])  // 1
numbers[0] = 10      // Arrays are mutable
```

### List (Immutable)
Can't add or remove elements after creation.

```kotlin
val fruits = listOf("Apple", "Banana", "Cherry")
println(fruits[0])   // Apple
// fruits.add("Mango")  // ERROR — immutable
```

### MutableList
Can add, remove, and change elements.

```kotlin
val fruits = mutableListOf("Apple", "Banana")
fruits.add("Cherry")
fruits.remove("Apple")
println(fruits)  // [Banana, Cherry]
```

### Set (Immutable — No Duplicates)

```kotlin
val numbers = setOf(1, 2, 3, 2, 1)
println(numbers)  // [1, 2, 3] — duplicates removed
```

### MutableSet

```kotlin
val numbers = mutableSetOf(1, 2, 3)
numbers.add(4)
numbers.add(2)   // ignored — already exists
```

### Map (Immutable)
Key-value pairs.

```kotlin
val capitals = mapOf("India" to "Delhi", "USA" to "Washington")
println(capitals["India"])  // Delhi
```

### MutableMap

```kotlin
val scores = mutableMapOf("Alice" to 90, "Bob" to 85)
scores["Charlie"] = 92
scores["Alice"] = 95
println(scores)  // {Alice=95, Bob=85, Charlie=92}
```

### Mutable vs Immutable Collections

| Type | Can Modify? | Use When |
|---|---|---|
| `listOf` | No | Read-only data |
| `mutableListOf` | Yes | Dynamic data |
| `setOf` | No | Unique read-only |
| `mutableSetOf` | Yes | Unique dynamic |
| `mapOf` | No | Fixed key-value data |
| `mutableMapOf` | Yes | Dynamic key-value |

> 💡 **Real-world tip:** Prefer immutable collections in function return types. This prevents callers from accidentally modifying your data.

---

## 12. Classes and Objects

### Basic Class

```kotlin
class Car {
    var brand: String = ""
    var speed: Int = 0

    fun drive() {
        println("$brand is driving at $speed km/h")
    }
}

val car = Car()
car.brand = "Toyota"
car.speed = 120
car.drive()  // Toyota is driving at 120 km/h
```

### Primary Constructor
The most common and concise way.

```kotlin
class Person(val name: String, var age: Int) {
    fun greet() = println("Hi, I'm $name")
}

val p = Person("Rahul", 25)
p.greet()  // Hi, I'm Rahul
```

### Secondary Constructor

```kotlin
class Person(val name: String) {
    var age: Int = 0

    constructor(name: String, age: Int) : this(name) {
        this.age = age
    }
}
```

### `init` Block
Runs when an object is created.

```kotlin
class Person(val name: String) {
    init {
        println("Person created: $name")
    }
}
```

---

## 13. Object-Oriented Programming

### Encapsulation
Hiding internal details. Use `private`, `protected`, `internal`, `public`.

```kotlin
class BankAccount(private var balance: Double) {
    fun deposit(amount: Double) {
        balance += amount
    }
    fun getBalance() = balance
}

val account = BankAccount(1000.0)
account.deposit(500.0)
println(account.getBalance())  // 1500.0
// account.balance  // ERROR — private
```

### Inheritance
See section 14 for full details.

### Polymorphism
Same function, different behavior depending on the object.

```kotlin
open class Animal {
    open fun sound() = println("Some sound")
}

class Dog : Animal() {
    override fun sound() = println("Bark")
}

class Cat : Animal() {
    override fun sound() = println("Meow")
}

val animals: List<Animal> = listOf(Dog(), Cat())
animals.forEach { it.sound() }
// Bark
// Meow
```

### Abstraction
Hiding implementation complexity. Use abstract classes or interfaces.

```kotlin
abstract class Shape {
    abstract fun area(): Double
}

class Circle(val radius: Double) : Shape() {
    override fun area() = Math.PI * radius * radius
}
```

---

## 14. Inheritance

### The `open` Keyword
In Kotlin, **all classes are `final` by default** (can't be inherited). You must mark a class `open` to allow inheritance.

```kotlin
open class Animal(val name: String) {
    open fun sound() {
        println("$name makes a sound")
    }
}

class Dog(name: String) : Animal(name) {
    override fun sound() {
        println("$name barks")
    }
}

val dog = Dog("Buddy")
dog.sound()  // Buddy barks
```

### `super` Keyword
Call the parent class's method.

```kotlin
class Dog(name: String) : Animal(name) {
    override fun sound() {
        super.sound()              // calls Animal's sound()
        println("$name also barks!")
    }
}
```

### Preventing Override
Use `final` to stop a method from being overridden further.

```kotlin
open class Animal {
    open fun sound() = println("Sound")
}

open class Dog : Animal() {
    final override fun sound() = println("Bark")  // Can't override in Dog's subclasses
}
```

> 💡 **Interview Tip:** "Why are Kotlin classes `final` by default?"  
> It's a design decision to encourage composition over inheritance and prevent accidental, fragile inheritance hierarchies. It forces you to consciously decide when to allow extension.

---

## 15. Abstract Class and Interface

### Abstract Class
A class that cannot be instantiated directly. It can have both abstract and concrete methods.

```kotlin
abstract class Vehicle(val brand: String) {
    abstract fun fuelType(): String   // Must be implemented

    fun describe() {                  // Concrete method — available to all
        println("$brand uses ${fuelType()}")
    }
}

class ElectricCar(brand: String) : Vehicle(brand) {
    override fun fuelType() = "Electricity"
}

val car = ElectricCar("Tesla")
car.describe()  // Tesla uses Electricity
```

### Interface
A contract — defines what a class can do, without state (mostly).

```kotlin
interface Flyable {
    fun fly()
    fun land() = println("Landing...")  // Can have default implementation
}

interface Swimmable {
    fun swim()
}

class Duck : Flyable, Swimmable {
    override fun fly() = println("Duck is flying")
    override fun swim() = println("Duck is swimming")
}
```

### Abstract Class vs Interface

| Feature | Abstract Class | Interface |
|---|---|---|
| Can have state (fields) | Yes | No (only val with no backing) |
| Constructor | Yes | No |
| Multiple inheritance | No (single) | Yes (multiple) |
| Use when | Shared base with state | Defining capabilities/contracts |

### When to Use What
- **Abstract class:** When subclasses share common state (fields) and behavior. Example: `Vehicle` base class with `brand`, `model` fields.
- **Interface:** When you want to define capabilities that multiple unrelated classes can implement. Example: `Clickable`, `Serializable`, `Flyable`.

---

## 16. Data Class

### What is a Data Class?
A class whose **primary purpose is to hold data**. Kotlin auto-generates boilerplate methods for you.

```kotlin
data class User(val id: Int, val name: String, val email: String)
```

That single line gives you:
- `toString()` — readable string output
- `equals()` — compares by field values
- `hashCode()` — consistent hash
- `copy()` — create a modified copy

### `toString()`

```kotlin
val user = User(1, "Rahul", "rahul@example.com")
println(user)  // User(id=1, name=Rahul, email=rahul@example.com)
```

### `equals()`

```kotlin
val user1 = User(1, "Rahul", "rahul@example.com")
val user2 = User(1, "Rahul", "rahul@example.com")
println(user1 == user2)  // true — compares fields, not references
```

Without `data class`, this would be `false` (comparing memory addresses).

### `copy()`
Create a modified copy without changing the original.

```kotlin
val original = User(1, "Rahul", "rahul@example.com")
val updated = original.copy(email = "new@example.com")
println(updated)  // User(id=1, name=Rahul, email=new@example.com)
```

### Destructuring

```kotlin
val user = User(1, "Rahul", "rahul@example.com")
val (id, name, email) = user
println("$id $name $email")  // 1 Rahul rahul@example.com
```

> 💡 **Interview Tip:** "In real Android/backend development, data classes are used for API response models, Room entities, and anything where you're just passing around structured data."

---

## 17. Sealed Class

### What is a Sealed Class?
A sealed class restricts which classes can inherit from it. All subclasses must be in the **same file**. This makes it perfect for representing **a fixed set of states**.

```kotlin
sealed class ApiResponse {
    data class Success(val data: String) : ApiResponse()
    data class Error(val message: String) : ApiResponse()
    object Loading : ApiResponse()
}
```

### Why Sealed Class is Useful
When you use `when` with a sealed class, Kotlin **forces you to handle all cases** — no missing states.

```kotlin
fun handleResponse(response: ApiResponse) {
    when (response) {
        is ApiResponse.Success -> println("Data: ${response.data}")
        is ApiResponse.Error -> println("Error: ${response.message}")
        is ApiResponse.Loading -> println("Loading...")
    }
}
```

No `else` needed — Kotlin knows all possible types.

### Sealed Class for Android UI State

```kotlin
sealed class UiState {
    object Loading : UiState()
    data class Success(val users: List<User>) : UiState()
    data class Error(val message: String) : UiState()
}

// In ViewModel:
val uiState: StateFlow<UiState> = ...

// In UI:
when (val state = uiState.value) {
    is UiState.Loading -> showLoader()
    is UiState.Success -> showUsers(state.users)
    is UiState.Error -> showError(state.message)
}
```

---

## 18. Enum Class

### What is an Enum?
A fixed set of named constants.

```kotlin
enum class Direction {
    NORTH, SOUTH, EAST, WEST
}

val dir = Direction.NORTH
println(dir)  // NORTH
```

### Enum with Properties

```kotlin
enum class Planet(val mass: Double, val radius: Double) {
    EARTH(5.972e24, 6.371e6),
    MARS(6.39e23, 3.389e6);

    fun surfaceGravity() = 6.674e-11 * mass / (radius * radius)
}

println(Planet.EARTH.surfaceGravity())
```

### Enum vs Sealed Class

| Feature | Enum | Sealed Class |
|---|---|---|
| Each instance has same structure | Yes | No (different data per subclass) |
| Can hold different data per case | No | Yes |
| Use when | Simple named constants | States with different payloads |

**Use Enum for:** Days of week, directions, status codes  
**Use Sealed Class for:** API responses (Success with data, Error with message), UI states

---

## 19. Object Keyword

### Object Declaration — Singleton
An `object` creates a class and **a single instance** of it at the same time (Singleton pattern).

```kotlin
object DatabaseConfig {
    val host = "localhost"
    val port = 5432

    fun connect() = println("Connecting to $host:$port")
}

DatabaseConfig.connect()  // Access directly, no `new` or `()`
```

### Companion Object
Like Java's `static` methods and fields — belong to the class, not to instances.

```kotlin
class MathHelper {
    companion object {
        fun square(n: Int) = n * n
        const val PI = 3.14159
    }
}

println(MathHelper.square(5))   // 25
println(MathHelper.PI)          // 3.14159
```

### Anonymous Object
Create a one-off object without a name (like anonymous classes in Java).

```kotlin
val greeter = object {
    fun greet() = println("Hello from anonymous object!")
}
greeter.greet()
```

### Object vs Class

| | `object` | `class` |
|---|---|---|
| Instances | Always exactly 1 | Can create many |
| Instantiation | Automatic | Manual with `()` |
| Use for | Singletons, utilities | Regular objects |

---

## 20. Extension Functions

### What is an Extension Function?
It lets you add new functions to existing classes **without modifying them** and without inheritance.

```kotlin
fun String.addExclamation() = "$this!"

println("Hello Kotlin".addExclamation())  // Hello Kotlin!
```

### Why Extension Functions are Useful
- Add utility methods to classes you don't own (like `String`, `List`, Android `Context`)
- Keep code clean and readable
- No need for utility classes full of static methods

### Real-world Use Cases

```kotlin
// String utilities
fun String.isValidEmail() = this.contains("@") && this.contains(".")

// Android Context extension
fun Context.toast(message: String) {
    Toast.makeText(this, message, Toast.LENGTH_SHORT).show()
}

// List extension
fun List<Int>.average() = if (isEmpty()) 0.0 else sum().toDouble() / size
```

### Limitations
- Extension functions don't actually modify the class
- They can't access private members of the class
- If a class has a member function with the same signature, the member function wins

---

## 21. Lambda and Higher-Order Functions

### Lambda Expression
A function without a name, assigned to a variable or passed directly.

```kotlin
val greet = { name: String -> "Hello, $name!" }
println(greet("Kotlin"))  // Hello, Kotlin!
```

### Higher-Order Functions
A function that takes another function as a parameter or returns a function.

```kotlin
fun doOperation(a: Int, b: Int, operation: (Int, Int) -> Int): Int {
    return operation(a, b)
}

val result = doOperation(5, 3) { x, y -> x + y }
println(result)  // 8
```

### Function as Parameter

```kotlin
fun applyToList(numbers: List<Int>, transform: (Int) -> Int): List<Int> {
    return numbers.map(transform)
}

val doubled = applyToList(listOf(1, 2, 3)) { it * 2 }
println(doubled)  // [2, 4, 6]
```

### The `it` Keyword
When a lambda has a single parameter, you can use `it` instead of naming it.

```kotlin
val numbers = listOf(1, 2, 3, 4, 5)
val evens = numbers.filter { it % 2 == 0 }
println(evens)  // [2, 4]
```

### Function as Return Type

```kotlin
fun getMultiplier(factor: Int): (Int) -> Int {
    return { number -> number * factor }
}

val triple = getMultiplier(3)
println(triple(5))  // 15
```

---

## 22. Scope Functions

Scope functions are used to execute a block of code on an object. They make your code more concise and readable.

### `let`
- **Object reference:** `it`
- **Returns:** Result of the lambda
- **Best for:** Null checks, transformations

```kotlin
val name: String? = "Kotlin"
val length = name?.let {
    println("Name is: $it")
    it.length
}
println(length)  // 6
```

### `run`
- **Object reference:** `this`
- **Returns:** Result of the lambda
- **Best for:** Initialization + computing a result

```kotlin
val result = "Hello Kotlin".run {
    println(this.uppercase())
    this.length
}
println(result)  // 12
```

### `with`
- **Object reference:** `this`
- **Returns:** Result of the lambda
- **Best for:** Multiple operations on the same object (non-extension)

```kotlin
val user = User(1, "Rahul", "rahul@example.com")
with(user) {
    println(name)
    println(email)
}
```

### `apply`
- **Object reference:** `this`
- **Returns:** The object itself
- **Best for:** Object configuration/initialization

```kotlin
val user = User(1, "", "").apply {
    name = "Rahul"        // if properties are var
    email = "r@test.com"
}
```

### `also`
- **Object reference:** `it`
- **Returns:** The object itself
- **Best for:** Side effects (logging, debugging) without changing the object

```kotlin
val numbers = mutableListOf(1, 2, 3)
    .also { println("Original: $it") }
    .apply { add(4) }
    .also { println("Modified: $it") }
```

### Scope Functions Comparison Table

| Function | Reference | Returns | Use Case |
|---|---|---|---|
| `let` | `it` | Lambda result | Null checks, transformations |
| `run` | `this` | Lambda result | Init + compute result |
| `with` | `this` | Lambda result | Multiple ops, non-extension |
| `apply` | `this` | The object | Object configuration |
| `also` | `it` | The object | Side effects, logging |

> 💡 **Memory trick:**  
> - `let` and `also` use `it` (they're "distant")  
> - `run`, `with`, `apply` use `this` (they're "intimate")  
> - `apply` and `also` return the object (for chaining)  
> - `let`, `run`, `with` return the lambda result

---

## 23. Collection Functions

These are the bread and butter of Kotlin functional programming.

### `map` — Transform Each Element

```kotlin
val users = listOf("Alice", "Bob", "Charlie")
val upperNames = users.map { it.uppercase() }
// [ALICE, BOB, CHARLIE]
```

### `filter` — Keep Elements Matching Condition

```kotlin
data class Product(val name: String, val price: Double, val inStock: Boolean)

val products = listOf(
    Product("Laptop", 50000.0, true),
    Product("Mouse", 800.0, false),
    Product("Keyboard", 1500.0, true)
)

val available = products.filter { it.inStock }
// [Laptop, Keyboard]
```

### `forEach` — Iterate (No Return)

```kotlin
products.forEach { println("${it.name}: ₹${it.price}") }
```

### `find` — First Match or Null

```kotlin
val laptop = products.find { it.name == "Laptop" }
println(laptop?.price)  // 50000.0
```

### `any` — True if at Least One Matches

```kotlin
val hasExpensive = products.any { it.price > 10000 }
println(hasExpensive)  // true
```

### `all` — True if All Match

```kotlin
val allInStock = products.all { it.inStock }
println(allInStock)  // false
```

### `count` — Count Matches

```kotlin
val inStockCount = products.count { it.inStock }
println(inStockCount)  // 2
```

### `sortedBy` — Sort by a Field

```kotlin
val byPrice = products.sortedBy { it.price }
// [Mouse, Keyboard, Laptop]
```

### `groupBy` — Group Into a Map

```kotlin
data class User(val name: String, val role: String)

val users = listOf(
    User("Alice", "Admin"),
    User("Bob", "User"),
    User("Charlie", "Admin")
)

val grouped = users.groupBy { it.role }
// {Admin=[Alice, Charlie], User=[Bob]}
```

---

## 24. Exception Handling

### Basic Try-Catch

```kotlin
try {
    val result = 10 / 0
} catch (e: ArithmeticException) {
    println("Error: ${e.message}")
} finally {
    println("This always runs")
}
```

### Catching Multiple Exceptions

```kotlin
try {
    val list = listOf(1, 2, 3)
    println(list[10])  // IndexOutOfBoundsException
} catch (e: IndexOutOfBoundsException) {
    println("Index error: ${e.message}")
} catch (e: Exception) {
    println("General error: ${e.message}")
}
```

### `throw`

```kotlin
fun divide(a: Int, b: Int): Int {
    if (b == 0) throw IllegalArgumentException("Cannot divide by zero")
    return a / b
}
```

### Custom Exception

```kotlin
class InsufficientBalanceException(message: String) : Exception(message)

fun withdraw(balance: Double, amount: Double): Double {
    if (amount > balance) throw InsufficientBalanceException("Not enough funds")
    return balance - amount
}
```

### `try` as Expression

```kotlin
val result = try {
    "123".toInt()
} catch (e: NumberFormatException) {
    -1
}
println(result)  // 123
```

---

## 25. Coroutines

### What is a Coroutine?
A coroutine is a lightweight piece of code that can be **suspended and resumed** without blocking a thread. Think of it as a function that can "pause" and let other work happen, then pick up where it left off.

### Why Coroutines?
Traditional threads are heavy (each takes ~1MB RAM). Coroutines are much lighter — you can run thousands of them. They make async code look like synchronous code (no callback hell).

### Coroutine vs Thread

| | Coroutine | Thread |
|---|---|---|
| Memory | Very light (~few KB) | Heavy (~1MB) |
| Blocking | Non-blocking (suspends) | Blocking |
| Syntax | Sequential, clean | Complex callbacks |
| Count | Thousands easily | Hundreds at most |

### `suspend` Function
A function that can be paused and resumed. Can only be called from a coroutine or another suspend function.

```kotlin
suspend fun fetchData(): String {
    delay(1000)  // Suspend for 1 second (doesn't block thread)
    return "Data fetched!"
}
```

### `launch` — Fire and Forget
Starts a coroutine without waiting for the result.

```kotlin
import kotlinx.coroutines.*

fun main() = runBlocking {
    launch {
        delay(1000)
        println("Hello from coroutine!")
    }
    println("Main code continues...")
}
// Main code continues...
// Hello from coroutine! (after 1 second)
```

### `async` + `await` — Get a Result

```kotlin
fun main() = runBlocking {
    val deferred = async {
        delay(1000)
        "Result from async"
    }
    println("Waiting...")
    println(deferred.await())  // waits for the result
}
```

### `runBlocking`
Blocks the current thread until all coroutines inside complete. Use only for testing or in `main()`.

```kotlin
fun main() = runBlocking {
    // Your coroutine code here
}
```

### Simulating an API Call

```kotlin
suspend fun fetchUser(id: Int): String {
    delay(500)  // Simulate network delay
    return "User #$id"
}

fun main() = runBlocking {
    println("Fetching user...")
    val user = fetchUser(1)
    println(user)  // User #1
}
```

---

## 26. Coroutine Dispatchers

Dispatchers control **which thread** a coroutine runs on.

### `Dispatchers.Main`
- Runs on the **UI/Main thread**
- Use for: Updating UI in Android
- Example: Setting text on a TextView

```kotlin
viewModelScope.launch(Dispatchers.Main) {
    textView.text = "Updated!"
}
```

### `Dispatchers.IO`
- Runs on a **background thread** optimized for I/O operations
- Use for: Network calls, database reads/writes, file operations
- Most common in Android + backend

```kotlin
viewModelScope.launch(Dispatchers.IO) {
    val data = api.fetchData()   // Network call
    database.save(data)          // DB operation
}
```

### `Dispatchers.Default`
- Runs on a **background thread** optimized for CPU-heavy work
- Use for: Sorting large lists, JSON parsing, complex calculations

```kotlin
launch(Dispatchers.Default) {
    val sorted = largeList.sortedBy { it.value }
}
```

### `Dispatchers.Unconfined`
- Starts in the caller's thread but can move to different threads
- Use for: Rarely — mostly in special testing scenarios
- Generally avoid in production code

### Dispatcher Summary

| Dispatcher | Thread | Use For |
|---|---|---|
| `Main` | UI Thread | UI updates |
| `IO` | Background (I/O pool) | Network, DB, files |
| `Default` | Background (CPU pool) | CPU-heavy computation |
| `Unconfined` | Varies | Special cases only |

---

## 27. Flow

### What is Flow?
Flow is Kotlin's way to handle **streams of data** asynchronously. It can emit multiple values over time (unlike `suspend` functions that return a single value).

```kotlin
flow {
    emit(1)
    delay(100)
    emit(2)
    delay(100)
    emit(3)
}
```

### Flow is Cold
A Flow doesn't run until you `collect` it. Each collector gets a fresh start.

```kotlin
val numberFlow = flow {
    println("Starting flow")
    for (i in 1..3) {
        delay(100)
        emit(i)
    }
}

// Nothing happens yet...
numberFlow.collect { println(it) }  // Now it runs
```

### `collect` — Consume a Flow

```kotlin
fun main() = runBlocking {
    val flow = flow {
        emit(1); emit(2); emit(3)
    }
    flow.collect { value ->
        println("Got: $value")
    }
}
```

### Flow Operators

```kotlin
flow.map { it * 2 }              // Transform each value
    .filter { it > 2 }           // Filter values
    .collect { println(it) }     // Consume
```

### Flow vs LiveData

| | Flow | LiveData |
|---|---|---|
| Android only? | No (pure Kotlin) | Yes (Android) |
| Lifecycle aware | No (unless StateFlow in Compose) | Yes |
| Operators | Rich (map, filter, etc.) | Limited |
| Cold/Hot | Cold by default | Hot |
| Best for | General data streams | UI data in Android |

### `StateFlow` and `SharedFlow`
- **StateFlow:** Hot flow with a current state — like LiveData replacement
- **SharedFlow:** For one-time events (navigation, snackbar)

```kotlin
class MyViewModel : ViewModel() {
    private val _uiState = MutableStateFlow<UiState>(UiState.Loading)
    val uiState: StateFlow<UiState> = _uiState.asStateFlow()
}
```

---

## 28. Kotlin in Android Development

### Kotlin for Android
Kotlin is the #1 recommended language for Android. All Jetpack libraries are Kotlin-first.

### Activity with Kotlin

```kotlin
class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val button = findViewById<Button>(R.id.btn_click)
        button.setOnClickListener {
            Toast.makeText(this, "Clicked!", Toast.LENGTH_SHORT).show()
        }
    }
}
```

### ViewModel with Coroutines

```kotlin
class UserViewModel(private val repository: UserRepository) : ViewModel() {

    private val _users = MutableStateFlow<List<User>>(emptyList())
    val users: StateFlow<List<User>> = _users.asStateFlow()

    fun loadUsers() {
        viewModelScope.launch {
            val result = repository.getUsers()  // suspend function
            _users.value = result
        }
    }
}
```

### Repository Pattern

```kotlin
class UserRepository(private val api: UserApi) {
    suspend fun getUsers(): List<User> {
        return api.fetchUsers()  // Retrofit call
    }
}
```

### Data Class for API Response

```kotlin
data class UserResponse(
    val id: Int,
    val name: String,
    val email: String
)
```

### Coroutines with Retrofit

```kotlin
interface UserApi {
    @GET("users")
    suspend fun fetchUsers(): List<UserResponse>
}
```

### Jetpack Compose Basics

```kotlin
@Composable
fun UserCard(user: User) {
    Card(modifier = Modifier.padding(8.dp)) {
        Column(modifier = Modifier.padding(16.dp)) {
            Text(text = user.name, style = MaterialTheme.typography.h6)
            Text(text = user.email, color = Color.Gray)
        }
    }
}
```

---

## 29. Kotlin in Backend Development

### Kotlin with Spring Boot
Spring Boot is the most popular framework for Kotlin backend development.

### Controller

```kotlin
@RestController
@RequestMapping("/api/users")
class UserController(private val userService: UserService) {

    @GetMapping
    fun getAllUsers(): List<UserDto> = userService.getAllUsers()

    @GetMapping("/{id}")
    fun getUserById(@PathVariable id: Long): UserDto = userService.getUser(id)

    @PostMapping
    fun createUser(@RequestBody dto: CreateUserDto): UserDto = userService.createUser(dto)
}
```

### Service

```kotlin
@Service
class UserService(private val userRepository: UserRepository) {

    fun getAllUsers(): List<UserDto> {
        return userRepository.findAll().map { it.toDto() }
    }

    fun getUser(id: Long): UserDto {
        return userRepository.findById(id)
            .orElseThrow { NotFoundException("User not found") }
            .toDto()
    }

    fun createUser(dto: CreateUserDto): UserDto {
        val user = User(name = dto.name, email = dto.email)
        return userRepository.save(user).toDto()
    }
}
```

### Entity and DTO

```kotlin
@Entity
@Table(name = "users")
data class User(
    @Id @GeneratedValue(strategy = GenerationType.IDENTITY)
    val id: Long = 0,
    val name: String,
    val email: String
)

data class UserDto(val id: Long, val name: String, val email: String)
data class CreateUserDto(val name: String, val email: String)

fun User.toDto() = UserDto(id, name, email)
```

### Repository

```kotlin
@Repository
interface UserRepository : JpaRepository<User, Long>
```

### Null Safety in Backend APIs
Kotlin's null safety helps prevent NPEs in your REST API responses.

```kotlin
fun getUserEmail(userId: Long): String {
    val user = userRepository.findById(userId).orElse(null)
    return user?.email ?: "unknown@email.com"  // Safe with Elvis
}
```

---

## 30. Kotlin Interview Questions

### Beginner Level

**Q: What is Kotlin?**  
A: Kotlin is a modern, statically-typed programming language that runs on the JVM. It's developed by JetBrains and is fully interoperable with Java. It's concise, null-safe, and the preferred language for Android development.

**Q: Difference between `val` and `var`?**  
A: `val` is read-only (like `final` in Java) — cannot be reassigned. `var` is mutable — can be reassigned. Best practice is to prefer `val` unless you genuinely need mutability.

**Q: Kotlin vs Java — key differences?**  
A: Kotlin has null safety, data classes, extension functions, default/named arguments, coroutines, and sealed classes built in. Kotlin code is more concise — a Java class with getters/setters/equals/hashCode becomes a one-liner data class in Kotlin.

**Q: What is null safety in Kotlin?**  
A: Kotlin separates nullable and non-nullable types at the compile level. A `String` can never be null. A `String?` can be null. This prevents NullPointerExceptions at compile time rather than runtime.

**Q: What are Kotlin data types?**  
A: `Int`, `Long`, `Float`, `Double`, `Boolean`, `Char`, `String`, and their nullable counterparts (`Int?`, `String?`, etc.)

### Intermediate Level

**Q: What is a data class?**  
A: A class designed to hold data. Kotlin auto-generates `toString()`, `equals()`, `hashCode()`, and `copy()`. Makes model/POJO classes extremely concise.

**Q: What is a sealed class?**  
A: A class with a restricted type hierarchy — all subclasses must be in the same file. Perfect for representing states (Loading, Success, Error) where `when` can exhaustively check all cases.

**Q: What is an extension function?**  
A: A way to add functionality to an existing class without modifying or inheriting from it. Useful for adding utility methods to classes you don't own.

**Q: What is a companion object?**  
A: The Kotlin equivalent of Java `static` members. It belongs to the class, not to instances. Accessed via the class name.

**Q: Difference between `List` and `MutableList`?**  
A: `List` is read-only (you can't add/remove elements). `MutableList` allows modification. Under the hood, both might be `ArrayList` but the interface differs.

**Q: Difference between abstract class and interface?**  
A: Abstract class can have state (fields), constructors, and both abstract and concrete methods. Interface has no state (mostly), no constructor, but allows multiple inheritance. Use abstract class for shared state; use interface for defining capabilities.

**Q: Enum vs sealed class?**  
A: Enums are for simple constants where each instance has the same structure. Sealed classes are for when each subtype can have different data — like `Success(data)` vs `Error(message)`.

### Advanced Level

**Q: Coroutine vs Thread?**  
A: Coroutines are much lighter (few KB vs ~1MB per thread). They are non-blocking — they suspend without blocking a thread. You can run thousands of coroutines concurrently. Threads block when waiting.

**Q: `launch` vs `async`?**  
A: `launch` is fire-and-forget — starts a coroutine and returns a `Job`. `async` starts a coroutine that computes a value and returns a `Deferred`. Use `.await()` to get the result from `async`.

**Q: What is a `suspend` function?**  
A: A function that can be paused and resumed by the coroutine runtime. It can only be called from within a coroutine or another suspend function. It does NOT block the thread — it suspends the coroutine.

**Q: Flow vs LiveData?**  
A: Flow is pure Kotlin (not Android-specific), more powerful with operators, cold by default, and works in backend. LiveData is Android-specific, lifecycle-aware, and hot. In modern Android with Compose, StateFlow is preferred over LiveData.

**Q: Explain scope functions and their differences.**  
A: There are 5 scope functions. `let`/`also` use `it`; `run`/`with`/`apply` use `this`. `apply`/`also` return the object; `let`/`run`/`with` return the lambda result. See the comparison table in section 22.

**Q: Why are Kotlin classes `final` by default?**  
A: It's a deliberate design decision to encourage composition over inheritance, preventing fragile inheritance hierarchies. You must explicitly mark a class `open` to allow subclassing.

**Q: How does Kotlin handle null safety internally?**  
A: At the bytecode level, Kotlin adds null checks via annotations (`@NotNull`, `@Nullable`) and runtime checks. The compiler enforces null safety rules and generates NPE-safe code. Nullable types in Kotlin compile to wrapped types with null checks at call sites.

---

## 31. Common Kotlin Mistakes

### 1. Overusing `!!`
```kotlin
// WRONG
val name = user!!.name!!.trim()!!

// RIGHT
val name = user?.name?.trim() ?: "Unknown"
```

### 2. Confusing `val` with Full Immutability
`val` means the reference can't be reassigned, not that the object is immutable.

```kotlin
val list = mutableListOf(1, 2, 3)
list.add(4)  // Works! val just can't be reassigned to a new list
list = mutableListOf(5, 6)  // ERROR: val cannot be reassigned
```

### 3. Using the Wrong Scope Function
```kotlin
// WRONG — using run when you should use apply (for config)
val user = User().run { name = "Rahul"; this }

// RIGHT
val user = User().apply { name = "Rahul" }
```

### 4. Blocking the Main Thread
```kotlin
// WRONG — Thread.sleep blocks the thread
viewModelScope.launch {
    Thread.sleep(1000)  // BLOCKS the thread!
}

// RIGHT — delay suspends the coroutine
viewModelScope.launch {
    delay(1000)  // Suspends, doesn't block
}
```

### 5. Not Handling Null Properly
```kotlin
// WRONG — assuming non-null without checking
fun getLength(str: String?) = str.length  // ERROR

// RIGHT
fun getLength(str: String?) = str?.length ?: 0
```

### 6. Misusing Coroutines
```kotlin
// WRONG — creating a new coroutine scope manually inside ViewModel
fun loadData() {
    GlobalScope.launch { /* ... */ }  // Not tied to lifecycle!
}

// RIGHT
fun loadData() {
    viewModelScope.launch { /* ... */ }  // Cancelled when ViewModel is cleared
}
```

### 7. Unnecessary Mutable Collections
```kotlin
// WRONG — mutable when you only read
fun getUsers(): MutableList<User> = mutableListOf(...)

// RIGHT — expose immutable, keep mutable private
private val _users = mutableListOf<User>()
fun getUsers(): List<User> = _users
```

---

## 32. Practical Coding Tasks

### Task 1: Reverse a String

**Problem:** Write a function to reverse a string.

```kotlin
fun reverseString(str: String): String = str.reversed()

fun main() {
    println(reverseString("Kotlin"))  // niltoK
}
```

**Explanation:** Kotlin's `String` has a built-in `reversed()` extension function.  
**Interview Tip:** You might also be asked to do it manually — use a `StringBuilder` or reverse loop.

---

### Task 2: Check Palindrome

**Problem:** Check if a string reads the same forwards and backwards.

```kotlin
fun isPalindrome(str: String): Boolean {
    val clean = str.lowercase().filter { it.isLetterOrDigit() }
    return clean == clean.reversed()
}

fun main() {
    println(isPalindrome("racecar"))  // true
    println(isPalindrome("hello"))    // false
    println(isPalindrome("A man a plan a canal Panama"))  // true
}
```

**Interview Tip:** Always handle case and non-alphanumeric characters in palindrome problems.

---

### Task 3: Count Vowels

**Problem:** Count the number of vowels in a string.

```kotlin
fun countVowels(str: String): Int {
    val vowels = setOf('a', 'e', 'i', 'o', 'u')
    return str.lowercase().count { it in vowels }
}

fun main() {
    println(countVowels("Hello Kotlin"))  // 3
}
```

**Interview Tip:** Use `count { }` — more Kotlin-idiomatic than a manual counter.

---

### Task 4: Find Largest Number in a List

**Problem:** Find the largest number in a list of integers.

```kotlin
fun findLargest(numbers: List<Int>): Int? {
    return numbers.maxOrNull()
}

fun main() {
    println(findLargest(listOf(3, 7, 1, 9, 4)))  // 9
    println(findLargest(emptyList()))              // null
}
```

**Interview Tip:** Use `maxOrNull()` — it returns null for empty lists instead of throwing an exception.

---

### Task 5: Filter Active Users

**Problem:** From a list of users, return only the active ones.

```kotlin
data class User(val name: String, val isActive: Boolean)

fun getActiveUsers(users: List<User>): List<User> {
    return users.filter { it.isActive }
}

fun main() {
    val users = listOf(
        User("Alice", true),
        User("Bob", false),
        User("Charlie", true)
    )
    println(getActiveUsers(users))  // [Alice, Charlie]
}
```

**Interview Tip:** This tests your knowledge of `filter` on data classes.

---

### Task 6: Create a Data Class for User

**Problem:** Model a user for an API response.

```kotlin
data class User(
    val id: Int,
    val name: String,
    val email: String,
    val isActive: Boolean = true
)

fun main() {
    val user = User(1, "Rahul", "rahul@example.com")
    println(user)

    val updated = user.copy(email = "new@example.com")
    println(updated)
}
```

**Interview Tip:** Show that you know about `copy()` and default parameter values.

---

### Task 7: Sealed Class for API Response

**Problem:** Model network response states.

```kotlin
sealed class Result<out T> {
    data class Success<T>(val data: T) : Result<T>()
    data class Error(val message: String, val code: Int = 0) : Result<Nothing>()
    object Loading : Result<Nothing>()
}

fun handleResult(result: Result<User>) {
    when (result) {
        is Result.Success -> println("User: ${result.data.name}")
        is Result.Error -> println("Error ${result.code}: ${result.message}")
        is Result.Loading -> println("Loading...")
    }
}
```

**Interview Tip:** Using generics with sealed classes (`out T`) is a common real-world pattern.

---

### Task 8: Create an Extension Function

**Problem:** Add a utility method to String to check if it's a valid email.

```kotlin
fun String.isValidEmail(): Boolean {
    return this.contains("@") && this.contains(".") && this.length > 5
}

fun main() {
    println("rahul@example.com".isValidEmail())  // true
    println("notanemail".isValidEmail())          // false
}
```

**Interview Tip:** Extension functions are great for adding utilities to classes you don't own.

---

### Task 9: Use Coroutine to Simulate API Call

**Problem:** Simulate fetching user data from a remote API.

```kotlin
import kotlinx.coroutines.*

data class User(val id: Int, val name: String)

suspend fun fetchUser(id: Int): User {
    delay(500)  // Simulate network delay
    return User(id, "User $id")
}

fun main() = runBlocking {
    println("Fetching user...")
    val user = fetchUser(1)
    println("Got: ${user.name}")  // Got: User 1
}
```

**Interview Tip:** Know why `runBlocking` is used (it bridges blocking and coroutine world) and when NOT to use it (not in Android UI code).

---

### Task 10: Use `map` and `filter` on a Product List

**Problem:** From a list of products, get names of in-stock items costing under ₹2000.

```kotlin
data class Product(val name: String, val price: Double, val inStock: Boolean)

fun getAffordableInStock(products: List<Product>): List<String> {
    return products
        .filter { it.inStock && it.price < 2000 }
        .map { it.name }
}

fun main() {
    val products = listOf(
        Product("Laptop", 50000.0, true),
        Product("Mouse", 800.0, true),
        Product("Keyboard", 1500.0, false),
        Product("USB Hub", 600.0, true)
    )
    println(getAffordableInStock(products))  // [Mouse, USB Hub]
}
```

**Interview Tip:** Chain `filter` then `map` — filter first so you process fewer items.

---

## 33. Kotlin Roadmap

```
BEGINNER KOTLIN
├── Setup (IntelliJ / Android Studio)
├── Variables (val, var)
├── Data Types
├── Operators
├── Conditions (if, when)
├── Loops (for, while)
└── Functions (basics)

OOP KOTLIN
├── Classes and Objects
├── Constructors (primary, secondary)
├── Inheritance (open, override)
├── Abstract Class and Interface
├── Encapsulation, Polymorphism
└── Object Keyword (singleton, companion)

KOTLIN FEATURES
├── Data Class
├── Sealed Class
├── Enum Class
├── Extension Functions
└── Null Safety (?, ?:, !!)

FUNCTIONAL KOTLIN
├── Lambda Expressions
├── Higher-Order Functions
├── Scope Functions (let, run, with, apply, also)
└── Collection Functions (map, filter, reduce)

COLLECTIONS
├── List, MutableList
├── Set, MutableSet
├── Map, MutableMap
└── Collection operations

COROUTINES
├── suspend functions
├── launch, async, await
├── runBlocking
└── Coroutine Dispatchers

FLOW
├── Cold Flow
├── StateFlow
├── SharedFlow
└── Flow operators

ANDROID KOTLIN
├── Activity / Fragment
├── ViewModel + StateFlow
├── Repository pattern
├── Retrofit + suspend
├── Room database
└── Jetpack Compose

BACKEND KOTLIN
├── Spring Boot + Kotlin
├── Controller / Service / Repository
├── Data Transfer Objects (DTOs)
└── Coroutines with Spring

INTERVIEW PREP
├── Common interview questions
├── Coding problems
├── Common mistakes to avoid
└── Best practices
```

---

## 34. Final Revision Notes

### Important Concepts to Revise
1. `val` vs `var` — reference immutability vs full immutability
2. Nullable types (`String?`) and operators (`?.`, `?:`, `!!`)
3. Data class — what it auto-generates
4. Sealed class — exhaustive `when` expressions
5. Companion object vs object declaration
6. Extension functions — how and why
7. Coroutines — `launch` vs `async`, `suspend` keyword
8. Dispatchers — Main, IO, Default
9. Scope functions — which returns what, `it` vs `this`
10. Flow vs LiveData

### Most Asked Kotlin Interview Topics
| Topic | Frequency |
|---|---|
| `val` vs `var` | ⭐⭐⭐⭐⭐ |
| Null safety | ⭐⭐⭐⭐⭐ |
| Data class | ⭐⭐⭐⭐⭐ |
| Coroutines | ⭐⭐⭐⭐⭐ |
| Sealed class | ⭐⭐⭐⭐ |
| Extension functions | ⭐⭐⭐⭐ |
| Scope functions | ⭐⭐⭐⭐ |
| `launch` vs `async` | ⭐⭐⭐⭐ |
| Flow | ⭐⭐⭐ |
| Companion object | ⭐⭐⭐ |

### Best Practice Checklist
- [ ] Use `val` by default, `var` only when necessary
- [ ] Prefer `?.` and `?:` over `!!`
- [ ] Use `data class` for model/POJO classes
- [ ] Use `sealed class` for states (API response, UI state)
- [ ] Keep coroutines scoped (`viewModelScope`, `lifecycleScope`)
- [ ] Use `Dispatchers.IO` for network and database work
- [ ] Expose immutable collections from functions and ViewModels
- [ ] Use named arguments for readability when calling with many params
- [ ] Prefer extension functions over utility classes
- [ ] Use `when` with sealed classes for exhaustive handling

### Final Advice from a Senior Engineer

> "Kotlin is not just 'Java with less code.' It's a language designed to help you write **safer, more expressive, and more maintainable** code. Take time to really understand null safety — it'll save you from entire categories of bugs. Learn coroutines properly — callbacks and threads are the past. And read other people's idiomatic Kotlin code (Android Jetpack source is great for this)."
>
> "In interviews, don't just memorize definitions. Be ready to explain **why** a feature exists and **when** you'd use it over alternatives. That's what separates a junior who knows Kotlin from a developer who thinks in Kotlin."
>
> "Practice writing code every day. The more you write, the more natural `?.let { }` and `when (sealed) { }` will feel. Good luck! 🚀"

