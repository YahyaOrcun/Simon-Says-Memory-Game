# Simon Says Memory Game

This project is an Arduino Uno based **Simon Says memory game**.  
The aim of the game is to test the player's memory by showing a color sequence and asking the player to repeat the same sequence correctly using colored buttons.

The game has three main difficulty modes:

- Easy
- Medium
- Hard

Each difficulty mode includes **3 levels**. As the player progresses through the levels, the game becomes more challenging.

---

## Final Product

The final version of the game was assembled inside a custom 3D-printed enclosure.

![Final Product](./images/final-product.jpg)

---

## Project Overview

The game uses four colored buttons:

- Red
- Blue
- Yellow
- Green

The system generates a color sequence. The player must repeat this sequence by pressing the correct colored buttons in the correct order.

If the player enters the sequence correctly, the game continues to the next level.  
If the player makes a mistake, the game resets or ends depending on the game logic.

This project combines:

- Arduino programming
- Circuit design
- Button-based user interaction
- Memory-based game logic
- 3D-printed product assembly

---

## Game Modes and Levels

| Difficulty Mode | Levels |
|---|---|
| Easy | Level 1, Level 2, Level 3 |
| Medium | Level 1, Level 2, Level 3 |
| Hard | Level 1, Level 2, Level 3 |

Each mode has its own level structure. The game becomes more difficult as the player moves from **Easy** to **Medium** and **Hard**.

---

## Hardware Components

The project was built using the following components:

- Arduino Uno
- 4 push buttons
- Red, blue, yellow, and green button layout
- Jumper wires
- Breadboard or circuit board
- Custom 3D-printed enclosure
- Power connection for Arduino Uno

---

## Circuit Schematic

The circuit schematic of the project is shown below.

![Circuit Schematic](./images/circuit-schematic.png)

---

## Arduino Code

The Arduino source code is included in the `src` folder.

Main code file:

```text
src/simon_says_game.ino
```

The Arduino code handles:

- Button input reading
- Color sequence generation
- Difficulty mode control
- Level progression
- User input checking
- Correct and incorrect answer logic
- Game reset operation

---

## 3D Printed Enclosure

The game has a custom 3D-printed enclosure.  
The enclosure consists of three main parts:

- Base
- Bottom Cover
- Top Cover

The enclosure design was created by **Ayşe Sude Cengiz**.  
The case was 3D printed by **Yahya Orçun Bilsel**, and the electronic circuit was placed inside the enclosure.

---

## Enclosure Parts

### Base

![Base](./images/base.jpg)

### Bottom Cover

![Bottom Cover](./images/bottom-cover.jpg)

### Top Cover

![Top Cover](./images/top-cover.jpg)

The 3D model files are located in the `3d-models` folder.

```text
3d-models/
├── base.stl
├── bottom-cover.stl
└── top-cover.stl
```

---

## Repository Structure

```text
Simon-Says-Memory-Game/
│
├── README.md
│
├── src/
│   └── simon_says_game.ino
│
├── images/
│   ├── final-product.jpg
│   ├── circuit-schematic.png
│   ├── base.jpg
│   ├── bottom-cover.jpg
│   └── top-cover.jpg
│
└── 3d-models/
    ├── base.stl
    ├── bottom-cover.stl
    └── top-cover.stl
```

---

## How the Game Works

1. The game starts with one of the difficulty modes: **Easy**, **Medium**, or **Hard**.
2. The system generates and shows a color sequence.
3. The player watches the sequence carefully.
4. The player repeats the sequence using the red, blue, yellow, and green buttons.
5. If the sequence is entered correctly, the player continues to the next level.
6. If the player makes a mistake, the game resets or ends depending on the game logic.

---

## Skills Practiced

This project helped improve practical and technical skills in:

- Arduino Uno programming
- Digital input reading with push buttons
- Memory-based game algorithm design
- Difficulty mode and level structure implementation
- Circuit design and hardware assembly
- Hardware and software debugging
- 3D printing and enclosure integration
- Turning an electronic prototype into a physical product

---

## Credits

- **Enclosure Design:** Ayşe Sude Cengiz  
- **3D Printing:** Yahya Orçun Bilsel  
- **Circuit Assembly:** Yahya Orçun Bilsel  
- **Arduino Programming and Game Implementation:** Yahya Orçun Bilsel  

---

## License

This project is shared for educational and portfolio purposes.  
You are free to review and use this project as a reference for learning, but please give proper credit if you use any part of the design, code, or documentation.
