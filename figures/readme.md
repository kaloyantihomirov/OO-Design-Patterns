# ✨ Figures Project ✨

This project is all about representing, manipulating, and extending 2D geometric figures in a flexible and maintainable way. It’s designed with SOLID principles, test-driven development, and a variety of design patterns in mind. The focus is on making figures easily creatable, cloneable, representable as strings, and storable in different formats.

## Features
- **Multiple Figure Types:** Triangle, Circle, Rectangle (easily extendable to more!).
- **Polymorphic Hierarchy:** Abstract base classes/interfaces for figures.
- **Immutability:** Once created, figure properties never change.
- **String Conversions:** Create figures from strings & convert them back to strings effortlessly.
- **Factory Patterns:** Use Abstract Factory and Factory Method patterns to create figures from:
  - Random generators 🎲
  - Standard input (STDIN) 💻
  - Files 📂
- **Cloning with Prototype:** Duplicate existing figures without worrying about their underlying types.
- **Reflection-Based Registration (Optional):** Seamlessly add new figure types without touching the factories.

## Technologies & Concepts
- **OOP & SOLID Principles**
- **Design Patterns:** Abstract Factory, Factory Method, Prototype
- **TDD & Unit Testing:** Ensuring quality and correctness
- **Smart Pointers (C++):** For safe and easy memory management
- **Streams & I/O:** Flexible input/output handling

## License
This project is available under the **CC BY-NC-SA 4.0** license.

Enjoy exploring and extending this figures world! 🦄✨
