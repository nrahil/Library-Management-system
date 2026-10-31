# Library Management System — Design Document

## 1. Where this project came from

The original `main.cpp` (see git history / README) was a single procedural
file: global parallel arrays for students and books, fixed caps
(`MAX_STUDENTS=20`, `MAX_BOOKS=15`), `char[]`/`strcpy` strings, one `main()`
mixing login, menus, and business rules. No classes, no structs.

It went through three deliberate evolutions:

1. **SOLID refactor** — split into classes with single responsibilities, wired
   through interfaces instead of globals (Repository, Strategy, Facade).
2. **Pattern showcase extension** — Singleton, Factory, Observer, and State
   pattern added on top, plus new item types (DVD, Magazine) and new features
   (Return Item, View Issued Items).
3. **Modular Service Architecture** — Decomposed the monolithic service into
   dedicated, decoupled domain services (`StudentService`, `CatalogService`,
   `CirculationService`, `Authenticator`), backed by explicit abstract interfaces
   (`IStudentService`, `ICatalogService`, `ICirculationService`, `IAuthService`),
   and organized the project into clear directory modules (`models/`, `repository/`,
   `services/`, `policy/`, `events/`, `ui/`, `common/`).

## 2. Layered & Modular Architecture

```
                                    main.cpp
                                       │
                      ┌────────────────┴───────────────┐
                      │                                │
                  ConsoleUI                     LibraryService (Facade)
                      │                                │
     ┌────────────────┼────────────────┐               │
     │                │                │               │
     ▼                ▼                ▼               ▼
IStudentService  ICatalogService  ICirculationService  IAuthService
(StudentService) (CatalogService) (CirculationService) (Authenticator)
     │                │                │
     │                │         (Coordinates
     │                │          Patrons & Items)
     ▼                ▼                ▼
IRepository<Student>  IItemRepository  IFeePolicy
(Student storage)    (Item storage)   (Pricing rules)
                            │
                       LibraryItem (abstract)
                       ├─ Book
                       ├─ DVD
                       └─ Magazine
                            │
                        ItemState (Available / Issued)

NotificationCenter (Global event bus, Singleton)
      │
IObserver ← ConsoleAuditObserver (prints [NOTICE] lines)
```

## 3. Modular Directory Structure

```
src/
├── common/             # Cross-cutting structures and utilities
│   ├── OperationResult.h
│   └── FormatUtils.h
├── models/             # Domain entities and polymorphic items
│   ├── LibraryItem.h / .cpp
│   ├── Book.h / .cpp
│   ├── DVD.h / .cpp
│   ├── Magazine.h / .cpp
│   ├── Student.h / .cpp
│   ├── ItemState.h / .cpp
│   └── ItemFactory.h / .cpp
├── repository/         # Data access interfaces and in-memory implementations
│   ├── IRepository.h
│   ├── InMemoryRepository.h
│   ├── IItemRepository.h
│   └── InMemoryItemRepository.h
├── policy/             # Business strategies (fees and deposit policies)
│   ├── FeePolicy.h / .cpp
├── events/             # Observer pattern event bus and subscribers
│   ├── LibraryEvent.h
│   ├── IObserver.h
│   ├── NotificationCenter.h / .cpp
│   └── ConsoleAuditObserver.h / .cpp
├── services/           # Decoupled domain services and Facade
│   ├── IStudentService.h
│   ├── StudentService.h / .cpp
│   ├── ICatalogService.h
│   ├── CatalogService.h / .cpp
│   ├── ICirculationService.h
│   ├── CirculationService.h / .cpp
│   ├── IAuthService.h
│   ├── Authenticator.h / .cpp
│   └── LibraryService.h / .cpp   (Facade coordinating the services)
└── ui/                 # Terminal formatting and user interaction
    ├── Console.h / .cpp
    └── ConsoleUI.h / .cpp
```

## 4. Class & Service Responsibilities (SRP)

| Module / Service | File | Single Responsibility |
|---|---|---|
| `StudentService` | `src/services/StudentService.*` | Student registration, lookups, balance deposits, low-balance checks |
| `CatalogService` | `src/services/CatalogService.*` | Item catalog creation, editing, inventory discovery and availability |
| `CirculationService` | `src/services/CirculationService.*` | Lending workflow: item issuing, returning, loan tracking, fee deduction |
| `Authenticator` (`AuthService`) | `src/services/Authenticator.*` | User password verification |
| `LibraryService` (Facade) | `src/services/LibraryService.*` | Unified facade orchestrating the specialized domain services |
| `Student` | `src/models/Student.*` | Student entity (roll, name, balance, financial mutations) |
| `LibraryItem` (+ `Book`/`DVD`/`Magazine`) | `src/models/LibraryItem.*`, etc. | Item identity, polymorphic description, and state delegation |
| `ItemState` (+ `AvailableState`/`IssuedState`) | `src/models/ItemState.*` | State pattern: item availability lifecycle transitions |
| `ItemFactory` | `src/models/ItemFactory.*` | Factory pattern: polymorphic item instantiation |
| `IRepository<T>` / `InMemoryRepository<T>` | `src/repository/IRepository.h`, etc. | Generic repository abstraction for value entities |
| `IItemRepository` / `InMemoryItemRepository` | `src/repository/IItemRepository.h`, etc. | Specialized repository owning polymorphic `LibraryItem` objects |
| `IFeePolicy` / `StandardFeePolicy` | `src/policy/FeePolicy.*` | Strategy pattern: business pricing rules |
| `NotificationCenter` | `src/events/NotificationCenter.*` | Singleton pub/sub event bus |
| `ConsoleAuditObserver` | `src/events/ConsoleAuditObserver.*` | Observer subscriber: audit event logger |
| `Console` | `src/ui/Console.*` | ANSI terminal styling helpers |
| `ConsoleUI` | `src/ui/ConsoleUI.*` | Console menu navigation and presentation layer |

## 5. SOLID Principles in the Modular Architecture

- **SRP (Single Responsibility Principle)**: Every service has a focused, single reason to change. `StudentService` does not know about catalog items; `CatalogService` does not manage student wallets; `CirculationService` coordinates between them through clean contracts.
- **OCP (Open/Closed Principle)**: New item types can be added without modifying existing services. New services or notification observers can be added without modifying existing publishers.
- **LSP (Liskov Substitution Principle)**: Any `IStudentService`, `ICatalogService`, or `ICirculationService` implementation can substitute seamlessly. `Book`, `DVD`, and `Magazine` substitute wherever `LibraryItem*` is required.
- **ISP (Interface Segregation Principle)**: Interfaces (`IStudentService`, `ICatalogService`, `ICirculationService`, `IAuthService`) are cohesive and tailored specifically to what clients require.
- **DIP (Dependency Inversion Principle)**: High-level modules and UI depend on service abstractions (`IStudentService`, `ICatalogService`, `ICirculationService`), which in turn depend on repository and policy interfaces (`IRepository`, `IItemRepository`, `IFeePolicy`).

## 6. Build & Run

To compile using `mingw32-make` or `make`:
```bash
mingw32-make
```
Or directly with `g++`:
```bash
g++ -std=c++17 -Wall -Isrc main.cpp \
    src/models/Book.cpp src/models/DVD.cpp src/models/Magazine.cpp \
    src/models/LibraryItem.cpp src/models/ItemState.cpp src/models/ItemFactory.cpp \
    src/models/Student.cpp src/policy/FeePolicy.cpp \
    src/events/NotificationCenter.cpp src/events/ConsoleAuditObserver.cpp \
    src/services/Authenticator.cpp src/services/StudentService.cpp \
    src/services/CatalogService.cpp src/services/CirculationService.cpp \
    src/services/LibraryService.cpp src/ui/Console.cpp src/ui/ConsoleUI.cpp \
    -o library.exe
```

Run the application:
```bash
./library.exe
```
Default password for Admin and Student: `password`.
